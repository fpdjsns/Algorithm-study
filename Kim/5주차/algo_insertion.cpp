
//
//  algo_insertion.cpp
//  알고리즘 문제해결전략 - 삽입정렬 뒤집기 
//
//  Created by Hubring on 2020. 2. 20.
//  Copyright © 2020년 Hubring. All rights reserved.
//  시간복잡도 O(NlogN)


#include<stdio.h>
#include<iostream>
#include<cassert>
#include<algorithm>

using namespace std;

typedef int KeyType;

struct Node {
	//노드에 저장된 원소
	KeyType key;
	int priority, size;
	Node *left, *right;

	Node(const KeyType _key) : key(_key), priority(rand()), size(1), left(NULL), right(NULL) {}

	void setLeft(Node* newLeft) { left = newLeft; calcSize(); }
	void setRight(Node* newRight) { right = newRight; calcSize(); }

	void calcSize() {
		size = 1;
		if (left) size += left->size;
		if (right) size += right->size;
	}
};


typedef pair<Node*, Node*> NodePair;

// root 를 루트로 하는 트립을 key 미만의 값과 이상의 값을 갖는
// 두 개의 트립으로 분리한다.
NodePair split(Node* root, KeyType key) {
	if (root == NULL) return NodePair(NULL, NULL);
	// 루트가 key 미만이면 오른쪽의 일부를 잘라낸다
	if (root->key < key) {
		NodePair rs = split(root->right, key);
		root->setRight(rs.first);
		return NodePair(root, rs.second);
	}
	// 루트가 key 이상이면 왼쪽의 일부를 잘라낸다
	NodePair ls = split(root->left, key);
	root->setLeft(ls.second);
	return NodePair(ls.first, root);
}

// root 를 루트로 하는 트립에 새 노드 node 를 삽입한 뒤 결과 트립의
// 루트를 반환한다.
Node* insert(Node* root, Node* node) {
	if (root == NULL) return node;
	// node 가 루트를 대체해야 한다: 해당 서브트립을 반으로 잘라
	// 각각 자손으로 한다
	if (root->priority < node->priority) {
		NodePair splitted = split(root, node->key);
		node->setLeft(splitted.first);
		node->setRight(splitted.second);
		return node;
	}
	else if (node->key < root->key)
		root->setLeft(insert(root->left, node));
	else
		root->setRight(insert(root->right, node));
	return root;
}

// a 와 b 가 두 개의 트립이고, max(a) < min(b) 일때 이 둘을 합친다
Node* merge(Node* a, Node* b) {
	if (a == NULL) return b;
	if (b == NULL) return a;

	if (a->priority < b->priority) {
		b->setLeft(merge(a, b->left));
		return b;
	}
	a->setRight(merge(a->right, b));
	return a;
}

// root 를 루트로 하는 트립에서 key 를 지운다
Node* erase(Node* root, KeyType key) {
	if (root == NULL) return root;
	// root 를 지우고 양 서브트립을 합친 뒤 반환한다
	if (root->key == key) {
		Node* ret = merge(root->left, root->right);
		delete root;
		return ret;
	}
	if (key < root->key)
		root->setLeft(erase(root->left, key));
	else
		root->setRight(erase(root->right, key));
	return root;
}

// root 를 루트로 하는 트리 중에서 k번째 원소를 반환한다
Node* kth(Node* root, int k) {
	int ls = (root->left ? root->left->size : 0);
	int rs = (root->right ? root->right->size : 0);
	if (k <= ls) return kth(root->left, k);
	if (k == ls + 1) return root;
	return kth(root->right, k - ls - 1);
}


// key 보다 작은 키값의 수를 반환한다
int countLessThan(Node* root, KeyType key) {
	if (root == NULL) return 0;
	if (root->key >= key)
		return countLessThan(root->left, key);
	int ls = (root->left ? root->left->size : 0);
	return ls + 1 + countLessThan(root->right, key);
}


int n, shifted[50000];
int A[50000];

void solve() {

	cin >> n;

	for (int i = 0; i < n; i++)
		cin >> shifted[i];

	//1~N까지의 숫자를 모두 저장하는 트립을 만든다.
	Node* candidates = NULL;
	for (int i = 0; i < n; i++)
		candidates = insert(candidates, new Node(i + 1));

	//뒤에서부터 A[]를 채워나간다.
	for (int i = n - 1; i >= 0; --i) {
		//후보 중 이 수보다 큰 수가 larger개 있다.
		int larger = shifted[i];
		Node*k = kth(candidates, i + 1 - larger);
		A[i] = k->key;
		candidates = erase(candidates, k->key);
	}

	for (int i = 0; i < n; i++)
		cout << A[i] << " ";

	cout << endl;
}

int main() {
	int testCase;
	scanf("%d", &testCase);

	for (int i = 0; i < testCase; i++) {
		solve();
	}
}