#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <iostream>

#define ALPHABETS 26
#define MOD 10007

using namespace std;

// 트라이의 한 노드를 나타내는 객체
class TrieNode {
public:
	int value;
	vector<TrieNode*> children;
	vector<TrieNode*> next;

	// 현 위치에서 끝나는 문자열의 번호
	int terminal;

	// 이 노드에서 매칭이 실패했을 때 이 곳으로 가서 계속한다.
	// 이 노드에 대응되는 문자열의 접미사이면서 트라이에 포함된 최대 문자열.
	// 깊이가 작은 것만.
	TrieNode* fail;
	// 이 노드가 방문되었을 때 등장하는 문자열들의 번호
	vector<int> output;

	TrieNode() : terminal(-1), fail(NULL) {
		children = vector<TrieNode*>(ALPHABETS);
		next = vector<TrieNode*>(ALPHABETS);
	}

	// 이 노드를 루트로 하는 트라이에 번호가 id 인 문자열 word 를 추가한다
	void insert(const char* word, int id) {
		// 문자열이 끝나면 terminal 만 참으로 바꾸고 종료
		if (*word == 0)
			terminal = id;
		else {
			int next = *word - 'a';
			// 없으면 생성
			if (children[next] == NULL)
				children[next] = new TrieNode();
			children[next]->insert(word + 1, id);
		}
	}

	TrieNode* find(const char* word) {
		if (*word == 0)
			return this;
		int next = *word - 'a';
		if (children[next] == NULL)
			return NULL;
		return children[next]->find(word + 1);
	}
};

// 코드 26.6 아호-코라식 알고리즘에서 실패 함수의 계산

// 트라이가 주어질 때 각 노드에 대해 실패 연결과 출력 문자열 목록을 계산한다.
void computeFailFunc(TrieNode* root) {
	// 루트에서부터 시작해 한 단계씩 아래로 내려가며 각 노드의 실패 연결을 계산한다.
	queue<TrieNode*> q;
	// 루트의 실패 연결은 자기 자신
	root->fail = root;
	q.push(root);

	int num = 0; // 더해짐

	while (!q.empty()) {
		TrieNode* here = q.front();
		q.pop();

		here->value = num++; // 더해짐

						  // here 의 모든 노드에 대해 실패 연결을 계산하고 이들을 큐에 넣는다
		for (int edge = 0; edge < ALPHABETS; ++edge) {
			TrieNode* child = here->children[edge];
			if (!child)
				continue;

			// 1레벨 노드의 실패 연결은 항상 루트
			if (here == root)
				child->fail = root;
			else {
				// 아닌 경우 부모의 실패 연결을 따라가면서 실패 연결을 찾는다
				TrieNode* t = here->fail;
				while (t != root && t->children[edge] == NULL)
					t = t->fail;
				if (t->children[edge])
					t = t->children[edge];
				child->fail = t;
			}
			// 출력 문자열 목록: 실패 연결에서 가져온 뒤,
			// 이 위치에서 끝나는 문자열이 있으면 추가한다
			child->output = child->fail->output;
			if (child->terminal != -1)
				child->output.push_back(child->terminal);
			q.push(child);
		}
	}
}

// 코드 26.8 보안종결자 문제를 해결하는 동적 계획법 알고리즘
vector<vector<int>> dp;

// 앞으로 length 글자를 더 만들어야 하는데, 아호-코라식 알고리즘의
// 현재 상태가 state에 주어질 때 IDS 에 걸리지 않는 문자열의 수는?
int count(int length, TrieNode* now) {
	// 실패
	if (now->output.size())
		return 0;
	// 성공
	if (length == 0)
		return 1;

	// memoization
	int& ret = dp[length][now->value];
	if (ret != -1)
		return ret;
	ret = 0;

	// 다음으로 letter 글자를 넣는 경우
	for (int letter = 0; letter < ALPHABETS; ++letter) {
		ret += count(length - 1, now->next[letter]);
		ret %= MOD;
	}
	return ret;
}

// 코드 26.9 트라이의 각 노드에 no와 next테이블을 계산하는 재귀 함수의 구현

// 상태 간의 전이 테이블을 next[]에 채운다. 
// computeFailFunc()를 통해 이미 실패 함수가 계산되어 있다고 가정
void computeTransition(TrieNode* now, int& wordSize) {
	now->value = wordSize++; // depth
	for (int chr = 0; chr < ALPHABETS; ++chr) {
		// next[] 값을 계산해 저장한다
		TrieNode* next = now;
		while (next != next->fail && next->children[chr] == NULL)
			next = next->fail;
		if (next->children[chr])
			next = next->children[chr];
		now->next[chr] = next;
		// 재귀적으로 모든 노드에 대해 전이 테이블을 계산한다
		if (now->children[chr])
			computeTransition(now->children[chr], wordSize);
	}
}

int main() {
	int C;
	cin >> C;
	while (C--) {
		dp = vector<vector<int>>(101, vector<int>(1001, -1));
		int N, M;
		cin >> N >> M;
		char word[11];

		TrieNode root = TrieNode();
		for(int i=0;i<M;i++){
			scanf("%s", word);
			root.insert(word, M);
		}
		int nc = 0;
		computeFailFunc(&root);
		computeTransition(&root, nc);

		printf("%d\n", count(N, &root));
	}
	return 0;
}
