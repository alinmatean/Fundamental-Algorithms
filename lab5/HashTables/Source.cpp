/**
Alin Matean
grupa 30228

Cautarea in tabela de dispersie // adresare deschisa, verificare patratica

Factor de umplere(alfa): 0.8 / 0.85 / 0.9 / 0.95 / 0.99

Timpul mediu pentru o cheie gasita este 1/alfa ln((1/(1-alfa)), iar pentru o cheie negasita (1/1-alfa).

Am ales n = 10007 dimensiunea tabelei.

Se observa o crestere treptata a numarului casutelor accesate si a numarului maxim de casute accesate
odata cu cresterea factorului de umplere in cazul unei chei care exista in tabela.

In cazul unei chei care nu exista in tabela cresterea este mult mai evidenta, si pentru numarul maxim de accese si pentru
numarul mediu.

Cum era de asteptat, se fac mult mai multe accese pentru o cheie care nu exista in tabela(cel mai bine se observa la
alfa = 0.99).

numarul mediu de accese pt o cheie gasita creste de la ~2 pana la ~6,
iar pentru o cheie negasita de la ~4 pana la ~100-110.

Astfel ajungem la concluzia ca o cheie care exista in tabela este gasita foarte rapid, in schimb una care nu exista necesita 
destul de multe accese pentru a concluziona ca nu exista mai ales daca tabela este aproape plina(peste 90%).

O problema cu tabela de dispersie care foloseste adresare deschisa este legata de stergerea elementelor si marcarea
locurilor de unde s-a sters. Tabela de dispersie cu adresare deschisa e utila atunci cand nu prea avem de 
sters elemente.


*/


#include <iostream>
#include <math.h>
#include "Profiler.h"

Profiler p("profiler");


using namespace std;

struct cell {
	int key;
	bool status;
};

int quadratic_probing(int k, int i, int n)
{
	return (k % n + i + i * i) % n;
}

int hash_insert(cell* T, int k, int n)
{
	int i = 0;
	do {
		int j = quadratic_probing(k, i, n);
		if (T[j].status == false)
		{
			T[j].key = k;
			T[j].status = true;
			return j;
		}
		else
			i++;
	} while (i != n);
	//printf("Cheia nu a putut fi inserata!");
}

int hash_search(cell* T, int k, int n, int &cnt)
{
	int i = 0;
	int j;
	do {
		j = quadratic_probing(k, i, n);
		cnt++;
		if (T[j].key == k && T[j].status == true)	
			return j;
		i++;
	} while (T[j].status == true && i != n);
	
	return -1;
}

void afisare(cell* T, int m)
{
	printf("\n\nTabela de dispersie este \n");
	for (int i = 0; i < m; i++)
	{
		if (T[i].status == true)
			printf("T[%d]=%d\n", i, T[i].key);
		else
			printf("T[%d]= --\n", i);
	}
}

void demo()
{
	int n = 12;/// 12 elemete in 13 casute ca sa avem factor de umplere ~ 95%
	int m = 13;
	int a[100];
	int cnt = 0;
	cell* T = (cell*)malloc(m*sizeof(cell));
	for (int i = 0; i < m; i++)
		T[i].status = false;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
		hash_insert(T, a[i], m);
	}
	afisare(T, m);
	int search;
	cout << "Cauta cheia: ";
	cin >> search;
	if (hash_search(T, search, m, cnt) != -1)
		printf("Cheia cautata se afla pe pozitia %d si a fost gasita din %d incercari!", hash_search(T, search, m, cnt), cnt);
	else
		printf("Cheia cautata nu exista! S-au facut %d accesari.", cnt);

}

void countOp(double alfa)
{
	if (alfa > 1)
		printf("Eroare factor de umplere!");
	int n = 10007;///dimensiunea tabelei
	int a[11507];
	int b[1500];
	int c[1500];
	int m =(double)(alfa * n) ;///numarul de elemnete
	//printf("--%d--", m);
	printf("     %.2lf               ", alfa);
	cell* T = (cell*)malloc(n * sizeof(cell));

	int avgFound = 0, avgNotFound = 0, maxFound = 0, maxNotFound = 0;
	
	for (int i = 0; i < 5; i++)
	{
		FillRandomArray(a, n+1500, 0, 50000, true);///inserate in tabela
		FillRandomArray(c, 1500, 0, m, true);///indici

		for (int j = 0; j < n; j++)
			T[j].status = false;
		for (int j = 0; j < m; j++)
			hash_insert(T, a[j], n);
		int k = m + 1;
		for (int j = 0, k = n; j < 1500 && k < n + 1500; j++, k++)
			b[j] = a[k];///elemente care nu sunt inserate in tabela
		
		for (int j = 0; j < 1500; j++)
		{
			int cnt = 0;
			hash_search(T, a[c[j]], n, cnt);
			avgFound += cnt;
			if (cnt > maxFound)
				maxFound = cnt;
		}


		for (int j = 0; j < 1500; j++)
		{
			int cnt = 0;
			hash_search(T, b[j], n, cnt);
			avgNotFound += cnt;
			if (cnt > maxNotFound)
				maxNotFound = cnt;
		}

	}
	
	printf("%.2lf                ", ((avgFound / 1500.0) / 5.0));
	printf("%d                 ", maxFound);
	printf("%.2lf               ", ((avgNotFound / 1500.0) / 5.0));
	printf("%d           ", maxNotFound);

	free(T);

}


void GenerareTabel()
{
	cout << "Factor de umplere |  CheieGasita  |    MaxCheieGasita    | CheieNegasita |   MaxCheieNegasita" << endl;
	countOp(0.8);
	printf("\n");
	countOp(0.85);
	printf("\n");
	countOp(0.9);
	printf("\n");
	countOp(0.95);
	printf("\n");
	countOp(0.99);
}

int main()
{
	//demo();
	//countOp(0.8);
	GenerareTabel();
	return 0;
}