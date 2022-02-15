/**
Alin Matean
grupa 30228

DFS

Complexitatea algoritmului este O(V+E).

dfs_noduri si dfs_muchii au complexitate O(n).

*/
#include <iostream>
#include "Profiler.h"
#include <time.h>

Profiler p("profiler");

using namespace std;

enum {
	COLOR_WHITE = 0,
	COLOR_GRAY,
	COLOR_BLACK
};

typedef struct _Node {
	int key;
	int nrVecini;
	struct _Node** vecini;
	int color;
	bool onStack;///onStack, index, low sunt pt Tarjan
	int index;
	int low;
}Node;

typedef struct {
	int nrNodes;
	Node** u;
}Graph;

typedef struct lista {
	int key;
	lista* next;
}List;

typedef struct Stack {
	Node* key;
	struct Stack* next;
}stack;

int ind;///index pentru Tarjan

stack* add(stack* s, Node* key)
{
	stack* nod = (stack*)malloc(sizeof(stack));
	nod->key = key;
	nod->next = nullptr;
	if (s == nullptr) {
		return nod;
	}
	nod->next = s;
	return nod;
}

void insertFirst(List** head, int givenKey)
{
	List* q = (List*)malloc(sizeof(List));
	q->key = givenKey;
	q->next = NULL;
	if (*head == NULL)
	{
		*head = q;
	}
	else
	{
		q->next = *head;
		*head = q;
	}
}

void DFS_visit(Node* u, Operation op)
{
	op.count();
	u->color = COLOR_GRAY;
	for (int i = 0; i < u->nrVecini; i++)
	{
		op.count(2);
		Node* v = u->vecini[i];
		if (v->color == COLOR_WHITE) {
			op.count();
			DFS_visit(v, op);
		}
	}
	op.count();
	u->color = COLOR_BLACK;
	//printf("%d\n",u->key);
}

void DFS(Graph *graph, Operation op)
{
	for (int i = 0; i < graph->nrNodes; i++)
	{
		graph->u[i]->color = COLOR_WHITE;
	}
	for (int i = 0; i < graph->nrNodes; i++)
	{
		if (graph->u[i]->color == COLOR_WHITE)
			DFS_visit(graph->u[i], op);
	}
}

void demoDFS()
{
	Profiler p("DFS");
	Operation op = p.createOperation("dfs", 6);
	Graph graph;
	graph.nrNodes = 6;
	graph.u = (Node**)malloc(graph.nrNodes * sizeof(Node*));
	for (int i = 0; i < graph.nrNodes; i++) {
		graph.u[i] = (Node*)malloc(sizeof(Node));
	}

	for (int i = 0; i < graph.nrNodes; i++) {
		graph.u[i]->key = i;
		graph.u[i]->vecini = (Node**)malloc(5*sizeof(Node*));
	}

	graph.u[0]->nrVecini = 0;
	//graph.u[0]->vecini[0] = graph.u[1];
	
	graph.u[1]->nrVecini = 2;
	graph.u[1]->vecini[0] = graph.u[2];
	graph.u[1]->vecini[1] = graph.u[4];
	
	graph.u[2]->nrVecini = 1;
	graph.u[2]->vecini[0] = graph.u[3];
	
	graph.u[3]->nrVecini = 1;
	graph.u[3]->vecini[0] = graph.u[4];

	graph.u[4]->nrVecini = 1;
	graph.u[4]->vecini[0] = graph.u[5];

	graph.u[5]->nrVecini = 1;
	graph.u[5]->vecini[0] = graph.u[1];

	DFS(&graph, op);
}


void free_graph(Graph* graph)
{
	if (graph->u != NULL) {
		for (int i = 0; i < graph->nrNodes; ++i) {
			if (graph->u[i] != NULL) {
				if (graph->u[i]->vecini != NULL) {
					free(graph->u[i]->vecini);
					graph->u[i]->vecini = NULL;
				}
				graph->u[i]->nrVecini = 0;
				free(graph->u[i]);
				graph->u[i] = NULL;
			}
		}
		free(graph->u);
		graph->u = NULL;
	}
	graph->nrNodes = 0;
}

