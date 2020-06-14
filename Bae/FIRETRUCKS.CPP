/**
 * PROBLEM : https://algospot.com/judge/problem/read/FIRETRUCKS
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int solve(int V, vector<vector<pair<int, int>>>& adj, vector<int>& fires, vector<int>& stations) {
	priority_queue<pair<int, int>> q;
	vector<int> dist = vector<int>(V + 1, 1e9);
	for (int i = 0; i < stations.size(); i++) {
		int station = stations[i];
		dist[station] = 0;
		q.push({ 0, station });
	}

	while (!q.empty()) {
		int distance = -q.top().first;
		int here = q.top().second;
		q.pop();

		if (dist[here]<distance) continue;

		for (int i = 0; i<adj[here].size(); i++) {
			int next = adj[here][i].first;
			int cost = adj[here][i].second + dist[here];

			if (cost<dist[next]) {
				dist[next] = cost;
				q.push({ -cost, next });
			}
		}
	}

	int ans = 0;
	for (int i = 0; i<fires.size(); i++) {
		ans += dist[fires[i]];
	}
	return ans;
}

int main() {

	int T;
	cin >> T;

	while (T--) {
		int V, E, n, m;
		cin >> V >> E >> n >> m;
		vector<vector<pair<int, int>>> adj = vector<vector<pair<int, int> > >(V + 1);

		int a, b, c;
		for (int i = 0; i<E; i++) {
			cin >> a >> b >> c;
			adj[a].push_back(make_pair(b, c));
			adj[b].push_back(make_pair(a, c));
		}

		vector<int> fires(n), stations(m);
		for (int i = 0; i<n; i++) {
			cin >> fires[i];
		}
		for (int i = 0; i < m; i++) {
			cin >> stations[i];
		}
		
		cout << solve(V, adj, fires, stations) << endl;
	}
	return 0;
}
