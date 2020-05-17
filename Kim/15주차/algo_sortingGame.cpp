#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>

using namespace std;

map<int, int > toSort;

int toNumber(vector<int> arr) {
	int res = 0;
	int dec = 1;
	int size = arr.size();
	for (int i = 0; i < size; i++) {
		res += dec * arr[i];
		dec *= 10;
	}
	return res;
}

//[0,...,n-1]의 모든 순열에 대해 toSort[]를 계산해 저장한다.
void precalc(int n) {
	vector<int> perm(n);
	for (int i = 0; i < n; i++) {
		perm[i] = i;
	}
	
	queue<vector<int> > q;
	q.push(perm);
	int permNum = toNumber(perm);
	toSort[permNum] = 0;

	while (!q.empty()) {
		vector<int> here = q.front();
		q.pop();
		int hereNum = toNumber(here);
		int cost = toSort[hereNum];
		for (int i = 0; i < n; i++) {
			for (int j = i + 2; j <= n; j++) {
				reverse(here.begin() + i, here.begin() + j);
				hereNum = toNumber(here);
				if (toSort.count(hereNum) == 0) {
					toSort[hereNum] = cost + 1;
					q.push(here);
				}
				reverse(here.begin() + i, here.begin() + j);
			}
		}
	}
}
int sortingGame(const vector<int>& perm) {
	//perm 을 [0,...,n-1]의 순열로 변환한다.
	int n = perm.size();
	vector<int> fixed(8);
	for (int i = 0; i < n; i++) {
		int smaller = 0;
		for (int j = 0; j < n; j++) {
			if (perm[j] < perm[i]) {
				smaller++;
			}
		}
		fixed[i] = smaller;
	}

	for (int i = n; i < 8; i++) {
		fixed[i] = i;
	}

	int fixedNum = toNumber(fixed);
	return toSort[fixedNum];
}


void solve() {
	int N;
	cin >> N;

	vector<int> arr(N, 0);
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	cout << sortingGame(arr) << endl;
}

int main() {
	int testCase;
	scanf("%d", &testCase);

	//미리 한번만 돌림
	precalc(8);
	
	for (int i = 0; i < testCase; i++) {
		solve();
	}
}

