/*
 *  Date : 2020.02.01
 *  Language : C
 *  Complexity : O(N)
 *  Data Structure : Stack
 *
 *  Problem : https://www.algospot.com/judge/problem/read/BRACKETS2
 */

#include <stdio.h>
#define MAX_N 10001

char stack[MAX_N];
char bracket_str[MAX_N];
int top = 0;
char answer[2][4] = { "NO", "YES" };

int solve() {
	char *ptr;
	ptr = bracket_str;
	while (*ptr) {
		switch (*ptr) {
			case ')':
				if (stack[--top] != '(') return 0;
				break;
			case '}':
				if (stack[--top] != '{') return 0;
				break;
			case ']':
				if (stack[--top] != '[') return 0;
				break;
			default:
				stack[top++] = *ptr;
		}
		ptr++;
	}
	if (top != 0)
		return 0;
	return 1;
}

int main() {
	int T, ret;
	scanf("%d", &T);
	while (T--) {
		scanf("%s", bracket_str);
		ret = solve();
		printf("%s\n", answer[ret]);
		top = 0;
	}
	return 0;
}
