//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
#include "functions.h"

void getModel(int model)
{
	switch (model)
	{
	case 0:
		//Barabasi_Ravasz_Vicsek();
		Barabasi_Ravasz_Vicsek_v2();
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

void Barabasi_Ravasz_Vicsek_v2()
{
#ifdef DEBUG
	printf("Barabasi-Ravasz-Vicsek\n");
#endif // DEBUG

	int k = 0;
	scanf_s("%i", &k);
#ifdef DEBUG
	printf("k = %i\n", k);
#endif // DEBUG
	//if (k > 7) return;  // BEZPIECZNIK !!! przy k==8 na STOSie exception ACCESS_VIOLATION przy wype³nianiu (a nie wychodzimy indeksami poza zakres!)

	allVertex = 1; // wêze³ w kroku 0

	// LICZBA WIERZCHO£KÓW 
	if (k > 0)
	{
		for (int i = 0; i < k; i++)
			allVertex = allVertex * 3;
	}
#ifdef DEBUG
	printf("Liczba wierzcholkow: %i\n", allVertex);

	int m = 0;
	// LICZBA KRAWEÊDZI                 
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
#endif // DEBUG


	adjacencyMatrix = createMatrix();
	indexMatrix = createMatrix();

	// TODO: zbudowaæ graf --> macierz s¹siedztwa i macieæ identyfikatorów
	// jeœli jest krawedz: macierzSasiedztwa[i][j] = 1
	// indexMatrix[i][j] = i <=> macierzSasiedztwa[i][j] = 1
	// jeœli nie ma krawedzi to macierzSasiedztwa[i][j] = nieskoñczonoœæ, a indexMatrix[i][j] jest niezainicjalizowana

	// krok 0
	short i = 0;
	short j = 0;
	short copyVertex = 0;

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
		short copyIndex_i = 0;
		short copyIndex_j = 0;
		short prevCopyIndex = 0;

		for (int step = 2; step <= k; step++)
		{
			for (i = 0; i < copyVertex; i++)
			{
				for (j = 0; j < copyVertex; j++)
				{
#ifdef DEBUG
					if (i >= allVertex || j >= allVertex)
						printf("i = %i, j = %i\n", i, j);
#endif // DEBUG

					if (adjacencyMatrix[i][j] == 1)
					{
						copyIndex_i = i + copyVertex;
						copyIndex_j = j + copyVertex;
#ifdef DEBUG
						if(copyIndex_i >= allVertex || copyIndex_j >= allVertex)
							printf("copyIndex_i = %i, copyIndex_j = %i\n", copyIndex_i, copyIndex_j);
#endif // DEBUG
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
#ifdef DEBUG
						if (copyIndex_i >= allVertex || copyIndex_j >= allVertex)
							printf("copyIndex_i = %i, copyIndex_j = %i\n", copyIndex_i, copyIndex_j);
#endif // DEBUG
						adjacencyMatrix[copyIndex_i][copyIndex_j] = 1;
						indexMatrix[copyIndex_i][copyIndex_j] = 1;

#ifdef DEBUG
						if (j >= allVertex)
							printf("j = %i\n", j);
#endif // DEBUG
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
			// czyli te, które do³o¿one w poprzednim kroku by³y po³¹czone z korzeniem, z przesuniêciem o copyVertex i 2*copyVertex
			// czyli zaczynami nie od 0, a od prevCopyIndex;


			// na koñcu pêtli
			prevCopyIndex = copyVertex;
			copyVertex *= 3;
		}
	}

	// przepisanie macierzy do list s¹siedztwa
	adjacencyLists = createAdjacencyLists();
	matrixToList();

	int distanceSum = 0;
	distanceSum = countDistances();

	printf("%i\n", distanceSum);


	deleteMatrix(adjacencyMatrix);
	deleteMatrix(indexMatrix);

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

	allVertex = 1; // wêze³ w kroku 0

	// LICZBA WIERZCHO£KÓW 
	if (k > 0)
	{
		for (int i = 0; i < k; i++)
			allVertex = allVertex * 3;
	}
#ifdef DEBUG
	printf("Liczba wierzcholkow: %i\n", allVertex);

	int m = 0;
	// LICZBA KRAWÊDZI                 
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
#endif // DEBUG


	adjacencyMatrix = createMatrix();
	indexMatrix = createMatrix();

	// TODO: zbudowaæ graf --> macierz s¹siedztwa i macieæ identyfikatorów
	// jeœli jest krawedz: macierzSasiedztwa[i][j] = 1
	// indexMatrix[i][j] = i <=> macierzSasiedztwa[i][j] = 1
	// jeœli nie ma krawedzi to macierzSasiedztwa[i][j] = nieskoñczonoœæ, a indexMatrix[i][j] jest niezainicjalizowana

	// krok 0
	short i = 0;
	short j = 0;
	short copyVertex = 0;

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
		short copyIndex_i = 0;
		short copyIndex_j = 0;
		short prevCopyIndex = 0;

		for (int step = 2; step <= k; step++)
		{
			for (i = 0; i < copyVertex; i++)
			{
				for (j = 0; j < copyVertex; j++)
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
			// czyli te, które do³o¿one w poprzednim kroku by³y po³¹czone z korzeniem, z przesuniêciem o copyVertex i 2*copyVertex
			// czyli zaczynami nie od 0, a od prevCopyIndex;


			// na koñcu pêtli
			prevCopyIndex = copyVertex;
			copyVertex *= 3;
		}

		// przejœæ po ca³ej distanceMartix, jeœli nie ma krawêdzi oraz i != j to nieskoñczonoœæ
		addInfinity(adjacencyMatrix);
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

	//wskaŸniki pomocnicze
	vertex* v1;
	vertex* v2;
	vertex* v3;
	vertex* vTemp;
	vertex* listHead;	// wskaŸnik na listê nowych wêz³ów

	//adjacencyListVertex** adjacencyList;	//tablica wskaŸników
	//adjacencyListVertex* aLVertex;			// wskaŸnik nawierzcho³ek w liœcie s¹siedztwa

	adjacencyMatrix = createMatrix();	// pusta macierz s¹siedztwa

	// tu mozna dac tablice wynikow a w ifie ja wypelniac, na koncu drukowac

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
		// krok 0
		// nowy wierzcho³ek - korzeñ
		v1 = malloc(sizeof(vertex)); // wskaŸnik
		if (v1 == NULL)
			return;
		v1->index = 0;
		v1->new = false; // bo to korzeñ

		listHead = v1; // g³owa listy

		// krok 1

		v2 = malloc(sizeof(vertex));
		if (v2 == NULL)
			return;
		v2->index = 2;	
		v2->new = true;
		v2->next = listHead;	// head to v1 next w v2 wskazuje na v1
		listHead = v2;			// head teraz to v2

		v3 = malloc(sizeof(vertex));
		if (v3 == NULL)
			return;
		v3->index = 1;
		v3->new = true;
		v3->next = listHead;		//next node3 o id 1 wskazuje na node2 o id 2
		listHead = v3;

		// aktualna lista nowych wêz³ów
		// head->1->2


		// wypelnienie macierzy s¹siedztwa dla kroku 1
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (i != j)
				{
					adjacencyMatrix[i][j] = 1;
					adjacencyMatrix[j][i] = 1;
				}
			}
		}

		int vertexCounter = 3;

		// krok n (> 1)
		int k = 2;
		int ancesorIndex = 0;
		//int tempIndex = 0;

		while (vertexCounter < allVertex)
		{
			vTemp = listHead;

			stack* s = createStack();  // na stosie bêd¹ nowe wierzcho³ki

			while (vTemp && vTemp->new == true && vertexCounter < allVertex)
			{
				// tworzymy nowy wierzcho³ek i wrzucamy go na stos
				v1 = malloc(sizeof(vertex));
				if (v1 == NULL)
					return;
				v1->index = vertexCounter;
				v1->new = true;
				v1->next = NULL;
				vertexCounter++;
				push(s, v1); // wrzucamy na stos

				// po³¹czenie z rodzicem (jeden wy¿ej)
				adjacencyMatrix[vTemp->index][v1->index] = 1;
				adjacencyMatrix[v1->index][vTemp->index] = 1;

				// po³¹czenie z przodkiem
				ancesorIndex = ((v1->index - 1) / 2) % (k - 1);
				adjacencyMatrix[v1->index][ancesorIndex] = 1;
				adjacencyMatrix[ancesorIndex][v1->index] = 1;

				if (vertexCounter < allVertex) // spr czy dodajemy drugi wierzcho³ek
				{
					// tworzymy nowy wierzcho³ek i wrzucamy go na stos
					v2 = malloc(sizeof(vertex));
					if (v2 == NULL)
						return;
					v2->index = vertexCounter;
					v2->new = true;
					v2->next = NULL;
					vertexCounter++;
					push(s, v2);

					// po³¹czenie z rodzicem (jeden wy¿ej)
					adjacencyMatrix[vTemp->index][v2->index] = 1;
					adjacencyMatrix[v2->index][vTemp->index] = 1;

					// po³¹czenie z przodkiem
					ancesorIndex = ((v2->index - 1) / 2) % (k - 1);
					adjacencyMatrix[v2->index][ancesorIndex] = 1;
					adjacencyMatrix[ancesorIndex][v2->index] = 1;

					// po³¹czenie 2 nowych ze sob¹ nawzajem
					adjacencyMatrix[v1->index][v2->index] = 1;
					adjacencyMatrix[v2->index][v1->index] = 1;


				}
				vTemp->new = false;
				vTemp = vTemp->next;  // przechodzimy do kolejnego
			}
			k++;

			while (!empty(s))  // dopóki stos nie jest pusty
			{
				v1 = top(s);
				pop(s);
				v1->next = listHead;
				listHead = v1;
				vTemp = listHead;
			}
		}


		// macierz jest gotowa, czyli nie potrzebujê tych list powy¿ej (chyba, ¿e bêdzie coœ nie tak, to trzeba siê przyjrzeæ
		// przepisanie macierzy do list s¹siedztwa
		adjacencyLists = createAdjacencyLists();
		matrixToList();

		// TODO algorytm BFS dla list s¹siedztwa (dla macierzy na za du¿¹ z³ozonoœæ czasow¹) DONE
		// zapisywanie wyników do tablicy
		int resultsMemo[1022];	// zapamiêtanie wyników testów, indeks w tablicy to liczba zadanych wierzcho³ków, najwiêksza liczba wierzcho³ków LSG to 1022
								// to do, spr jaka jest faktycznie najwieksza liczba tych wierzcho³ków?				
		for (int i = 0; i < 1022; i++)
			resultsMemo[i] = -1;  // -1 to brak wyniku

		resultsMemo[0] = 0;
		resultsMemo[1] = 0;
		resultsMemo[2] = 1;
		resultsMemo[3] = 3;

		// jeœli wyniku w tabali brak (sprawdzenie to O(1), to liczymy 
		if (resultsMemo[allVertex] == -1)
		{
			int distanceSum = 0;
			distanceSum = countDistances();
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
		short i, j;
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

		short trackIndex = 1;
		short prevAddedVertex = i - trackIndex;
#ifdef DEBUG
		printf("trackIndex = %i\nliczba ostatnio dodanych wierzchow = %i\n", trackIndex, prevAddedVertex);
#endif // DEBUG

		// krok n (<1)
		if (allVertex > 3)
		{
			int k = 2;
			short ancesorIndex = 0;
			
			// to lacznie z przodkami w duzej petli do --tu break?-- while (i < allVertex)
			do
			{
				short tempIndex = 0;
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

					// po³¹czenie miêdzy dodan¹ par¹
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
	
	scanf_s("%i", &allVertex);
#ifdef DEBUG
	printf("liczba wierzcholkow = %i\n", allVertex);
#endif // DEBUG

	adjacencyMatrix = createMatrix();
	adjacencyLists = createAdjacencyLists();
	adjacencyListVertex* v;

	// krok 0
	// nowy wierzcho³ek - korzeñ
	v = malloc(sizeof(adjacencyListVertex)); // wskaŸnik
	if (v == NULL)
		return;
	v->index = 0;
	v->bottom = true;
	v->next = NULL;

	// lista s¹siedztwa - v0 na razie brak s¹siadów, reszta - ka¿dy ma za s¹siada v0
	adjacencyLists[0] = NULL;
	for (int i = 1; i < allVertex; i++)
	{
		adjacencyLists[i] = v;
	}

	// zliczenie odleg³oœci od ka¿dego po przodkach do v0 - póŸniej siê to przyda
	//int* throughAncestors = (int*)calloc(allVertex, sizeof(int));
	int throughAncestors[1022];
	for (int i = 0; i < 1022; i++)
	{
		throughAncestors[i] = 0;
	}

	for (int i = 3; i < allVertex; i++)
	{
		if (i % 2 == 1)
		{
			throughAncestors[i] = i / 2;
		}
		else
		{
			throughAncestors[i] = (i - 1) / 2;
		}
	}

	for (int i = 3; i < allVertex; i++)
	{
		int index = throughAncestors[i];
		while (index != 0)
		{
			v = malloc(sizeof(adjacencyListVertex));
			if (v == NULL)
				break;
			v->index = index;
			v->bottom = false; //?
			v->next = adjacencyLists[i];
			adjacencyLists[i] = v;
			index = throughAncestors[index];
		}
	}

	for (int i = 0; i < allVertex; i++)
	{
		v = adjacencyLists[i];
		while (v)
		{
			adjacencyMatrix[i][v->index] = 1;  // na liscie to by³oby trudne...
			adjacencyMatrix[v->index][i] = 1;
			v = v->next;
		}
	}


	// wyczyszczenie tymczasowej listy s¹siedztwa
	for (int i = allVertex - 1; i > 0; i = i - 2)
	{
		v = adjacencyLists[i];
		if (v)
		{
			free(v);
		}
	}
	for (int i = 0; i < allVertex; i++)
	{
		adjacencyLists[i] = NULL;
	}


	matrixToList();

	int distanceSum = countDistances();
	printf("%i\n", distanceSum);

	//free(throughAncestors);
	deleteMatrix(adjacencyMatrix);
	deleteAdjacencyLists(adjacencyLists);
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

short** createMatrix()
{
	short** matrix = (short**)calloc(allVertex, sizeof(short*));   // calloc od razu inicjalizuje 0
	if (matrix != NULL)
	{
		for (int i = 0; i < allVertex; ++i)
			matrix[i] = (short*)calloc(allVertex, sizeof(short));
	}

	return matrix;
}

void deleteMatrix(short** matrix)
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
	adjacencyListVertex**  adjcLists = (adjacencyListVertex**)calloc(allVertex, sizeof(adjacencyListVertex*));
	return adjcLists;
}

void deleteAdjacencyLists(adjacencyListVertex** adjcLists)
{
	if (adjcLists != NULL)
	{
		adjacencyListVertex* v;
		adjacencyListVertex* vDelete;
		for (int i = 0; i < allVertex; i++)
		{
			v = adjacencyLists[i];
			while (v)
			{
				vDelete = v;
				v = v->next;
				free(vDelete);
			}
		}
		//free(adjcLists);  // ju¿ wy¿ej zwolniliœmy wskaŸniki, które s¹ bezpoœrednio w tablicy
	}
}


void addInfinity(short** distanceMatrix)
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

void Floyd_Warshall(short** distanceMatrix)
{
	int result = 0;

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

	//result /= 2; // nasz graf nie jest kierunkowy, wiêc algorytm ka¿d¹ krawêdŸ liczy jak dwie w dwóch kierunkach, dlatego wynik trzeb apodzieliæ na 2

#ifdef DEBUG
	printf("Result = %i\n", result);
	printMatrix(distanceMatrix);
#else
	printf("%i\n", result);
#endif // DEBUG

	
}

// zamiana macierzy s¹siedztwa na listê
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
				if (v == NULL)
					return;
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

int countDistances()
{
	int distanceSum = 0;
	for (int v = 0; v < allVertex; v++)
	{
		// suma odleglosci miêdzy wierzcho³kiem v a pozosta³ymi (kolejnymi, unikamy tu powrórnego liczenia odleg³oœci w drug¹ str)
		BFSvertex* sum = BFS(v);
		for (int i = v; i < allVertex; i++)
		{
			//i sumuje te odleg³oœci
			distanceSum += sum[i].distance;

		}
		free(sum);
	}
	return distanceSum;
}

BFSvertex* BFS(int start) // tu wrzucamy listê s¹siedztwa
{
	adjacencyListVertex* v;
	BFSvertex* tab = malloc(sizeof(BFSvertex) * allVertex);

	if (tab == NULL)
		return NULL;

	for (int i = 0; i < allVertex; i++) 
	{
		tab[i].distance = MAXVAL;
		tab[i].visited = false;
	}
	
	tab[start].distance = 0;
	tab[start].visited = true;


	queue *q = createQueue();  // tworzymy kolejkê
	enqueue(q, start);	
	while (!emptyQ(q)) 
	{
		int u = frontQ(q);

		dequeue(q);
		v = adjacencyLists[u];

		while (v) 
		{
			if ((v->index != u) && (tab[v->index].visited == false)) 
			{
				tab[v->index].distance = tab[u].distance + 1;
				tab[v->index].visited = true;

				enqueue(q, v->index);
			}
			v = v->next;
		}
	}

	return tab;
}

// POMOCNICZE
#ifdef DEBUG
void matrixForTest()
{
	// dla wejœcia: 1 6 | wyjscie: 20
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

void printMatrix(short** matrix)
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
#endif // DEBUG
