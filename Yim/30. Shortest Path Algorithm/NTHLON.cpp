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
// ������ ����
int V;
// �׷����� ���� ����Ʈ, (����� ���� ��ȣ, ���� ����ġ)���� ��´�.
vector<pair<int, int>> adj[410];
const int start = 401;
// (A�� ������ ���� �ð�-B�� ������ ���� �ð�)�� ���� ��ȣ�� ��ȯ�Ѵ�.
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
			// �� ª�� ��θ� �߰��ϸ� dist[]�� �����ϰ� �켱���� ť�� �ִ´�.
			if (dist[there] > next_dist) {
				dist[there] = next_dist;
				pq.push(make_pair(-next_dist, there));
			}
		}

	}
	return dist;
}
//a[] = A�� ������ ���� ���� �ð�
//b[] = B�� ������ ���� ���� �ð�
int solve(const vector<int>& a, const vector<int>& b) {
	// �׷����� �����.
	V = 402;
	for (int i = 0; i < V; ++i)
		adj[i].clear();
	for (int i = 0; i < a.size(); ++i) {
		int diff = a[i] - b[i];
		adj[start].push_back(make_pair(vertex(diff), a[i]));
	}

	// ���� ����
	for (int diff = -200; diff <= 200; ++diff) {
		// i�� ������ �ڿ� ���δٸ�?
		for (int i = 0; i < a.size(); ++i) {
			int next = diff + a[i] - b[i];
			// �ð� ������ ���� ���� 200�� �Ѵ� ������ ���� �ʿ䰡 ����
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