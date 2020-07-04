/**
 * problem : https://algospot.com/judge/problem/read/DRUNKEN
 * algorithm : Floyd
 * time complexity : O(V^3 + VlogV)
 */
 
#include <iostream>
#include <vector>
#include <string>
#include<algorithm>

#define INF 1e9

using namespace std;

int main() {

	int V, E;
	cin >> V >> E;
	vector<int> cost(V);
	vector<pair<int, int>> sortedCost(V);
	for (int i = 0; i < V; i++) {
		cin >> cost[i];
		sortedCost[i] = { cost[i], i };
	}
	vector<vector<int>> adj(V, vector<int>(V, INF));
	int u, v, w;
	for (int i = 0; i < E; i++) {
		cin >> u >> v >> w;
		u--; v--;
		adj[u][v] = adj[v][u] = w;
	}
	for (int i = 0; i < V; i++) {
		adj[i][i] = 0; 
	}

	sort(sortedCost.begin(), sortedCost.end());
	vector<vector<int>> answer, dist;
	answer = dist = adj;

	for (int k = 0; k < V; k++) {
		int x = sortedCost[k].second;
		for (int u = 0; u < V; u++) {
			for (int v = 0; v < V; v++) {
				dist[u][v] = min(dist[u][v], dist[u][x] + dist[x][v]);
				answer[u][v] = min(answer[u][v], dist[u][x] + cost[x] + dist[x][v]);
			}
		}
	}

	int C;
	cin >> C;
	while (C--) {
		cin >> u >> v;
		cout << answer[--u][--v] << endl;
	}

	return 0;
}
