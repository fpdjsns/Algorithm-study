/*
 *  Date : 2020.03.14
 *  Language : C/C++
 *  Complexity : O(NlogN)
 *  Data Structure : Fenwick Tree
 *  Algorithm :
 *
 *  Problem : https://algospot.com/judge/problem/read/MEASURETIME
 */
#include <stdio.h>
#include <vector>
using namespace std;

struct FenwickTree {
	vector<int> tree;
	FenwickTree(int n) : tree(n + 1) {}
	// A[0..pos]의 부분합
	int sum(int pos) {
		++pos;
		int ret = 0;
		while (pos > 0) {
			ret += tree[pos];
			pos &= (pos - 1);
		}
		return ret;
	}

	void add(int pos, int val) {
		++pos;
		while (pos < tree.size()) {
			tree[pos] += val;
			pos += (pos & -pos);
		}
	}
};

long long count_moves(const vector<int> &A) {
	FenwickTree tree(1000000);
	long long ret = 0;
	for (int i = 0; i < A.size(); ++i) {
		ret += tree.sum(999999) - tree.sum(A[i]);
		tree.add(A[i], 1);
	}
	return ret;
}

void main() {
	int T;
	int N, tmp;
	vector<int> arr;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		for (int i = 0; i < N; ++i) {
			scanf("%d", &tmp);
			arr.push_back(tmp);
		}
		printf("%d\n", count_moves(arr));
		arr.clear();
	}
	system("pause");
}