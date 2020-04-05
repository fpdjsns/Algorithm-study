
//
//  algo_nh.cpp
//  알고리즘 문제해결전략 - 보안종결자
//
//  Created by Hubring on 2020. 4. 05.
//  Copyright © 2020년 Hubring. All rights reserved.
//

#include<stdio.h>
#include <string.h>
#include<algorithm>
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int N, M;
int cache[101][1001];

const int MOD = 10007;
const int ALPHABETS = 26;

int toNumber(char ch) { return ch - 'a'; }

//트라이의 한 노드를 나타내는 객체
struct TrieNode{		
	int no;
	TrieNode* nextNode[ALPHABETS];

	//현 위치에서 끝나는 문자열의 번호
	int terminal;
	TrieNode* children[ALPHABETS];

	//이 노드에서 매칭이 실패했을 때 이곳에서 재시작
	TrieNode *fail;
	//출력 문자열의 목록 : 이 노드가 방문되었을 떄 등장하는 바늘 문자열들의 번호
	vector<int> output;

	TrieNode() : terminal(-1), fail(NULL)
	{
		memset(children, 0, sizeof(children));
	}

	~TrieNode()
	{
		for (int i = 0; i < ALPHABETS; i++) {
			if (children[i]) {
				delete children[i];
			}
		}
	}

	void insert(const char* key, int id)
	{
		if (*key == 0) {
			terminal = id;
		}
		else
		{
			int next = toNumber(*key);
			
			if (children[next] == NULL) {
				children[next] = new TrieNode();
			}

			children[next]->insert(key + 1, id);
		}
	}

	TrieNode* find(const char* key)
	{
		if (*key == 0) {
			return this;
		}

		int next = toNumber(*key);
		
		if (children[next] == NULL) {
			return NULL;
		}

		return children[next]->find(key + 1);
	}

	//trie에포함된 패턴들을 s에서 찾는다.
	//s 내에서 패턴이 출현할 때마다 (마지막 글자, 패턴 번호)의 쌍을 저장한다.
	static vector<pair<int, int>> ahoCorasick(const char* s, TrieNode* root)
	{
		vector<pair<int, int>> ret;
		TrieNode* state = root;
		
		for (size_t i = 0; s[i]; i++)
		{
			int chr = toNumber(s[i]);
			while (state != root && state->children[chr] == NULL) {
				state = state->fail;
			}

			if (state->children[chr]) {
				state = state->children[chr];
			}

			for (size_t j = 0; j < state->output.size(); j++) {
				ret.push_back(make_pair(i, state->output[j]));
			}
		}
		return ret;
	}
};



//트라이가 주어질 때 각 노드에 대해 실패 연결과 출력 문자열의 목록을 계산한다.
void computeFailFunc(TrieNode *root)
{
	// 루트에서 시작 한 단계씩 내려가며 각 노드의 실패 연결 계산
	queue<TrieNode*> q;

	//루트의 실패 연결은 자기 자신
	root->fail = root;
	q.push(root);

	while (!q.empty()) {
		TrieNode* here = q.front();
		q.pop();

		// here의 모든 자손에 대해 실패 연결을 계산하고 이들을 큐에 넣는다.
		for (int edge = 0; edge < ALPHABETS; edge++)
		{
			TrieNode* child = here->children[edge];
			if (!child)	continue;

			//1레벨 노드의 실패 연결은 항상 루트
			if (here == root) {
				child->fail = root;
			}
			else {
				//아닌 경우 부모의 실패 연결을 따라가면서 실패 연결을 찾는다.
				TrieNode* t = here->fail;
				while (t != root && t->children[edge] == NULL) {
					t = t->fail;
				}

				if (t->children[edge]) {
					t = t->children[edge];
				}

				child->fail = t;
			}

			//출력 문자열 목록: 실패 연결을 따라간 노드에서 복사해온 뒤, 
			//이 위치에서 끝나는 바늘 문자열이 있으면 추가한다.
			child->output = child->fail->output;
			if (child->terminal != -1) {
				child->output.push_back(child->terminal);
			}

			q.push(child);
		}
	}
}

//시간 복잡도 O(N*A*L)
// 상태 간의 전이 테이블을 next[]에 채운다. computeFailFunc()를 통해 
// 이미 실패 함수가 계산되어 있다고 가정한다.
void computeTransition(TrieNode* here, int& nodeCounter ) {
	//0에서 시작하는 번호를 매긴다. cach[]이 인덱스
	here->no = nodeCounter++;
	//here 뒤에 글자 chr를 붙였을 때 어느 상태로 가는가?
	for (int chr = 0; chr < ALPHABETS; chr++)
	{
		TrieNode *next = here;
		while (next != next->fail && next->children[chr] == NULL) {
			next = next->fail;
		}

		if (next->children[chr]) {
			next = next->children[chr];
		}

		here->nextNode[chr] = next;
		//재귀적으로 모든 노드에 대해 전이 테이블을 계산한다.
		if (here->children[chr]) {
			computeTransition(here->children[chr], nodeCounter);
		}

	}
}


//시간 복잡도 O(N*M*A*L)
//앞으로 length라는 글자를 더 만들어야 하는데, 야호 코라식 알고리즘의 
//현재 상태가 state에 주어질 때 IDS에 걸리지 않는 문자열의 수는?
int _count(int length, TrieNode* state) {

	//기저 사례 : 이 상태에 문자열이 출현하면 곧장 종료.
	if (state->output.size()) {
		return 0;
	}

	//기저 사례: 문자열을 전부 만든 경우.
	if (length == 0) {
		return 1;
	}

	int& ret = cache[length][state->no];
	if (ret != -1) return ret;
	ret = 0;

	//다음으로 letter글자를 넣을 경우
	for (int letter = 0; letter < ALPHABETS; letter++)
	{
		ret += _count(length-1, state->nextNode[letter]);
		ret %= MOD;
	}

	return ret;


}


void solve(){

	memset(cache, -1, sizeof(cache));
	cin >> N >> M ;

	TrieNode trie;

	char a[15];

	for (int i=0; i<M; i++)
	{
		cin >> a;
		trie.insert(a, M - i);
	}

	int number = 0;

	computeFailFunc(&trie);
	computeTransition(&trie, number);
	int res = _count(N, &trie);

	printf("%d\n", res);

}


int main() {
	int testCase;
	scanf("%d", &testCase);

	for (int i = 0; i < testCase; i++) {
		solve();
	}
}

