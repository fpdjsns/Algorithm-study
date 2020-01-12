
//
//  algo_greduation.cpp
//  알고리즘 문제해결전략 - 비트마스크
//
//  Created by Hubring on 2020. 1. 12.
//  Copyright © 2020년 Hubring. All rights reserved.
//


#include<stdio.h>
#include<iostream>
#include<algorithm>
//#include <intrin.h>

using namespace std;

const int INF = 10000;
const int INIT = -1;

int prerequisite[15], //선수 과목 
courses[12]; //학기 개설 과목 
int N, //전공과목 수
K, //들어야할 과목 수 
M,//학기 수 
L; //한학기에 들을 수 있는 최대 과목 수 


int dp[12][5001]; //dp[학기][수강상태] = 앞으로 들어야할 최소 학기 수
int minGraduationCondition(int semesterNo, int taken) {
	//if (__popcnt(taken) >= K) return 0; //모든 과목 수강 //visual C++
	if (__builtin_popcount(taken) >= K) return 0; //모든 과목 수강 //gcc C++

	if (semesterNo == M) return INF; //더이상 수강할 학기 없음

	int& ret = dp[semesterNo][taken];
	if (ret != INIT) return ret; //한번 방문했던 상태라면 리턴
	ret = INF;

	//수강가능한 과목 확인
	int canTaken = (courses[semesterNo] & ~taken);

	//선수과목을 모두 들었는지 확인
	for (int i = 0; i < N; i++) {
		if ((canTaken & (1 << i)) == 0) continue;
		if (prerequisite[i] & ~taken) { //선수과목을 안들었다면 제외
			canTaken ^= (1 << i);
		}
	}

	//수강가능한 조합
	for (int take = canTaken; take > 0; take = (take - 1) & canTaken) {
		//if (__popcnt(take) > L) continue;
		if (__builtin_popcount(take) > L) continue;
		ret = min(ret, minGraduationCondition(semesterNo + 1, taken | take) + 1);
	}

	//수강하지 않는 경우
	ret = min(ret, minGraduationCondition(semesterNo + 1, taken));

	if (ret > INF) return INF;
	return ret;
}

void init() {
	for (int i = 0; i < 11; i++) {
		fill_n(dp[i], 5000, INIT);
	}
	fill_n(courses, 11, 0);
	fill_n(prerequisite, 15, 0);
}

void solve() {
	init();

	cin >> N >> K >> M >>L;

	// i 과목의 선수과목 정보 입력
	int R // 선수과목 수
		, classNo; //과목번호
	for (int i = 0; i < N; i++) {
		cin >> R;
		for (int j = 0; j < R; j++) {
			cin >> classNo;
			prerequisite[i] |= (1 << classNo);
		}
	}

	//i 학기 개설 과목 정보 입력
	int C; //개설과목 수
	for (int i = 0; i < M; i++) {
		cin >> C;
		for (int j = 0; j < C; j++) {
			cin >> classNo;
			courses[i] |= (1 << classNo);
		}
	}

	int result = minGraduationCondition(0, 0);

	if (result == INF)	cout << "IMPOSSIBLE" << endl;
	else					cout << result << endl;
}

int main() {
	int c;
	cin >> c;

	for (int i = 0; i < c; i++) {
		solve();
	}

	return -1;
}
