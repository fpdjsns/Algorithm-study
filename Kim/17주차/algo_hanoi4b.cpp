//
//  algo_hanoi4b.cpp
//  알고리즘 문제해결전략 - 하노이의 탑
//
//  Created by Hubring on 2020. 5. 31.
//  Copyright © 2020년 Hubring. All rights reserved.
//  시간복잡도 : O(P^(N+2)) P 기둥의 수, N 원반의 수

#include<stdio.h>
#include <string.h>
#include<iostream>
#include <string>
#include <vector>
#include <algorithm>
#include<queue>

using namespace std;

int c[1 << 12*2];

//idx번째 원판의 기둥위치를 구함
int get(int state, int idx) {
	return (state >> (idx * 2)) & 3;
}

//idx번째 원판을 value기둥 위치로 옮김
int set(int state, int idx, int value) {
	return (state & ~(3 << (idx * 2)) //idx번째 원판위치 초기화
		| (value << idx * 2)); //idx번째 원판위치 value 기둥으로 저장;
}

int sgn(int x) {
	if (!x) return 0;
	return x > 0 ? 1 : -1;
}

int incr(int x){
	if (x < 0) return x - 1;
	return x + 1;
}


int bidir(int discs, int begin, int end) {
	queue<int> q;

	if (begin == end) 
		return 0;
	
	memset(c, 0, sizeof(c));
	c[begin] = 1;
	c[end] = -1;
	q.push(begin);
	q.push(end);

	while (!q.empty()) {
		int here = q.front();
		q.pop();

		
		int top[4] = { -1, -1, -1, -1 };

		//각 기둥위치에서 맨위에 있는 원판의 번호
		for (int i = discs - 1; i >= 0; i--) {
			top[get(here, i)] = i;
		}

		//원판 옮기기
		for (int i = 0; i < 4; i++) {
			//원판이 없는 기둥은 넘김
			if (top[i] == -1) continue;
			
			//원판이 있는 기둥인경우 맨위 원판을 옮긴다.
			for (int j = 0; j < 4; j++) {
				if (i == j) continue; 

				//옮길 기둥에 원판이 없거나 맨위 원판이 더 큰경우
				if (top[j] == -1 || top[j] > top[i]) {
					int there = set(here, top[i], j);

					//방문전인 경우
					if (c[there] == 0) {
						c[there] = incr(c[here]);
						q.push(there);
					}

					//가운데서 만나는 경우
					else if (sgn(c[there]) != sgn(c[here]))
						return abs(c[there]) + abs(c[here]) - 1;
				}
			}

			
		}
	}

	return -1;
}



void solve() {
	int n;
	cin >> n;

	int begin =0, end = 0;

	int cnt, num;
	for (int i = 0; i < 4; i++) {
		cin >> cnt;
		for (int j = 0; j < cnt; j++) {
			cin >> num ; //원판
			num -= 1;
			begin = set(begin, num, i);
		}
	}

	//맨오른쪽으로 이동
	for (int j = 0; j < n; j++) {
		end = set(end, j, 3);
	}

	cout << bidir(n, begin, end) << endl;

}



int main() {
	int testCase;
	scanf("%d", &testCase);

	for (int i = 0; i < testCase; i++) {
		solve();
	}

	return 0;
}