#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <queue>
#include <iostream>
#include <math.h>
#include <malloc.h>
#include <string.h>
using namespace std;
//하노이의 탑 문제를 해결하는 양방향 탐색의 구현
const int MAX_DISCS = 12;
//index번 원반이 몇 번 기둥에 꽂혀있는지 반환한다.
int get(int state, int index) {
	return (state >> (index * 2)) & 3;
}
//state를 index번 원반이 value기둥에 꽂혀있는 상태로 변경한다.
int set(int state, int index, int value) {
	return (state & ~(3 << (index * 2))) | (value << (index * 2));
}
int c[(1 << (MAX_DISCS * 2))];
//x의 부호를 반환한다.
int sgn(int x) { if (!x) return 0; return x > 0 ? 1 : -1; }
//x의 절대값을 1 증가시킨다.
int incr(int x) { if (x < 0) return x - 1; return x + 1; }
//discs개의 원반이 있고, 각 원반의 시작 위치와 목표 위치가
//begin, end에 주어질 때 최소 움직임의 수를 계산한다.
int bidir(int discs, int begin, int end) {
	if (begin == end) return 0;
	queue<int> q;
	//초기화를 0으로 하는 데 주의
	memset(c, 0, sizeof(c));
	//정방향 탐색은 양수로, 역방향 탐색은 음수로 표시한다.
	q.push(begin); c[begin] = 1;
	q.push(end); c[end] = -1;
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		int top[4] = { -1, -1, -1, -1 };
		for (int i = discs - 1; i >= 0; i--)
			top[get(here, i)] = i;
		for (int i = 0; i < 4; i++)
			if (top[i] != -1)
				for (int j = 0; j < 4; j++)
					if (i != j && (top[j] == -1 || top[j] > top[i])) {
						int there = set(here, top[i], j);
						//아직 방문하지 않은 정점인 경우
						if (c[there] == 0) {
							c[there] = incr(c[here]);
							q.push(there);
						}
						//가운데서 만난 경우
						else if (sgn(c[there]) != sgn(c[here]))
							return abs(c[there]) + abs(c[here]) - 1;
					}
	}
	return -1;
}

int main(void) {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, discs, start, end;
		int total_discs;
		n = start = 0;
		scanf("%d", &total_discs);
		for (int i = 0; i < 4; i++) {
			//원반의 갯수
			scanf("%d", &discs);
			for (int j = 0; j < discs; j++) {
				scanf("%d", &n);
				start = set(start, n - 1, i);
			}
		}
		end = pow(2, 2 * total_discs) - 1;
		printf("%d\n", bidir(total_discs, start, end));

	}
	return 0;
}

