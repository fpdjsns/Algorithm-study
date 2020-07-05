//
//  algo_drunken.cpp
//  알고리즘 문제해결전략 - 음주운전단속 문제
//
//  Created by Hubring on 2020. 7. 05.
//  Copyright © 2020년 Hubring. All rights reserved.
//  O(V^3)
#include <iostream>
#include<stdio.h>
#include <vector>
#include <string>
#include<algorithm>

using namespace std;

#define INF 987654321


int V, E;
int adj[500][500];
int delay[500];
int W[500][500];

void solve() {

	cin >> V >> E;
	for (int i = 0; i < V; i++) {
		cin >> delay[i];
	}

	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			adj[i][j] = INF;
		}
	}

	int u, v, w;
	for (int i = 0; i < E; i++) {
		cin >> u >> v >> w;
		u--, v--;
		adj[u][v] = adj[v][u] = w;
	}

	//모든 정점들을 예상 시간 별로 정렬한다.
	vector<pair<int, int>> order;
	for (int i = 0; i < V; i++) {
		order.push_back({delay[i], i});
	}
	sort(order.begin(), order.end());

	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (i == j) {
				W[i][j] = 0;
				adj[i][j] = 0;
			}
			else {
				W[i][j] = adj[i][j];
			}
		}
	}

	for (int k = 0; k < V; k++) {
		int w = order[k].second;
		for (int i = 0; i < V; i++) {
			for (int j = 0; j< V; j++) {
				adj[i][j] = min(adj[i][j], adj[i][w] + adj[w][j]);
				W[i][j] = min(W[i][j], adj[i][w] + delay[w] + adj[w][j]);
			}
		}
	}
}


int main() {
	solve();

	int testCase;
	scanf("%d", &testCase);

	int u, v;
	for (int i = 0; i < testCase; i++) {
		cin >> u >> v;
			cout << W[--u][--v] << endl;
	}
	return 0;
}


