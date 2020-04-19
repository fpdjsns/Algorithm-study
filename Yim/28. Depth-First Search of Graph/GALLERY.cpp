/*
 *  Date : 2020.04.19
 *  Language : C++
 *  Complexity : O(G + H)
 *  Data Structure :
 *  Algorithm :
 *
 *  Problem : https://www.algospot.com/judge/problem/read/GALLERY
 */

#include <iostream>
#include <queue>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

const int WATCHED = 0;
const int UNWATCHED = 1;
const int INSTALLED = 2;

bool visit[1001] = { false, };

int C = 0, H = 0, G = 0;

int install = 0;

vector<vector<int> > adj;

int DFS(int here)
{
	visit[here] = true;

	bool child[3] = { false, false, false };

	for (int i = 0; i < adj[here].size(); ++i)
	{
		if (!visit[adj[here][i]])
		{
			child[DFS(adj[here][i])] = true;
		}
	}

	if (child[UNWATCHED])
	{
		++install;

		return INSTALLED;
	}

	if (child[INSTALLED])
	{
		return WATCHED;
	}

	return UNWATCHED;
}

int main(void)
{
	int u = 0, v = 0;

	scanf("%d", &C);

	while (C--) {
		scanf("%d %d", &G, &H); // G : 갤러리의 수, H : 복도의 수

		adj.resize(G);

		while (H--)
		{
			scanf("%d %d", &u, &v);

			adj[u].push_back(v);
			adj[v].push_back(u);
		}

		for (int i = 0; i < adj.size(); i++)
		{
			sort(adj[i].begin(), adj[i].end());
		}

		for (int i = 0; i < G; i++)
		{
			if (!visit[i] && DFS(i) == UNWATCHED)
			{
				++install;
			}
		}

		printf("%d\n", install);

		install = 0;

		memset(visit, false, sizeof(visit));

		for (int i = 0; i < G; i++)
		{
			if (!adj[i].empty()) adj[i].clear();
		}
	}

	return 0;
}