
//
//  algo_josephus.cpp
//  알고리즘 문제해결전략 - 조세푸스 문제
//
//  Created by Hubring on 2020. 2. 1.
//  Copyright © 2020년 Hubring. All rights reserved.
//  시간복잡도 : O((N-2) * K) = O(NK)  // (3<= N,K <= 1000)

#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<list>
using namespace std;

/// <summary>
///	조세푸스 문제 : 포위당한 N명이 원형으로 둘러선 뒤 
/// 1번부터 차례로 자살하며 자살한 사람으로부터 시계방향으로 K번쨰 있는 사람이 죽을 경우 마지막 남은 두명의 위치 출력
/// </summary>
///<param name = 'n'>포위당한 병사수< / param>
///<param name = 'k'> k: 시계방향으로 k번째 살아있는 사람< / param>
///<returns> 마지막 남은 두명의 위치 출력</returns>
void josephus(int n, int k) {

	//포위당한 병사 리스트 (연결리스트)
	list<int> soldiers;
	for (int i = 1; i <= n; i++) soldiers.push_back(i);

	// curr : 현재 죽을 사람의 위치
	list<int>::iterator curr = soldiers.begin();

	//한사람이 자살하면 시계방향으로 K번째 살아 있는 사람이 자살한다.
	//마지막 두사람이 살아남으면 끝
	while (soldiers.size() > 2) {
		curr = soldiers.erase(curr);
		if (curr == soldiers.end())	curr = soldiers.begin();
		
		for (int i = 0; i < k - 1; i++) {
			curr++;
			if (curr == soldiers.end())	curr = soldiers.begin();
		}
	}
	//살아남은 사람의 위치를 출력한다. 
	cout << soldiers.front() << " " << soldiers.back() << endl;
}

void solve() {
	int n, k; 
	cin >> n >> k;
	josephus(n, k);
}

int main() {
	int testCase;
	scanf("%d", &testCase);

	for (int i = 0; i < testCase; i++) {
		solve();
	}
}