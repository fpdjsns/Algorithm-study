
//
//  algo_traversal.cpp
//  알고리즘 문제해결전략 - 트리 순회 순서 변경
//
//  Created by Hubring on 2020. 2. 16.
//  Copyright © 2020년 Hubring. All rights reserved.
// 시간복잡도 : O(N^2)

#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string>
using namespace std;


int N; //노드수
vector<int> preorder, inorder; //전위순회, 중위순회


void printPostOerder(int s_p, int e_p, int s_i, int e_i) {
	if (e_p < s_p)  return;

	//부모
	int root = preorder[s_p];

	//중위순회에서 부모 노드 찾기
	int left = 0; //왼쪽 트리 노드 수 
	for (int i = s_i; i <= e_i; i++) {
		if (inorder[i] == root) {
			break;
		}
		left++;
	}

	//왼쪽 순회
	printPostOerder(s_p + 1, s_p + left, s_i, s_i + left);
	//오른쪽 순회
	printPostOerder(s_p + left + 1, e_p, s_i + left + 1, e_i);

	//부모 출력
	cout << root << ' ';
}



void solve() {

	cin >> N;

	int inputNum;
	for (int i = 0; i < N; i++) {
		cin >> inputNum;
		preorder.push_back(inputNum);
	}

	for (int i = 0; i < N; i++) {
		cin >> inputNum;
		inorder.push_back(inputNum);
	}

	printPostOerder(0, N - 1, 0, N - 1);

	preorder.clear();
	inorder.clear();
}



int main() {
	int testCase;
	scanf("%d", &testCase);

	for (int i = 0; i < testCase; i++) {
		solve();
	}
}
