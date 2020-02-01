/*
 *  Date : 2020.02.01
 *  Language : C
 *  Complexity : O(N)
 *  Data Structure : Linked List
 *
 *  Problem : https://www.algospot.com/judge/problem/read/JOSEPHUS
 */
 
#include <stdio.h>
#include <malloc.h>

struct node {
	int i;
	struct node *prev, *next;
};

struct node *head;

void createGroup(int n) {
	struct node *p;
	p = (struct node *)calloc(1, sizeof(struct node));
	p->i = 1;
	head = p;
	for (int j = 2; j <= n; ++j) {
		p->next = (struct node *)calloc(1, sizeof(struct node));
		p->next->prev = p;
		p->next->i = j;
		p = p->next;
	}
	p->next = head;
	head->prev = p;
}

struct node *searchNode(struct node *cur, int k) {
	struct node *cur_k = cur;

	while (k--)
		cur_k = cur_k->next;
	return cur_k;
}

struct node * deleteNode(struct node *cur) {
	struct node *p = cur;

	p->next->prev = p->prev;
	p->prev->next = p->next;
	p = p->next;
	delete(cur);
	return p;
}

void solve(int n, int k) {
	struct node *p = NULL, *cur;
	int remainCnt = 0;
	int answer[2];

	createGroup(n);
	remainCnt = n;
	cur = head;
	while (remainCnt > 2){
		// Die kth soldier
		p = deleteNode(cur);
		// Search soldier to be died
		cur = searchNode(p, k - 1);
		remainCnt--;
	}
	if (p->i > p->next->i) {
		answer[1] = p->i;
		answer[0] = p->next->i;
	}
	else {
		answer[0] = p->i;
		answer[1] = p->next->i;
	}

	printf("%d %d\n", answer[0], answer[1]);
}

int main() {
	int T;
	int N, K;

	scanf_s("%d", &T);
	while (T--) {
		scanf_s("%d %d", &N, &K);
		solve(N, K);
	}
	return 0;
}
