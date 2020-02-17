/*
 *  Date : 2020.02.16
 *  Language : C
 *  Complexity : O(N)
 *  Data Structure : Tree
 *  Algorithm : 
 *
 *  Problem : https://algospot.com/judge/problem/read/TRAVERSAL
 */
#include <stdio.h>
#include <malloc.h>

int pre_order[100];
int in_order[100];
int k;

struct TREE {
	int node;
	struct TREE *left, *right;
};

void searchPostorder(struct TREE *tree) {
	if (tree->node == 0) return;
	searchPostorder(tree->left);
	searchPostorder(tree->right);
	printf("%d ", tree->node);
}

void solve(int s, int e, struct TREE *tree) {
	int ret = -1;

	if (s > e) return;
	for (int i = s; i <= e; ++i) {
		if (in_order[i] == pre_order[k]) {
			ret = i;
		}
	}
	if (ret == -1) return;

	tree->node = pre_order[k++];
	tree->left = (struct TREE *)calloc(1, sizeof(struct TREE));
	tree->right = (struct TREE *)calloc(1, sizeof(struct TREE));

	solve(s, ret - 1, tree->left);
	solve(ret + 1, e, tree->right);

	return;
}

int main() {
	int T, N;
	struct TREE *tree = (struct TREE *)calloc(1, sizeof(struct TREE));

	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%d", &pre_order[i]);
		}
		for (int i = 0; i < N; i++) {
			scanf("%d", &in_order[i]);
		}

		solve(0, N-1, tree);
		searchPostorder(tree);
		k = 0;
	}
	return 0;
}