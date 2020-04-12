/**
 * problem : https://www.algospot.com/judge/problem/read/DICTIONARY
 * algorithm : DFS
 * time complexity : O(NM) // N : 단어 수, M : 각 단어 길이
 */

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
vector<vector<int>> adj;
vector<int> seen, order;

void dfs(int now) {
	seen[now] = 1;
	for (int next = 0; next < adj.size(); next++) {
		if (adj[now][next] && !seen[next]) {
			dfs(next);
		}
	}
	order.push_back(now);
}

vector <int> topologicalSort() {
	int n = adj.size();
	seen = vector<int>(n, 0);
	order.clear();

	for (int i = 0; i < n; i++) {
		if (!seen[i]) dfs(i);
	}

	// 역순
	reverse(order.begin(), order.end());
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (adj[order[j]][order[i]]) {
				return vector<int>();
			}
		}
	}

	return order;
}

void makeGraph(vector<string>& words) {

	// init
	adj = vector<vector<int>>(26, vector<int>(26, 0));

	for (int i = 1; i < words.size(); i++) {
		for (int j = 0; j < min(words[i].size(), words[i - 1].size()); j++) {
			// first different start alphabet
			if (words[i - 1][j] != words[i][j]) {
				adj[words[i-1][j] - 'a'][words[i][j] - 'a'] = 1; // connect
				break;
			}
		}
	}
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		int n;
		cin >> n;
		vector<string> words(n);
		for (int i = 0; i < n; i++) cin >> words[i];

		makeGraph(words);
		vector<int> ans = topologicalSort();

		if (ans.empty()) {
			cout << "INVALID HYPOTHESIS" << endl;
		}
		else {
			for (int i = 0; i < ans.size(); i++)
				cout << (char)(ans[i] + 'a');
			cout << endl;
		}
	}
	return 0;
}
