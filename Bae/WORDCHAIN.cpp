/**
 * problem : https://www.algospot.com/judge/problem/read/WORDCHAIN
 * algorithm : DFS
 * time complexity : O(N)
 */ 

#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <iostream>
#define ALPHA 26

using namespace std;

vector<vector<int>> adj;
vector<string> graph[ALPHA][ALPHA];

//indegree[i]=i로 시작하는 단어의 수
//outdegree[i]=i로 끝나는 단어의 수
vector<int> indegree, outdegree;

//유향 그래프의 인접행렬 adj가 주어질 때 오일러 서킷 혹은 트레일을 계산한다.
void getEulerCircuit(int here, vector<int>& circuit) {
	for (int there = 0; there < adj[here].size(); there++) {
		while (adj[here][there] > 0) {
			adj[here][there]--;//간선을 지운다
			getEulerCircuit(there, circuit);
		}
	}
	circuit.push_back(here);

}
//현재 그래프의 오일러 트레일이나 서킷을 반환한다.
vector<int> getEulerTrailOrCircuit() {
	vector<int> circuit;
	//우선 트레일을 찾아본다:시작점이 존재하는 경우
	for (int i = 0; i<ALPHA; i++)
		if (outdegree[i] == indegree[i] + 1) {
			getEulerCircuit(i, circuit);
			return circuit;
		}
	//아니면 서킷이니,간선에 인접한 아무 정점에서나 시작한다.
	for (int i = 0; i<ALPHA; i++)
		if (outdegree[i]) {
			getEulerCircuit(i, circuit);
			return circuit;
		}
	//모두 실패한 경우 빈 배열을 반환한다.
	return circuit;
}

// 오일러 서킷 확인
// 시작점, 끝점은 하나씩만 있어야 한다.
// 이 외에는 들어오는 간선과 나가는 간선의 수가 같아야 함.
bool checkEuler() {
	int startV = 0, endV = 0;
	for (int i = 0; i < ALPHA; i++) {
		int delta = outdegree[i] - indegree[i];
		//모든 정점의 차수는 -1,1 또는 0이어야 한다.
		if (delta < -1 || 1 < delta) return false;
		if (delta == 1) startV++;
		if (delta == -1) endV++;
	}
	//시작점과 끝점은 각 하나씩 있거나 하나도 없어야 한다.
	return(startV == 1 && endV == 1) || (startV == 0 && endV == 0);
}

void makeGraph(const vector<string>& words) {
	
	// init
	for (int i = 0; i < ALPHA; i++)
		for (int j = 0; j < ALPHA; j++)
			graph[i][j].clear();
	adj = vector<vector<int> >(ALPHA, vector<int>(ALPHA, 0));
	indegree = vector<int>(ALPHA, 0);
	outdegree = vector<int>(ALPHA, 0);
	
	for (int i = 0; i < words.size(); i++) {
		string word = words[i];
		int s = word[0] - 'a';
		int e = word[word.size() - 1] - 'a';
		graph[s][e].push_back(word);
		adj[s][e]++;
		outdegree[s]++;
		indegree[e]++;
	}
}
string solve(const vector<string>& words) {
	makeGraph(words);

	if (!checkEuler()) return "IMPOSSIBLE";
	//오일러 서킷이나 경로를 찾아낸다.
	vector<int> circuit = getEulerTrailOrCircuit();
	//모든 간선을 방문하지 못하면 실패
	if (circuit.size() != words.size() + 1) return "IMPOSSIBLE";

	//아닌 경우 방문순서를 뒤집은 뒤 간선들을 모아 문자열로 만들어 반환한다.
	reverse(circuit.begin(), circuit.end());
	string ans;
	for (int i = 1; i < circuit.size(); i++) {
		int a = circuit[i - 1], b = circuit[i];
		if (ans.size()) ans += " ";
		ans += graph[a][b].back();
		graph[a][b].pop_back();
	}
	return ans;
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		int n;
		cin >> n;
		vector<string> arr(n);
		for (int i = 0; i < n; i++) cin >> arr[i];
		cout << solve(arr) << endl;
	}
	return 0;
}
