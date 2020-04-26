/**
 * problem : https://www.algospot.com/judge/problem/read/MEETINGROOM
 * algorithm : 2-SAT
 * time complexity : O(N^2)
 * 2-SAT 참고 : https://hellogaon.tistory.com/23, https://blog.naver.com/PostView.nhn?blogId=kks227&logNo=220803009418
 */
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <set>
#include <stack>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

int N;
vector<vector<int>> adj;

// 회의실 사용 시간이 겹치지 않는가.
bool disjoint(const pair<int, int>& p, const pair<int, int>& q)
{
	return p.second <= q.first || q.second <= p.first;
}

void makeGraph(const vector<pair<int, int>>& meetings)
{
	int vars = meetings.size();
	
	adj.clear();
	adj.resize(vars * 2);

	for(int i=0; i < vars; i += 2)
	{
		// i, i+1 회의 중 하나는 한다. = 주간과 월간 회의 중 하나는 한다.
		int j = i + 1;
		adj[i * 2 + 1].push_back(j * 2); // 주간 회의를 하지 않으면 월간 회의를 한다.
		adj[j * 2 + 1].push_back(i * 2); // 월간 회의를 하지 않으면 주간 회의를 한다.
	}

	for(int i=0; i < vars; i++)
		for(int j=0; j < i; j++)
		{
			// i, j 회의실 사용 시간이 겹치는 경우
			if(!disjoint(meetings[i], meetings[j]))
			{
				adj[i * 2].push_back(j * 2 + 1); // i가 회의를 하는 경우 j는 회의를 하지 못한다.
				adj[j * 2].push_back(i * 2 + 1); // j가 회의를 하는 경우 i는 회의를 하지 못한다.
			}
		}
}


vector<int> sccId, discovered, finished;
int sccCounter, vertexCounter;
stack<int> st;

vector<vector<int>> ans;

int scc(int here)
{
	int ret = discovered[here] = vertexCounter++;
	st.push(here);

	for(size_t i=0; i < adj[here].size(); i++)
	{
		int there = adj[here][i];

		if(discovered[there] == -1)
			ret = min(ret, scc(there));
		else if(discovered[there] < discovered[here] && finished[there] != 1)
			ret = min(ret, discovered[there]);
	}

	if(ret == discovered[here])
	{
		ans.push_back(vector<int>());
		while(true)
		{
			int t = st.top();
			st.pop();
			sccId[t] = sccCounter;
			ans[sccCounter].push_back(t);
			finished[t] = 1;
			if(t == here)
				break;
		}
		sccCounter++;
	}

	return ret;
}

vector<int> tarjanSCC()
{
	sccId = discovered = finished = vector<int>(adj.size(), -1);
	sccCounter = vertexCounter = 0;

	for(int i=0; i < adj.size(); i++)
		if(discovered[i] == -1)
			scc(i);
	return sccId;
}



vector<int> solve2SAT()
{
	int n = adj.size() / 2; // 회의실 번호는 n개
	vector<int> label = tarjanSCC(); // 컴포넌트 분리

	// 주간, 월간 2개 있으므로 회의실 번호 x n개 탐색.
	for(int i=0; i < 2 * n; i+=2)
		// i번 회의실을 사용한다(label[i])와 사용하지 않는다(label[i+1])의 boolean 값이 같은 경우는 나올 수 없다.
		if(label[i] == label[i+1]) // 이 두 경우가 같은 사이클에 있다면 
			return vector<int>(); // 불가능


	// tarjan 알고리즘은 역순으로 label이 매겨지므로 label 값으로 역순 정렬 시킨다.
	// 컴포넌트들의 위상정렬. 들어오는 간선이 없는 컴포넌트부터 탐색해야 함.
	vector<pair<int, int>> order;
	for(int i=0; i < 2 * n; i++)
		order.push_back({-label[i], i});
	sort(order.begin(), order.end());

	// 정답 배열 세팅
	vector<int> value(n, -1);
	for(int i=0; i < 2 * n; i++)
	{
		int vertex = order[i].second; // 정점 번호
		int num = vertex / 2; // 회의실을 사용하고, 안하고 2가지 경우를 저장했으므로 실제 회의실 번호는 /2한 값이다.
		bool use = vertex % 2 == 0; // 회의실 사용하는 경우인지.
		if(value[num] != -1) // 이미 회의실 사용여부 세팅했다면 pass
			continue;

		// num을 사용하는 경우가 먼저 나온 경우 사용하지 않음이 참.
		// num을 사용하지 않은 경우가 먼저 나온 경우 사용함이 참.
		// 가장 처음 정점은 거짓 정점으로 분류하기 때문이다.
		value[num] = !use;
	}
	return value;
}

int main()
{
	int T;
	scanf("%d", &T);

	while(T--)
	{
		scanf("%d", &N);

		vector<pair<int, int>> a(N * 2);
		for(int i=0; i < N; i++)
			scanf("%d%d%d%d", &a[2 * i].first, &a[2 * i].second, &a[2 * i + 1].first, &a[2 * i + 1].second);

		makeGraph(a);

		vector<int> ans = solve2SAT();
		if(ans.empty())
			puts("IMPOSSIBLE");
		else
		{
			puts("POSSIBLE");
			for(size_t i=0; i < ans.size(); i+=2)
			{
				if(ans[i])
					printf("%d %d\n", a[i].first, a[i].second);
				else
					printf("%d %d\n", a[i + 1].first, a[i + 1].second);
			}
		}
	}

	return 0;
}
