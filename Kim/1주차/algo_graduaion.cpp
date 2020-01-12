
//
//  algo_greduation.cpp
//  알고리즘 문제해결전략 - 비트마스크
//
//  Created by Hubring on 2019. 2. 14..
//  Copyright © 2019년 Hubring. All rights reserved.
//


#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string>
#include<climits>
using namespace std;


const int INF = 1e9;

/*
* N : 전공 과목 수 (1<=N<=12)
* K : 들어야할 과목 수  (1<=K<=N)
* M : 학기의 수 (1<=M<=10)
* L : 학기에 최대 수강 가능 과목의 수 (1<=L<=10)
*/
int N, K, M, L;

// dp[학기][들은 과목 상태] = 현재까지 상태에서 들은 최소 학기 수 
int dp[12][1 << 12];
// subject[i] : 과목 i의 선수 과목 비트 
int subject[13];
// semester[i] : 학기 i의 개설 과목 비트 
int semester[13];

int result;


int getCount(int n) {
	if (n <= 1)
		return n;
	return getCount(n / 2) + (n % 2);
}


int canGraduation( int semesterId, int doneSubject ) {

	if (getCount(doneSubject) >= K) {
		return 0;
	}
	if (semesterId == M) return INF;

	int& ret = dp[semesterId][doneSubject];
	if (ret !=-1) return ret;
	ret = INF;


	int courses = (semester[semesterId] & ~doneSubject);
	for (int i = 0; i < N; i++) {
		if ((courses  & (1<< i)) && ((subject[i] & doneSubject) != subject[i])) {
			courses &= ~(1 << i);
		}
	}

	for (int take = courses; take > 0; take = ((take - 1) & courses)) {
		if (getCount(take) > L) continue;
		ret = min(ret, canGraduation(semesterId + 1, doneSubject | take)+1);
	}
	ret = min(ret, canGraduation(semesterId + 1, doneSubject));

	return ret;
}


void init() {
	int size = 1 << 12;

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < size; j++)
			dp[i][j] = -1;
		subject[i] = 0;
		semester[i] = 0;
	}
}

void solve() {
	init();

	scanf("%d %d %d %d", &N, &K, &M, &L);

	//0번 과목부터 순서대로 각 과목의 선수 과목
	for (int i = 0; i < N; i++) {
		int size, subjectId;
		scanf("%d", &size);
		for (int j = 0; j < size; j++) {
			scanf("%d", &subjectId);
			subject[i] |= 1<< subjectId;
		}
	}


	//0번 학기부터 순서대로 각 학기의 개설 과목
	for (int i = 0; i < M; i++) {
		int size, subjectId;
		scanf("%d", &size);
		for (int j = 0; j < size; j++) {
			scanf("%d", &subjectId);
			semester[i] |= 1 << subjectId;
		}
	}


	int result = canGraduation(0, 0);

	if (result == INF) 
		printf("IMPOSSIBLE\n");
	else 
		printf("%d\n", result);

}



int main() {
	int testCase;
	scanf("%d", &testCase);

	for (int i = 0; i < testCase; i++) {
		solve();
	}
}