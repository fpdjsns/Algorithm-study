/**
 * problem : https://algospot.com/judge/problem/read/ITES
 * algorithm : two pointer
 * time complexity : O(N)
 * space complexity : O(N)
 */

 /**
  * 이 코드는 런타임 오류가 발생한다.
  * RTE (SIGKILL: program was forcefully killed, probably memory limit exceeded)
  *
  * 원인은 공간 복잡도가 O(N)이기 때문.
  * N은 50,000,000 이고 이를 int형 배열에 저장한다고 하면
  * 필요한 메모리는 50,000,000 * 4byte / 1024 = 195,312.5 kb
  * 195,312.5는 메모리 제한(65,536kb)을 넘기기 때문에 위와 같은 에러가 발생한다.
  */

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

int MAX_N = 50000001;
vector<int> signals = vector<int>(MAX_N, -1);

void setSignals() {
	long long int outsideSignal = 1983;
	long long int TMP = pow(2, 32);
	for (int i = 0; i < MAX_N; i++) {
		signals[i] = outsideSignal % 10000 + 1;
		outsideSignal = ((long long int)outsideSignal * 214013 + 2531011) % TMP;
	}
}

int solve(int K, int N) {
	int ans = 0;

	int subSum = 0;
	int first = 0;
	for (int last = 0; last < N; last++) {
		subSum += signals[last];
		while (first <= last) {
			if (subSum < K) break;
			if (subSum == K) ans++;
			subSum -= signals[first++];
		}
	}

	return ans;
}

int main() {

	setSignals();

	int C;
	cin >> C;

	while (C--) {
		int K, N;
		cin >> K >> N;
		cout << solve(K, N) << endl;
	}
	return 0;
}