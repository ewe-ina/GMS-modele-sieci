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
#ifdef DEBUG
	printf("Barabasi-Ravasz-Vicsek\n");
#endif // DEBUG

	int k = 0;
	scanf_s("%i", &k);
#ifdef DEBUG
	printf("k = %i\n", k);
#endif // DEBUG
	if (k > 6) return;  // BEZPIECZNIK

	allVertex = 1; // w�ze� w kroku 0

	// LICZBA WIERZCHO�K�W 
	if (k > 0)
	{
		for (int i = 0; i < k; i++)
			allVertex = allVertex * 3;
	}
#ifdef DEBUG
	printf("Liczba wierzcholkow: %i\n", allVertex);
#endif // DEBUG


	// LICZBA KRAWE�DZI                 
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
#ifdef DEBUG
	printf("Liczba krawedzi: %i\n", m);
#endif // DEBUG


	distanceMatrix = createMatrix();
	indexMatrix = createMatrix();

	// TODO: zbudowa� graf --> macierz s�siedztwa i macie� identyfikator�w
	// je�li jest krawedz: macierzSasiedztwa[i][j] = 1
	// indexMatrix[i][j] = i <=> macierzSasiedztwa[i][j] = 1
	// je�li nie ma krawedzi to macierzSasiedztwa[i][j] = niesko�czono��, a indexMatrix[i][j] jest niezainicjalizowana

	// krok 0
	int i = 0;
	int j = 0;
	int copyVertex = 0;
	int copyIndex_i = 0;
	int copyIndex_j = 0;
	int prevCopyIndex = 0;
	//int prevCopyIndex_j = 0;

	// krok 1
	if (k > 0)
	{
		for (i = 1; i < 3; i++)
		{
			distanceMatrix[i][j] = distanceMatrix[j][i] = 1;
			indexMatrix[i][j] = i;
			indexMatrix[j][i] = j;
		}
		copyVertex = 3;
	}

	// krok >=2
	if (k > 1)
	{
		for (int step = 2; step <= k; step++)
		{
			for (int i = 0; i < copyVertex; i++)
			{
				for (int j = 0; j < copyVertex; j++)
				{
					if (distanceMatrix[i][j] == 1)
					{
						copyIndex_i = i + copyVertex;
						copyIndex_j = j + copyVertex;
						distanceMatrix[copyIndex_i][copyIndex_j] = 1;
						indexMatrix[copyIndex_i][copyIndex_j] = 1;

						if (j > prevCopyIndex && distanceMatrix[0][j] == 1)
						{
							distanceMatrix[0][copyIndex_j] = distanceMatrix[copyIndex_j][0] = 1;
							indexMatrix[0][copyIndex_j] = 0;
							indexMatrix[copyIndex_j][0] = copyIndex_j;
						}

						copyIndex_i += copyVertex;
						copyIndex_j += copyVertex;
						distanceMatrix[copyIndex_i][copyIndex_j] = 1;
						indexMatrix[copyIndex_i][copyIndex_j] = 1;

						if (j > prevCopyIndex && distanceMatrix[0][j] == 1)
						{
							distanceMatrix[0][copyIndex_j] = distanceMatrix[copyIndex_j][0] = 1;
							indexMatrix[0][copyIndex_j] = 0;
							indexMatrix[copyIndex_j][0] = copyIndex_j;
						}
					}
				}
			}

			// dolne z korzeniem - DONE WYZEJ
			// czyli te, kt�re do�o�one w poprzednim kroku by�y po��czone z korzeniem, z przesuni�ciem o copyVertex i 2*copyVertex
			// czyli zaczynami nie od 0, a od prevCopyIndex;


			// na ko�cu p�tli
			prevCopyIndex = copyVertex;
			copyVertex *= 3;
		}

		// przej�� po ca�ej distanceMartix, je�li nie ma kraw�dzi oraz i != j to niesko�czono��
		for (int i = 0; i < allVertex; i++)
		{
			for (int j = 0; j < allVertex; j++)
			{
				if (i != j && distanceMatrix[i][j] == 0)
				{
					distanceMatrix[i][j] = MAXVAL;
				}
			}
		}
	}
	



	//printMatrix(distanceMatrix);
	
	Floyd_Warshall();

	deleteMatrix(distanceMatrix);
		
}

void Lu_Su_Guo()
{
#ifdef DEBUG
	printf("Lu-Su-Guo\n");
#endif // DEBUG

	
	// test 1 6 -> JEST OK
	// matrixForTest();
}

void Simplical()
{
#ifdef DEBUG
	printf("Simplical\n");
#endif // DEBUG
	
}

void Wzrostowo_iteracyjny()
{
#ifdef DEBUG
	printf("Wzrostowo-iteracyjny\n");
#endif // DEBUG
	
}

void DCN()
{
#ifdef DEBUG
	printf("DCN\n");
#endif // DEBUG
	
}

void GFG()
{
#ifdef DEBUG
	printf("GFG\n");
#endif // DEBUG
	
}
void Kronecker()
{
#ifdef DEBUG
	printf("Kronecker\n");
#endif // DEBUG

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
	long long int result = 0;

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
			if (distanceMatrix[i][j] != MAXVAL)
			{
				result += distanceMatrix[i][j];
			}
		}
	}

	result /= 2; // nasz graf nie jest kierunkowy, wi�c algorytm ka�d� kraw�d� liczy jak dwie w dw�ch kierunkach, dlatego wynik trzeb apodzieli� na 2

#ifdef DEBUG
	printf("Result = %lli\n", result);
#else
	printf("%lli\n", result);
#endif // DEBUG

	
}


// POMOCNICZE
void matrixForTest()
{
	// dla wej�cia: 1 6 | wyjscie: 20
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
	distanceMatrix[1][5] = MAXVAL;
	//indexMatrix[1][5] = 1;
	distanceMatrix[2][0] = 1;
	indexMatrix[2][0] = 2;
	distanceMatrix[2][1] = 1;
	indexMatrix[2][1] = 2;
	distanceMatrix[2][3] = MAXVAL;
	//indexMatrix[2][3] = 2;
	distanceMatrix[2][4] = MAXVAL;
	//indexMatrix[2][4] = 2;
	distanceMatrix[2][5] = 1;
	indexMatrix[2][5] = 2;
	distanceMatrix[3][0] = 1;
	indexMatrix[3][0] = 3;
	distanceMatrix[3][1] = 1;
	indexMatrix[3][1] = 3;
	distanceMatrix[3][2] = MAXVAL;
	distanceMatrix[3][4] = 1;
	indexMatrix[3][4] = 3;
	distanceMatrix[3][5] = MAXVAL;
	//indexMatrix[3][5] = 3;
	distanceMatrix[4][0] = 1;
	indexMatrix[4][0] = 4;
	distanceMatrix[4][1] = 1;
	indexMatrix[4][1] = 4;
	distanceMatrix[4][2] = MAXVAL;
	distanceMatrix[4][3] = 1;
	indexMatrix[4][3] = 4;
	distanceMatrix[4][5] = MAXVAL;
	//indexMatrix[4][5] = 4;
	distanceMatrix[5][0] = 1;
	indexMatrix[5][0] = 5;
	distanceMatrix[5][1] = MAXVAL;
	distanceMatrix[5][2] = 1;
	indexMatrix[5][2] = 5;
	distanceMatrix[5][3] = MAXVAL;
	distanceMatrix[5][4] = MAXVAL;

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