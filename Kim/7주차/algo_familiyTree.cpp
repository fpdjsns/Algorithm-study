
	//
	//  algo_familiyTree.cpp
	//  알고리즘 문제해결전략 - 족보 탐험
	//
	//  Created by Hubring on 2020. 3. 08..
	//  Copyright © 2020년 Hubring. All rights reserved.
	//  시간복잡도 O(QN)

	#include<stdio.h>
	#include<iostream>
	#include<algorithm>
	#include<vector>
	#include<queue>
	#include<string>
	#include<climits>
	using namespace std;

	int fathers[100001]; //i번의 아버지의 번호 저장
	int aAncestors[100001]; //a번의 n촌 번호 저장
	int bAncestors[100001]; //b번의 n촌 번호 저장


	/// <summary>
	///	 가족 촌수 구하기
	/// 족보에는 시조의 후손이 아닌 사람은 주어지지 않으며, 자기 자신의 조상이 되는 등의 모순된 입력 또한 주어지지 않습니다.
	/// 입력의 크기가 크므로 가능한 빠른 입력 방법을 사용하는 것이 좋습니다.
	/// </summary>
	void solve() {
		// 족보에 포함된 사람의 수 N (1 <= N <= 100,000), 
		// 촌수를 계산할 두 사람의 수 Q (1 <= Q <= 10,000) 
		int N, Q;
		scanf("%d %d", &N, &Q);


		// N-1 개의 정수로 1번부터 N-1 번까지 각 사람의 아버지의 번호
		for (int i = 1; i < N; i++) {
			scanf("%d", &fathers[i]);
		}

		//Q 줄에 각 2개의 정수로 두 사람의 번호 a, b 가 주어집니다. (0 <= a,b < N)
		for (int i = 0; i < Q; i++) {
			int a, b;
			scanf("%d %d", &a, &b);

			int an = 0, bn = 0;

			//a번호의 조상 저장
			for (int af = a; af != 0; af = fathers[af])
				aAncestors[an++] = af;

			//b번호의 조상 저장
			for (int bf = b; bf != 0; bf = fathers[bf])
				bAncestors[bn++] = bf;

			//공통 조상이 다른 지점 찾기
			while (an > 0 && bn > 0) {
				if (aAncestors[an-1] != bAncestors[bn-1]) {
					break;
				}
				an--;
				bn--;
			}

			printf("%d\n", an+bn);
		}

	}



	int main() {
		int testCase;
		scanf("%d", &testCase);

		for (int i = 0; i < testCase; i++) {
			solve();
		}
	}



