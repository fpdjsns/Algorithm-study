//
//  algo_gallery.cpp
//  알고리즘 문제해결전략 - 감시 카메라 설치
//
//  Created by Hubring on 2020. 4. 19. 
//  Copyright © 2020년 Hubring. All rights reserved.
//  시간복잡도 : O(G + H)

#include <iostream>
#include <queue>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;




int G, H;
vector<vector<int>> adj;
vector<bool> visit;

const int WATCHED = 0;
const int UNWATCHED = 1;
const int INSTALLED = 2;

int installed;

int dfs(int here)
{
	visit[here] = true;
	bool children[3] = {};

  //연결된 경로를 찾아 카메라 설치 여부 확인
	for(size_t i=0; i < adj[here].size(); i++)
	{
		int there = adj[here][i];
		if(!visit[there])
			children[dfs(there)] = true;
	}
  
  // 카메라 감시가 없다면, 감시 카메라 
	if(children[UNWATCHED])
	{
		installed++;
		return INSTALLED;
	}

 // 이미 카메라를 설치한 경우
	if(children[INSTALLED]){
		return WATCHED;
  }

 // 최종 노드인 경우
	return UNWATCHED;
}

void solve(){
    scanf("%d%d", &G, &H);

		adj = vector<vector<int>>(G + 1);
		visit = vector<bool>(G+1, false);

		for(int i=0; i < H; i++)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			adj[u].push_back(v);
			adj[v].push_back(u);
		}

		installed = 0;
		for(int i=0; i < G; i++){
			if(!visit[i] && dfs(i) == UNWATCHED){
				  installed++;
      }
    }

		printf("%d\n", installed);

}



int main() {

	int testCase;
	scanf("%d", &testCase);

	for (int i = 0; i < testCase; i++) {
		solve();
	}
  
  return 0;
}
