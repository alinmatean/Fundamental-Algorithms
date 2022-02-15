/**
Alin Matean
grupa 30228

Statistici dinamice de ordine

OS_SELECT -> returneaza al i-lea cel mai mic element din arbore
OS_DELETE -> sterge al i-lea element din arbore

Complexitatea OS_SELECT si OS_DELETE este O(logn), pe care o repetam de n ori in fiecare caz => O(nlogn)

*/

#include <iostream>
#include "Profiler.h"

Profiler p("profiler");

using namespace std;

struct Node {
	int key;
	int size;
	struct Node* left;
	struct Node* right;
};

Node* createNode(int v, int s)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = v;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->size = s;
	return newNode;
}

Node* buildTree(int A[], int start, int end)
{
	if (start > end)
		return NULL;
	else {
		int mid = (start + end) / 2;
		//printf("%d\n", A[mid]);
		Node* newNode = createNode(A[mid], end - start + 1);
		//printf("%d\n", newNode->size);
		newNode->left = buildTree(A, start, mid-1);
		newNode->right = buildTree(A, mid + 1, end);
		//newNode->size = 1 + (newNode->left->size) + (newNode->right->size);
		return newNode;
	}

}

void prettyPrint(Node* nod, int nivel)
{
	if (nod == NULL)
		return;
	prettyPrint(nod->right, nivel + 1);
	cout << endl;
	int m = nivel;
	while (m) {
		cout << "          ";
		m--;
	}
	cout << nod->key << " / size:" << nod->size << endl;
	prettyPrint(nod->left, nivel+1);
}

Node* OS_SELECT(Node* x, int i, int n)
{
	Operation op = p.createOperation("OS_Select", n);
	int r;
	op.count();
	if (x->left == NULL)
		r = 1;
	else {
		op.count();
		r = x->left->size + 1;
	}
	if (i == r)
		return x;
	else
		if (i < r) {
			//op.count();
			return OS_SELECT(x->left, i, n);
		}
	//op.count();
	return OS_SELECT(x->right, i - r, n);

}

Node* OS_DELETE(Node* x, int i, int n)
{
	Operation op = p.createOperation("OS_Delete", n);
	int r;
	op.count();
	if (x->left == NULL)
		r = 1;
	else
		r = x->left->size + 1;

	if (i == r) {
		op.count();
		if (x->left == NULL && x->right == NULL)
			return NULL;
		op.count();
		if (x->right == NULL)
			return x->left;
		op.count();
		if (x->left == NULL)
			return x->right;

		op.count(4);
		Node* succesor = OS_SELECT(x->right, 1, n);
		x->key = succesor->key;
		x->size--;
		x->right = OS_DELETE(x->right, 1, n);
	}
	else if (i < r) {
		op.count(2);
		x->size--;
		x->left = OS_DELETE(x->left, i, n);
	}
	else {
		op.count(2);
		x->size--;
		x->right = OS_DELETE(x->right, i - r, n);
	}
	return x;
}


void demo()
{
	int a[11] = { 1,6,7,11,14,16,18,20,21,24,28 };
	int n = 11;
	Node* nod = buildTree(a, 0, 10);
	prettyPrint(nod, 0);
	int k = 7;
	Node* p = OS_SELECT(nod, k, 11);

	cout << endl;
	cout << "Al "<< k <<"-lea cel mai mic: "<< p->key;
	prettyPrint(nod, 0);
	OS_DELETE(nod, 7, n);
	OS_DELETE(nod, 3, n);
	OS_DELETE(nod, 9, n);
	cout <<"----------------------------------------------" <<"\n\n\n";
	prettyPrint(nod, 0);

}

void countOp()
{
	int a[10005];

	for (int k = 0; k < 5; k++) {
		for (int n = 100; n <= 10000; n += 100) {
			printf("%d\n", n);
			FillRandomArray(a, n, 1, 50000, true, ASCENDING);
			Node* nod = buildTree(a, 0, n);
			int m = n;
			for (int i = 0; i<n;i++)
			{
				int x = rand() % m + 1;
				m--;
				//cout << i <<":" <<x << endl;
				Node* p = OS_SELECT(nod, x, n);
				OS_DELETE(nod, x, n);
			}
		
		}

	}

	p.divideValues("OS_Select", 5);
	p.divideValues("OS_Delete", 5);
	p.createGroup("OS_Select vs OS_Delete", "OS_Select", "OS_Delete");
	p.showReport();

}

int main()
{
	//demo();
	//countOp();
	
	return 0;
}