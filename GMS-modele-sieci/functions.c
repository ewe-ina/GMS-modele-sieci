#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void getModel(int model)
{
	switch (model)
	{
	case 0:
		Barabasi_Ravasz_Vicsek();
		break;
	case 1:
		Lu_Su_Guo();
		break;
	case 2:
		Simplical();
		break;
	case 3:
		Wzrostowo_iteracyjny();
		break;
	case 4:
		DCN();
		break;
	case 5:
		GFG();
		break;
	case 6:
		Kronecker();
		break;
	default:
		break;
	}
}

void Barabasi_Ravasz_Vicsek()
{
	printf("Barabasi-Ravasz-Vicsek\n");
	int k = 0;
	scanf_s("%i", &k);
	printf("k = %i\n", k);

	allVertex = 1; // wêze³ w kroku 0

	// LICZBA WIERZCHO£KÓW 
	if (k > 0)
	{
		for (int i = 0; i < k; i++)
			allVertex = allVertex * 3;
	}
	printf("Liczba wierzcholkow: %i\n", allVertex);

	// LICZBA KRAWEÊDZI                 
	int m = 0;
	if (k > 0)
	{
		int j = 1;
		for (int i = 0; i < k; i++) 
		{
			j = j * 2;
			m = m * 3 + j;
		}
	}
	printf("Liczba krawedzi: %i\n", m);
		
}

	void Lu_Su_Guo()
	{
		printf("Lu-Su-Guo\n");
	}

	void Simplical()
	{
		printf("Simplical\n");
	}

	void Wzrostowo_iteracyjny()
	{
		printf("Wzrostowo-iteracyjny\n");
	}

	void DCN()
	{
		printf("DCN\n");
	}

	void GFG()
	{
		printf("GFG\n");
	}
	void Kronecker()
	{
		printf("Kronecker\n");
	}


// POMOCNICZE
void printMatrix(int **Matrix)
{
    for(int i=0; i<allVertex; i++) {
        for(int j=0;j<allVertex; j++)
            printf("%3i",Matrix[i][j]);
        printf("\n");
    }
}