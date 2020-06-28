#include <iostream>
#include <vector>
#include <string>
#include<algorithm>

using namespace std;

#define MAX_V 101
#define INF 987654321

int V,  W , E;
bool reachable[MAX_V][MAX_V];

int bellman2(int src, int target, vector<pair<int, int>> adj[]) {
	vector<int> upper(V, INF);
	upper[src] = 0;

	for (int iter = 0; iter < V - 1; ++iter) {
		for (int here = 0; here < V ; ++here) {
			for (int i = 0;  i < adj[here].size(); ++i) {
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
				upper[there] = min(upper[there], upper[here]+cost);
			}
		}
	}

	//음수 확인
	for (int here = 0; here < V; ++here) {
		for (int i = 0;  i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			int cost = adj[here][i].second;

			if (upper[here]+cost < upper[there]) {
				if (reachable[src][here] && reachable[here][target])
					return -INF;
			}
		}
	}
	return upper[target];
}



void solve() {
	cin >> V >> W;
	vector<pair<int, int>> adj[MAX_V];
	vector<pair<int, int>> adj_neg[MAX_V];


	for (int i = 0; i <= V; i++) {
		for (int j = 0; j <= V; j++) {
			reachable[i][j] = false;
			if (i == j) reachable[i][j] = true;
		}
	}

	for (int i = 0; i < W; i++) {
		int s, e, cost;
		cin >> s >> e >> cost;
		adj[s].push_back({ e, cost });
		adj_neg[s].push_back({ e, -cost });
		reachable[s][e] = true;
	}


	for (int k = 0; k < V; k++) {
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				reachable[i][j] = reachable[i][j] || (reachable[i][k] && reachable[k][j]);
			}
		}
	}

	if (!reachable[0][1]) {
		cout << "UNREACHABLE" << endl;
		return;
	}

	int min_ret =  bellman2(0, 1, adj);
	int max_ret = -bellman2(0, 1, adj_neg);

	if (min_ret == -INF) {
		cout << "INFINITY ";
	}
	else {
		cout << min_ret << " ";
	}


	if (max_ret == INF) {
		cout << "INFINITY " << endl;
	}
	else {
		cout << max_ret << endl;
	}
}


int main() {
	int testCase;
	scanf("%d", &testCase);

	for (int i = 0; i < testCase; i++) {
		solve();
	}
	return 0;
}


