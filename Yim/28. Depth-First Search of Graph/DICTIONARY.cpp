/*
 *  Date : 2020.04.12
 *  Language : C++
 *  Complexity : O(NL)
 *  Data Structure :
 *  Algorithm : DFS
 *
 *  Problem : https://www.algospot.com/judge/problem/read/DICTIONARY
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 26 + 1;


//���ĺ��� �� ���ڿ� ���� ���� ���
//����(i, j)�� ���ĺ� i�� j���� �տ� �;� ���� ��Ÿ��
vector<vector<int>> alphabet;
vector<int> seen, order;

void makeGraph(const vector<string> &words)
{
	alphabet = vector<vector<int>>(26, vector<int>(26, 0));

	for (int j = 1; j < words.size(); j++)
	{
		int i = j - 1;
		int len = min(words[i].size(), words[j].size());

		//word[i]�� word[j] �տ� ���� ������ ã�´�
		for (int k = 0; k < len; k++)
			if (words[i][k] != words[j][k])
			{
				int a = words[i][k] - 'a';
				int b = words[j][k] - 'a';
				alphabet[a][b] = 1;

				break;
			}
	}
}

void DFS(int here)
{
	seen[here] = 1;
	for (int there = 0; there < alphabet.size(); there++)
		if (alphabet[here][there] && !seen[there])
			DFS(there);

	order.push_back(here);
}

//alphabet�� �־��� �׷����� ���������� ����� ��ȣ���Ѵ�
//�׷����� Directed Adjacent Graph�� �ƴ϶�� �� ���͸� ��ȯ
vector<int> topologicalSort(void)
{
	int N = alphabet.size();

	seen = vector<int>(N, 0);
	order.clear();

	for (int i = 0; i < N; i++)
		if (!seen[i])
			DFS(i);

	reverse(order.begin(), order.end());

	//���� �׷����� DAG�� �ƴ϶�� ���� ����� ������ ������ �ִ�
	for (int i = 0; i < N; i++)
		for (int j = i + 1; j < N; j++)
			if (alphabet[order[j]][order[i]])
				return vector<int>();

	//����Ŭ�� ���� ����� DFS���� ���� ������ ��ȯ
	return order;
}

int main(void)
{
	int C;
	cin >> C;

	for (int t = 0; t < C; t++)
	{
		int N;
		cin >> N;

		vector<string> words(N);
		for (int i = 0; i < N; i++)
			cin >> words[i];

		makeGraph(words);
		vector<int> result = topologicalSort();

		if (result.empty())
			cout << "INVALID HYPOTHESIS";
		else
			for (int i = 0; i < result.size(); i++)
				cout << char(result[i] + 'a');
		cout << "\n";
	}
	return 0;
}

