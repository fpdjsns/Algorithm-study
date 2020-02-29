
//
//  algo_runningmedian.cpp
//  알고리즘 문제해결전략 - 변화하는 중앙값
//
//  Created by Hubring on 2020. 2. 29.
//  Copyright © 2020년 Hubring. All rights reserved.
//
//  시간복잡도 : O(NlogN)

#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string>
#include<climits>
using namespace std;


//신호 생성
struct RNG {
	int seed, a, b;

	RNG(int _a, int _b) : a(_a), b(_b), seed(1983) {}
	int next() {
		int ret = seed;
		seed = ((seed * (long long) a) + b) % 20090711;
		return ret;
	}
};


/// <summary>
///	수열에 새로운 수가 추가될때마다 바뀌는 중간값을 찾음
/// </summary>
///<param name = 'n'>n개의 난수(1<=n<=200000)< / param>
///<param name = 'rng'>수열에 추가할 난수 생성기< / param>
int runningMedian(int n, RNG rng) {
	priority_queue<int, vector<int>, greater<int>> minHeap; 
	priority_queue<int, vector<int>, less<int>> maxHeap; 
	if (n == 1) return rng.next();

	maxHeap.push(rng.next());
	int res = maxHeap.top();

	for (int i = 2; i <= n; i++) {
		(maxHeap.size() == minHeap.size()) ? maxHeap.push(rng.next()) : minHeap.push(rng.next());

		if (maxHeap.top()>minHeap.top()) {
			int num1 = maxHeap.top();
			int num2 = minHeap.top();
			maxHeap.pop();
			minHeap.pop();

			minHeap.push(num1);
			maxHeap.push(num2);
		}
		res = (res + maxHeap.top()) % 20090711;
	}

	return res;
}


void solve() {
	int n, a, b;
	cin >> n >> a >> b;
	cout << runningMedian(n, RNG(a, b)) << endl;
}



int main() {
	int testCase;
	scanf("%d", &testCase);

	for (int i = 0; i < testCase; i++) {
		solve();
	}
}