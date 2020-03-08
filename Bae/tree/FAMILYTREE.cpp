/**
 * problem : https://algospot.com/judge/problem/read/FAMILYTREE
 * 최선을 다했지만 정답이 나오지 않는다..
 */

#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <iostream>

using namespace std;

class SegmentTree {
private:
	const int ROOT = 1;
	const int MIN = 0;
	const int MAX = 20001;
	int N;
	vector<int> heights;

	// index 1부터 시작 
	vector<int> nodes;

	int init(int ind, int s, int e) {
		if (s == e) // 단노드
			return nodes[ind] = heights[s - 1];

		int m = (s + e) / 2;
		int left = init(2 * ind, s, m);
		int right = init(2 * ind + 1, m + 1, e);
		return nodes[ind] = min(left, right);
	}

	void init() {
		N = heights.size();
		int h = (int)ceil(log2(N));

		nodes = vector<int>(1 << (h + 1), MAX);
		init(ROOT, 1, N);
	}

	int question(int ind, int s, int e, int a, int b) {

		if (b < s || a > e) return MAX; // 범위 벗어남
		if (a <= s && b >= e) return nodes[ind]; // [s,e]가 [a,b]에 완전 포함

		int m = (s + e) / 2;
		int left = question(2 * ind, s, m, a, b);
		int right = question(2 * ind + 1, m + 1, e, a, b);
		return min(left, right);
	}


public:
	SegmentTree() {};
	SegmentTree(vector<int> heights) {
		this->heights = heights;
		init();
	}

	int question(int a, int b) {
		return question(ROOT, 1, N, a, b);
	}
};


class Solve {

	int N;
	vector<vector<int>> edges;
	vector<int> p;

	int find(int n) {
		if (p[n] == -1)
			return n;
		return p[n] = find(p[n]);
	}

	int merge(int a, int b) {
		a = find(a);
		b = find(b);
		if (a != b)
			p[b] = a;
		return p[b];
	}

	void init(vector<int> arr, vector<vector<int>> eds) {
		int N = arr.size();
		tree = vector<int>(N, 0);
		depth = vector<int>(N, 0);
		edges = vector<vector<int>>(N);
		p = vector<int>(N, -1);
		vector<int> indexes(N, 0);
		queue<pair<int, int>> q;
		q.push({ 0, 0 }); // (index, depth)
		int ind = 0;
		while (!q.empty()) {
			int p = q.front().first;
			int d = q.front().second;

			indexes[p] = ind;
			depth[ind++] = d; // set depth
			q.pop();
			for (int i = 0; i < eds[p].size(); i++) {
				q.push({ eds[p][i], d + 1 });
			}
		}
		for (int i = 0; i < N; i++) {
			tree[indexes[i]] = indexes[arr[i]]; // setTree
			
			// setEdges
			for (int j = 0; j < eds[i].size(); j++) {
				edges[indexes[i]].push_back(indexes[eds[i][j]]);
				merge(indexes[i], indexes[eds[i][j]]);
			}
		}
	}

public:
	vector<int> tree;
	vector<int> depth;
	/**
	* 부모 노드가 번호가 더 크게 재배치 후 부모 노드를 tree에 저장
	* depth 배열 세팅
	*/
	Solve(vector<int> arr) {
		N = arr.size();
		vector<vector<int>> edges(N);
		for (int i = 1; i < N; i++) {
			int p = arr[i];
			edges[p].push_back(i);
		}
		init(arr, edges);
	}

	int getParent(int a, int b) {
		return merge(a, b);
	}
};



int main() {
	int C;
	cin >> C;
	while (C--) {
		int N; cin >> N;
		int	Q; cin >> Q;
		vector<int> arr(N, 0);
		for (int i = 1; i < N; i++) {
			cin >> arr[i];
		}
		Solve solve = Solve(arr);
		SegmentTree st = SegmentTree(solve.depth);
		int a, b;
		for (int i = 0; i < Q; i++) {
			scanf("%d %d", &a, &b);
			if (a > b) {
				int tmp = a;
				a = b;
				b = tmp;
			}
			int pDepth = st.question(a, b);
			int ans = solve.depth[a] + solve.depth[b] - 2 * solve.depth[pDepth];
			printf("%d\n", ans);
		}
	}
	return 0;
}
