/*
* Student: Spaczai Carla Noemi
* Grupa: 30229
* Am implementat operatiile de inserare si cautare intr­-o tabela de dispersie care foloseste adresarea deschisa cu verificare patratica.
* Am realizat un tabel care contine efortul mediu depus pentru elementele gasite, efortul maxim depus pentru elementele gasite, efortul mediu depus pentru elementele
* care nu au fost gasite si efortul maxim depus pentru elementele care nu au fost gasite pentru diferiti factori de umplere.
* 
* Observam in tabelul realizat ca:
* Pentru toti factorii de umplere testati, efortul mediu si efortul maxim depus pentru elementele gasite cuprind valori ale caror diferenta nu este foarte mare.
* Pentru toti factorii de umplere testati, efortul mediu si efortul maxim depus pentru elementele care nu au fost gasite cuprind valori ale caror diferenta este
* destul de mare. Cu cat este mai mare factorul de umplere, cu atat este mai mare si efortul mediu si efortul maxim depus.
*/

#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"

Profiler P("HASHTABLE");

//#define CAPACITATE_DEMO 20
#define CAPACITATE_DEMO 11
#define CAPACITATE_EVALUARE 10007
#define NR_TESTS 5
#define CAUTARE_ELEMENTE 3000

typedef struct HashTable
{
	int* vector;
	int capacitate;
} HashTable;

HashTable* creareHashTable(int capacitate)
{
	HashTable* HT = (HashTable*)malloc(sizeof(HashTable));
	HT->capacitate = capacitate;
	HT->vector = (int*)malloc(capacitate * sizeof(int));
	for (int i = 0; i < capacitate; i++)
	{
		HT->vector[i] = NULL;
	}
	return HT;
}

int functieHash(int key, int i, int capacitate)
{
	int H = (key + 6 * i + 9 * i * i) % capacitate;
	while (H < 0)
	{
		H += capacitate;
	}
	return H;
}

void inserareHashTable(HashTable* HT, int key, int capacitate)
{
	int i = 0;
	do {
		int j = functieHash(key, i, capacitate);
		if (HT->vector[j] == NULL)
		{
			HT->vector[j] = key;
			printf("Am inserat elementul %d pe pozitia %d.\n", key, j);
			break;
		}
		else
		{
			i += 1;
		}
	} while (i != capacitate);
	if (i == capacitate)
	{
		printf("Tabelul este plin! Nu se poate insera elementul %d.\n", key);
	}
}

void cautareHashTable(HashTable* HT, int key, int capacitate)
{
	int i = 0;
	int k = functieHash(key, i, capacitate);
	do {
		int j = functieHash(key, i, capacitate);
		if (HT->vector[j] == key)
		{
			printf("Am gasit elementul %d pe pozitia %d.\n", key, j);
			break;
		}
		i += 1;
		k = j;
	} while (HT->vector[k] != NULL && i != capacitate);
	if (HT->vector[k] == NULL || i == capacitate)
	{
		printf("Nu am gasit acest element: %d.\n", key);
	}
}

void Afisare(HashTable* HT)
{
	printf("Tabelul are: %d celule.\n", HT->capacitate);
	for (int i = 0; i < HT->capacitate; i++)
	{
		printf("%d ", HT->vector[i]);
	}
	printf("\n");
}

void demo()
{
	HashTable* HT = creareHashTable(CAPACITATE_DEMO);
	int vector_intermediar[CAPACITATE_DEMO];
	int capacitate_ocupata;
	if ((CAPACITATE_DEMO * 95) % 100 == 0)
	{
		capacitate_ocupata = CAPACITATE_DEMO * 95 / 100;
	}
	else
	{
		capacitate_ocupata = CAPACITATE_DEMO * 95 / 100 + 1;
	}
	//FillRandomArray(vector_intermediar, capacitate_ocupata, -100, 100, false);
	FillRandomArray(vector_intermediar, capacitate_ocupata, 1, 100, false);
	for (int i = 0; i < capacitate_ocupata; i++)
	{
		inserareHashTable(HT, vector_intermediar[i], CAPACITATE_DEMO);
	}
	Afisare(HT);
	for (int i = 0; i < capacitate_ocupata; i += 3)
	{
		cautareHashTable(HT, vector_intermediar[i], CAPACITATE_DEMO);
	}
}