void DFS_grafic()
{
	Profiler p("DFS");

	for (int n = 100; n <= 4500; n += 100)
	{
		printf("%d\n", n);
		Operation op = p.createOperation("dfs-muchii", n);
		Graph graph;
		graph.nrNodes = 100;
		graph.u = (Node**)malloc(graph.nrNodes * sizeof(Node*));
		for (int i = 0; i < graph.nrNodes; i++) {
			graph.u[i] = (Node*)malloc(sizeof(Node));
		}

		for (int i = 0; i < graph.nrNodes; i++) {
			graph.u[i]->key = i;
			graph.u[i]->vecini = (Node**)malloc(100 * sizeof(Node*));
			graph.u[i]->nrVecini = 0;
		}


		for (int i = 0; i < n; i++)
		{
			int a, b;
			a = 0;
			b = 0;
			while (a == b)
			{
				a = rand() % graph.nrNodes;
				b = rand() % graph.nrNodes;
			}
			graph.u[a]->vecini[graph.u[a]->nrVecini++] = graph.u[b];
		}
		DFS(&graph, op);
		free_graph(&graph);
	}



	for (int n = 100; n <= 200; n += 10)
	{
		printf("%d\n", n);
		Operation op = p.createOperation("dfs-noduri", n);
		Graph graph;
		graph.nrNodes = n;
		graph.u = (Node**)malloc(graph.nrNodes * sizeof(Node*));
		for (int i = 0; i < graph.nrNodes; i++) {
			graph.u[i] = (Node*)malloc(sizeof(Node));
		}

		for (int i = 0; i < graph.nrNodes; i++) {
			graph.u[i]->key = i;
			graph.u[i]->vecini = (Node**)malloc(100 * sizeof(Node*));
			graph.u[i]->nrVecini = 0;
		}


		for (int i = 0; i < 4500; i++)
		{
			int a, b;
			a = 0;
			b = 0;
			while (a == b)
			{
				a = rand() % graph.nrNodes;
				b = rand() % graph.nrNodes;
			}
			graph.u[a]->vecini[graph.u[a]->nrVecini++] = graph.u[b];
		}
		DFS(&graph, op);
		free_graph(&graph);
	}

	p.showReport();
}

///Sortarea Topologica

void DFS_visitT(Node* u, List** l)
{
	u->color = COLOR_GRAY;
	for (int i = 0; i < u->nrVecini; i++)
	{
		Node* v = u->vecini[i];
		if (v->color == COLOR_GRAY) {
			cout << "Nu avem sortare topologica! Exista ciclu.";
			return;	
		}
		if (v->color == COLOR_WHITE) {
			DFS_visitT(v, l);
		}
	}
	u->color = COLOR_BLACK;
	insertFirst(l, u->key);
}

void DFST(Graph* graph, List** l)
{
	for (int i = 0; i < graph->nrNodes; i++)
	{
		graph->u[i]->color = COLOR_WHITE;
	}
	for (int i = 0; i < graph->nrNodes; i++)
	{
		if (graph->u[i]->color == COLOR_WHITE)
			DFS_visitT(graph->u[i], l);
	}
}

void demoST()
{
	Graph graph;
	graph.nrNodes = 9;
	graph.u = (Node**)malloc(graph.nrNodes * sizeof(Node*));
	for (int i = 0; i < graph.nrNodes; i++) {
		graph.u[i] = (Node*)malloc(sizeof(Node));
	}

	for (int i = 0; i < graph.nrNodes; i++) {
		graph.u[i]->key = i;
		graph.u[i]->vecini = (Node**)malloc(5 * sizeof(Node*));
	}

	graph.u[0]->nrVecini = 2;
	graph.u[0]->vecini[0] = graph.u[1];
	graph.u[0]->vecini[1] = graph.u[2];

	graph.u[1]->nrVecini = 2;
	graph.u[1]->vecini[0] = graph.u[2];
	graph.u[1]->vecini[1] = graph.u[3];

	graph.u[2]->nrVecini = 0;

	graph.u[3]->nrVecini = 1;
	graph.u[3]->vecini[0] = graph.u[4];

	graph.u[4]->nrVecini = 0;

	graph.u[5]->nrVecini = 1;
	graph.u[5]->vecini[0] = graph.u[4];

	graph.u[6]->nrVecini = 2;
	graph.u[6]->vecini[0] = graph.u[3];
	graph.u[6]->vecini[1] = graph.u[5];

	graph.u[7]->nrVecini = 1;
	graph.u[7]->vecini[0] = graph.u[2];

	graph.u[8]->nrVecini = 0;

	/*graph.u[0]->nrVecini = 0;

	graph.u[1]->nrVecini = 0;

	graph.u[2]->nrVecini = 1;
	graph.u[2]->vecini[0] = graph.u[1];

	graph.u[3]->nrVecini = 1;
	graph.u[3]->vecini[0] = graph.u[0];

	graph.u[4]->nrVecini = 2;
	graph.u[4]->vecini[0] = graph.u[0];
	graph.u[4]->vecini[1] = graph.u[1];


	graph.u[5]->nrVecini = 2;
	graph.u[5]->vecini[0] = graph.u[0];
	graph.u[5]->vecini[1] = graph.u[2];*/

	cout << "Sortarea topologica: ";
	List** st = (List**)malloc(sizeof(List*));
	DFST(&graph, st);
	
	//insertFirst(st, graph.u[3]->key);
	List** q = st;
	while (*q != NULL)
	{
		cout << (*q)->key << " ";
		*q = (*q)->next;
	}
}

