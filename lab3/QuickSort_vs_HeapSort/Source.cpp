/**
Alin Matean
Grupa 30228

QuickSort vs HeapSort
-AverageCase: QuickSort si HeapSort au complexitate O(nlogn) in caz mediu statistic.
Desi au aceeasi complexitate, se poate observa numarul mai mic de operatii pe care il face QuickSort, 
mai ales o data cu cresterea lungimii sirului.
 ! QuickSort > HeapSort !
Daca am alege pivotul random, am obtine un algoritm si mai eficient, am reduce putin numarul operatilor.

QuickSort - BestCase:
-este un sir de genul: 1, 3, 2, 6, 5, 7, 4.
Astfel incat mijlocul fiecarui sir/subsir sa fie pe ultima pozitie si sa devina pivot.
Avem tot complexitate O(nlogn), insa se efectueaza mai putine operatii per total.

QuicKSort - WorstCase
-am ales un sir ordonat crescator, unde pivotul va fi cel mai mare element mereu.
Se vede un efort mare pe care il face QuickSort pe un astfel de sir, se ajunge la complexitate O(n^2),
cu mult mai multe operatii efectuate decat pe un caz mediu statistic.


*/


#include <iostream>
#include "Profiler.h"

Profiler p("profiler");

using namespace std;

void swap(int &a, int &b)
{
	int aux = a;
	a = b;
	b = aux;
}
//HeapSort - 3functii
void max_heapify(int a[], int i, int n, Operation op)
{
	int l = 2 * i;
	int r = 2 * i + 1;
	int largest;
	op.count();
	if (l <= n && a[l] > a[i])
	{
		largest = l;
	}
	else {
		largest = i;
	}
	op.count();
	if (r <= n && a[r] > a[largest])
	{
		largest = r;
	}

	if (largest != i)
	{
		op.count(3);
		int aux = a[i];
		a[i] = a[largest];
		a[largest] = aux;

		max_heapify(a, largest, n, op);
	}
}

void bottom_up(int a[], int n, Operation op)
{
	for (int i = n / 2; i >= 1; i--)
	{
		max_heapify(a, i, n, op);
	}
}

void heapSort(int a[], int n)
{
	Operation op = p.createOperation("HeapSort", n);
	bottom_up(a, n, op);
	int m = n;
	for (int i = n; i >= 2; i--)
	{
		op.count(3);
		int aux = a[1];
		a[1] = a[i];
		a[i] = aux;
		m--;
		max_heapify(a, 1, m, op);
	}
}

//QuickSort - 2functii
int partition(int a[], int l, int r, Operation op)
{
	op.count();
	int x = a[r];
	int i = l-1;
	for (int j = l; j <= r - 1; j++) {
		op.count();
		if (a[j] <= x) {
			i++;
			op.count(3);
			swap(a[i], a[j]);
		}
	}
	op.count(3);
	swap(a[i+1], a[r]);
	return (i+1) ;
}

void QuickSort(int a[], int l, int r, int n)
{
	Operation op = p.createOperation("QuickSort", n);
	int q;
	if (l < r) {
		int q = partition(a, l, r, op);
		QuickSort(a, l, q-1, n);
		QuickSort(a, q+1, r, n);
	}
}

//QuickSelect(am facut din nou functia de partition fara parametru op)- 3functii
int partitions(int a[], int l, int r, int n)
{
	int x = a[r];
	int i = l - 1;
	for (int j = l; j <= r - 1; j++) {
		if (a[j] <= x) {
			i++;
			swap(a[i], a[j]);
		}
	}
	swap(a[i + 1], a[r]);
	return (i + 1);
}

int randomized_partition(int a[], int l, int r, int n)
{
	int i = l + (rand() % (r-l+1));
	swap(a[r], a[i]);
	return partitions(a, l, r, n);

}

int randomized_select(int a[], int p, int r, int i, int n)
{
	if (p == r)
		return a[p];
	int q = randomized_partition(a, p, r, n);
	int k = q - p + 1;
	if (i == k)
		return a[q];
	else if (i < k)
		return randomized_select(a, p, q - 1, i, n);
	else 
		return randomized_select(a, q + 1, r, i - k, n);

}
//am facut initial grafic si pt RandomizedQuickSort doar ca sa vad daca e diferenta mare intre el si QuickSort normal
void Randomized_QuickSort(int a[], int l, int r, int n)
{
	int p;
	if (l < r)
	{
		p = randomized_partition(a, l, r, n);
		Randomized_QuickSort(a, l, p - 1,n);
		Randomized_QuickSort(a, p + 1, r,n);

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

	//QuickSort(a, 1, n, n);
	//heapSort(a, n);
	//Randomized_QuickSort(a, 1, n, n);

	for (int i = 1; i <= n; i++)
	{
		cout << a[i] << " ";
	}
}

void demoQuickSelect()
{
	int a[10005];
	int n;
	cout << "Numarul de elemente: ";
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	int x;
	cout << "Alege al catelea cel mai mic element din sir il vrei: ";
	cin >> x;
	int y = randomized_select(a, 1, n, x, n);
	if (x < 0 || x>n)
		return;
	if (x == 1)
		cout << "Cel mai mic element din sir este: " << x;
	else
		cout << "Al " << x << "-lea cel mai mic element din sir este: " << y;
}

void average()
{
	int a[10005];
	int a1[10005];
	int n;
	for (int n = 100; n <= 10000; n += 100) {
		printf("%d\n", n);
		for (int k = 0; k < 5; k++) {
			FillRandomArray(a, n+1);
			memcpy(a1, a, (n+1) * sizeof(int));
			QuickSort(a, 1, n, n);
			heapSort(a1, n);
		}

	}
	p.divideValues("QuickSort", 5);
	p.divideValues("HeapSort", 5);
	p.createGroup("QuickSort vs HeapSort", "QuickSort", "HeapSort");
	p.showReport();
}

void moveMiddleToPivot(int a[], int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		moveMiddleToPivot(a, left, mid - 1);
		moveMiddleToPivot(a, mid+1, right);
		swap(a[mid], a[right]);
	}
}

void best()
{
	int a[10005];
	int n;
	/*cin >> n;
	FillRandomArray(a, n + 1, 1, 100, FALSE, ASCENDING);
	for (int i = 1; i <= n; i++)
		cout << a[i] << " ";
	cout << endl;
	moveMiddleToPivot(a, 1, n);
	for (int i = 1; i <= n; i++)
		cout << a[i] << " ";*/
		
	for (int n = 100; n <= 10000; n += 100) {
		printf("%d\n", n);
		FillRandomArray(a, n + 1, 1, 50000, false, ASCENDING);
		moveMiddleToPivot(a, 1, n);
		QuickSort(a, 1, n, n);
	}
	p.showReport();

}

void worst()
{
	int a[10005];
	int n;
	for (int n = 100; n <= 10000; n += 100) {
		printf("%d\n", n);
		FillRandomArray(a, n + 1, 1, 50000, false, ASCENDING);
		QuickSort(a, 1, n, n);
	}
	p.showReport();
}

int main()
{
	//demo();
	//demoQuickSelect();
	//average();
	//best();
	//worst();
	return 0;
}