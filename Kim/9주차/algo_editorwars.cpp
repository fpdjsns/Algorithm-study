
//
//  algo_editorwars.cpp
//  알고리즘 문제해결전략 -	 에디터 전쟁
//
//  Created by Hubring on 2020. 3. 21. 에서 4년전코드..
//  Copyright © 2020년 Hubring. All rights reserved.
//  시간복잡도 O(N+M)

#include<stdio.h>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>

#define MAX(x,y) x>y ? x : y

using namespace std;

char relation[2][5] = { "ACK", "DIS" };

int num, reply;
int parent[10001];
int ranking[10001];
int enemy[10001];
int _size[10001];

void init();
void make_set(int u);
int find_set(int u);
void swap(int* u, int* v);
int union_set(int u, int v);
bool ack(int u, int v);
bool dis(int u, int v);
int maxParty();

int main()
{
	int testcase;
	int A, B;
	int flag = 0;
	char tmp_relation[5];

	scanf("%d", &testcase);

	for (int itr = 1; itr <= testcase; itr++)
	{
		scanf("%d %d", &num, &reply);

		init();      // Initialization
		flag = 0;

		for (int cnt = 1; cnt <= reply; cnt++)
		{
			scanf("%s %d %d", tmp_relation, &A, &B);

			//make_set(A);
			//make_set(B);

			if (!strcmp(tmp_relation, relation[0]))
			{
				if (!ack(A, B) && flag == 0) flag = cnt;
			}
			else
			{
				if (!dis(A, B) && flag == 0) flag = cnt;
			}
		}
		if (flag) cout << "CONTRADICTION AT " << flag << endl;
		else
		{
			cout << "MAX PARTY SIZE IS " << maxParty() << endl;
		}
	}
	return 0;
}

void init()
{
	for (int i = 0; i <= num; i++)
	{
		parent[i] = i;
		ranking[i] = -1;
		_size[i] = 1;
		enemy[i] = -1;
	}
}

void make_set(int u)
{
	if (parent[u] != -1) return;
	parent[u] = u;
	ranking[u] = 1;
}

int find_set(int u)
{
	if (u == parent[u]) return u;
	return parent[u] = find_set(parent[u]);
}

void swap(int* u, int* v)
{
	int tmp = *u;
	*u = *v;
	*v = tmp;
}

int union_set(int u, int v)
{
	if (u == -1 || v == -1) return MAX(u, v);
	u = find_set(u);
	v = find_set(v);

	//이미 둘이 같은 트리에 속한 경우
	if (u == v) return u;

	//항상 rank[v]가 더 크므로 u를 v의 자식으로 넣는다.
	if (ranking[u] > ranking[v]) swap(&u, &v);

	if (ranking[u] == ranking[v]) ++ranking[v];
	parent[u] = v;
	_size[v] += _size[u];

	return v;
}

bool ack(int u, int v)
{
	u = find_set(u);
	v = find_set(v);

	//두 집합이 서로 적대 관계라면 모순
	if (enemy[u] == v) return false;

	int a = union_set(u, v);
	int b = union_set(enemy[u], enemy[v]);

	//동지의 적은 나의 적
	enemy[a] = b;

	//두 집합 다 적대하는 집합이 없으면 b는 -1일수 도 있다.
	if (b != -1) enemy[b] = a;

	return true;
}

bool dis(int u, int v)
{
	u = find_set(u);
	v = find_set(v);

	//둘이 같은 관계라면 모순
	if (v == u) return false;

	//적의 적은 나의 동지
	int a = union_set(u, enemy[v]);
	int b = union_set(v, enemy[u]);

	enemy[a] = b;
	enemy[b] = a;

	return true;
}

int maxParty()
{
	int ret = 0;

	for (int node = 0; node < num; ++node)
	{
		if (find_set(node) == node)
		{
			int Enemy = enemy[node];
			if (Enemy > node) continue;

			//같은 모임 쌍을 두번 세지 않기 위해, enemy < node인 경우만 센다.
			//Enemy == -1인 경우도 정확히 한 번씩 세게 된다

			int mySize = _size[node];
			int enemySize = (Enemy == -1 ? 0 : _size[Enemy]);

			//두 집합 중 큰 집합을 더한다.
			ret += MAX(mySize, enemySize);
		}
	}

	return ret;
}
