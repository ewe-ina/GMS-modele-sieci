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
		//Lu_Su_Guo();
		Lu_Su_Guo_v2();
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


	adjacencyMatrix = createMatrix();
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
			adjacencyMatrix[i][j] = adjacencyMatrix[j][i] = 1;
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
					if (adjacencyMatrix[i][j] == 1)
					{
						copyIndex_i = i + copyVertex;
						copyIndex_j = j + copyVertex;
						adjacencyMatrix[copyIndex_i][copyIndex_j] = 1;
						indexMatrix[copyIndex_i][copyIndex_j] = 1;

						if (j > prevCopyIndex && adjacencyMatrix[0][j] == 1)
						{
							adjacencyMatrix[0][copyIndex_j] = adjacencyMatrix[copyIndex_j][0] = 1;
							indexMatrix[0][copyIndex_j] = 0;
							indexMatrix[copyIndex_j][0] = copyIndex_j;
						}

						copyIndex_i += copyVertex;
						copyIndex_j += copyVertex;
						adjacencyMatrix[copyIndex_i][copyIndex_j] = 1;
						indexMatrix[copyIndex_i][copyIndex_j] = 1;

						if (j > prevCopyIndex && adjacencyMatrix[0][j] == 1)
						{
							adjacencyMatrix[0][copyIndex_j] = adjacencyMatrix[copyIndex_j][0] = 1;
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
		addInfinity(adjacencyMatrix);
		/*for (int i = 0; i < allVertex; i++)
		{
			for (int j = 0; j < allVertex; j++)
			{
				if (i != j && distanceMatrix[i][j] == 0)
				{
					distanceMatrix[i][j] = MAXVAL;
				}
			}
		}*/
	}
	



	//printMatrix(adjacencyMatrix);
	
	Floyd_Warshall(adjacencyMatrix);

	deleteMatrix(adjacencyMatrix);
	deleteMatrix(indexMatrix);
		
}

void Lu_Su_Guo_v2()
{
#ifdef DEBUG
	printf("Lu-Su-Guo v2\n");
#endif // DEBUG

	scanf_s("%i", &allVertex);
#ifdef DEBUG
	printf("liczba wierzcholkow = %i\n", allVertex);
#endif // DEBUG

	////wska�niki pomocnicze
	//vertex* v1;
	//vertex* v2;
	//vertex* v3;
	//vertex* vTemp;
	//vertex* listHead;

	////adjacencyListVertex** adjacencyList;	//tablica wska�nik�w
	//adjacencyListVertex* aLVertex;			// wska�nik nawierzcho�ek w li�cie s�siedztwa

	//createMatrix();	// pusta macierz s�siedztwa

	//// krok 0
	//// nowy wierzcho�ek - korze�
	//v1 = malloc(sizeof(vertex)); // wska�nik
	//v1->index = 0;
	//v1->new = false; // bo to korze�

	//listHead = v1; // g�owa listy

	//// krok 1

	//v2 = malloc(sizeof(vertex));
	//v2->index = 2;	
	//v2->new = true;
	//v2->next = listHead;	// head to v1 next w v2 wskazuje na v1
	//listHead = v2;			// head teraz to v2

	//v3 = malloc(sizeof(vertex));
	//v3->index = 1;
	//v3->new = true;
	//v3->next = listHead;		//next node3 o id 1 wskazuje na node2 o id 2
	//listHead = v3;

	// aktualna lista nowych w�z��w
	// head->1->2

	adjacencyMatrix = createMatrix();

	// krok 0
	if (allVertex < 2)
	{
		printf("%i\n", 0);
	}
	else if (allVertex == 2)
	{
		printf("%i\n", 1);
	}
	else
	{
		// krok 1
		int i, j;
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				if (i != j)
				{
					adjacencyMatrix[i][j] = 1;
					adjacencyMatrix[j][i] = 1;
				}
			}
		}

		//int vertexCounter = 3;	// nie wiem czy bedzie potrzebny
		int trackIndex = 1;
		int prevAddedVertex = i - trackIndex;

		// krok n (<1)
		int k = 2;
		int ancesorIndex = 0;
		int tempIndex = 0;

		if (allVertex > 3)
		{
			// to lacznie z przodkami w duzej petli do --tu break?-- while (i < allVertex)
			do
			{
				tempIndex = trackIndex;
				for (j = trackIndex; j <= prevAddedVertex; j++)
				{
					adjacencyMatrix[i][j] = adjacencyMatrix[j][i] = 1;
					//polaczenie z przodkiem
					ancesorIndex = ((i - 1) / 2) % (k - 1);
					adjacencyMatrix[i][ancesorIndex] = adjacencyMatrix[ancesorIndex][i] = 1;

					i++;
					if (i >= allVertex)
						break;

					adjacencyMatrix[i][j] = adjacencyMatrix[j][i] = 1;
					//polaczenie z przodkiem
					ancesorIndex = ((i - 1) / 2) % (k - 1);
					adjacencyMatrix[i][ancesorIndex] = adjacencyMatrix[ancesorIndex][i] = 1;

					// po��czenie mi�dzy dodan� par�
					adjacencyMatrix[i][i - 1] = adjacencyMatrix[i - 1][i] = 1;

					trackIndex++;

					i++;
					if (i >= allVertex)
						break;
				}

				prevAddedVertex = i - tempIndex;
				k++;

			} while (i < allVertex);

		}

		// macierz jest gotowa, czyli nie potrzebuj� tych list powy�ej (chyba, �e b�dzie co� nie tak, to trzeba si� przyjrze�
		// przepisanie macierzy do list s�siedztwa
		adjacencyLists = createAdjacencyLists();
		matrixToList();

		// TODO algorytm BFS dla list s�siedztwa (dla macierzy na za du�� z�ozono�� czasow�)
		// TODO zapisywanie wynik�w do tablicy
		int resultsMemo[1022];	// zapami�tanie wynik�w test�w, indeks w tablicy to liczba zadanych wierzcho�k�w, najwi�ksza liczba wierzcho�k�w LSG to 1022
								// to do, spr jaka jest faktycznie najwieksza liczba tych wierzcho�k�w?				
		for (int i = 0; i < 1022; i++)
			resultsMemo[i] = -1;  // -1 to brak wyniku

		resultsMemo[0] = 0;
		resultsMemo[1] = 0;
		resultsMemo[2] = 1;
		resultsMemo[3] = 3;

		// je�li wyniku w tabali brak (sprawdzenie to O(1), to liczymy 
		if (resultsMemo[allVertex] == -1)
		{
			int distanceSum = 0;
			for (int v = 0; v < allVertex; v++)
			{
				// suma odleglosci mi�dzy wierzcho�kiem v a pozosta�ymi (kolejnymi, unikamy tu powr�rnego liczenia odleg�o�ci w drug� str)
				BFSvertex* sum = BFS(v);
				for (int i = v; i < allVertex; i++)
				{
					//i sumuje te odleg�o�ci
					distanceSum += sum[i].distance;

				}
				free(sum);
			}

			resultsMemo[allVertex] = distanceSum;
		}

		printf("%i\n", resultsMemo[allVertex]);
	}

	deleteMatrix(adjacencyMatrix);
	deleteAdjacencyLists(adjacencyLists);
}

