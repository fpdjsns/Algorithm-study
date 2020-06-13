/**
 * problem : https://algospot.com/judge/problem/read/ROUTING
 * algorithm : dijkstra
 * time complexity : O(ElogE)
 */

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <map>
#include <set>

using namespace std;

double solve(int N, vector<vector<pair<int, double>>>& adj) {
	vector<bool> check(N, false);
	vector<double> dist(N, -1);
	priority_queue<pair<double, int>> q;

	q.push({ -1, 0 });
	dist[0] = 1;
	
	int now, next;
	double nowWeight, weight;
	while (!q.empty()) {
		now = q.top().second;
		nowWeight = -q.top().first;
		q.pop();
		if (check[now]) continue;
		check[now] = true;

		for(vector<pair<int, double>>::iterator it = adj[now].begin(); it!=adj[now].end(); it++) {
			next = (*it).first;
			weight = (*it).second;

			if (check[next]) continue;
			if (dist[next] == -1 || dist[next] > nowWeight * weight) {
				dist[next] = nowWeight * weight;
				q.push({ -dist[next], next });
			}
		}
	}
	return dist[N-1];
}

int main() {

	int T; cin >> T;
	while (T--) {
		int N, M;
		cin >> N >> M;
		vector<vector<pair<int, double>>> adj(N);
		for (int i = 0; i < M; i++) {
			int u, v;
			double w;
			cin >> u >> v >> w;
			adj[u].push_back({ v, w });
			adj[v].push_back({ u, w });
		}
		printf("%.10lf\n", solve(N, adj));
	}
	return 0;
}
