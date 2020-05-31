#include <iostream>
#include <queue>
#include <math.h>

using namespace std;

int N;
const int MAX_DISC = 12;
vector<int> c;

int get(int state, int index) {
	return (state >> (index * 2)) & 3;
}

int set(int state, int index, int value) {
	return (state & ~(3 << (index * 2))) | (value << (index * 2));
}

int sgn(int x) {
	if (!x) 
		return 0;
	return ( x > 0 ) ? 1 : -1;
}

int incr(int x) {
	return (x<0) ? x - 1 : x + 1;
}

int bidir(int discs, int begin, int end) {
	if (begin == end) 
		return 0;

	queue<int> q;
	c = vector<int>(1 << (MAX_DISC * 2), 0);
	
	q.push(begin); 
	c[begin] = 1;
	
	q.push(end); 
	c[end] = -1;
	
	while (!q.empty()) {
		int now = q.front();
		q.pop();
		int top[4] = { -1,-1,-1,-1 };
		for (int i = discs - 1; i >= 0; --i)
			top[get(now, i)] = i;
		//  i번 -> j번
		for (int i = 0; i < 4; ++i) {
			if (top[i] != -1)
				for (int j = 0; j < 4; j++)
					if (i != j && (top[j] == -1 || top[j] > top[i])) {
						int next = set(now, top[i], j);
						//   아직 방문 x
						if (c[next] == 0) {
							c[next] = incr(c[now]);
							q.push(next);
						}
						//  center
						else if (sgn(c[next]) != sgn(c[now]))
              return abs(c[next]) + abs(c[now]) - 1;
					}
		}
	}
	return -1;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		cin >> N;
		int num, n;
		int first = 0;
		int end = pow(2, 2 * N) - 1;
		for (int i = 0; i<4; i++) {
			cin >> num;
			for (int j = 0; j<num; j++) {
				cin >> n;
				first = set(first, n - 1, i);
			}
		}
		cout << bidir(N, first, end) << endl;
	}
	return 0;
}
