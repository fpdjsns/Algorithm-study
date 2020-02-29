#include <stdio.h>
#include <queue>
#define INF 100000
using namespace std;

int tree[400000];
int max_tree[400000];
int h[100000];

int init(int tree[], int arr[], int left, int right, int node) {
	if (left == right) {
		return tree[node] = arr[left];
	}
	int mid = (left + right) / 2;
	int left_min = init(tree, arr, left, mid, node * 2);
	int right_min = init(tree, arr, mid + 1, right, node * 2 + 1);
	return tree[node] = min(left_min, right_min);
}

int query(int tree[], int left, int right, int node, int node_left, int node_right) {
	if (right < node_left || left > node_right) {
		return INF;
	}
	if (left <= node_left && node_right <= right) {
		return tree[node];
	}

	int mid = (node_left + node_right) / 2;
	return min(query(tree, left, right, node * 2, node_left, mid),
		query(tree, left, right, node * 2 + 1, mid + 1, node_right));
}

int update(int tree[], int index, int value, int node, int node_left, int node_right) {
	if (index < node_left || node_right < index) {
		return tree[node];
	}
	if (node_left == node_right)
		return tree[node] = value;
	int mid = (node_left + node_right) / 2;
	return tree[node] = min(update(tree, index, value, node * 2, node_left, mid),
		update(tree, index, value, node * 2 + 1, mid + 1, node_right));
}

void solve() {
	int ret;
	int n, q;
	int a, b;

	scanf("%d %d", &n, &q);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &h[i]);
	}
	init(tree, h, 0, n - 1, 1);

	for (int i = 0; i < n; ++i) {
		h[i] = (-1)*h[i];
	}
	init(max_tree, h, 0, n - 1, 1);

	while (q--) {
		ret = 0;
		scanf("%d %d", &a, &b);
		ret = (-1) * query(tree, a, b, 1, 0, n - 1) + (-1) * query(max_tree, a, b, 1, 0, n - 1);
		printf("%d\n", ret);
	}
	
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}