/*
Alin Matean
grupa 30228

Multimi disjuncte

Operatiile pe multimi disjuncte, FindSet si Union tind spre complexitate O(n), 
unde n este numarul de noduri.

*/

#include <iostream>
#include "Profiler.h"

Profiler p("profiler");

using namespace std;

struct Node {
	int key;
	int rank;
	Node* p;
};

struct Muchie {
	int u;
	int v;
	int cost;
};

Node* makeSet(int x)
{	Node* p = (Node*)malloc(sizeof(Node));
	p->key = x;
	p->p = p;
	p->rank = 0;
	return p;
}

void link(Node* x, Node* y, Operation op)
{
	op.count();
	if (x->rank > y->rank) {
		op.count();
		y->p = x;
	}
	else {
		op.count(2);
		x->p = y;
		if (x->rank == y->rank) {
			y->rank += 1;
			op.count();
		}

	}
}

Node* FindSet(Node* x, int n)
{
	Operation op = p.createOperation("FindSet", n);
	op.count();
	if (x != x->p)
	{
		op.count();
		x->p = FindSet(x->p, n);
	}
	op.count();
	return x->p;
}

void Union(Node* x, Node* y, int n)
{
	Operation op = p.createOperation("Union", n);
	link(FindSet(x, n), FindSet(y, n), op);
}

void sortEdges(Muchie** m, int n)
{
	for (int i = 1; i < n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			if (m[i]->cost > m[j]->cost) {
				Muchie* aux = m[i];
				m[i] = m[j];
				m[j] = aux;
			}
		}
	}
}

void MST_Kruskal(Muchie m[], int nrNoduri, int nrMuchii)
{
	Node** p = (Node**)malloc(nrNoduri*sizeof(Node*));
	for (int i = 0; i < nrNoduri; i++)
	{
		p[i] = makeSet(i);
	}

	for (int i = 0; i < nrMuchii; i++)
	{
		for (int j = i + 1; j < nrMuchii; j++)
		{
			if (m[i].cost > m[j].cost) {
				Muchie aux = m[i]; 
				m[i] = m[j];
				m[j] = aux;
				
			}
		}
	}
	//for (int i = 0; i < nrMuchii; i++)
		//printf("%d\n" , m[i].cost);
	for (int i = 0; i < nrMuchii; i++)
		if (FindSet(p[m[i].u], nrNoduri) != FindSet(p[m[i].v], nrNoduri)) {
			Union(p[m[i].u], p[m[i].v], nrNoduri);
			//printf("Am ales muchia dintre: %d-%d cu costul: %d\n", m[i].u, m[i].v, m[i].cost);
		}

}

void print(Node* p[], int n)
{
	for (int i = 0; i < n; i++)
		cout << "Nodul: " << p[i]->key << " are parintele: " << FindSet(p[i], n)->key << endl;
}

void demo()
{
	Node* a[10];
	for (int i = 0; i < 5; i++)
		a[i] = makeSet(i);

	for (int i = 0; i < 5; i++)
		cout << "Nodul: " << a[i]->key << endl;
	Union(a[0], a[3], 10);
	Union(a[0], a[2], 10);
	Union(a[4], a[1], 10);
	print(a, 10);
}

void demo_KruskKal()
{
	int nrNoduri = 5;			
	int nrMuchhii = 6;
	Muchie* m = (Muchie*)malloc(nrMuchhii*sizeof(Muchie));

	m[0].u = 0;
	m[0].v = 1;
	m[0].cost = 6;

	m[1].u = 1;
	m[1].v = 2;
	m[1].cost = 9;

	m[2].u = 2;
	m[2].v = 0;
	m[2].cost = 3;

	m[3].u = 2;
	m[3].v = 4;
	m[3].cost = 4;

	m[4].u = 2;
	m[4].v = 3;
	m[4].cost = 3;

	m[5].u = 3;
	m[5].v = 4;
	m[5].cost = 5;

	MST_Kruskal(m, nrNoduri, nrMuchhii);
}

void countOp()
{
	Node* a[10000];

	for (int n = 100; n <= 10000; n+=100)
	{
		printf("%d\n", n);
		int nrMuchii = n * 4;
		Muchie* m = (Muchie*)malloc(nrMuchii*sizeof(Muchie));
		for (int i = 1; i <= n; i++)
		{
			m[i-1].u = (i-1);
			m[i-1].v = i;
			m[i-1].cost = rand() % n;
			//printf("%d-%d cu costul: %d\n", m[i].u, m[i].v, m[i].cost);
		}

		for (int i = n; i <= nrMuchii; i++)
		{
			int a = rand() % n;
			int b = rand() % n;
			if ((a != b + 1) && (a!=b))
			{
				m[i-1].u = a;
				m[i-1].v = b;
				m[i-1].cost = rand() % 10000;
			}
			else {
				m[i-1].u = (a + rand() % n) % n;
				m[i-1].v = b;
				m[i-1].cost = rand()%10000;
			}

		}
		//for (int i = 0; i < nrMuchii; i++)
			//printf("%d: %d-%d cu cost: %d\n", i,m[i].u, m[i].v, m[i].cost);

		MST_Kruskal(m, n, nrMuchii);
	}
	//p.createGroup("FindSet vs Union", "FindSet", "Union");
	p.addSeries("Disjoint Sets", "FindSet", "Union");
	p.showReport();
}

int main()
{
	//demo();
	//demo_KruskKal();
	//countOp();
	return 0;
}