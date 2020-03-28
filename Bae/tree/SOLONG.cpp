/**
 * 시간초과 뜹니다.
 * 왜죠..?
 * 로직 똑같은거 같은데..
 */

#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <iostream>
#include <string.h>

using namespace std;

class Node {
	vector<Node*> children;
public:
	char val; // 문자
	bool isEnd; // 문자열의 종료 노드인가
	int wordPriorityIndex; // 우선시되는 단어의 인덱스 
	Node(char val) {
		this->val = val;
		this->isEnd = false;
		this->children = vector<Node*>(26, NULL);
		this->wordPriorityIndex = -1;
	}

	void add(const char* s, int wordIndex) {
		// update wordIndex
		if (this->wordPriorityIndex == -1)
			this->wordPriorityIndex = wordIndex;

		// end of string
		if (*s == 0) { 
			this->isEnd = true;
			return;
		}

		// update children
		Node* child = children[*s-'A'];
		if (child == NULL) { // if not exist child
			child = new Node(*s); // create
			children[*s - 'A'] = child;
		}
		child->add(s + 1, wordIndex);
	}

	Node* find(const char* s) {
		if (*s == 0) return this;
		Node* child = children[*s - 'A'];
		if (child == NULL) return NULL;
		return child->find(s + 1);
	}

	int getTypingCnt(const char* s, int wordIndex) {
		if (*s == 0) return 0;
		if (this->wordPriorityIndex == wordIndex) {
			return 1; // tab
		}
		return children[*s - 'A']->getTypingCnt(s + 1, wordIndex) + 1;
	}
};

class Trie {
public:
	Node* root = new Node(' ');

	Trie(vector<pair<int, string>> arr) {
		// 출현빈도, 단어 사전 순 정렬
		sort(arr.begin(), arr.end(), [arr](const pair<int, string>& a, const pair<int, string>& b) {
			if (a.first == b.first)
				return a.second < b.second;
			return a.first > b.first;
		});

		// make trie
		for (int i = 0; i < arr.size(); i++) {
			root->add(arr[i].second.c_str(), i);
		}
		// root is not typing
		root->wordPriorityIndex = -1;
	}

	int solve(vector<char*> wordArr) {
		int ans = wordArr.size() - 1; 
		for (int i = 0; i < wordArr.size(); i++) {
			char* word = wordArr[i];
			Node* findNode = root->find(word);
			if (findNode == NULL || !findNode->isEnd) {
				ans += strlen(word);
				continue;
			}
			ans += root->getTypingCnt(word, findNode->wordPriorityIndex);
		}
		return ans;
	}
};


int main() {
	int C;
	scanf("%d", &C);
	while(C--) {
		int N, M;
		scanf("%d", &N);
		scanf("%d", &M);
		vector<pair<int, string>> arr(N);
		for (int i = 0; i < N; i++) {
			char tmpWord[11];
			scanf("%s", tmpWord);
			arr[i].second = tmpWord;
			scanf("%d", &arr[i].first);
		}

		Trie* trie = new Trie(arr);
		int ans = M - 1; // space
		for (int i = 0; i < M; i++) {
			char word[11];
			scanf("%s", word);
			Node* findNode = trie->root->find(word);
			if (findNode == NULL || !findNode->isEnd) {
				ans += strlen(word);
				continue;
			}
			ans += trie->root->getTypingCnt(word, findNode->wordPriorityIndex);
		}
		printf("%d\n", ans);
	}

	return 0;
}
