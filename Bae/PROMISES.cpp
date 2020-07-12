/**
 * problem : https://algospot.com/judge/problem/read/PROMISES
 * algorithm : Floyd
 * time complexity : O(V^3 + M*V^2)
 */
 
#include <iostream>
#include <vector>
#include <string>
#include<algorithm>

#define INF 1e9

using namespace std;

bool checkValid(int V, vector<vector<int>>& dist, pair<pair<int, int>, int> plan) {
	int u = plan.first.first;
	int v = plan.first.second;
	int w = plan.second;
	if (dist[u][v] != INF &&
		dist[u][v] <= w) return false;

	// update dist
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			dist[i][j] = min(dist[i][j], min(dist[i][u] + w + dist[v][j], dist[i][v] + w + dist[u][j]));
		}
	}

	return true;
}

int solve(int V, vector<pair<pair<int,int>,int>> roads, vector<pair<pair<int, int>, int>> plans) {
	vector<vector<int>> dist(V, vector<int>(V, INF));
	
	// connect
	for (auto now : roads) {
		int u = now.first.first; 
		int v = now.first.second;
		int w = now.second;
		dist[u][v] = dist[v][u] = min(dist[u][v], w);
	}
	for (int i = 0; i < V; i++)
		dist[i][i] = 0;
	for (int k = 0; k < V; k++) 
		for (int i = 0; i < V; i++) 
			for (int j = 0; j < V; j++) 
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

	// check ans
	int ans = 0;
	for (auto now : plans) {
		ans += !checkValid(V, dist, now);
	}
	return ans;
}

int main() {
	int C;
	cin >> C;
	int V, M, N;
	while (C--) {
		cin >> V >> M >> N;
		vector<pair<pair<int, int>, int>> roads(M), plans(N);
		for (int i = 0; i < M; i++) 
			cin >> roads[i].first.first >> roads[i].first.second >> roads[i].second;
		for (int i = 0; i < N; i++) 			
			cin >> plans[i].first.first >> plans[i].first.second >> plans[i].second;

		cout << solve(V, roads, plans) << endl;
	}
	return 0;
}
