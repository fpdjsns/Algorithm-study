
//
//  algo_dictionary.cpp
//  알고리즘 문제해결전략 -	 고대어 사전
//
//  Created by Hubring on 2020. 4. 12. 
//  Copyright © 2020년 Hubring. All rights reserved.
//  시간복잡도 O(NL) 단어수 N, 단어의 길이 L

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;



//알파벳의 각 글자에 대한 인접 행렬
//간선(i, j)는 알파벳 i가 j보다 앞에 와야 함을 나타냄
vector<vector<int>> alphabet;


void makeGraph(const vector<string> &words)
{
	alphabet = vector<vector<int>>(26, vector<int>(26, 0));

	for (int j = 1;  j<words.size(); j++)
	{
		int i = j - 1;
		int len = min(words[i].size(), words[j].size());

		//word[i]가 word[j] 앞에 오는 이유를 찾는다
		for (int k = 0; k < len; k++) {
			if (words[i][k] != words[j][k]){
				int a = words[i][k] - 'a';
				int b = words[j][k] - 'a';
				alphabet[a][b] = 1;

				break;
			}
		}
	}

}


vector<int> seen, order;
void dfs(int here)
{
	seen[here] = 1;
	for (int there = 0; there < alphabet.size(); there++) {
		if (alphabet[here][there] && !seen[there]) {
			dfs(there);
		}		
	}
	order.push_back(here);
}



//alphabet에 주어진 그래프를 위상정렬한 결과를 반환한다
//그래프가 DAG(Directed Adjacent Graph)가 아니라면 빈 벡터를 반환한다
vector<int> topologicalSort(void)
{
	int N = alphabet.size();
	seen = vector<int>(N, 0);
	order.clear();

	for (int i = 0; i < N; i++) {
		if (!seen[i]) dfs(i);
	}

	reverse(order.begin(), order.end());

	//만약 그래프가 DAG가 아니라면 정렬 결과에 역방향 간선이 있다.
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			if (alphabet[order[j]][order[i]]) {
				return vector<int>();
			}
		}
	}

	//사이클이 없는 경우라면 DFS에서 얻은 순서를 반환한다.
	return order;
}


void solve() {

	int N;
	cin >> N;

	vector<string> words(N);

	for (int i = 0; i < N; i++) {
		cin >> words[i];
	}

	makeGraph(words);

	vector<int> result = topologicalSort();

	if (result.empty()) {
		cout << "INVALID HYPOTHESIS";
	}
	else {
		for (int i = 0; i < result.size(); i++) {
			cout << char(result[i] + 'a');
		}
	}

	cout << "\n";
}



int main() {

	int testCase;
	scanf("%d", &testCase);

	for (int i = 0; i < testCase; i++) {
		solve();
	}
}

