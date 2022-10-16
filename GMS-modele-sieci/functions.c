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

	distanceMatrix = createMatrix();
	indexMatrix = createMatrix();

	// TODO: zbudowaæ graf --> macierz s¹siedztwa i macieæ identyfikatorów
	// jeœli jest krawedz: macierzSasiedztwa[i][j] = 1
	// indexMatrix[i][j] = i <=> macierzSasiedztwa[i][j] = 1
	// jeœli nie ma krawedzi to macierzSasiedztwa[i][j] = nieskoñczonoœæ, a indexMatrix[i][j] jest niezainicjalizowana


	printMatrix(distanceMatrix);
	
	Floyd_Warshall();

	deleteMatrix(distanceMatrix);
		
}

void Lu_Su_Guo()
{
	printf("Lu-Su-Guo\n");
	// test 1 6 -> JEST OK
	// matrixForTest();
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

int** createMatrix() // moze zainicjowac wartosciami -1?
{
	int** matrix = (int**)calloc(allVertex, sizeof(int*));
	if (matrix != NULL)
	{
		for (int i = 0; i < allVertex; ++i)
			matrix[i] = (int*)calloc(allVertex, sizeof(int));
	}

	for (int i = 0; i < allVertex; i++)
	{
		for (int j = 0; j < allVertex; j++)
		{
			
			if (matrix != NULL && *matrix != NULL)
			{
			//printf("[i,j] = [%i,%i]\n", i, j);
			matrix[i][j] = 0;
			}
		}
	}

	return matrix;
}

void deleteMatrix(int** matrix)
{
	if (matrix != NULL)
	{
		for (int i = 0; i < allVertex; ++i)
			free(matrix[i]);
		free(matrix);
	}
}

void Floyd_Warshall()
{
	int result = 0;

	for (int u = 0; u < allVertex; u++)
	{
		for (int i = 0; i < allVertex; i++)
		{
			for (int j = 0; j < allVertex; j++)
			{
				if (distanceMatrix[i][j] > distanceMatrix[i][u] + distanceMatrix[u][j])
				{
					distanceMatrix[i][j] = distanceMatrix[i][u] + distanceMatrix[u][i];
					indexMatrix[i][j] = indexMatrix[u][j];
				}
			}
		}
	}

	for (int i = 0; i < allVertex; i++)
	{
		for (int j = 0; j < allVertex; j++)
		{
			if (distanceMatrix[i][j] != INT_MAX)
			{
				result += distanceMatrix[i][j];
			}
		}
	}

	result /= 2; // nasz graf nie jest kierunkowy, wiêc algorytm ka¿d¹ krawêdŸ liczy jak dwie w dwóch kierunkach, dlatego wynik trzeb apodzieliæ na 2

	printf("Result = %i\n", result);
}


// POMOCNICZE
void matrixForTest()
{
	// dla wejœcia: 1 6 | wyjscie: 20
	allVertex = 6;
	distanceMatrix = createMatrix();
	indexMatrix = createMatrix();

	distanceMatrix[0][1] = 1;
	distanceMatrix[0][2] = 1;
	distanceMatrix[0][3] = 1;
	distanceMatrix[0][4] = 1;
	distanceMatrix[0][5] = 1;
	distanceMatrix[1][0] = 1;
	indexMatrix[1][0] = 1;
	distanceMatrix[1][2] = 1;
	indexMatrix[1][2] = 1;
	distanceMatrix[1][3] = 1;
	indexMatrix[1][3] = 1;
	distanceMatrix[1][4] = 1;
	indexMatrix[1][4] = 1;
	distanceMatrix[1][5] = INT_MAX;
	//indexMatrix[1][5] = 1;
	distanceMatrix[2][0] = 1;
	indexMatrix[2][0] = 2;
	distanceMatrix[2][1] = 1;
	indexMatrix[2][1] = 2;
	distanceMatrix[2][3] = INT_MAX;
	//indexMatrix[2][3] = 2;
	distanceMatrix[2][4] = INT_MAX;
	//indexMatrix[2][4] = 2;
	distanceMatrix[2][5] = 1;
	indexMatrix[2][5] = 2;
	distanceMatrix[3][0] = 1;
	indexMatrix[3][0] = 3;
	distanceMatrix[3][1] = 1;
	indexMatrix[3][1] = 3;
	distanceMatrix[3][2] = INT_MAX;
	distanceMatrix[3][4] = 1;
	indexMatrix[3][4] = 3;
	distanceMatrix[3][5] = INT_MAX;
	//indexMatrix[3][5] = 3;
	distanceMatrix[4][0] = 1;
	indexMatrix[4][0] = 4;
	distanceMatrix[4][1] = 1;
	indexMatrix[4][1] = 4;
	distanceMatrix[4][2] = INT_MAX;
	distanceMatrix[4][3] = 1;
	indexMatrix[4][3] = 4;
	distanceMatrix[4][5] = INT_MAX;
	//indexMatrix[4][5] = 4;
	distanceMatrix[5][0] = 1;
	indexMatrix[5][0] = 5;
	distanceMatrix[5][1] = INT_MAX;
	distanceMatrix[5][2] = 1;
	indexMatrix[5][2] = 5;
	distanceMatrix[5][3] = INT_MAX;
	distanceMatrix[5][4] = INT_MAX;

	Floyd_Warshall();

	deleteMatrix(distanceMatrix);
	deleteMatrix(indexMatrix);
}

void printMatrix(int** matrix)
{
	if (matrix != NULL)
	{
		for (int i = 0; i < allVertex; i++)
		{
			for (int j = 0; j < allVertex; j++)
			{
				printf("%3i", matrix[i][j]);
			}
			printf("\n");
		}
	}
}