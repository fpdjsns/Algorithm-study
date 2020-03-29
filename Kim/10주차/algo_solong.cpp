
//
//  algo_solong.cpp
//  알고리즘 문제해결전략 - 조세푸스 문제
//
//  Created by Hubring on 2020. 3. 29.
//  Copyright © 2020년 Hubring. All rights reserved.
//  시간복잡도 : O(KNlgN+L) - K : 문자열 최대길이, N : 사전 문자수, L : 타이핑할 문자열의 전체 길이  

#include<stdio.h>
#include<string.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string>
#include<climits>
using namespace std;
	

struct TrieNode {
	TrieNode* child[26];

	//이 노드에서 종료하는 문자열의 번호, 없으면 -1
	int terminal;

	//이 노드를 루트로 하는 트라이에 가장 먼저 추가된 단어의 번호, -1로 초기화
	int first;
	TrieNode() : terminal(-1), first(-1){
		memset(child, 0, sizeof(child));
	}
	~TrieNode() {
		for (int i = 0; i < 26; i++) {
			if (child[i]) {
				delete child[i];
			}
		}
	}


	//이 노드를 루토로 하는 트라이에 번호 id인 문자열 key 추가
	void insert(const char* key , int id) {
		//first 우선 갱신
		if (first == -1) {
			first = id;
		}

		//문자열이 끝났다면 terminal만 바꾸고 종료
		if (*key == 0) {
			terminal = id;
		}
		else {
			int next = *key - 'A';
			if (child[next] == NULL) {
				child[next] = new TrieNode();
			}

			child[next]->insert(key + 1, id);
		}
	}

	//이 노드를 루트로 하는 트라이에 문자열 key와 대응되는 노드를 찾는다.
	// 없으면 NULL을 반환한다.
	TrieNode* find(const char* key) {
		if (*key == 0) {
			return this;
		}
		int next = *key - 'A';
		if (child[next] == NULL) {
			return NULL;
		}
		return child[next]->find(key+1);
	}

	//이 노드까지 타이핑해 왔을 때 번호 id인 key를
	//타이핑하기 위해 최소 몇 번의 키를 더 눌러야 하나?
	int type(const char* key, int id) {
		//문자열 종료시
		if (*key == 0) {
			return 0;
		}
		//가장 첫번째 추천 문자열과 일치
		if (first == id) {
			return 1;
		}

		int next = *key - 'A';
		return 1 + child[next]->type(key+1, id);
	}

	//사전을 나타내는 트라이가 주어질 때, 단어 word를 타이핑하는 데 
	//몇 번이나 키를 눌러야 하는지 계산한다.
	int countKeys(TrieNode* trie, const char* word) {
		//이문자열이 사전에 있는지 확인하고 있다면 번호를 구한다.
		TrieNode* node = trie->find(word);

		//사전에 없다면 직접 타이핑한다.
		if (node == NULL || node->terminal == -1) return strlen(word);

		//탐색하면 타이핑할 방법을 찾는다.
		return trie->type(word, node ->terminal ) ;
	}




};



void solve() {

	int N, M;
	cin >> N >> M;

	vector <pair<int, string>> input;
	for (int i = 0; i < N; i++) {
		char buf[11];
		int freq;
		cin >> buf >> freq;
		input.push_back(make_pair(-freq, buf));
	}

	sort(input.begin(), input.end());

	TrieNode* trie = new TrieNode();
	for (int i = 0; i < input.size(); i++) {
		trie->insert(input[i].second.c_str(), i);
	}

	trie->first = -1;


	int res = 0;
	for (int i = 0; i < M; i++) {
		char word[11];
		cin >> word;
		res+= trie->countKeys(trie, word);
	}

	cout << res + M-1 << endl;

}



int main() {
	int testCase;
	scanf("%d", &testCase);

	for (int i = 0; i < testCase; i++) {
		solve();
	}
}
