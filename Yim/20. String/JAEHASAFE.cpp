/*
 *  Date : 2020.02.08
 *  Language : C
 *  Complexity : O(N)
 *  Data Structure : N/A
 *  Algorithm : KMP
 *
 *  Problem : https://www.algospot.com/judge/problem/read/JAEHASAFE
 */

#include <stdio.h>
#include <string.h>

char cur_dial[10001];
char next_dial[10001];

int pi[10001];

void getPartialMatch(char *n, int size_n) {
	int begin = 1, matched = 0;
	while (begin + matched < size_n) {
		if (n[begin + matched] == n[matched]) {
			++matched;
			pi[begin + matched - 1] = matched;
		}
		else {
			if (matched == 0) begin++;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
}

int kmp(char *h, char *n, int size_h, int size_n) {
	int j = 0;
	int matched = 0, ret = 0;
	getPartialMatch(n, size_n);

	for (int i = 0; i < size_h * 2; ++i) {
		j = i % size_h;
		while (matched > 0 && h[j] != n[matched]) {
			matched = pi[matched - 1];
		}
		if (h[j] == n[matched]) {
			++matched;
			if (matched >= size_n) {
				return i - (size_n - 1);
				matched = pi[matched - 1];
			}
		}
	}
	return ret;
}

int solve(int N) {
	int ret = 0;
	char *orig, *tar;
	int orig_size, tar_size;

	for (int i = 0; i < N; ++i) {
		scanf("%s", next_dial);
		tar = cur_dial;
		orig = next_dial;
		orig_size = strlen(next_dial);
		tar_size = strlen(cur_dial);
		// 시계 방향
		if (i % 2 == 0) {
			ret += kmp(orig, tar, orig_size, tar_size);
		}
		// 반시계 방향
		else {
			ret += kmp(tar, orig, tar_size, orig_size);
		}

		strcpy(cur_dial, next_dial);
	}

	return ret;
}
int main() {
	int T, N, ret = 0;
	int dir = 1;

	scanf("%d", &T);

	while (T--) {
		scanf("%d", &N);
		scanf("%s", cur_dial);
		ret = solve(N);
		printf("%d\n", ret);
		ret = 0;
	}

	return 0;
}