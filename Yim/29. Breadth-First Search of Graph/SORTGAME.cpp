/*
 *  Date : 2020.05.17
 *  Language : C++
 *  Complexity : O(1)
 *  Data Structure :
 *  Algorithm :
 *
 *  Problem : https://www.algospot.com/judge/problem/read/SORTGAME
 */
#include <stdio.h>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

int arr[8];
queue<vector<int> > q;
vector<int> sorted(8);
map<vector<int>, int> m;

void precalc(int n) {
	int dist = 0;
	vector<int> cur;
	sorted.resize(n);

	for (int i = 0; i < n; ++i)
		sorted[i] = i + 1;
	m[sorted] = 0;
	q.push(sorted);

	while (!q.empty()) {
		cur = q.front();
		q.pop();
		dist = m[cur];
		for (int i = 0; i < n; ++i) {
			for (int j = i + 2; j <= n; ++j) {
				reverse(cur.begin() + i, cur.begin() + j);
				if (m.count(cur) == 0) {
					m[cur] = dist + 1;
					q.push(cur);
				}
				reverse(cur.begin() + i, cur.begin() + j);
			}
		}
	}
}

void solve(int n) {
	int ret;
	int cnt;
	int temp[8];
	int k = 0;
	int ix = 0;
	vector<int> small_arr(n);

	for (int i = 0; i < n; ++i) {
		ix = 0;
		for (int j = 0; j < n; ++j) {
			if (arr[i] > arr[j])
				ix++;
		}
		small_arr[i] = ix + 1;
	}
	printf("%d\n", m[small_arr]);
	return;
}
int main() {
	int tc;
	int n;
	scanf("%d", &tc);
	while (tc--) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i)
			scanf("%d", &arr[i]);
		precalc(n);
		solve(n);
	}
}