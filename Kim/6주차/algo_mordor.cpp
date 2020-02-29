//
//  algo_mordor.cpp
//  알고리즘 문제해결전략 - 등산로
//
//  Created by Hubring on 2020. 2. 29.
//  Copyright © 2020년 Hubring. All rights reserved.
//
//  시간복잡도 : O(N+QlogN) N(구간트리생성)+QlogN(구간트리 질의)

#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <string>

using namespace std;
typedef pair<int, int> P;

#define MAX 300000

int N;
int height[100001];

//구간 최대와 최소 높이를 저장
struct segmentTree {
	vector<P> range;

	segmentTree() {
		range.resize(N * 4);
		makeTree(0, N - 1, 1);
	}

	P makeTree(int left, int right, int node) {
		if (left == right) {
			return range[node] = make_pair(height[left], height[left]);
		}

		int mid = (left + right) / 2;
		P leftMinMax= makeTree(left, mid, node * 2); //왼쪽 구간의 최대 최소 
		P rightMinMax = makeTree(mid + 1, right, node * 2 + 1); //오른쪽 구간의 최대 최소 

		int minHeight = min(leftMinMax.first, rightMinMax.first);
		int maxHeight = max(leftMinMax.second, rightMinMax.second);

		P ret = make_pair(minHeight, maxHeight);
		
		return range[node] = ret;
	}

	P query(int left, int right, int node, int nodeLeft, int nodeRight) {
		if (nodeRight < left || right < nodeLeft) {
			return make_pair(MAX, -MAX);
		}

		if (left <= nodeLeft && nodeRight <= right) {
			return range[node];
		}

		int mid = (nodeLeft + nodeRight) / 2;
		P leftMinMax = query(left, right, node * 2, nodeLeft, mid);
		P rightMinMax = query(left, right, node * 2 + 1, mid + 1, nodeRight);

		int minHeight = min(leftMinMax.first, rightMinMax.first);
		int maxHeight = max(leftMinMax.second, rightMinMax.second);

		P ret = make_pair(minHeight, maxHeight);

		return ret;
	}
};

/// <summary>
///	 등산로의 난이도를 구하라 (난이도 = 최대해발고도 - 최저해발고도)
/// </summary>
void solve() {
	//N: 표지판의 수 (1<=N<=100000)
	//Q: 개방을 고려하고 있는 등산로의 수 (1<=Q<=10000)
	int Q;
	cin >> N >> Q;

	//해발고도
	for (int i = 0; i < N; ++i)
		cin >> height[i];

	segmentTree segmentTree;

	//a: 등산로의 첫번째 표시판 번호, b: 등산로의 마지막 표지판 번호
	for(int i=0; i< Q; i++){
		int a, b;  
		cin >> a >> b;

		P res = segmentTree.query(a, b, 1, 0, N - 1);
		cout << res.second - res.first << endl;
	}

}



int main() {
	int testCase;
	scanf("%d", &testCase);

	for (int i = 0; i < testCase; i++) {
		solve();
	}
}

