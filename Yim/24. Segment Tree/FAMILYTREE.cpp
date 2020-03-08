#include <stdio.h>
#include <queue>
#define INF 100000
using namespace std;

int tree[400000];
int no2serial[100000];
int serial2no[100000];
int depth[100000];
int index[100000];
vector<int> child[100000];
int serial;
int N;
int trip_size = 0;

int init(int tree[], const vector<int> &arr, int left, int right, int node) {
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

//깊이가 d인 노드 here 이하를 전위 탐색(preorder Traversal)
void traverse(int here, int d, vector<int> &trip)
{

	//traverse()가 처음 방문하자마자 일렬 번호를 부여
	no2serial[here] = serial;
	serial2no[serial] = here;
	serial++;

	//깊이 계산
	depth[here] = d;

	//trip에 현재 노드의 일렬 번호를 추가
	index[here] = trip.size();
	trip.push_back(no2serial[here]);

	//모든 자식 노드 방문
	for (int i = 0; i < child[here].size(); i++)
	{
		traverse(child[here][i], d + 1, trip);
		//자식 노드를 방문하고 현재 노드로 들어올 때마다 다시 추가
		trip.push_back(no2serial[here]);
	}

}

int getDistance(int a, int b, int arr_size) {
	int common_p; // 공통 조상
	int ix_a = index[a];
	int ix_b = index[b];
	int query_n;
	if (ix_a > ix_b)
		swap(ix_a, ix_b);
	query_n = query(tree, ix_a, ix_b, 1, 0, arr_size - 1);
	common_p = serial2no[query_n];
	return (depth[a] + depth[b] - 2 * depth[common_p]);
}

void solve() {
	vector<int> trip;
	serial = 0;
	traverse(0, 0, trip);
	trip_size = trip.size();
	init(tree, trip, 0, trip_size - 1, 1);
}
int main() {
	int T;
	int Q;
	int parent, a, b;

	scanf("%d", &T);
	while (T--) {
		for (int j = 0; j < 100000; j++)
			child[j].clear();
		scanf("%d %d", &N, &Q);
		for (int i = 1; i < N; ++i) {
			scanf("%d", &parent);
			child[parent].push_back(i);
		}
		solve();
		for (int i = 0; i < Q; ++i) {
			scanf("%d %d", &a, &b);
			printf("%d\n", getDistance(a, b, trip_size));
		}
	}
	return 0;
}