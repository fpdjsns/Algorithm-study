/*
 *  Date : 2020.06.28
 *  Language : C++
 *  Complexity : O(VE)
 *  Data Structure :
 *  Algorithm : Belloman_Ford
 *
 *  Problem : https://www.algospot.com/judge/problem/read/TIMETRIP
 */
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iostream>
#define MAX_V 101
#define INF 1e9
using namespace std;
int V;
bool updated;
int bellonman_ford2(int src, int target, vector < vector<pair<int, int>>> adj) {
	vector<int> upper(V, INF);
	upper[src] = 0;
	updated = false;
	
	for (int j = 0; j < V; ++j) {
		for (int here = 0; here < V; ++here) {
			if (upper[here] == INF) continue;
			for (int i = 0; i < adj[here].size(); i++) {
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
				if (upper[there] > upper[here] + cost) {
					upper[there] = upper[here] + cost;
				}
			}
		}
	}
	// 음수 사이클 존재 여부
	for (int here = 0; here < V; ++here) {
		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].first;
			int cost = adj[here][i].second;
			if (upper[here] + cost < upper[there]) {
				updated = true;
				break;
			}
		}
	}
	return upper[target];
}

int main() {
	int TC, W;
	int a, b, c;
	scanf("%d", &TC);
	while (TC--) {
		scanf("%d %d", &V, &W);
		vector < vector<pair<int, int>>> min_adj(V);// [MAX_V];
		vector < vector<pair<int, int>>> max_adj(V);// [MAX_V];
		for (int i = 0; i < W; ++i) {
			scanf("%d %d %d", &a, &b, &c);
			min_adj[a].push_back({ b, c });
			max_adj[a].push_back({ b, -c });
		}
		int ret[2];
		ret[0] = bellonman_ford2(0, 1, min_adj);
		if (ret[0] == INF) printf("UNREACHABLE\n");
		else {
			if (updated)
				printf("INFINITY ");
			else
				printf("%d ", ret[0]);
			ret[1] = bellonman_ford2(0, 1, max_adj);
			if (ret[1] == INF || updated)
				printf("INFINITY\n");
			else
				printf("%d\n", ret[1] * (-1));
		}
	}

	return 0;
}