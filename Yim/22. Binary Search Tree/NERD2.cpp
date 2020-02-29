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
	// it : (x,y)�� �ٷ� ���ʿ� �ִ� ��
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
	// (x,y)�� �߰��Ǿ�����
	if (isDominated(p, q)) return coords.size();
	// ������ �ִ� ���� �� (x, y)���� ���� ���� ����
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