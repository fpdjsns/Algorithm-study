/*
 *  Date : 2020.04.12
 *  Language : C++
 *  Complexity : O(N)
 *  Data Structure :
 *  Algorithm : Euler Circuit/Trail
 *
 *  Problem : https://www.algospot.com/judge/problem/read/WORDCHAIN
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

const int MAX = 30;


//�׷����� ���� ���
vector<vector<int>> adj;

//graph[i][j]=i�� �����ؼ� j�� ������ �ܾ��� ���
vector<string> graph[MAX][MAX];

//indegree[i] = i�� �����ϴ� �ܾ��� ��
//outdegree[i] = i�� ������ �ܾ��� ��
vector<int> indegree, outdegree;

void makeGraph(const vector<string> &words)
{
	//���� ���� �ʱ�ȭ
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			graph[i][j].clear();

	adj = vector<vector<int>>(MAX, vector<int>(MAX, 0));
	indegree = outdegree = vector<int>(MAX, 0);

	//�� �ܾ �׷����� �߰�
	for (int i = 0; i < words.size(); i++)
	{
		int a = words[i][0] - 'a';
		int b = words[i][words[i].size() - 1] - 'a';

		graph[a][b].push_back(words[i]);
		adj[a][b]++;
		outdegree[a]++;
		indegree[b]++;
	}
}

//directed �׷����� ���� ��� adj�� �־��� �� ���Ϸ� ��Ŷ Ȥ�� Ʈ���� ���
void getEulerCircuit(int here, vector<int> &circuit)
{
	for (int there = 0; there < adj.size(); there++)
		while (adj[here][there] > 0)
		{
			adj[here][there]--; //������ �����
			getEulerCircuit(there, circuit);
		}
	circuit.push_back(here);
}

//���� �׷����� ���Ϸ� Ʈ�����̳� ��Ŷ�� ��ȯ�Ѵ�
vector<int> getEculterTrailOrCircuit(void)
{
	vector<int> circuit;
	//�켱 Ʈ������ ã�ƺ���: �������� �����ϴ� ���

	for (int i = 0; i < MAX; i++)
		if (outdegree[i] == indegree[i] + 1)
		{
			getEulerCircuit(i, circuit);
			return circuit;
		}

	//�ƴϸ� ��Ŷ�̴�, ������ ������ �ƹ� ���������� ����
	for (int i = 0; i < MAX; i++)
		if (outdegree[i])
		{
			getEulerCircuit(i, circuit);
			return circuit;
		}

	//��� ������ ��� �� �迭 ��ȯ
	return circuit;
}

//���� �׷����� ���Ϸ� ��Ŷ/Ʈ���� ���� ���� Ȯ��
bool checkEuler(void)
{
	//���� �������� ������ ��
	int plus1 = 0, minus1 = 0;
	for (int i = 0; i < MAX; i++)
	{
		int delta = outdegree[i] - indegree[i];
		//��� ������ ������ -1, 1, �Ǵ� 0�̿����Ѵ�
		if (delta < -1 || delta > 1)
			return false;
		if (delta == 1)
			plus1++;
		if (delta == -1)
			minus1++;
	}

	//�������� ������ �� �ϳ��� �ְų� �ϳ��� ����� �Ѵ�
	return (plus1 == 1 && minus1 == 1) || (plus1 == 0 && minus1 == 0);
}

string solve(const vector<string> &words)
{
	makeGraph(words);

	//������ ���� ������ ����
	if (!checkEuler())
		return "IMPOSSIBLE";

	//���Ϸ� ��Ŷ�̳� ��θ� ã�Ƴ���
	vector<int> circuit = getEculterTrailOrCircuit();

	//��� ������ �湮���� �������� ����
	if (circuit.size() != words.size() + 1)
		return "IMPOSSIBLE";

	//�湮 ������ ������ �� �������� ��� ���ڿ��� ����� ��ȯ
	reverse(circuit.begin(), circuit.end());

	string result;
	for (int i = 1; i < circuit.size(); i++)
	{
		int a = circuit[i - 1], b = circuit[i];
		if (result.size())
			result += " ";
		result += graph[a][b].back();
		graph[a][b].pop_back();
	}
	return result;
}

int main(void)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int test_case;

	cin >> test_case;

	for (int t = 0; t < test_case; t++)
	{
		int N;
		cin >> N;
		vector<string> words(N);

		for (int i = 0; i < N; i++)
			cin >> words[i];

		cout << solve(words) << "\n";
	}
	return 0;
}