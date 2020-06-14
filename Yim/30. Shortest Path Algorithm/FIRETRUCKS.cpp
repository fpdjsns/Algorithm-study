#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

int V, E, n, m;
vector<vector<pair<int, int>>> adj;
int fire[1002], location[1002];
const int INF = 987654321;

// 우선순위 큐를 사용하지 않은 다익스트라 알고리즘
vector<int> dijkstra(int x)
{

	vector<int> dist(V+1, INF);
	vector<bool> visited(V+1, false);
	dist[x] = 0, visited[x] = false;
	while (true) {
		int closest = INF, here;
		for (int i = 0; i < V+1; ++i)
			if (!visited[i] && dist[i] < closest) {
				closest = dist[i];
				here = i;
			}
		if (closest == INF) break;
		visited[here] = true;
		for (int i = 0; i < adj[here].size(); ++i)
		{
			int there = adj[here][i].first;
			if (visited[there]) continue;
			int nextDist = dist[here] + adj[here][i].second;
			dist[there] = min(dist[there], nextDist);
		}
	}
	return dist;
}



// 우선순위 큐를 사용한 다익스트라 알고리즘
vector<int> dijkstra2(int x)
{
	vector<int> dist(V + 1, INF);
	dist[x] = 0;
	priority_queue<pair<int, int>> pq;

	pq.push(make_pair(0, x));
	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		if (dist[here] < cost) continue;
		for (int i = 0; i < adj[here].size(); ++i)
		{
			int there = adj[here][i].first;
			int nextDist = cost +adj[here][i].second;
			if (dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	return dist;
}

int main()
{
	int C;
	cin >> C;
	while (C--) {
		cin >> V >> E >> n >> m;
		adj = vector<vector<pair<int, int>>>(E, vector<pair<int, int>>());
		for (int i = 0; i < E; ++i)
		{
			int n1, n2, n3;
			cin >> n1 >> n2 >> n3;
			adj[n1].push_back(make_pair(n2, n3));
			adj[n2].push_back(make_pair(n1, n3));
		}
		for (int i = 0; i < n; ++i)
			cin >> fire[i];
		for (int i = 0; i < m; ++i) {
			int num;
			cin >> num;
			adj[0].push_back(make_pair(num, 0));
			adj[num].push_back(make_pair(0, 0));
		}

		vector<int> dist;
		dist = dijkstra(0);
		int sum = 0;

		for (int i = 0; i < n; ++i)
		{
			sum += dist[fire[i]];
		}

		cout << sum << "\n";
	}
	return 0;
}