///Tarjan
void scc(Node* v, stack** s)
{
	v->index = ind;
	v->low = ind;
	ind++;
	*s = add(*s, v);
	v->onStack = true;
	for (int i = 0; i < v->nrVecini; i++)
	{
		if (v->vecini[i]->index == -1)
		{
			scc(v->vecini[i], s);
			/*int min;
			if (v->low < v->vecini[i]->low)
				min = v->low;
			else
				min = v->vecini[i]->low;*/

			v->low = min(v->low, v->vecini[i]->low);
		}
		else if (v->vecini[i]->onStack) {
			/*int min;
			if (v->low < v->vecini[i]->index)
				min = v->low;
			else
				min = v->vecini[i]->index;*/

			v->low = min(v->low, v->vecini[i]->index);
		}
	}

	if (v->low == v->index)
	{
		printf("Componenta conexa: ");
		int k;
		do {
			k = (*s)->key->key;
			(*s)->key->onStack = false;
			cout << k << " ";
			*s = (*s)->next;
		} while (v->key != k);

		cout << endl;
	}
}


void tarjan(Graph* graph)
{
	ind = 0;
	stack* s = nullptr;

	for(int i = 0; i< graph->nrNodes; i++)
	{
		graph->u[i]->color = COLOR_WHITE;
		graph->u[i]->index = -1;
		graph->u[i]->onStack = false;
	}

	for (int i = 0; i < graph->nrNodes; i++)
	{
		if (graph->u[i]->index == -1)
			scc(graph->u[i], &s);
	}
}

void demoTarjan()
{
	Graph graph;
	graph.nrNodes = 9;
	graph.u = (Node**)malloc(graph.nrNodes * sizeof(Node*));
	for (int i = 0; i < graph.nrNodes; i++) {
		graph.u[i] = (Node*)malloc(sizeof(Node));
	}

	for (int i = 0; i < graph.nrNodes; i++) {
		graph.u[i]->key = i;
		graph.u[i]->vecini = (Node**)malloc(5 * sizeof(Node*));
	}

	graph.u[0]->nrVecini = 1;
	graph.u[0]->vecini[0] = graph.u[1];

	graph.u[1]->nrVecini = 2;
	graph.u[1]->vecini[0] = graph.u[2];
	graph.u[1]->vecini[1] = graph.u[4];

	graph.u[2]->nrVecini = 1;
	graph.u[2]->vecini[0] = graph.u[3];

	graph.u[3]->nrVecini = 1;
	graph.u[3]->vecini[0] = graph.u[4];

	graph.u[4]->nrVecini = 1;
	graph.u[4]->vecini[0] = graph.u[5];

	graph.u[5]->nrVecini = 2;
	graph.u[5]->vecini[0] = graph.u[1];
	graph.u[5]->vecini[1] = graph.u[8];

	graph.u[6]->nrVecini = 0;

	graph.u[7]->nrVecini = 1;
	graph.u[7]->vecini[0] = graph.u[6];

	graph.u[8]->nrVecini = 1;
	graph.u[8]->vecini[0] = graph.u[3];

	tarjan(&graph);

}

int main()
{
	srand(time(NULL));
	//demoDFS();///este in functia DFS_visit un printf pe care l-am comentat
	//DFS_grafic();
	//demoST();///sortare topologica
	//demoTarjan();///Tarjan
	return 0;
}