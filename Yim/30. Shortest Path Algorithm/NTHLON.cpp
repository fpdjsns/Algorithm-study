/*
 *  Date : 2020.06.20
 *  Language : C++
 *  Complexity : O(|E|lg|V|)
 *  Data Structure :
 *  Algorithm : dijkstra
 *
 *  Problem : https://www.algospot.com/judge/problem/read/NTHLON
 */

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#define INF 1000000
using namespace std;
// 정점의 개수
int V;
// 그래프의 인접 리스트, (연결된 정점 번호, 간선 가중치)쌍을 담는다.
vector<pair<int, int>> adj[410];
const int start = 401;
// (A국 선수의 예상 시간-B국 선수의 예상 시간)의 정점 번호를 반환한다.
int vertex(int diff) {
	return diff + 200;
}

vector<int> dijkstra(int src) {
	vector<int> dist(V, INF);
	dist[src] = 0;
	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, src));
	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		if (dist[here] < cost) continue;
		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			int next_dist = cost + adj[here][i].second;
			// 더 짧은 경로를 발견하면 dist[]를 갱신하고 우선순위 큐에 넣는다.
			if (dist[there] > next_dist) {
				dist[there] = next_dist;
				pq.push(make_pair(-next_dist, there));
			}
		}

	}
	return dist;
}
//a[] = A국 선수의 종목별 예상 시간
//b[] = B국 선수의 종목별 예상 시간
int solve(const vector<int>& a, const vector<int>& b) {
	// 그래프를 만든다.
	V = 402;
	for (int i = 0; i < V; ++i)
		adj[i].clear();
	for (int i = 0; i < a.size(); ++i) {
		int diff = a[i] - b[i];
		adj[start].push_back(make_pair(vertex(diff), a[i]));
	}

	// 현재 차이
	for (int diff = -200; diff <= 200; ++diff) {
		// i번 종목을 뒤에 붙인다면?
		for (int i = 0; i < a.size(); ++i) {
			int next = diff + a[i] - b[i];
			// 시간 차이의 절대 값이 200을 넘는 정점은 만들 필요가 없음
			if (abs(next) > 200) continue;
			adj[vertex(diff)].push_back(make_pair(vertex(next), a[i]));
		}
	}
	vector<int> shortest = dijkstra(start);
	int ret = shortest[vertex(0)];
	if (ret == INF) return -1;
	return ret;
}


int main() {
	int T;
	int m;
	int ret;
	int data_a, data_b;
	scanf("%d", &T);
	while (T--) {
		vector<int> a, b;
		scanf("%d", &m);
		for (int i = 0; i < m; ++i) {
			scanf("%d %d", &data_a, &data_b);
			a.push_back(data_a);
			b.push_back(data_b);
		}
		ret = solve(a, b);
		if (ret == -1)
			printf("IMPOSSIBLE\n");
		else
			printf("%d\n", ret);
	}
	return 0;
}