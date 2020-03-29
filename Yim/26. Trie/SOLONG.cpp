/*
 *  Date : 2020.03.29
 *  Language : C/C++
 *  Complexity : O(NlgN)
 *  Data Structure : TRIE
 *  Algorithm :
 *
 *  Problem : https://algospot.com/judge/problem/read/SOLONG
 */
#include <stdio.h>
#include <malloc.h>
#include <vector>
#include <algorithm>
#include <string.h>

#define ALPHABET 26
#define AtoN(a) ((int)((a) - 'A'))

using namespace std;

struct TRIE {
	int first, terminal;
	struct TRIE *alpha[ALPHABET];
}*trie;

void insertTrie(struct TRIE* t,const char* str, int k) {
	if (t->first == -1) t->first = k;
	if (*str == '\0') {
		t->terminal = k;
	}
	else {
		if (t->alpha[AtoN(*str)] == NULL) {
			t->alpha[AtoN(*str)] = (struct TRIE*)calloc(1, sizeof(struct TRIE));
			t->alpha[AtoN(*str)]->first = -1;
			t->alpha[AtoN(*str)]->terminal = -1;
		}
		insertTrie(t->alpha[AtoN(*str)], str + 1, k);
	}
}

struct TRIE* find(struct TRIE* t, const char *str) {
	int ret;
	int max = 0;
	if (*str == '\0') {
		return t;
	}
	if (t->alpha[AtoN(*str)] == NULL) {
		return NULL;
	}
	return find(t->alpha[AtoN(*str)], str + 1);
}

int getCnt(struct TRIE* t, const char* str, int k) {
	if (*str == '\0') return 0;
	if (t->first == k) return 1;
	return getCnt(t->alpha[AtoN(*str)], str + 1, k) + 1;
}

int getKeyCnt(struct TRIE* t, const char* str) {
	struct TRIE *node = find(t, str);
	if (node == NULL || node->terminal == -1)
		return strlen(str);
	return getCnt(t, str, node->terminal);
}

void solve(int n, int m) {
	char word[11];
	int freq, ret = 0;
	vector<pair<int, string>> input;

	for (int i = 0; i < n; ++i) {
		scanf("%s %d", word, &freq);
		input.push_back(make_pair(-freq, word));
	}

	sort(input.begin(), input.end());
	struct TRIE* t = (struct TRIE*)calloc(1, sizeof(struct TRIE));
	t->first = -1;
	t->terminal = -1;
	for (int i = 0; i < input.size(); ++i)
		insertTrie(t, input[i].second.c_str(), i);
	t->first = -1;

	for (int i = 0; i < m; ++i) {
		scanf("%s", word);
		ret += getKeyCnt(t, word);
	}
	ret += m - 1;
	printf("%d\n", ret);
}

int main() {
	int T;
	int N, M;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &N, &M);
		solve(N, M);
	}
	return 0;
}