void Lu_Su_Guo()
{
#ifdef DEBUG
	printf("Lu-Su-Guo\n");
#endif // DEBUG

	scanf_s("%i", &allVertex);
#ifdef DEBUG
	printf("liczba wierzcholkow = %i\n", allVertex);
#endif // DEBUG

	adjacencyMatrix = createMatrix();
	indexMatrix = createMatrix();

	// krok 0
	if (allVertex < 2)
	{
		printf("%i\n", 0);
	}
	else if (allVertex == 2)
	{
		printf("%i\n", 1);
	}
	else
	{
		// krok 1
		int i, j;
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				if (i != j)
				{
					adjacencyMatrix[i][j] = 1;
					indexMatrix[i][j] = i;
					adjacencyMatrix[j][i] = 1;
					indexMatrix[j][i] = j;
				}
			}
		}

		int trackIndex = 1;
		int prevAddedVertex = i - trackIndex;
#ifdef DEBUG
		printf("trackIndex = %i\nliczba ostatnio dodanych wierzchow = %i\n", trackIndex, prevAddedVertex);
#endif // DEBUG

		// krok n (<1)
		int k = 2;
		int ancesorIndex = 0;
		int tempIndex = 0;

		if (allVertex > 3)
		{
			// to lacznie z przodkami w duzej petli do --tu break?-- while (i < allVertex)
			do
			{
				tempIndex = trackIndex;
				for (j = trackIndex; j <= prevAddedVertex; j++)
				{
					adjacencyMatrix[i][j] = adjacencyMatrix[j][i] = 1;
					indexMatrix[i][j] = i;
					indexMatrix[j][i] = j;
					//polaczenie z przodkiem
					ancesorIndex = ((i - 1) / 2) % (k - 1);
					adjacencyMatrix[i][ancesorIndex] = adjacencyMatrix[ancesorIndex][i] = 1;
					indexMatrix[i][ancesorIndex] = i;
					indexMatrix[ancesorIndex][i] = ancesorIndex;

					i++; 
					if (i >= allVertex)
						break;

					adjacencyMatrix[i][j] = adjacencyMatrix[j][i] = 1;
					indexMatrix[i][j] = i;
					indexMatrix[j][i] = j;
					//polaczenie z przodkiem
					ancesorIndex = ((i - 1) / 2) % (k - 1);
					adjacencyMatrix[i][ancesorIndex] = adjacencyMatrix[ancesorIndex][i] = 1;
					indexMatrix[i][ancesorIndex] = i;
					indexMatrix[ancesorIndex][i] = ancesorIndex;

					// po��czenie mi�dzy dodan� par�
					adjacencyMatrix[i][i - 1] = adjacencyMatrix[i - 1][i] = 1;
					indexMatrix[i][i - 1] = i;
					indexMatrix[i - 1][i] = i - 1;

					trackIndex++;

					i++;
					if (i >= allVertex)
						break;
				}

				prevAddedVertex = i - tempIndex;
				k++;

			} while (i < allVertex);

		}

