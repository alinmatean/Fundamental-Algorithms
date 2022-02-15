/**
Alin Matean
grupa 30228

Interclasare K liste orodonate

Complexitatea algoritmului folosind un min-heap este O(nlogk) unde n este numarul total de elemnte si k numarul listelor.
Se construieste un min heap cu adresele primelor elemente din fiecare lista, se extrage minimul si se reface strcutura
de heap, in lista din care s-a extras se trece la urmatorul element.

Daca fixam k ca fiind 5/10/100 si n variaza intre 100-10000, se observa si pe grafice ca tinde spre o complexitate liniara
O(n).

In schimb daca fixam n = 10000 si k variaza intre 10-500(op va depinde de k), tinde spre complexitate O(log k). 

Am considerat listele cu numar egal de elemente(m = n/k).

Cocluzie: se fac destul de multe operatii cand si n si k sunt mai mari(ex n = 10000 si k = 500 -> aproape 400.000 operatii), 
dar avand in vedere ca majoritate sunt pe liste, cu pointer la first si last sunt O(1)(ex: inserare),
extract-min pe min-heap din nou O(1), greutatea fiind pe refacerea structurii de heap.

*/

#include <iostream>
#include "Profiler.h"

Profiler p("profiler");

using namespace std;

typedef struct node {
    int key;
    struct node* next;
} NodeT;

void print_list(NodeT* head) {
    NodeT* p = head;
    while (p != NULL) {
        printf("%d ", p->key);
        p = p->next;
    }
    printf("\n");
}

void insert_first(NodeT** head, NodeT** tail, int givenKey) {
    NodeT* nod = (NodeT*)malloc(sizeof(NodeT));
    nod->key = givenKey;
    nod->next = *head;
    *head = nod;
    if (*tail == NULL) { /// lista era goala
        *tail = nod;
    }
}

void insert_last(NodeT** head, NodeT** tail, int givenKey) {
    NodeT* nod = (NodeT*)malloc(sizeof(NodeT));
    nod->key = givenKey;
    nod->next = NULL;
    if (*head == NULL) { /// lista era goala
        *head = nod;
    }
    else {
        (*tail)->next = nod;
    }
    *tail = nod;
}

void insert_last(NodeT** head, int givenKey) {
    NodeT* nod = (NodeT*)malloc(sizeof(NodeT));
    nod->key = givenKey;
    nod->next = NULL;
    if (*head == NULL) {
        *head = nod;
    }
    else
    {
        NodeT* p = *head;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = nod;

    }
}

void delete_first(NodeT** head) {
    if (*head == NULL) {
        return;
    }
    NodeT* old = *head;
    *head = (*head)->next;
    free(old);
}

NodeT* createNode(int key)
{
    NodeT* q = (NodeT*)malloc(sizeof(NodeT));
    q->key = key;
    q->next = NULL;
    return q;
}

void min_heapify(NodeT* list[], int i, int n, Operation op)
{
    int l = 2 * i;
    int r = 2 * i+1;
    int smallest;
    op.count();
    if (l <= n && list[l]->key < list[i]->key)
    {
        smallest = l;
    }
    else {
        smallest = i;
    }
    op.count();
    if (r <= n && list[r]->key < list[smallest]->key)
    {
        smallest = r;
    }

    if (smallest != i)
    {
        NodeT* aux = list[i];
        list[i] = list[smallest];
        list[smallest] = aux;
        op.count(3);
        min_heapify(list, smallest, n, op);
    }
}

void Bottom_up(NodeT* a[], int k, Operation op)
{
    for (int i = k / 2 ; i >= 1; i--)
        min_heapify(a, i, k, op);
}

NodeT* kWayMerge(NodeT* list[], int n, int k)
{
    Operation op = p.createOperation("Interclasare K liste", n);
    int heapSize = k;
    Bottom_up(list, k, op);
    NodeT* lout = (NodeT*)malloc(sizeof(NodeT));
    NodeT* tail = (NodeT*)malloc(sizeof(NodeT));
    lout = tail = NULL;
    bool flag = true;
    while (heapSize > 0)
    {
        op.count(2);
        int aux = list[1]->key;
        insert_last(&lout, &tail, aux);
        list[1] = list[1]->next;

        /*if (flag == true)
        {
            lout = createNode(aux);
            flag = false;
        }
        else
        {
            insert_last(&lout, &tail, aux);
        }
        */
        op.count();
        if (list[1] == NULL)
        {
            op.count();
            list[1] = list[heapSize];
            heapSize--;
        }
        min_heapify(list, 1, heapSize, op);

    }
    return lout;
}

void demo(int k)
{
    int a[10005];
    NodeT** list = (NodeT**)malloc(505 * sizeof(NodeT*));
    int n = 5;
    cout << "n = ";
    cin >> n;
    int x;
    int m;
    
    for (int i = 1; i <= k; i++)
        list[i] = NULL;
    //for (int i = 0; i <n; i++)
      //  cin >> a[i];
    m = n / k;
    for (int i = 1; i <= k; i++)
    {
        cout << "lista " << i << endl;
        cin >> x;
        list[i] = createNode(x);
        for (int j = 1; j < m; j++)
        {
            cin >> x;
            insert_last(&list[i], x);
        }
    }
    //for (int i = 1; i <= k; i++)
      //  print_list(list[i]);
    
    NodeT* lout = kWayMerge(list, n, k);
    
    print_list(lout);


}

void KLists(int k)
{
    int a[10005];
    NodeT** list = (NodeT**)malloc(10005 * sizeof(NodeT*));
    NodeT* tail = NULL;
    int n = 100;
    /*
    for (int n = 100; n <= 10000; n += 100)
    {
        for (int j = 1; j <= k; j++)
        {
            FillRandomArray()
        }
    }
    */
    int m;
    for (int n = 100; n <= 10000; n += 100){
        printf("%d\n", n);
        m = n / k;
        //printf("M este: %d\n", m);
        for (int j = 1; j <= k; j++) {
            FillRandomArray(a, m+1, 1, 50000, false, ASCENDING);
            list[j] = createNode(a[1]);
            for (int i = 2; i <= m; i++)
            {
                insert_last(&list[j], a[i]);
            }
        }
        NodeT* lout = kWayMerge(list, n, k);
    }
    p.showReport();
}

void KListsN()
{
    int a[10005];
    int n = 10000;
    NodeT** list = (NodeT**)malloc(10005 * sizeof(NodeT*));
    int m;

    for (int k = 10; k <= 500; k += 10)
    {
        printf("%d\n", k);
        m = n / k;
        for (int j = 1; j <= k; j++) {
            FillRandomArray(a, m+1, 1, 50000, false, ASCENDING);
            list[j] = createNode(a[1]);
            for (int i = 2; i <= m; i++)
            {
                insert_last(&list[j], a[i]);
            }
        }
        NodeT* lout = kWayMerge(list, n, k);
    }

    p.showReport();
    
}

int main()
{
    //demo(4);
    //KLists(5);
    //KLists(10);
    //KLists(100);
    //KListsN();/// k - la createOperation
	return 0;
}