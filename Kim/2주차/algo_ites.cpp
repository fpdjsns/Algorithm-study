//
//  algo_ites.cpp
//  알고리즘 문제해결전략 - 외계 신호 분석
//
//  Created by Hubring on 2020. 2. 1.
//  Copyright © 2020년 Hubring. All rights reserved.
//  시간복잡도 : O(N)

#include<stdio.h>
#include<iostream>
#include <queue>
using namespace std;

//신호 생성
struct RNG {
	unsigned seed;

	RNG() : seed(1983u) {}
	unsigned next() {
		unsigned ret = seed % 10000u + 1;
		seed = (seed * 214013u + 2531011u);
		return ret;
	}
};


///<summary> 길이 N인 신호 기록이 주어질 때 합이 K인 부분 수열의 수</summary>
///<param name = 'k'>찾을 수열의 합< / param>
///<param name = 'n'>신호의 길이< / param>
///<returns>합이 K인 부분 수열의 수</returns>
int getItesCount(int k , int n) {
	int result = 0; // 합이 K인 부분수열의 수
	RNG rng; // 신호값(초기 0번째)
	queue<int> sequence; // 합이 K값이 넘지않은 신호값을 저장하는 큐

	int sum = 0; //현재 큐에 저장된 신호의 총합

	for (int i = 0; i < n; i++) {
		int signal = rng.next(); //다음 신호값을 받음
		//받은 신호 값을 큐에 넣음
		sum += signal;
		sequence.push(signal);

		//큐의 신호 총합이 항상 K값을 넘지 않아야 하므로 가장 먼저 받은 신호의 값을 뺌
		while (k < sum) {
			sum-=sequence.front();
			sequence.pop();
		}

		// 만약 수열의 총합의 K와 같다면 결과 수를 증가시킴
		if (sum == k)  result++;
	}


	return result;
}


void solve() {
	int n, k;
	cin >> k >> n;
	cout << getItesCount(k, n) << endl;
}


int main() {
	int testCase;
	scanf("%d", &testCase);

	for (int i = 0; i < testCase; i++) {
		solve();
	}
}
