
//
//  algo_brackets2.cpp
//  알고리즘 문제해결전략 - 짝이 맞지 않는 괄호
//
//  Created by Hubring on 2020. 2. 1.
//  Copyright © 2020년 Hubring. All rights reserved.
//  시간복잡도 : O(N), N은 문자열의 길이(1 <= N <= 10000)

#include<stdio.h>
#include<iostream>
#include<stack>
#include <map>
#include <string>
using namespace std;


/// <summary>
/// 짝이 맞지 않는괄호 찾기
/// </summary>
///<param name = 'str'>"(){}[]"만 포함된 문자열< / param>
///<returns>괄호의 짝이 맞는지 여부</returns>
bool isMatchedBracket(const string& str ) {
	map<char, char> bracketMap; //열린괄호 짝을 저장하고 있는 맵
	bracketMap['(']= ')';
	bracketMap['{'] = '}';
	bracketMap['['] = ']';


	stack<char> openStack;
	int strSize = str.size();
	for (int i = 0; i < strSize; i++) {
		char c = str[i]; //c : 괄호
		//열린괄호라면 스택에 넣음
		if (bracketMap.find(c) != bracketMap.end()) {
			openStack.push(c);
		}
		else {
			//닫힌괄호와 열린괄호가 짝이 맞는지 확인
			if (openStack.empty()) return false;
			if (bracketMap[openStack.top()] != c) return false;
			openStack.pop(); 
		}
	}

	//열린 괄호가 모두 비워져있다면 매칭 성공 이외 실패
	return openStack.empty();
 }



void solve() {
	string inputStr;
	cin >> inputStr;
	string result = isMatchedBracket(inputStr) ? "YES" : "NO" ;
	cout << result << endl;
}


int main() {
	int testCase;
	scanf("%d", &testCase);

	for (int i = 0; i < testCase; i++) {
		solve();
	}
}