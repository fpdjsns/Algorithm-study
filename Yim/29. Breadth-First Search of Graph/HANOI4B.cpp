#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <queue>
#include <iostream>
#include <math.h>
#include <malloc.h>
#include <string.h>
using namespace std;
//�ϳ����� ž ������ �ذ��ϴ� ����� Ž���� ����
const int MAX_DISCS = 12;
//index�� ������ �� �� ��տ� �����ִ��� ��ȯ�Ѵ�.
int get(int state, int index) {
	return (state >> (index * 2)) & 3;
}
//state�� index�� ������ value��տ� �����ִ� ���·� �����Ѵ�.
int set(int state, int index, int value) {
	return (state & ~(3 << (index * 2))) | (value << (index * 2));
}
int c[(1 << (MAX_DISCS * 2))];
//x�� ��ȣ�� ��ȯ�Ѵ�.
int sgn(int x) { if (!x) return 0; return x > 0 ? 1 : -1; }
//x�� ���밪�� 1 ������Ų��.
int incr(int x) { if (x < 0) return x - 1; return x + 1; }
//discs���� ������ �ְ�, �� ������ ���� ��ġ�� ��ǥ ��ġ��
//begin, end�� �־��� �� �ּ� �������� ���� ����Ѵ�.
int bidir(int discs, int begin, int end) {
	if (begin == end) return 0;
	queue<int> q;
	//�ʱ�ȭ�� 0���� �ϴ� �� ����
	memset(c, 0, sizeof(c));
	//������ Ž���� �����, ������ Ž���� ������ ǥ���Ѵ�.
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
						//���� �湮���� ���� ������ ���
						if (c[there] == 0) {
							c[there] = incr(c[here]);
							q.push(there);
						}
						//����� ���� ���
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
			//������ ����
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

