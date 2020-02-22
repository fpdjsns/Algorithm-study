#include <stdio.h>
#include <algorithm>
#include <map>

using namespace std;

map<int, int> coords;

bool isDominated(int x, int y) {
	map<int, int>::iterator it = coords.lower_bound(x);
	if (it == coords.end()) return false;
	return it->second > y;
}

void removeDominated(int x, int y) {
	map<int, int>::iterator it = coords.lower_bound(x);
	if (it == coords.begin()) return;
	--it;
	// it : (x,y)의 바로 왼쪽에 있는 점
	while (true) {
		if (it->second > y) break;
		if (it == coords.begin()) {
			coords.erase(it);
			break;
		}
		else {
			map<int, int>::iterator jt = it;
			jt--;
			coords.erase(it);
			it = jt;

		}
	}
}

int addParticipant(int p, int q) {
	// (x,y)가 추가되었을때
	if (isDominated(p, q)) return coords.size();
	// 기존에 있던 점들 중 (x, y)보다 작은 점들 지움
	removeDominated(p, q);
	coords[p] = q;
	return coords.size();
}

int solve(int n) {
	int  p, q, ret = 0;
	for (int i = 0; i < n; ++i) {
		scanf("%d %d", &p, &q);
		ret += addParticipant(p, q);
	}
	return ret;
}
int main() {
	int T, N;

	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		printf("%d\n", solve(N));
		coords.clear();
	}
	system("pause");
	return 0;
}