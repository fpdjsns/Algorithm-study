//
//  algo_routing.cpp
//  알고리즘 문제해결전략 - 신호 라우팅
//
//  Created by Hubring on 2020. 6. 14..
//  Copyright © 2020년 Hubring. All rights reserved.


#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string>
#include<climits>
#include <float.h>
using namespace std;

int INF = 987654321;
int V, E, N, M;


//인접리스트
vector<pair<int, int>> adj[1011];

vector<int> dijkstra(vector<int> src) {
	vector<int> dist(V+1, INF);
	priority_queue<pair<int, int>> pq;

	for (int i = 0; i < src.size(); i++) {
		dist[src[i]] = 0;
		pq.push(make_pair(0, src[i]));
	}
	

	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		if (dist[here] < cost) continue;

		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].second;
			int nextDist = cost + adj[here][i].first;

			if (dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}

	}
	return dist;
}

void init() {
	for (int i = 0; i < V; i++) {
		adj[i].clear();
	}
}


void solve() {
	cin >> V >> E >> N >>M;

	int a, b, t;

	for (int i = 0; i < E; i++) {
		cin >> a >> b >> t;
		adj[a].push_back(make_pair(t, b));
		adj[b].push_back(make_pair(t, a));
	}

	vector<int>src, fire;
	int num;
	for (int i = 0; i < N; i++) {
		cin >> num;
		fire.push_back(num);
	}

	for (int i = 0; i < M; i++) {
		cin >> num;
		src.push_back(num);
	}

	vector<int>dist = dijkstra(src);
	long long sum = 0;
	for (int i = 0; i < N; i++) {
		sum += dist[fire[i]];
	}
	cout << sum << endl;
	init();
}

int main() {
	int testCase;
	scanf("%d", &testCase);

	for (int i = 0; i < testCase; i++) {
		solve();
	}
}