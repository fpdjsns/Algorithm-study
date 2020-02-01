/*
 *  Date : 2020.02.01
 *  Language : C
 *  Complexity : O(N)
 *  Data Structure : Queue
 *
 *  Problem : https://www.algospot.com/judge/problem/read/ITES
 */

#include <stdio.h>
#define MAX_K 500000
unsigned int seed;
int queue[MAX_K];
int s, e;

int genSignal() {
	int temp = seed;
	seed = (seed * 214013u + 2531011u);
	return seed % 10000 + 1;
}

int solve(int n, int k) {
	int l, r, sum, ret, signal;
	l = r = ret = 0;
	sum = 0;

	for (l = 0; l < n; l++) { 
		while (sum < k && r < n) {
			signal = genSignal();
			sum += signal;
			queue[e++] = signal;
			e %= MAX_K;
			r++;
		}
		if (sum == k) ret++;
		sum -= queue[s++];
		s %= MAX_K;
	}
	return ret;
}

int main() {
	int T, N, K;
	int ret;

	scanf("%d", &T);
	while (T--) {
		seed = 1983;
		scanf("%d %d", &K, &N);
		ret = solve(N, K);
		printf("%d\n", ret);
	}
	return 0;
}
