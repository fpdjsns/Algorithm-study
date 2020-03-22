#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
int C, N, M;

struct UnionFind {
	vector<int> parent, rank, size, enemy; // ����� �θ� ���, Ʈ���� ��ũ, Ʈ���� ũ��, ��������� ������ ��Ʈ
	UnionFind(int n) : parent(n), rank(n, 0), enemy(n, -1), size(n, 1) {
		for (int i = 0; i < n; i++) parent[i] = i;
	}
	//��Ʈ�� ã�´�.
	int find(int u) {
		if (parent[u] == u) return u;
		return parent[u] = find(parent[u]);
	}
	//u�� v�� ���ļ� ��Ʈ��ȣ�� ��ȯ
	int merge(int u, int v) {
		//�������� ��� ������ ��ȯ
		if (u == -1 || v == -1) return max(u, v);
		u = find(u), v = find(v);
		//��Ʈ�� ���� ���
		if (u == v) return u;
		if (rank[u] > rank[v]) swap(u, v);
		if (rank[u] == rank[v]) rank[v]++;
		//��ũ�� ���� ��带 �� �������� ��ģ��.
		parent[u] = v;
		size[v] += size[u];
		return v;
	}

	//u�� v�� ���� ���ΰ�.
	bool dis(int u, int v) {
		u = find(u), v = find(v);
		if (u == v) return false; //���� ������� ����
		//���� ���� ����
		int a = merge(u, enemy[v]), b = merge(v, enemy[u]);
		enemy[a] = b, enemy[b] = a;
		return true;
	}
	bool ack(int u, int v) {
		u = find(u), v = find(v);
		if (enemy[u] == v) return false;
		//������ ���� ���� ��
		int a = merge(u, v), b = merge(enemy[u], enemy[v]);
		enemy[a] = b;
		if (b != -1) enemy[b] = a;
		return true;
	}
};

int maxParty(const UnionFind t) {
	int res = 0;
	for (int node = 0; node < N; node++) {
		if (t.parent[node] == node) {
			int enemy = t.enemy[node];

			//���� ������ �� �� �̻� ���� �������� �� ��츸 ����.
			if (enemy > node) continue;

			int Size = t.size[node];
			int enemySize = (enemy == -1 ? 0 : t.size[enemy]);
			res += max(Size, enemySize);
		}
	}
	return res;
}

int main()
{
	scanf("%d", &C);
	while (C--) {
		scanf("%d %d", &N, &M);
		UnionFind t(N);
		bool makeSense = true;
		int resLine = 0;
		for (int j = 0; j < M; j++) {
			char str[5];
			int n, m;
			scanf("%s %d %d", str, &n, &m);
			if (!makeSense) continue;
			if (str[0] == 'A') {
				if (!t.ack(n, m)) {
					makeSense = false;
					resLine = j + 1;
				}
			}
			else {
				if (!t.dis(n, m)) {
					makeSense = false;
					resLine = j + 1;
				}
			}
		}
		if (makeSense)
			printf("MAX PARTY SIZE IS %d\n", maxParty(t));
		else
			printf("CONTRADICTION AT %d\n", resLine);
	}
}