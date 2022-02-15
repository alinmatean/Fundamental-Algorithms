/**
Alin Matean
grupa 30228

Analiza algoritmi:

BubbleSort:
->AverageCase: O(n^2) atribuiri /// O(n^2) comparatii /// O(n^2) total
->BestCase: O(1) atribuiri /// O(n) comparatii /// O(n) total
->WorstCase: O(n^2) atribuiri /// O(n^2) comparatii /// O(n^2) total

SelectionSort
->AverageCase: O(n) atribuiri /// O(n^2) comparatii /// O(n^2) total
->BestCase: O(1) atribuiri /// O(n^2) comparatii /// O(n^2) total
->WorstCase: O(n) atribuiri /// O(n^2) comparatii /// O(n^2) total

InsertionSort /// fara binarySearch
->AverageCase: O(n^2) atribuiri /// O(n^2) comparatii /// O(n^2) total
->BestCase: O(n) atribuiri /// O(n) comparatii /// O(n) total
->WorstCase: O(n^2) atribuiri /// O(n^2) comparatii /// O(n^2) total

InsertionSort /// cu binarySearch
->AverageCase: O(n^2) atribuiri /// O(nlogn) comparatii /// O(n^2) total
->BestCase: O(n) atribuiri /// O(nlogn) comparatii /// O(nlogn) total
->WorstCase: O(n^2) atribuiri /// O(n^2) comparatii /// O(n^2) total


Daca am avea un sir sortat, as alege BubbleSort pentru O(1) atribuiri si pentru implementarea mai simpla.

Pe un caz mediu statistic, cel mai eficient algoritm din punctul de vedere al atribuirilor este SelectionSort,
iar din punctul de vedere al comparatilor InsertionSort cu binarySearch, fiind insa poate mai dificil de implementat.
As alege SelectionSort pentru timp constant in cazul atribuirilor.

Pe worstcase, selectionSort este singurul care are O(n) atribuiri, in final complexitatea fiind insa patratica pentru
toti algoritmii.

*/


#include <stdio.h>
#include "Profiler.h"

Profiler p("profiler");

void bubbleSort(int v[], int n)
{
	Operation atrib = p.createOperation("atrib_bubbleSort", n);
	Operation comp = p.createOperation("comp_bubbleSort", n);
	bool flag = false;
	for (int i = 0; i < n - 1; i++) {
		flag = false;
		for (int j = 0; j < n - i - 1; j++) {
			comp.count();
			if (v[j] > v[j + 1]) {
				atrib.count(3);
				int aux = v[j];
				v[j] = v[j+1];
				v[j + 1] = aux;
				flag = true;
			}
		}
		if (!flag) {
			break;
		}

	}
}

void selectionSort(int v[], int n)
{
	Operation atrib = p.createOperation("atrib_selSort", n);
	Operation comp = p.createOperation("comp_selSort", n);
	int minim;
	for (int i = 0; i < n; i++) {
		minim = i;
		for (int j = i + 1; j < n; j++) {
			comp.count();
			if (v[j] < v[minim]) {
				minim = j;
			}
		}
		if (i != minim) {
			atrib.count(3);
			int aux = v[i];
			v[i] = v[minim];
			v[minim] = aux;
		}
	}
}

int binarySearch(int a[], int k, int st, int dr, int n)
{
	Operation comp = p.createOperation("comp_insSort", n);
	if (dr <= st) {
		comp.count();
		if (k > a[dr]) 
			return (dr + 1);
		else 
			return dr;
	}

	int mid = (st + dr) / 2;

	comp.count();
	if (k == a[mid])
		return mid + 1;
	comp.count();
	if (k > a[mid])
		return binarySearch(a, k, mid + 1, dr, n);
	return binarySearch(a, k, st, mid - 1, n);
}

void insertionSort(int v[], int n)
{
	Operation atrib = p.createOperation("atrib_insSort", n);
	Operation comp = p.createOperation("comp_insSort", n);
	int x, j, y;
	for (int i = 1; i < n; i++) {
		atrib.count();
		x = v[i];
		j = i - 1;
		y = binarySearch(v, x, 0, j, n); //pozitia
		//comp.count();
		//while(j>=0 && v[j] > x)
		while (j >= y) {
			//comp.count();
			atrib.count();
			v[j + 1] = v[j];
			j--;
		}
		atrib.count();
		v[j + 1] = x;
	}
}

