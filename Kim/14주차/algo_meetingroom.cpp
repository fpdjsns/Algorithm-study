
//
//  algo_meetingroom.cpp
//  알고리즘 문제해결전략 - 회의실배정
//
//  Created by Hubring on 2020. 4. 26..
//  Copyright © 2020년 Hubring. All rights reserved.
//  

#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<stack>

using namespace std;

//그래프의 인접 리스트 표현
vector<vector<int>> adj;


vector<int> sccId,
discovered; //각 정점의 발견 순서
stack<int> st; //정점의 번호를 담는 스택
int sccCounter, vertexCounter;

int scc(int here) {
	int ret = discovered[here] = vertexCounter++;

	st.push(here);
	for (int i = 0; i < adj[here].size(); i++) {
		int there = adj[here][i];

		if (discovered[there] == -1) {
			ret = min(ret, scc(there));
		}
		else if (sccId[there] == -1) {
			ret = min(ret, discovered[there]);
		}
	}

	if (ret == discovered[here]) {
		while (true) {
			int t = st.top();
			st.pop();
			sccId[t] = sccCounter;
			if (t == here) {
				break;
			}
		}
		sccCounter++;
	}

	return ret;
}

vector<int> tarjanSCC() {
	//배열들을 전부 초기화
	sccId = discovered = vector<int>(adj.size(), -1);
	//카운터 초기화
	sccCounter = vertexCounter = 0;

	//모든 정정에 대해 scc호출
	for (int i = 0; i < adj.size(); i++) {
		if (discovered[i] == -1) {
			scc(i);
		}
	}

	return sccId;
}


// 회의실 사용 시간이 겹치지 않는지를 확인한다.
bool disjoint(const pair<int, int>& a, const pair<int, int>& b){
	return (a.second <= b.first || b.second <= a.first);
}

//meetings[] 각 팀이 하고 싶어하는 회의시간의 목록
//2-SAT 문제로 변환한 뒤 함의 그래프 생성한다.
//i번 팀은 meetings[i*2] 혹은 meetings[i*2+1]중 하나 시간에 회의실을 사용해야 한다.
void makeGraph(const vector<pair<int, int>>& meetings){
	int vars = meetings.size();

	adj.clear();
	adj.resize(vars * 2);

	//월간
	for (int i = 0; i < vars; i += 2){
		int j = i + 1;
		adj[i * 2 + 1].push_back(j * 2); //~i => j
		adj[j * 2 + 1].push_back(i * 2); //~j => i
	}

	//주간
	for (int i = 0; i < vars; i++) {
		for (int j = 0; j < i; j++){
			// i번 회의와 j번 회의가 서로 겹칠 경우
			if (!disjoint(meetings[i], meetings[j])){
				adj[i * 2].push_back(j * 2 + 1); // i => ~j
				adj[j * 2].push_back(i * 2 + 1);// j => ~i
			}
		}
	}
}



//abj에 함의 그래프의 인접 리스트 표현이 주어질 때, 2-SAT문의 답을 반환한다.
vector<int> solve2SAT(){
	int n = adj.size() / 2; // 변수의 수

	//강결합 요소별로 묶음
	vector<int> label = tarjanSCC(); 

	// SAT 문제를 푸는 것이 불가능한지 확인
	// 한 변수를 나타내는 두 정점이 같은 강결합 요소에 속한 경우 답이 없음
	for (int i = 0; i < 2 * n; i += 2) {
		if (label[i] == label[i + 1]) {
			return vector<int>(); 
		}
	}

	//답 생성
	vector<int> value(n, -1);

	// Tarjan 알고리즘에서 SCC번호는 위상 정렬의 역순으로 배정
	vector<pair<int, int>> order;
	for (int i = 0; i < 2 * n; i++) {
		order.push_back(make_pair( -label[i], i ));
	}
	sort(order.begin(), order.end());


	//각 정점의 값을 배정
	for (int i = 0; i < 2 * n; i++){
		int vertex = order[i].second; 
		int variable = vertex / 2; 
		bool isTrue = vertex % 2 == 0; 

		if (value[variable] != -1) {
			continue;
		}
	
		//notA가 A보다 먼저나오면 A는 참
		//A가 notA보다 먼저 나오면 A는 거짓
		value[variable] = !isTrue;
	}


	return value;
}


void solve() {
	int N;

	scanf("%d", &N);

	vector<pair<int, int>> meetings(N * 2);

	int a, b, // 주간 회의시간
		c, d; // 월간 회의시간

	//각 팀의 주,월 회의시간 입력
	for (int i = 0; i < N; i++) {
		cin >> a >> b >> c >> d;

		int idx = i * 2;
		meetings[idx].first = a;
		meetings[idx].second = b;

		meetings[idx+1].first = c;
		meetings[idx+1].second = d;
	}

	makeGraph(meetings);

	vector<int> ans = solve2SAT();

	if (ans.size() <= 0) {
		cout <<"IMPOSSIBLE"<<endl;
		return;
	}
	
	cout << "POSSIBLE" << endl;

	for (int i = 0; i < ans.size(); i += 2)
	{
		if (ans[i]) {
			cout << meetings[i].first << " " << meetings[i].second << endl;
		}
		else {
			cout << meetings[i+1].first << " " << meetings[i+1].second << endl;
		}
	}
}

int main() {
	int testCase;
	scanf("%d", &testCase);

	for (int i = 0; i < testCase; i++) {
		solve();
	}
}

