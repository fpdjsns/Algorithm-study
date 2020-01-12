
//
//  algo_christmas.cpp
//  알고리즘 문제해결전략 부분합
//
//  Created by Hubring on 2020. 1. 12..
//  Copyright © 2019년 Hubring. All rights reserved.
//


#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string>
using namespace std;

#define MOD 20091101
#define MAX 100010

int N, K;
int subSum[MAX];
int cnt[MAX]; //?? 제발루

int allCasesOrderGrit() {
	int res = 0;
	for (int i = 0; i <= N; i++) {
		cnt[subSum[i]]++;
	}
	for (int i = 0; i < K; i++) {
		if (cnt[i] < 2) continue;
		res =( res+(((long long) cnt[i] * (cnt[i] - 1)) / 2)) %MOD;
	}
	return res;
}


int dp[MAX];
int prevSum[MAX];
int maxOrderGrit() {

	for (int i = 0; i <= N; i++) {
		if( i > 0) dp[i] = dp[i - 1];
		else dp[0] = 0;

		int loc = prevSum[subSum[i]];
		if (loc != -1) dp[i] = max(dp[i],  dp[loc] + 1);
		prevSum[subSum[i]] = i;
	}
	return dp[N];
}


void init() {
	for (int i = 0; i < MAX; i++) {
		prevSum[i] = -1;
		cnt[i] =  subSum[0] = dp[0] = 0;
	}
}
void solve() {
	init();

	subSum[0] = 0;

	scanf("%d %d", &N, &K);

	int input;
	for (int i = 1; i <= N; i++) {
		scanf("%d", &input);
		subSum[i] = (subSum[i - 1]+ input) % K;
	}

	printf("%d %d\n", allCasesOrderGrit(), maxOrderGrit());
}



int main() {
	int testCase;
	scanf("%d", &testCase);

	for (int i = 0; i < testCase; i++) {
		solve();
	}
}