#ifdef DEBUG
		printMatrix(adjacencyMatrix);
		printf("\n");
		printMatrix(indexMatrix);
		printf("\n");
#endif // DEBUG

		
		addInfinity(adjacencyMatrix);
		Floyd_Warshall(adjacencyMatrix);
	}

	deleteMatrix(adjacencyMatrix);
	deleteMatrix(indexMatrix);
	
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

int** createMatrix()
{
	int** matrix = (int**)calloc(allVertex, sizeof(int*));
	if (matrix != NULL)
	{
		for (int i = 0; i < allVertex; ++i)
			matrix[i] = (int*)calloc(allVertex, sizeof(int));
	}

	for (int i = 0; i < allVertex; i++) // TO RACZEJ NIEPOTRZEBNE
	{
		for (int j = 0; j < allVertex; j++)
		{
			
			if (matrix != NULL && *matrix != NULL)
			{
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


adjacencyListVertex** createAdjacencyLists()
{
	adjacencyListVertex** tab = (adjacencyListVertex**)calloc(allVertex, sizeof(adjacencyListVertex*));
	return tab;
}

void deleteAdjacencyLists(adjacencyListVertex** adjacencyLists)
{
	if (adjacencyLists != NULL)
	{
		free(adjacencyLists);
	}
}


void addInfinity(int** distanceMatrix)
{
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

void Floyd_Warshall(int** distanceMatrix)
{
	long long int result = 0;

	for (int u = 0; u < allVertex; u++)
	{
		for (int i = 0; i < allVertex; i++)
		{
			for (int j = 0; j < allVertex; j++)
			{
				if (distanceMatrix[i][u] != MAXVAL && distanceMatrix[u][j] != MAXVAL && distanceMatrix[i][j] > distanceMatrix[i][u] + distanceMatrix[u][j])
				{
					distanceMatrix[i][j] = distanceMatrix[i][u] + distanceMatrix[u][j];
					indexMatrix[i][j] = indexMatrix[u][j];
				}
			}
		}
	}


	for (int i = 0; i < allVertex; i++)
	{
		for (int j = i; j < allVertex; j++)
		{
			if (distanceMatrix[i][j] != MAXVAL)
			{
				result += distanceMatrix[i][j];
			}
		}
	}

	//result /= 2; // nasz graf nie jest kierunkowy, wi�c algorytm ka�d� kraw�d� liczy jak dwie w dw�ch kierunkach, dlatego wynik trzeb apodzieli� na 2

#ifdef DEBUG
	printf("Result = %lli\n", result);
	printMatrix(distanceMatrix);
#else
	printf("%lli\n", result);
#endif // DEBUG

	
}

// zamiana macierzy s�siedztwa na list�
void matrixToList() 
{
#ifdef DEBUG
	printMatrix(adjacencyMatrix);
#endif // DEBUG

	for (int i = allVertex - 1; i >= 0; i--) 
	{
		for (int j = allVertex - 1; j >= 0; j--) 
		{
			if (adjacencyMatrix[i][j] == 1) 
			{
				adjacencyListVertex* v = malloc(sizeof(adjacencyListVertex));				
				v->index = j;
				//v->bottom = false;
				v->next = adjacencyLists[i];
				adjacencyLists[i] = v;
			}
		}
	}
#ifdef DEBUG
	printAdjacencyList();
#endif // DEBUG

}

BFSvertex* BFS(int start) // tu wrzucamy list� s�siedztwa
{
#ifdef DEBUG
	printf("start = %i\n", start);
#endif // DEBUG

	adjacencyListVertex* v;
	BFSvertex* tab = malloc(sizeof(BFSvertex) * allVertex);
	for (int i = 0; i < allVertex; i++) 
	{
		tab[i].distance = MAXVAL;
		tab[i].visited = false;
	}
	
	tab[start].distance = 0;
	tab[start].visited = true;

#ifdef DEBUG
	for (int i = 0; i < allVertex; i++) 
	{
		printf("tab[%i].distance = %9i\n",i, tab[i].distance);
		printf("tab[%i].visited = %9s\n", i, tab[i].visited ? "true" : "false");
	}
	printf("\n");
#endif // DEBUG


	tail = 0;
	head = 0;
	enqueue(start);	// u�ywamy funkcji z queue.c
	while (!emptyQ()) 
	{
		int u = frontQ();

		dequeue();
		v = adjacencyLists[u];

#ifdef DEBUG
		printf("u = %i\n", u);
		printf("v->index = %i\n", v->index);
#endif // DEBUG

		while (v) 
		{
			if ((v->index != u) && (tab[v->index].visited == false)) 
			{
				tab[v->index].distance = tab[u].distance + 1;
				tab[v->index].visited = true;
#ifdef DEBUG
				printf("tab[%i].distance = %i\n", v->index, tab[v->index].distance);
#endif // DEBUG

				enqueue(v->index);
			}
			v = v->next;
		}
	}

#ifdef DEBUG
	for (int i = 0; i < allVertex; i++)
	{
		printf("tab[%i].distance = %9i  ", i, tab[i]);
	}
	printf("\n\n");
#endif // DEBUG

	return tab;
}

// POMOCNICZE
void matrixForTest()
{
	// dla wej�cia: 1 6 | wyjscie: 20
	allVertex = 6;
	adjacencyMatrix = createMatrix();
	indexMatrix = createMatrix();

	adjacencyMatrix[0][1] = 1;
	adjacencyMatrix[0][2] = 1;
	adjacencyMatrix[0][3] = 1;
	adjacencyMatrix[0][4] = 1;
	adjacencyMatrix[0][5] = 1;
	adjacencyMatrix[1][0] = 1;
	indexMatrix[1][0] = 1;
	adjacencyMatrix[1][2] = 1;
	indexMatrix[1][2] = 1;
	adjacencyMatrix[1][3] = 1;
	indexMatrix[1][3] = 1;
	adjacencyMatrix[1][4] = 1;
	indexMatrix[1][4] = 1;
	adjacencyMatrix[1][5] = MAXVAL;
	//indexMatrix[1][5] = 1;
	adjacencyMatrix[2][0] = 1;
	indexMatrix[2][0] = 2;
	adjacencyMatrix[2][1] = 1;
	indexMatrix[2][1] = 2;
	adjacencyMatrix[2][3] = MAXVAL;
	//indexMatrix[2][3] = 2;
	adjacencyMatrix[2][4] = MAXVAL;
	//indexMatrix[2][4] = 2;
	adjacencyMatrix[2][5] = 1;
	indexMatrix[2][5] = 2;
	adjacencyMatrix[3][0] = 1;
	indexMatrix[3][0] = 3;
	adjacencyMatrix[3][1] = 1;
	indexMatrix[3][1] = 3;
	adjacencyMatrix[3][2] = MAXVAL;
	adjacencyMatrix[3][4] = 1;
	indexMatrix[3][4] = 3;
	adjacencyMatrix[3][5] = MAXVAL;
	//indexMatrix[3][5] = 3;
	adjacencyMatrix[4][0] = 1;
	indexMatrix[4][0] = 4;
	adjacencyMatrix[4][1] = 1;
	indexMatrix[4][1] = 4;
	adjacencyMatrix[4][2] = MAXVAL;
	adjacencyMatrix[4][3] = 1;
	indexMatrix[4][3] = 4;
	adjacencyMatrix[4][5] = MAXVAL;
	//indexMatrix[4][5] = 4;
	adjacencyMatrix[5][0] = 1;
	indexMatrix[5][0] = 5;
	adjacencyMatrix[5][1] = MAXVAL;
	adjacencyMatrix[5][2] = 1;
	indexMatrix[5][2] = 5;
	adjacencyMatrix[5][3] = MAXVAL;
	adjacencyMatrix[5][4] = MAXVAL;

	Floyd_Warshall(adjacencyMatrix);

	deleteMatrix(adjacencyMatrix);
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

void printAdjacencyList()
{
	for (int i = 0; i < allVertex; i++)
	{
		adjacencyListVertex* ptr = adjacencyLists[i];

		//start from the beginning
		printf("[%d]", i);
		while (ptr != NULL)
		{
			printf(" -> %d", ptr->index);
			ptr = ptr->next;
		}

		printf("\n");
	}
}