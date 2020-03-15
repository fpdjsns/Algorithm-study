//
//  algo_measuretime.cpp
//  알고리즘 문제해결전략 - 삽입정렬시간재기
//
//  Created by Hubring on 2020. 3. 15.
//  Copyright © 2020년 Hubring. All rights reserved.
//
//  시간복잡도 : O(NlgM) - (M : 숫자의 최대치)

#include<stdio.h>
#include<vector>
#include<iostream>

using namespace std;

struct FenwickTree
{
	vector<int> tree;
	FenwickTree(int n) : tree(n + 1) {}

	int sum(int pos) {
		++pos;
		int ret = 0;
		while (pos > 0)
		{
			ret += tree[pos];
			pos &= (pos - 1);
		}

		return ret;
	}

	void add(int pos, int val) {
		++pos;
		while (pos < tree.size()) {
			tree[pos] += val;
			pos += (pos&-pos);
		}
	}

};

vector<int> A;

void input() {
	int n;

	cin >> n;
	for (int i = 0; i < n; i++) {
		int input;
		cin >> input;
		A.push_back(input);
	}
}

long long CountMoves() {
	FenwickTree tree(1000000);
	long long ret = 0;
	for (int i = 0; i < A.size(); ++i) {
		ret += tree.sum(999999) - tree.sum(A[i]);
		tree.add(A[i], 1);
	}
	return ret;
}

void solve() {
	input();
	cout << CountMoves() << endl;
	A.clear();
}

int main() {

	int testCase;
	cin >> testCase;

	for (int i = 0; i < testCase; i++) {
		solve();
	}

	return 0;
}
