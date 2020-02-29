#include <stdio.h>
#include <random>

using namespace std;
typedef int KeyType;

int n;
int shift[50000];
int arr[50000];

struct Node {
	KeyType key;
	int priority, size;
	Node *left, *right;
	Node(const KeyType& _key) : key(_key), priority(rand()),
		size(1) ,left(NULL), right(NULL) {} 
	void setLeft(Node* newLeft) {
		left = newLeft;
		calcSize();
	}
	void setRight(Node* newRight) {
		right = newRight;
		calcSize();
	}

	void calcSize() {
		size = 1;
		if (left) size += left->size;
		if (right) size += right->size;
	}
};

typedef pair<Node*, Node*> NodePair;
// root�� ��Ʈ�� �ϴ� Ʈ���� key �̸��� ���� �̻��� ���� ����
// �ΰ��� Ʈ������ �и�
NodePair split(Node* root, KeyType key) {
	if (root == NULL) return NodePair(NULL, NULL);
	// ��Ʈ�� key �̸��̸� ������ ����Ʈ���� �ɰ���.
	if (root->key < key) {
		NodePair rs = split(root->right, key);
		root->setRight(rs.first);
		return NodePair(root, rs.second);
	}
	// ��Ʈ�� key�̻��̸� ���� ����Ʈ���� �ɰ���.
	NodePair ls = split(root->left, key);
	root->setLeft(ls.second);
	return NodePair(ls.first, root);
}

// root�� ��Ʈ�� �ϴ� Ʈ���� �� ��� node�� ������ �� ��� Ʈ����
// ��Ʈ�� ��ȯ�Ѵ�.
Node* insert(Node* root, Node* node) {
	if (root == NULL) return node;
	// node�� ��Ʈ�� ��ü�ؾ� �Ѵ�. �ش� ����Ʈ���� ������ �߶�
	// ���� �ڼ����� �Ѵ�.
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

// a�� b�� �ΰ��� Ʈ���̰� max(a) < min(b) �϶� �� ���� ��ģ��.
Node* merge(Node *a, Node* b) {
	if (a == NULL) return b;
	if (b == NULL) return a;
	if (a->priority < b->priority) {
		b->setLeft(merge(a, b->left));
		return b;
	}
	a->setRight(merge(a->right, b));
	return a;
}

Node* erase(Node *root, KeyType key) {
	if (root == NULL) return root;
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

Node* kth(Node* root, int k) {
	int leftsize = 0;
	if (root->left != NULL)
		leftsize = root->left->size;
	if (k <= leftsize) return kth(root->left, k);
	if (k == leftsize + 1) return root;
	return kth(root->right, k - leftsize - 1);
}
void solve(int n) {
	Node* num = NULL;
	for (int i = 0; i < n; ++i)
		num = insert(num, new Node(i + 1));
	for (int i = n - 1; i >= 0; --i) {
		int large = shift[i];
		Node* k = kth(num, i + 1 - large);
		arr[i] = k->key;
		num = erase(num, k->key);
	}
	for (int i = 0; i < n; ++i)
		printf("%d ", arr[i]);
}

int main() {
	int T, N;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		for (int i = 0; i < N; ++i) {
			scanf("%d", &shift[i]);
		}
		solve(N);
	}
	system("pause");
}