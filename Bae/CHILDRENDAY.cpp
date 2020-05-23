/**
 * problem : https://algospot.com/judge/problem/read/CHILDRENDAY
 * algorithm : BFS
 * time complexity : O(2N * |d|)
 */
 
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <map>
#include <set>

using namespace std;

// now 정점에서 edge 간선을 타고 갔을때 나오는 정점
int append(int now, int edge, int mod) {
	int next = now * 10 + edge;
	int ans = next % mod;
	if (next >= mod) ans += mod;
	return ans;
}

// digits에 속한 숫자들만으로 구성되고,
// C % n == m인 최소의 C를 찾는다.
string gifts(vector<int> digits, int n, int m) {
	// 간선의 번호를 오름차순으로 정렬해 두면 
	// 사전순으로 가장 앞에 있는 경로를 찾을 수 있다.
	sort(digits.begin(), digits.end());

	/**
	흰색 정점 = 현재 숫자가 n 미만
	회색 정점 = 현재 숫자가 n 이상

	흰색 정점 i는 0 ~ n, 회색 정점 i는 n ~ 2n - 1로 표현
	parent[i] = BFS 스패닝 트리에서 정점 i의 부모
	choice[i] = parent[i] 에서 i로 연결된 간선의 번호
	*/
	vector<int> parent(2 * n, -1), choice(2 * n, -1);
	queue<int> q;

	// 흰색 0번을 큐에 추가
	parent[0] = 0;
	q.push(0);

	while (!q.empty()) {
		int now = q.front();
		q.pop();

		for (int i = 0; i < digits.size(); i++) {
			// 간선 digits[i] 방문
			int next = append(now, digits[i], n);
			if (parent[next] >= 0) continue;

			parent[next] = now;
			choice[next] = digits[i];
			q.push(next);
		}
	}

	// 회색 m번에 도달하지 못했으면 실패
	if (parent[n + m] == -1) 
		return "IMPOSSIBLE";
	
	// 부모로 가는 연결을 따라가면서 C를 계산
	string ret;
	int now = n + m;
	while (parent[now] != now) {
		ret += (char)('0' + choice[now]);
		now = parent[now];
	}

	// 역순
	reverse(ret.begin(), ret.end());
	return ret;

}

int main() {
	int C;
	cin >> C;
	while (C--) {
		string D;
		int N, M;
		cin >> D >> N >> M;
		vector<int> digits(D.size());
		for (int i = 0; i < D.size(); i++)
			digits[i] = D[i]-'0';
		cout << gifts(digits, N, M) << endl;
	}
	return 0;
}
