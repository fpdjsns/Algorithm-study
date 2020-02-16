#include <stdio.h>
#include <malloc.h>

struct CASTLE {
	int x, y, r;
}castle[100];

struct TREE {
	struct CASTLE wall;
	struct TREE *tree[100];
};

int max_mov_count;

int solve(struct TREE *fortress, struct CASTLE castle, int count) {
	int i, l, r, ret;
	struct TREE *temp_tree;

	l = (fortress->wall.x - castle.x)*(fortress->wall.x - castle.x)
		+ (fortress->wall.y - castle.y)*(fortress->wall.y - castle.y);
	r = (fortress->wall.r - castle.r)*(fortress->wall.r - castle.r);

	if (l > r)
		return -1;

	for (i = 0; fortress->tree[i]; ++i) {
		temp_tree = fortress->tree[i];

		ret = solve(temp_tree, castle, count+1);
		if (ret == 0)
			return 0;
	}

	if (fortress->tree[i] == NULL) {
		fortress->tree[i] = (struct TREE *)calloc(1, sizeof(struct TREE));
		fortress->tree[i]->wall = castle;
		if (count + 1 > max_mov_count)
			max_mov_count = count + 1;
		return 0;
	}
	return 0;
}

int main() {
	int T, N;
	struct TREE *fortress;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		scanf("%d %d %d", &(castle[0].x), &(castle[0].y), &(castle[0].r));
		fortress = (struct TREE *)calloc(1, sizeof(struct TREE));
		fortress->wall = castle[0];
		for (int i = 1; i < N; i++) {
			scanf("%d %d %d", &(castle[i].x), &(castle[i].y), &(castle[i].r));
			solve(fortress, castle[i], 0);
		}
		printf("%d\n", max_mov_count);
		max_mov_count = 0;
	}
	return 0;
}