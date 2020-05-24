
//
//  algo_childrenday.cpp
//  알고리즘 문제해결전략 
//
//  Created by Hubring on 2020. 05. 24..
//  Copyright © 2020년 Hubring. All rights reserved.
//


#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string>
using namespace std;

int append(int here , int edge, int mod) {
	int there = here * 10 + edge;
	if (there >= mod) return mod + there % mod;
	return there % mod;
}


string gifts(string digits, int n, int m) {
	//간선의 번호를 오름차순으로 정렬
	//사전순으로 가장 앞 경로를 찾기 위함
	sort(digits.begin(), digits.end());


	//흰색정점(시작점) i는 0~n-1, 회색정점 i는 n~2n-1로 표현
	//parent[i] = BFS 스패닝 트리에서 정점 i의 부모
	//choice[i] = parent[i] 에서 i로 연결된 간선의 번호
	vector<int> parent(2 * n, -1), choice(2 * n, -1);
	queue<int> q;

	//흰색 0번을 큐에 추가
	parent[0] = 0;
	q.push(0);
	while (!q.empty()) {
		int here = q.front();
		q.pop();

		for (int i = 0; i < digits.size(); i++) {
			//간선 digits[i]-'0'을 따라가 본다.
			int there = append(here, digits[i] - '0', n);
			if (parent[there] == -1) {
				parent[there] = here;
				choice[there] = digits[i] - '0';
				q.push(there);
			}
		}
	}


	//회색 m 번에 도달하지 못하면 실패
	if (parent[n + m] == -1)  return "IMPOSSIBLE";
	
	//부모로 가는 연결을 따라가면서 C를 계산
	string ret;
	int here = n + m;
	while (parent[here] != here) {
		ret += char('0' + choice[here]);
		here = parent[here];
	}

	reverse(ret.begin(), ret.end());
	return ret;
}



int solve() {
	string c;
	int n, m;
	cin >> c >> n >> m;

	cout << gifts(c, n, m) << endl;
}


int main() {
	int testCase;
	scanf("%d", &testCase);

	for (int i = 0; i < testCase; i++) {
		solve();
	}
}