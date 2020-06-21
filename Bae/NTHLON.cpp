/**
 * problem : https://algospot.com/judge/problem/read/NTHLON
 * time complexity : O(ElogV)
 * algorithm : dijkstra
 */
 
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#define IMPOSSIBLE 1e9
#define VERTEX 200
#define START 0
using namespace std;

vector<vector<pair<int, int>>> setGraph(vector<pair<int, int>> arr) {
	int M = arr.size();
	vector<vector<pair<int, int>>> adj(2 * VERTEX); // (diff, cost(time))
	for (int i = 0; i < M; i++) {
		int a = arr[i].first;
		int b = arr[i].second;
		int gap = a - b;
		adj[START].push_back({ VERTEX + gap, a });

		// 2번 이상 사용 가능 간선 연결
		for (int j = 1; j < 2 * VERTEX; j++) {
			int v = gap + j;
			if (v < 1 || v >= VERTEX * 2) continue; // 범위 벗어남
			adj[j].push_back({ v, a });
		}
	}
	return adj;
}

int solve(vector<pair<int, int>> arr) {
	vector<vector<pair<int, int>>> adj = setGraph(arr);
	vector<int> dist(VERTEX * 2, IMPOSSIBLE);

	priority_queue<pair<int, int>> q;
	dist[START] = 0; // start
	q.push({ 0, START });

	while (!q.empty()) {
		int now = q.top().second;
		int cost = -q.top().first;
		q.pop();
		if (cost > dist[now]) continue;

		for (int i = 0; i < adj[now].size(); i++) {
			int next = adj[now][i].first;
			int nextCost = adj[now][i].second + cost;
			if (nextCost < dist[next]) {
				dist[next] = nextCost;
				q.push({ -nextCost, next });
			}
		}
	}

	return dist[VERTEX];
}


int main() {
	int T;
	cin >> T;
	while (T--) {
		int M; cin >> M;
		vector<pair<int, int>> arr(M);
		for (int i = 0; i < M; i++) {
			cin >> arr[i].first >> arr[i].second;
		}
		int ans = solve(arr);
		if (ans == IMPOSSIBLE)
			cout << "IMPOSSIBLE" << endl;
		else
			cout << ans << endl;
	}
}
