//
//  algo_habit.cpp
//  알고리즘 문제해결전략 - 말버릇
//
//  Created by Hubring on 2020. 2. 8.
//  Copyright © 2020년 Hubring. All rights reserved.
//  시간복잡도 : O(N^2)

#include<stdio.h>
#include <string.h>
#include<iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


struct SuffixComparator {
	const string& s;
	SuffixComparator(const string& s) : s(s) {}
	bool operator () (int i, int j) {
		//s,substr 대신에 strcmp를 쓰면 임시 객체를 만드는 비용이 절약된다.
		return strcmp(s.c_str() + i, s.c_str() + j) <0;
	}
};

//접두사 배열 생성 (STL정렬이용 - O(nlogn))
vector<int> getSuffixArrayNaive(const string& s) {
	//접미사의 시작 위치를 담은 배열 생성
	vector<int> perm;
	for (int i = 0; i < s.size(); i++) perm.push_back(i);

	sort(perm.begin(), perm.end(), SuffixComparator(s));
	return perm;
}


//s[i..]와 s[j..]의 공통 접두사의 최대 길이를 계산한다.  - O(n)
int commonPrefix(const string& s, int i, int j) {
	int k = 0;
	while (i<s.size() && j < s.size() && s[i] == s[j]) {
		++i; ++j; ++k;
	}
	return k;
}


/// <summary>
///	문자열 내 공통 부분 문자열이 k번 이상나타나며, 가장 긴 부분 문자열의 길이를 출력
/// </summary>
///<param name = 'k'> k번 이상 등장하는 부분문자열< / param>
///<param name = 's'>대본 문자열< / param>
int longestFrequent(int k , const string& s) {
	vector<int> a = getSuffixArrayNaive(s);
	int ret = 0;
	for (int i = 0; i + k <= s.size(); i++) {
		ret = max(ret, commonPrefix(s, a[i], a[i+k-1]));
	}

	return ret;
}




void solve() {
	int k;
	string s;

	cin >> k >> s;
	cout << longestFrequent(k,s) << endl;
}



int main() {
	int testCase;
	scanf("%d", &testCase);

	for (int i = 0; i < testCase; i++) {
		solve();
	}
}