/**
Alin Matean
grupa 30228

Arbori Multicai

1.Reprezentarea sir de parinti: un sir in care retinem pentru fiecare nod cheia parintelui
2.Reprezentarea sir de copii: fiecare nod este o structura care are: cheia, numarCopii, copiii(daca exista)
3.Reprezentarea binara: fiecare nod este o structura care are: cheia, primulCopil(daca exista), urmatorulFrate(daca exista)

Am pus in sirul initial de parinti un 0 pe prima pozitie, imi intra intr o bucla infinita altfel(ori la primul prettyPrint
ori la prettyPrint2 /// nu am reusit sa fac sa mearga ambele fara un 0 initial).

Pentru transformarea1(din sir de parinti in sir de copii): complexitatea este O(n), parcurgem o data intreg sirul de parinti,
pe fiecare nod i(in afara de radacina) il punem ca si copil la p[i]. Nu folosim memorie aditionala in afara de structura 
fiecarui nod.

Pentru transformarea2(din sir de copii in reprezentare binara): complexitate O(n), plecam din radacina si pentru fiecare nod
setam recursiv primul copil si urmatorul frate daca exista. Legaturile se fac pe revenirea din apel,
la final o sa returnam tot radacina. Folosim un nodPrecedent ca memorie aditionala pentru a retine nodul anterior care ne va
ajuta sa setam ulterior legtura de "urmatorul frate".

PrettyPrint1 are complexitate O(n^2): pentru fiecare nod care nu e parinte, cautam parintele in vector si daca il
gasim pe o pozitie apelam prettyPrint cu acel nod ca fiind noul nostru parinte.

PrettyPrint2 parcurgem pentru fiecare nod doar lista de copii si nu intreg sirul.=>O(n):-?

PrettyPrint3 tot O(n) pentru ca vom ajunge sa trecem prin fiecare nod o singura data deoarece avem pointer catre
primul copil si urmatorul frate.


*/

#include <iostream>

using namespace std;;

typedef struct NodR2
{
	int key;
	int nrCopii;
	struct NodR2* copii[3];
}NodeR2;

typedef struct NodR3 {
	int key;
	struct NodR3* primCopil;
	struct NodR3* urmFrate;
}NodeR3;

void prettyPrint1(int parinte, int p[], int nivel, int n)
{
	int m = nivel;
	while (m)
	{
		printf("   ");
		m--;
	}
	printf("%d\n", parinte);
	for (int i = 1; i <= n; i++)
		if (p[i] == parinte)
			prettyPrint1(i, p, nivel + 1, n);
}

void transformare1(int p[], NodeR2** r2)
{
	for (int i = 1; i <= 9; i++) {
		r2[i]->nrCopii = 0;
		r2[i]->key = i;
	}

	for (int i = 1; i <= 9; i++)
		if (p[i] != -1) {
			r2[p[i]]->copii[r2[p[i]]->nrCopii] = r2[i];
			r2[p[i]]->nrCopii++;
		}
}

void prettyPrint2(NodeR2* root, int nivel)
{
	if (root->key != NULL) {
		int m = nivel;
		while (m)
		{
			printf("   ");
			m--;
		}
		printf("%d\n", root->key);
		for (int i = 0; i < root->nrCopii; i++)
			prettyPrint2(root->copii[i], nivel + 1);
	}
}

NodR3* transformare2(NodeR2* r2)
{
	NodeR3* nodNou = (NodeR3*)malloc(sizeof(NodeR3));
	nodNou->key = r2->key;
	nodNou->urmFrate = NULL;
	if (r2->nrCopii == 0)
		nodNou->primCopil = NULL;
	else {
		nodNou->primCopil = transformare2(r2->copii[0]);
		NodR3* nodPrecedent = nodNou->primCopil;
		for (int i = 1; i < r2->nrCopii; i++)
		{
			nodPrecedent->urmFrate = transformare2(r2->copii[i]);
			nodPrecedent = nodPrecedent->urmFrate;
		}
	}

	return nodNou;
}

void prettyPrint3(NodeR3* root, int nivel)
{
	if (root != NULL) {
		int m = nivel;
		while (m) {
			printf("   ");
			m--;
		}
		printf("%d\n", root->key);
		prettyPrint3(root->primCopil, nivel + 1);
		prettyPrint3(root->urmFrate, nivel);
	}
}

int main()
{
	int p[10] = { 0, 2, 7, 5, 2, 7, 7, -1, 5, 2 };
	int n = 10;
	printf("PP1:\n");
	int x;
	for (int i = 1; i <= n; i++)
		if (p[i] == -1) {
			x = i;
			prettyPrint1(i, p, 0, n);
		}

	printf("\nPP2:\n");

	NodeR2** r2 = (NodeR2**)malloc(9 * sizeof(NodeR2*));
	for (int i = 1; i <= 9; i++)
		r2[i] = (NodeR2*)malloc(sizeof(NodeR2));

	transformare1(p, r2);
	//printf("%d ", r2[x]->key);
	prettyPrint2(r2[x], 0);

	printf("\nPP3:\n");

	NodeR3* r3 = transformare2(r2[x]);
	//printf("%d ", r3->key);
	prettyPrint3(r3, 0);
	return 0;
}