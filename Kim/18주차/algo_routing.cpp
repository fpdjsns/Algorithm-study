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

double INF = DBL_MAX;
int V, E;


//인접리스트
vector<pair<double, int>> adj[20001];

vector<double> dijkstra(int src) {
	vector<double> dist(V, INF);
	dist[src] = 1;

	priority_queue<pair<double, int>> pq;
	pq.push(make_pair(-1, src));

	while (!pq.empty()) {
		double cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		if (dist[here]< cost) continue;

		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].second;
			double nextDist = cost * adj[here][i].first;

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
	cin >> V >> E;
	
	int a, b;
	double c;

	for (int i = 0; i < E; i++) {
		cin >> a >> b >> c;
		adj[a].push_back(make_pair(c, b));
		adj[b].push_back(make_pair(c, a));
	}

	for (int i = 0; i < V; i++) {
		sort(adj[i].begin(), adj[i].end());
	}

	vector<double>dist = dijkstra(0);
	cout << fixed;
	cout.precision(10);
	cout << dist[V - 1] << endl;
	init();
}

int main() {
	int testCase;
	scanf("%d", &testCase);

	for (int i = 0; i < testCase; i++) {
		solve();
	}
}