void demo()
{
	int v[] = {12, 7, 1278, 872, -3, 823, 6782, 10, 90, 100};
	int v1[] = { 12, 7, 1278, 872, -3, 823, 6782, 10, 90, 100 };
	int v2[] = { 12, 7, 1278, 872, -3, 823, 6782, 10, 90, 100 };
	int n = sizeof(v) / sizeof(int);
	
	bubbleSort(v, n);
	selectionSort(v1, n);
	insertionSort(v2, n);
	printf("BubbleSort: ");
	for (int i = 0; i < n; i++)
	{
		printf("%d  ", v[i]);
	}
	printf("\n");
	printf("SelectionSort: ");
	for (int i = 0; i < n; i++)
	{
		printf("%d  ", v1[i]);
	}
	printf("\n");
	printf("InsertionSort: ");
	for (int i = 0; i < n; i++)
	{
		printf("%d  ", v2[i]);
	}

}

void average()
{
	int v[10005];
	int v1[10005];
	int v2[10005];
	int n = sizeof(v) / sizeof(int);

	for (int n = 100; n <= 10000; n += 100) {
		printf("%d\n", n);
		for (int k = 0; k < 5; k++) {
			FillRandomArray(v, n);
			memcpy(v1, v, n * sizeof(int));
			memcpy(v2, v, n * sizeof(int));
			bubbleSort(v, n);
			selectionSort(v1, n);
			insertionSort(v2, n);
		}

	}

	p.divideValues("atrib_bubbleSort", 5);
	p.divideValues("comp_bubbleSort", 5);
	p.divideValues("atrib_selSort", 5);
	p.divideValues("comp_selSort", 5);
	p.divideValues("atrib_insSort", 5);
	p.divideValues("comp_insSort", 5);
	p.addSeries("total_bubbleSort", "comp_bubbleSort", "atrib_bubbleSort");
	p.addSeries("total_selSort", "comp_selSort", "atrib_selSort");
	p.addSeries("total_insSort", "comp_insSort", "atrib_insSort");
	p.createGroup("comp", "comp_bubbleSort", "comp_selSort");
	p.createGroup("atrib", "atrib_bubbleSort", "atrib_insSort");

	p.showReport();

}

void best()
{
	int v[10005];
	int n = sizeof(v) / sizeof(int);

	for (int n = 100; n <= 10000; n += 100) {
		printf("%d\n", n);

			FillRandomArray(v, n, 10, 500000, false, ASCENDING);
			bubbleSort(v, n);
			selectionSort(v, n);
			insertionSort(v, n);
		
	}
	

	p.divideValues("atrib_bubbleSort", 5);
	p.divideValues("comp_bubbleSort", 5);
	p.divideValues("atrib_selSort", 5);
	p.divideValues("comp_selSort", 5);
	p.divideValues("atrib_insSort", 5);
	p.divideValues("comp_insSort", 5);
	p.addSeries("total_bubbleSort", "comp_bubbleSort", "atrib_bubbleSort");
	p.addSeries("total_selSort", "comp_selSort", "atrib_selSort");
	p.addSeries("total_insSort", "comp_insSort", "atrib_insSort");
	//p.createGroup("comp", "comp_bubbleSort", "comp_selSort", "comp_insSort");
	//p.createGroup("atrib", "atrib_bubbleSort", "atrib_insSort");

	p.showReport();
}

void worst()
{
	int v[10005];
	int v1[10005];
	int v2[10005];
	int n = sizeof(v) / sizeof(int);

	for (int n = 100; n <= 10000; n += 100) {
		printf("%d\n", n);
			FillRandomArray(v, n, 10, 500000, false, DESCENDING);
			memcpy(v2, v, n * sizeof(int));
			bubbleSort(v, n);
			insertionSort(v2, n);

			v1[0] = v[n-1];
			for (int i = 1; i < n; i++) {
				v1[i] = v[i-1];
			}
		
			selectionSort(v1, n);

	}


	p.divideValues("atrib_bubbleSort", 5);
	p.divideValues("comp_bubbleSort", 5);
	p.divideValues("atrib_selSort", 5);
	p.divideValues("comp_selSort", 5);
	p.divideValues("atrib_insSort", 5);
	p.divideValues("comp_insSort", 5);
	p.addSeries("total_bubbleSort", "comp_bubbleSort", "atrib_bubbleSort");
	p.addSeries("total_selSort", "comp_selSort", "atrib_selSort");
	p.addSeries("total_insSort", "comp_insSort", "atrib_insSort");
	//p.createGroup("comp", "comp_bubbleSort", "comp_selSort", "comp_insSort");
	p.createGroup("atrib", "atrib_bubbleSort", "atrib_insSort");

	p.showReport();
}

int main()
{
	//demo();
	//average();
	best();
	//worst();

	return 0;
}