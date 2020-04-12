
//
//  algo_wordchain.cpp
//  알고리즘 문제해결전략 -	 단어 제한 끝말잇기
//
//  Created by Hubring on 2020. 4. 12. 
//  Copyright © 2020년 Hubring. All rights reserved.
//  시간복잡도 O(NA) 단어수 N, 알파벳수 A

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;


//adj[i][j]= i와 j사이의 간선의 수
vector<vector<int>> adj; 
//graph[i][j]= i로 시작해서 j로 끝나는 단어의 목록
vector<string> graph[26][26]; 

vector<int> indegree; //indegree[i]=i로 시작하는 단어의 수
vector<int> outdegree; //outdegree[i]=i로 끝나는 단어의 수

void makeGraph(const vector<string>& words) {
	
	//전역변수 초기화
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			graph[i][j].clear();
		}
	}

	adj = vector<vector<int>>(26, vector<int>(26, 0));
	indegree = outdegree = vector<int>(26, 0);

	//각 단어를 그래프에 추가
	for (int i = 0; i < words.size(); i++) {
		int front = words[i][0] - 'a';
		int end = words[i][words[i].size() - 1] - 'a';
		graph[front][end].push_back(words[i]);

		adj[front][end]++;
		outdegree[front]++;
		indegree[end]++;
	}
}

//유향그래프의 인접 행렬adj가 주어질 때 오일러 서킷 혹은 트레일을 계산한다.
void getEulerCircuit(int here, vector<int>&circuit) {

	for (int there = 0; there < adj.size(); there++) {
		while (adj[here][there] > 0) {
			adj[here][there]--; //간선을 지운다.
			getEulerCircuit(there, circuit);
		}
	}
	circuit.push_back(here);
}

//현재 그래프의 오일러 트레일이나 서킷을 반환한다.
vector<int> getEulerTrailOrCircuit() {
	vector<int> circuit;

	//우선 트레일을 찾아본다 : 시작점이 존재하는 경우
	for (int i = 0; i < 26; i++) {
		if (outdegree[i] == indegree[i] + 1) {
			getEulerCircuit(i, circuit);
			return circuit;
		}
	}

	//아니면 서킷이니, 간선에 인접한 아무 정점에서나 시작한다.
	for (int i = 0; i < 26; i++) {
		if (outdegree[i]) {
			getEulerCircuit(i, circuit);
			return circuit;
		}
	}

	//모두 실패한 경우 빈 배열을 반환한다.
	return circuit;
}

//현재 그래프의 오일러 서킷/트레일 존재 여부를 확인한다.
bool checkEuler() {

	//예비 시작점과 끝점의 수
	int plus1 = 0, minus1 = 0;

	for (int i = 0; i < 26; i++) {
		int delta = outdegree[i] - indegree[i];

		//모든 정점의 차수는 -1,1,0이어야 한다.
		if (delta < -1 || 1 < delta) return false;
		else if (delta == 1) plus1++;
		else if (delta == -1) minus1++;

	}

	//시작점과 끝점은 각 하나씩 있거나 하나도 없어야 한다.
	return (plus1 == 1 && minus1 == 1) || (plus1 == 0 && minus1 == 0);
}

void solve() {

	int num;
	cin >> num;

	vector <string> words(num);
	for (int i = 0; i < num; i++) {
		cin >> words[i];
	}

	makeGraph(words);

	//차수가 맞지 않으면 실패
	if (!checkEuler()) {
		cout << "IMPOSSIBLE" << endl;
		return; 
	}

	//오일러 서킷이나 경로를 찾아낸다
	vector<int> circuit = getEulerTrailOrCircuit();

	//모든 간선을 방문하지 못했으면 실패!
	if (circuit.size() != words.size() + 1) {
		cout << "IMPOSSIBLE" << endl;
		return;
	}

	//아닌 경우 방문 순서를 뒤집은 뒤 간선들을 모아 문자열로 만들어 반환한다.
	reverse(circuit.begin(), circuit.end());

	string ret;
	for (int i = 1; i < circuit.size(); i++) {
		int a = circuit[i - 1], b = circuit[i];
		if (ret.size()) ret += " ";
		ret += graph[a][b].back();
		graph[a][b].pop_back();
	}

	cout << ret << endl;

}



int main() {

	int testCase;
	scanf("%d", &testCase);

	for (int i = 0; i < testCase; i++) {
		solve();
	}
}