void inserareEvaluare(HashTable* HT, int key, int capacitate)
{
	int i = 0;
	do {
		int j = functieHash(key, i, capacitate);
		if (HT->vector[j] == NULL)
		{
			HT->vector[j] = key;
			break;
		}
		else
		{
			i += 1;
		}
	} while (i != capacitate);
}

int numarOperatiiCautare(HashTable* HT, int key, int capacitate)
{
	int i = 0;
	int k = functieHash(key, i, capacitate);
	do {
		int j = functieHash(key, i, capacitate);
		if (HT->vector[j] == key)
		{
			break;
		}
		i += 1;
		k = j;
	} while (HT->vector[k] != NULL && i != capacitate);
	return i;
}

void evaluare()
{
	float factori[] = { 0.8, 0.85, 0.9, 0.95, 0.99 };
	printf("     Caz     |  Efort Mediu Gasite  |  Efort Maxim Gasite  |  Efort Mediu Negasite  |  Efort Maxim Negasite  \n");
	for (int j = 0; j < sizeof(factori) / sizeof(float); j++)
	{
		int NOCGasite = 0, NOCNegasite = 0, NOCGMaxim = 0, NOCNMaxim = 0;
		for (int i = 0; i < NR_TESTS; i++)
		{
			HashTable* HT = creareHashTable(CAPACITATE_EVALUARE);
			int vector_intermediar[CAPACITATE_EVALUARE];
			int capacitate_ocupata;
			int intermediar = CAPACITATE_EVALUARE * factori[j] * 100;
			if (intermediar % 100 == 0)
			{
				capacitate_ocupata = intermediar / 100;
			}
			else
			{
				capacitate_ocupata = intermediar / 100 + 1;
			}
			//FillRandomArray(vector_intermediar, capacitate_ocupata, -50000, 50000, false);
			FillRandomArray(vector_intermediar, capacitate_ocupata, 1, 50000, false);
			for (int i = 0; i < capacitate_ocupata; i++)
			{
				inserareEvaluare(HT, vector_intermediar[i], CAPACITATE_EVALUARE);
			}
			int NOCG = 0;
			int NOCN = 0;
			for (int i = 0; i < CAUTARE_ELEMENTE; i += 2)
			{
				NOCG += numarOperatiiCautare(HT, vector_intermediar[i], CAPACITATE_EVALUARE);
			}
			if (NOCG > NOCGMaxim)
			{
				NOCGMaxim = NOCG;
			}
			int V[CAUTARE_ELEMENTE / 2];
			FillRandomArray(V, CAUTARE_ELEMENTE / 2, 50001, 100000, false);
			for (int i = 0; i < (CAUTARE_ELEMENTE / 2); i++)
			{
				NOCN += numarOperatiiCautare(HT, V[i], CAPACITATE_EVALUARE);
			}
			if (NOCN > NOCNMaxim)
			{
				NOCNMaxim = NOCN;
			}
			NOCGasite += NOCG;
			NOCNegasite += NOCN;
		}
		float EMG = (float)NOCGasite / (CAUTARE_ELEMENTE / 2);
		float EMN = (float)NOCNegasite / (CAUTARE_ELEMENTE / 2);
		printf("     %.2f    |       %f       |          %d         |       %f        |          %d", factori[j], EMG, NOCGMaxim, EMN, NOCNMaxim);
		printf("\n");
	}
}

int main()
{
	//demo();
	evaluare();
	return 0;
}