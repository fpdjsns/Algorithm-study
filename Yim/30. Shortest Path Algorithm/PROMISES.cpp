/*
 *  Date : 2020.07.12
 *  Language : C++
 *  Complexity : O(V^3 + N*V^2)
 *  Data Structure :
 *  Algorithm : Floyd
 *
 *  Problem : https://www.algospot.com/judge/problem/read/PROMISES
 */
#include <stdio.h>
#include <algorithm>
#include <iostream>

#define INF 1e9
using namespace std;
int V, N, M;
long long adj[201][201];

bool update(int a, int b, int c) {
	if (adj[a][b] <= c) return false;
	for (int x = 0; x < V; ++x) {
		for (int y = 0; y < V; ++y) {
			adj[x][y] = min(adj[x][y],
				min(adj[x][a] + c + adj[b][y],
					adj[x][b] + c + adj[a][y]));
		}
	}
	return true;
}
int main() {
	int tc;
	int a, b, c;
	int ret;
	scanf("%d", &tc);

	while (tc--) {
		ret = 0;
		scanf("%d %d %d", &V, &M, &N);
		for (int i = 0; i < V; ++i)
			for (int j = 0; j < V; ++j) {
				if (i == j)
					adj[i][i] = 0;
				else
					adj[i][j] = INF;
			}

		for (int i = 0; i < M; ++i) {
			scanf("%d %d %d", &a, &b, &c);
			if (adj[a][b] == INF
				|| (adj[a][b] !=INF && adj[a][b] > c))
					adj[a][b] = adj[b][a] = c;
		}

		for (int k = 0; k < V; ++k) {
			for (int i = 0; i < V; ++i) {
				for (int j = 0; j < V; ++j) {
						adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
				}
			}
		}
		for (int i = 0; i < N; ++i) {
			scanf("%d %d %d", &a, &b, &c);
			if (!update(a, b, c)) {
				ret++;
			}
		}

		printf("%d\n", ret);
	}
	return 0;
}