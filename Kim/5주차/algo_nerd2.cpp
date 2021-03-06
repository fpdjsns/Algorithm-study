
//
//  algo_nerd2.cpp
//  알고리즘 문제해결전략 - 너드인가, 너드가 아닌가? 2
//
//  Created by Hubring on 2020. 2. 20.
//  Copyright © 2020년 Hubring. All rights reserved.
//  시간복잡도 O(NlogN)

#include<iostream>
#include<algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;


void solve() {

	//신청한 사람의 수  (1 <= N <= 50000)
	int n;
	cin >> n;


	//너드인 사람 Set (문제수, 그릇 수 우선순위 정렬)
	set<pair<int, int>> nerds;
	long long res = 0;

	//N 줄에 각 2개의 정수로 각 사람의 문제 수 pi 와 라면 그릇 수 qi 가 참가 신청한 순서대로 주어집니다 (0 <= pi,qi <= 100000) . 
	for (int i = 0; i < n; i++) {
		pair<int, int> p;
		cin >> p.first >> p.second;

		//find leftmost node not less than _Keyval in mutable tree
		set<pair<int, int>>::iterator it = nerds.lower_bound(p);

		// 추가된 사람보다 문제수가 큰사람이 없는 경우 or
		// 추가된 사람의 문제수보다 바로 작은 사람의 그룻수 역시 작은 경우 추가 가능
		if (it == nerds.end() || p.second > it->second)
		{
			//해당 위치에 추가
			set<pair<int, int>>::iterator curr = nerds.insert(it, p);

			//추가된 사람보다 그릇수도 작은 사람 모두 삭제
			while (curr != nerds.begin()) {
				curr--;
				if (curr->second >= p.second) break;
				curr = nerds.erase(curr);
			}
		}
		res += nerds.size();

	}
	cout << res << endl;
}



int main() {
	int testCase;
	scanf("%d", &testCase);

	for (int i = 0; i < testCase; i++) {
		solve();
	}
}