#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <map>

using namespace std;

map<vector<int>, int> costMap;

void precalc(int n) {

	queue<vector<int>> q;
	vector<int> v(n);
	for (int i = 0; i < n; i++)
		v[i] = i;
	costMap[v] = 0;
	q.push(v);
	int c;

	while (!q.empty()){
		v = q.front();
		q.pop();
		c = costMap[v];
		for (int i = 0; i < n; i++) {
			for (int j = i + 2; j <= n; j++) {
				reverse(v.begin() + i, v.begin() + j);
				if (costMap.count(v) == 0) {
					q.push(v);
					costMap[v] = c + 1;
				}
				reverse(v.begin() + i, v.begin() + j);
			}
		}
	}
}

int solve(vector<int> arr) {
	int n = arr.size();
	precalc(n);
	vector<int> sorted = arr;
	sort(sorted.begin(), sorted.end());
	map<int, int> tmpMap;
	for (int i = 0; i < n; i++) {
		tmpMap[sorted[i]] = i;
	}
	for (int i = 0; i < arr.size(); i++) {
		arr[i] = tmpMap[arr[i]];
	}
	return costMap[arr];
}

int main() {
	int C, N;
	cin >> C;
	while (C--) {
		cin >> N;
		vector<int> arr(N);
		for (int i = 0; i < N; i++) cin >> arr[i];
		cout << solve(arr) << endl;
	}
	return 0;
}
