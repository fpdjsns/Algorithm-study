//
//  algo_promises.cpp
//  알고리즘 문제해결전략 -	 선거공약
//
//  Created by Hubring on 2020. 7. 12. 
//  Copyright © 2020년 Hubring. All rights reserved.
//  시간복잡도 O(V^3+V^2*N)

#include <iostream>
#include<stdio.h>
#include <vector>
#include <string>
#include<algorithm>

using namespace std;

#define INF 1e9
int V, M, N;


struct Node {
	int u, v, w;
};



bool update(vector<vector<int>> &adj, int a, int b, int c) {
	if (adj[a][b] <= c) 
		return false;
	
	for (int x = 0; x < V; ++x) {
		for (int y = 0; y < V; ++y) {
			adj[x][y] = min(adj[x][y],
				min(adj[x][a] + c + adj[b][y],
					adj[x][b] + c + adj[a][y]));
		}
	}
	
	return true;
}

void solve(){
	cin >> V >> M >> N;

	vector<vector<int>>  adj(V);
	
	for (int i = 0; i < V; ++i){
		adj[i] = vector<int>(V, INF);
		adj[i][i] = 0;
	}

	int u, v, w;
	for (int i = 0; i < M; ++i) {
		cin >> u >> v >> w;
		if (adj[u][v] > w) {
			adj[u][v] = adj[v][u] = w;
		}
	}

	for (int k = 0; k < V; ++k) {
		for (int i = 0; i < V; ++i) {
			for (int j = 0; j < V; ++j) {
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
			}
		}
	}

	int res = 0;
	for (int i = 0; i < N; ++i) {
		cin >> u >> v >> w;
		if (!update(adj, u, v, w)) {
			res++;
		}
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

