//
//  algo_nthlon.cpp
//  알고리즘 문제해결전략 - 조세푸스 문제
//
//  Created by Hubring on 2020. 6. 21.
//  Copyright © 2020년 Hubring. All rights reserved.
//

#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string>
#include<climits>

using namespace std;

#define INF 987654321


// 정점의 개수
int V;

// 그래프의 인접 리스트
vector<pair<int, int>> adj[410];

const int START = 401;

// (A국 선수의 예상 시간-B국 선수의 예상 시간)의 정점 번호를 반환
int vertex( int delta ) {
	return delta + 200;
}

vector<int> dijkstra(int src) {
	vector<int> dist(V, INF);
	dist[src] = 0;
	
	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, src));

	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		if (dist[here] < cost)
			continue;
		
		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			int next = cost + adj[here][i].second;

			if (dist[there] > next) {
				dist[there] = next;
				pq.push(make_pair(-next, there));
			}
		}

	}
	return dist;
}
//a[] = A국 선수의 종목별 예상 시간
//b[] = B국 선수의 종목별 예상 시간
int solve(const vector<int>& a, const vector<int>& b) {

	// 그래프를 만든다.
	V = 402;
	for (int i = 0; i < V; ++i) {
		adj[i].clear();
	}

	for (int i = 0; i < a.size(); ++i) {
		int delta = a[i] - b[i];
		adj[START].push_back(make_pair(vertex(delta), a[i]));
	}

	// 현재 차이
	for (int delta = -200; delta <= 200; ++delta) {
		// i번 종목을 뒤에 붙인다면?
		for (int i = 0; i < a.size(); ++i) {
			int next = delta + a[i] - b[i];
			// 시간 차이의 절대 값이 200을 넘는 정점은 만들 필요가 없음
			if (abs(next) > 200) continue;
			adj[vertex(delta)].push_back(make_pair(vertex(next), a[i]));
		}
	}
	vector<int> shortest = dijkstra(START);
	int ret = shortest[vertex(0)];
	if (ret == INF) return -1;
	return ret;
}


void preprocess() {
	int m;
	cin >> m;

	vector<int> a, b;
	int  tmp1, tmp2;
	for (int i = 0; i < m; ++i) {
		cin >> tmp1 >> tmp2;
		a.push_back(tmp1);
		b.push_back(tmp2);
	}

	int res = solve(a, b);
	if (res == -1)	cout<< "IMPOSSIBLE" << endl;
	else cout << res << endl;
}

int main() {
	int testCase;
	scanf("%d", &testCase);

	for (int i = 0; i < testCase; i++) {
		preprocess();
	}
	return 0;
}


