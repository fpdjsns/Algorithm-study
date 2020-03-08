#include <stdio.h>
#include <queue>
using namespace std;

int getSeed(int seed, int a, int b) {
	return ((seed * (long long)a + b) % 20090711);
}

int solve() {
	int n, a, b, seed = 1983;
	int ret = 0;
	int temp_min, temp_max;
	priority_queue<int, vector<int>, less<int>> max_heap;
	priority_queue<int, vector<int>, greater<int>> min_heap;

	scanf("%d %d %d", &n, &a, &b);

	for (int i = 0; i < n; ++i) {
		if (min_heap.size() == max_heap.size())
			max_heap.push(seed);
		else 
			min_heap.push(seed);

		if (!min_heap.empty() && !max_heap.empty()
			&& min_heap.top() < max_heap.top()) {
			temp_min = min_heap.top();
			temp_max = max_heap.top();
			min_heap.pop();
			max_heap.pop();
			min_heap.push(temp_max);
			max_heap.push(temp_min);
		}

		ret = (max_heap.top() + ret) % 20090711;
		/* generate random value */
		seed = getSeed(seed, a, b);
	}
	return ret;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		printf("%d\n", solve());
	}
	return 0;
}