/**
Alin Matean	
grupa 30228

Build-Heap
BottomUp vs TopDown

AverageCase
BottomUp are complexitate O(n) pe cazul mediu statistic, in timp ce TopDown are O(nlogn).
! BottomUp > TopDown !

BottomUp utilizeaza heapify si porneste de la ultimul nod parinte in constructia heapului, deoarece frunzele sunt
considerate deja heap, si interschimba parinte-copil cand e cazul.

TopDown porneste de la primul element din sir si adauga succesiv restul elementelor, "urcand" elementul adaugat cat e cazul
construind heap-ul.

Un avantaj al tehnicii TopDown ar fi comparatile mai putine si faptul ca nu folosim variabile auxiliare, precum: l, r, largest in cazul BottomUp.
Insa per total, BottomUp este mai eficienta(in sepcial datorita atribuirilor mult mai putine decat la TD)!

Pe WorstCase, complexitatile raman la fel(O(n) - BU /// O(nlogn) - TD), insa se vede mai tare diferenta 
dintre BottomUp si TopDown.
Am considerat WorstCase un sir crescator.

*/


#include <iostream>
#include "Profiler.h"

Profiler p("profiler");

using namespace std;

void max_heapify(int a[], int i, int n)
{
	Operation atrib = p.createOperation("atrib_BottomUp", n);
	Operation comp = p.createOperation("comp_BottomUp", n);
	int l = 2 * i;
	int r = 2 * i + 1;
	int largest;
	comp.count();
	if (l <= n && a[l] > a[i])
	{
		largest = l;
	}
	else {
		largest = i;
	}
	comp.count();
	if (r <= n && a[r] > a[largest])
	{
		largest = r;
	}

	if (largest != i)
	{
		atrib.count(3);
		int aux = a[i];
		a[i] = a[largest];
		a[largest] = aux;

		max_heapify(a, largest, n);
	}
}

void bottom_up(int a[], int n)
{
	for (int i = n / 2; i >= 1; i--)
	{
		max_heapify(a, i, n);
	}
}

void heap_increase_key(int a[], int i, int n)
{
	Operation atrib = p.createOperation("atrib_TopDown", n);
	Operation comp = p.createOperation("comp_TopDown", n);
	comp.count();
	while (i > 1 && a[i] > a[i / 2])
	{
		comp.count();
		atrib.count(3);
		int aux = a[i];
		a[i] = a[i / 2];
		a[i / 2] = aux;
		i = i / 2;
	}
}

void top_down(int a[], int n)
{
	//int j = 0;
	for (int i = 1; i <= n; i++)
	{
		//j = i;
		heap_increase_key(a, i, n);
	}
}

void heapSort(int a[], int n)
{
	bottom_up(a, n);
	//top_down(a, n);
	int m = n;
	for (int i = n; i >= 2; i--)
	{
		int aux = a[1];
		a[1] = a[i];
		a[i] = aux;
		m--;
		max_heapify(a, 1, m);
	}
}


void demo()
{
	int a[10000];
	int n;
	cin >> n;
	//cout << n<<'\n';
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	//bottom_up(a, n);
	heapSort(a, n);
	//top_down(a, n);
	for(int i = 1; i <= n; i++)
	{
		cout << a[i] << " ";
	}
}

void average()
{
	int v[10005];
	int v1[10005];
	int n = sizeof(v) / sizeof(int);

	for (int n = 100; n <= 10000; n += 100) {
		printf("%d\n", n);
		for (int k = 0; k < 5; k++) {
			FillRandomArray(v, n+1);
			memcpy(v1, v, (n+1) * sizeof(int));
			bottom_up(v, n);
			top_down(v1, n);
		}

	}

	p.divideValues("atrib_TopDown", 5);
	p.divideValues("comp_TopDown", 5);
	p.divideValues("atrib_BottomUp", 5);
	p.divideValues("comp_BottomUp", 5);
	p.createGroup("atrib", "atrib_BottomUp", "atrib_TopDown");
	p.createGroup("comp", "comp_BottomUp", "comp_TopDown");
	p.addSeries("TopDown", "atrib_TopDown", "comp_TopDown");
	p.addSeries("BottomUp", "atrib_BottomUp", "comp_BottomUp");
	p.createGroup("BottomUp vs TopDown", "BottomUp", "TopDown");

	p.showReport();

}

void worst()
{
	int v[10005];
	int v1[10005];
	int n = sizeof(v) / sizeof(int);

	for (int n = 100; n <= 10000; n += 100) {
		printf("%d\n", n);
			FillRandomArray(v, n+1, 10, 500000, false, ASCENDING);
			memcpy(v1, v, (n+1) * sizeof(int));
			//heapSort(v, n);
			bottom_up(v, n);
			top_down(v1, n);

	}

	p.divideValues("atrib_TopDown", 5);
	p.divideValues("comp_TopDown", 5);
	p.divideValues("atrib_BottomUp", 5);
	p.divideValues("comp_BottomUp", 5);
	p.createGroup("atrib", "atrib_BottomUp", "atrib_TopDown");
	p.createGroup("comp", "comp_BottomUp", "comp_TopDown");
	p.addSeries("TopDown", "atrib_TopDown", "comp_TopDown");
	p.addSeries("BottomUp", "atrib_BottomUp", "comp_BottomUp");
	p.createGroup("BottomUp vs TopDown", "BottomUp", "TopDown");

	p.showReport();
}

int main()
{
	demo();
	//average();
	//worst();

	return 0;
}