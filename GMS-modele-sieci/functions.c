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
		//Wzrostowo_iteracyjny();
		Wzrostowo_iteracyjny_v2();
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

void Barabasi_Ravasz_Vicsek_v2() // można jeszcze zapamiętywać macierz z poprzedniego kroku
{
#ifdef DEBUG
	printf("Barabasi-Ravasz-Vicsek\n");
#endif // DEBUG

	int k = 0;
	scanf_s("%i", &k);
#ifdef DEBUG
	printf("k = %i\n", k);
#endif // DEBUG
	//if (k > 7) return;  // BEZPIECZNIK !!! przy k==8 na STOSie exception ACCESS_VIOLATION przy wypełnianiu (a nie wychodzimy indeksami poza zakres!)
							// malloc przyc=dzielil za malo pamieci - zmiana int na short pomogla, ale wciaz dziala za wolno dla k=8

	allVertex = 1; // węzeł w kroku 0

	// LICZBA WIERZCHOŁKÓW 
	if (k > 0)
	{
		for (int i = 0; i < k; i++)
			allVertex = allVertex * 3;
	}
#ifdef DEBUG
	printf("Liczba wierzcholkow: %i\n", allVertex);

	int m = 0;
	// LICZBA KRAWEĘDZI                 
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


	adjacencyMatrix = createMatrix(allVertex);

	// zbudować graf --> macierz sąsiedztwa
	// jeśli jest krawedz: macierzSasiedztwa[i][j] = 1

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

						if (j > prevCopyIndex && adjacencyMatrix[0][j] == 1)
						{
							adjacencyMatrix[0][copyIndex_j] = 1;
							adjacencyMatrix[copyIndex_j][0] = 1;
						}

						copyIndex_i += copyVertex;
						copyIndex_j += copyVertex;
#ifdef DEBUG
						if (copyIndex_i >= allVertex || copyIndex_j >= allVertex)
							printf("copyIndex_i = %i, copyIndex_j = %i\n", copyIndex_i, copyIndex_j);
#endif // DEBUG
						adjacencyMatrix[copyIndex_i][copyIndex_j] = 1;

#ifdef DEBUG
						if (j >= allVertex)
							printf("j = %i\n", j);
#endif // DEBUG
						if (j > prevCopyIndex && adjacencyMatrix[0][j] == 1)
						{
							adjacencyMatrix[0][copyIndex_j] = 1;
							adjacencyMatrix[copyIndex_j][0] = 1;
						}
					}
				}
			}

			// dolne z korzeniem - DONE WYZEJ
			// czyli te, które dołożone w poprzednim kroku były połączone z korzeniem, z przesunięciem o copyVertex i 2*copyVertex
			// czyli zaczynami nie od 0, a od prevCopyIndex;


			// na końcu pętli
			prevCopyIndex = copyVertex;
			copyVertex *= 3;
		}
	}

	// przepisanie macierzy do list sąsiedztwa
	adjacencyLists = createAdjacencyLists(allVertex);
	matrixToList(allVertex);

	int distanceSum = 0;
	distanceSum = countDistances();

	printf("%i\n", distanceSum);


	deleteMatrix(adjacencyMatrix);
	deleteAdjacencyLists(adjacencyLists, allVertex);
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

	allVertex = 1; // węzeł w kroku 0

	// LICZBA WIERZCHOŁKÓW 
	if (k > 0)
	{
		for (int i = 0; i < k; i++)
			allVertex = allVertex * 3;
	}
#ifdef DEBUG
	printf("Liczba wierzcholkow: %i\n", allVertex);

	int m = 0;
	// LICZBA KRAWĘDZI                 
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


	adjacencyMatrix = createMatrix(allVertex);
	indexMatrix = createMatrix(allVertex);

	// zbudować graf --> macierz sąsiedztwa i macierz identyfikatorów
	// jeśli jest krawedz: macierzSasiedztwa[i][j] = 1
	// indexMatrix[i][j] = i <=> macierzSasiedztwa[i][j] = 1
	// jeśli nie ma krawedzi to macierzSasiedztwa[i][j] = nieskończoność, a indexMatrix[i][j] jest niezainicjalizowana

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
			// czyli te, które dołożone w poprzednim kroku były połączone z korzeniem, z przesunięciem o copyVertex i 2*copyVertex
			// czyli zaczynami nie od 0, a od prevCopyIndex;


			// na końcu pętli
			prevCopyIndex = copyVertex;
			copyVertex *= 3;
		}

		// przejść po całej distanceMartix, jeśli nie ma krawędzi oraz i != j to nieskończoność
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

	//wskaźniki pomocnicze
	vertex* v1;
	vertex* v2;
	vertex* v3;
	vertex* vTemp;
	vertex* listHead;	// wskaźnik na listę nowych węzłów

	//vertex** adjacencyList;	//tablica wskaźników
	//vertex* aLVertex;			// wskaźnik nawierzchołek w liście sąsiedztwa

	adjacencyMatrix = createMatrix(allVertex);	// pusta macierz sąsiedztwa

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
		// nowy wierzchołek - korzeń
		v1 = malloc(sizeof(vertex)); // wskaźnik
		if (v1 == NULL)
			return;
		v1->index = 0;
		v1->new = false; // bo to korzeń

		listHead = v1; // głowa listy

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

		// aktualna lista nowych węzłów
		// head->1->2


		// wypelnienie macierzy sąsiedztwa dla kroku 1
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

			stack* s = createStack();  // na stosie będą nowe wierzchołki

			while (vTemp && vTemp->new == true && vertexCounter < allVertex)
			{
				// tworzymy nowy wierzchołek i wrzucamy go na stos
				v1 = malloc(sizeof(vertex));
				if (v1 == NULL)
					return;
				v1->index = vertexCounter;
				v1->new = true;
				v1->next = NULL;
				vertexCounter++;
				push(s, v1); // wrzucamy na stos

				// połączenie z rodzicem (jeden wyżej)
				adjacencyMatrix[vTemp->index][v1->index] = 1;
				adjacencyMatrix[v1->index][vTemp->index] = 1;

				// połączenie z przodkiem
				ancesorIndex = ((v1->index - 1) / 2) % (k - 1);
				adjacencyMatrix[v1->index][ancesorIndex] = 1;
				adjacencyMatrix[ancesorIndex][v1->index] = 1;

				if (vertexCounter < allVertex) // spr czy dodajemy drugi wierzchołek
				{
					// tworzymy nowy wierzchołek i wrzucamy go na stos
					v2 = malloc(sizeof(vertex));
					if (v2 == NULL)
						return;
					v2->index = vertexCounter;
					v2->new = true;
					v2->next = NULL;
					vertexCounter++;
					push(s, v2);

					// połączenie z rodzicem (jeden wyżej)
					adjacencyMatrix[vTemp->index][v2->index] = 1;
					adjacencyMatrix[v2->index][vTemp->index] = 1;

					// połączenie z przodkiem
					ancesorIndex = ((v2->index - 1) / 2) % (k - 1);
					adjacencyMatrix[v2->index][ancesorIndex] = 1;
					adjacencyMatrix[ancesorIndex][v2->index] = 1;

					// połączenie 2 nowych ze sobą nawzajem
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


		// macierz jest gotowa, czyli nie potrzebuję tych list powyżej (chyba, że będzie coś nie tak, to trzeba się przyjrzeć
		// przepisanie macierzy do list sąsiedztwa
		adjacencyLists = createAdjacencyLists(allVertex);
		matrixToList(allVertex);

		// TODO algorytm BFS dla list sąsiedztwa (dla macierzy na za dużą złozoność czasową) DONE
		// zapisywanie wyników do tablicy
		int resultsMemo[MAXVERTEXES];	// zapamiętanie wyników testów, indeks w tablicy to liczba zadanych wierzchołków
								// to do, spr jaka jest faktycznie najwieksza liczba tych wierzchołków?				
		for (int i = 0; i < MAXVERTEXES; i++)
			resultsMemo[i] = -1;  // -1 to brak wyniku

		resultsMemo[0] = 0;
		resultsMemo[1] = 0;
		resultsMemo[2] = 1;
		resultsMemo[3] = 3;

		// jeśli wyniku w tabali brak (sprawdzenie to O(1), to liczymy 
		if (resultsMemo[allVertex] == -1)
		{
			int distanceSum = 0;
			distanceSum = countDistances();
			resultsMemo[allVertex] = distanceSum;
		}

		printf("%i\n", resultsMemo[allVertex]);
	}

	deleteMatrix(adjacencyMatrix);
	deleteAdjacencyLists(adjacencyLists, allVertex);
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

	adjacencyMatrix = createMatrix(allVertex);
	indexMatrix = createMatrix(allVertex);

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

					// połączenie między dodaną parą
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

void Wzrostowo_iteracyjny_v2()  // drugie podejście -> zliczanie odległości na bieżąco
{
#ifdef DEBUG
	printf("Wzrostowo-iteracyjny\n");
#endif // DEBUG

	int k = 0;
	int r = 0;
	scanf_s("%i %i", &k, &r);
#ifdef DEBUG
	printf("k = %i  r = %i\n", k, r);
#endif // DEBUG

	allVertex = 1;
	for (int i = 0; i < k; i++)
	{
		allVertex = allVertex * 2 * r;
	}
	allVertex = (allVertex * r + 3 * r - 2) / (2 * r - 1);
#ifdef DEBUG
	printf("liczba wierzcholkow = %i\n", allVertex);
#endif // DEBUG

	adjacencyMatrix = createMatrix(allVertex);

	// posługujemy się krawędziami
	edge* e1;
	edge* e2;
	edge* eTemp;
	edge* listHead;

	// krok 0 tworzymy 1 kradzędź z dwoma wierzchołkami
	e1 = malloc(sizeof(edge));
	if (e1 == NULL)
		return;
	e1->index = 0;
	e1->v1index = 0;
	e1->v2index = 1;
	e1->new = true;
	e1->next = NULL;
	// uzupełniamy macierz sąsiedztwa
	adjacencyMatrix[0][1] = 1;
	adjacencyMatrix[1][0] = 1;
	// krawędż na początek listy
	listHead = e1;

	// krok > 0
	int lastVertexIndex = e1->v2index; // 1
	int lastEdgeIndex = e1->index;     // 0
	int prevStep = 0;

	while (prevStep < k)
	{
		eTemp = listHead;

		while (eTemp && eTemp->new)  // dopóki mamy wierzchołki w liście i są one nowe (nowe w poprzednik kroku)
		{
			for (int i = 0; i < r; i++) // tyle dochodzi wierzchołków da jedną krawędź z poprzedniego kroku
			{
				// tworzymy nową krawędź połączoną z v1index poprzedniej krawędzi i  z nowym wierzchołkiem
				e1 = malloc(sizeof(edge));
				e1->index = lastEdgeIndex + 1;  // wiem, że można to zapisać ++lastEdge, ale tak jak jest, jest bardziej czytelnie
				lastEdgeIndex++;
				e1->v1index = eTemp->v1index;
				e1->v2index = lastVertexIndex + 1; // nowy wierzchołek
				lastVertexIndex++;
				e1->new = true;
				e1->next = NULL;
				// uzupełniamy macierz sąsiedztwa
				adjacencyMatrix[e1->v1index][e1->v2index] = 1;
				adjacencyMatrix[e1->v2index][e1->v1index] = 1;
				// zliczamy na bieżąco bezpośrednio w macierzy sąsiedztwa - na końcu będziemy mieć macierz odległości!
				coutTempDistancesInMatrix(lastVertexIndex, e1->v1index, e1->v2index);

				// druga krawędź (e1 i e2 mają wspólny wierzchołek v2index) łączymy z nowym wierzchołkiem i v2index poprzedniej krawędzi
				e2 = malloc(sizeof(edge));
				e2->index = lastEdgeIndex + 1;
				lastEdgeIndex++;
				e2->v1index = eTemp->v2index;
				e2->v2index = lastVertexIndex;
				e2->new = true;
				e2->next = NULL;
				// uzupełniamy macierz sąsiedztwa
				adjacencyMatrix[e2->v1index][e2->v2index] = 1;
				adjacencyMatrix[e2->v2index][e2->v1index] = 1;
				// zliczamy na bieżąco bezpośrednio w macierzy sąsiedztwa - na końcu będziemy mieć macierz odległości!
				coutTempDistancesInMatrix(lastVertexIndex, e2->v1index, e2->v2index);

				// nowe krawędzie na początek listy
				e1->next = listHead;
				e2->next = e1;
				listHead = e2;
			}

			// krawędz, do której dołączylismy już komplet już nie jest nowa i przechodzimy do kolejnej
			eTemp->new = false;
			eTemp = eTemp->next;
		}

		prevStep++;
	}

	int distanceSum = 0;
	for (int i = 0; i < allVertex; i++)
	{
		for (int j = i; j < allVertex; j++)
			distanceSum += adjacencyMatrix[i][j];
	}
	printf("%i\n", distanceSum);

	deleteMatrix(adjacencyMatrix);
}


void Wzrostowo_iteracyjny()  // za wolne, trzeba inaczej -> zliczać odległości na bieżąco?
{
#ifdef DEBUG
	printf("Wzrostowo-iteracyjny\n");
#endif // DEBUG

	int k = 0;
	int r = 0;
	scanf_s("%i %i", &k, &r);
#ifdef DEBUG
	printf("k = %i  r = %i\n", k, r);
#endif // DEBUG

	allVertex =1;
	for (int i = 0; i < k; i++)
	{
		allVertex = allVertex * 2 * r;
	}
	allVertex = (allVertex * r + 3 * r - 2) / (2 * r - 1);
#ifdef DEBUG
	printf("liczba wierzcholkow = %i\n", allVertex);
#endif // DEBUG

	adjacencyMatrix = createMatrix(allVertex);

	// posługujemy się krawędziami
	edge* e1;
	edge* e2;
	edge* eTemp;
	edge* listHead;

	// krok 0 tworzymy 1 kradzędź z dwoma wierzchołkami
	e1 = malloc(sizeof(edge));
	if (e1 == NULL)
		return;
	e1->index = 0;
	e1->v1index = 0;
	e1->v2index = 1;
	e1->new = true;
	e1->next = NULL;
	// uzupełniamy macierz sąsiedztwa
	adjacencyMatrix[0][1] = 1;
	adjacencyMatrix[1][0] = 1;
	// krawędż na początek listy
	listHead = e1;

	// krok > 0
	int lastVertexIndex = e1->v2index; // 1
	int lastEdgeIndex = e1->index;     // 0
	int prevStep = 0;

	while (prevStep < k)
	{
		eTemp = listHead;

		while (eTemp && eTemp->new)  // dopóki mamy wierzchołki w liście i są one nowe (nowe w poprzednik kroku)
		{
			for (int i = 0; i < r; i++) // tyle dochodzi wierzchołków da jedną krawędź z poprzedniego kroku
			{
				// tworzymy nową krawędź połączoną z v1index poprzedniej krawędzi i  z nowym wierzchołkiem
				e1 = malloc(sizeof(edge));
				e1->index = lastEdgeIndex + 1;  // wiem, że można to zapisać ++lastEdge, ale tak jak jest, jest bardziej czytelnie
				lastEdgeIndex++;
				e1->v1index = eTemp->v1index;
				e1->v2index = lastVertexIndex + 1; // nowy wierzchołek
				lastVertexIndex++;
				e1->new = true;
				e1->next = NULL;
				// uzupełniamy macierz sąsiedztwa
				adjacencyMatrix[e1->v1index][e1->v2index] = 1;
				adjacencyMatrix[e1->v2index][e1->v1index] = 1;

				// druga krawędź (e1 i e2 mają wspólny wierzchołek v2index) łączymy z nowym wierzchołkiem i v2index poprzedniej krawędzi
				e2 = malloc(sizeof(edge));
				e2->index = lastEdgeIndex + 1;
				lastEdgeIndex++;
				e2->v1index = eTemp->v2index;
				e2->v2index = lastVertexIndex;
				e2->new = true;
				e2->next = NULL;
				// uzupełniamy macierz sąsiedztwa
				adjacencyMatrix[e2->v1index][e2->v2index] = 1;
				adjacencyMatrix[e2->v2index][e2->v1index] = 1;

				// nowe krawędzie na początek listy
				e1->next = listHead;
				e2->next = e1;
				listHead = e2;
			}

			// krawędz, do której dołączylismy już komplet już nie jest nowa i przechodzimy do kolejnej
			eTemp->new = false;
			eTemp = eTemp->next;
		}

		prevStep++;
	}

	adjacencyLists = createAdjacencyLists(allVertex);
	matrixToList(allVertex);

	int distanceSum = countDistances();
	printf("%i\n", distanceSum);

	deleteMatrix(adjacencyMatrix);
	deleteAdjacencyLists(adjacencyLists, allVertex);
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

	adjacencyMatrix = createMatrix(allVertex);
	adjacencyLists = createAdjacencyLists(allVertex);
	vertex* v;

	// krok 0
	// nowy wierzchołek - korzeń
	v = malloc(sizeof(vertex)); // wskaźnik
	if (v == NULL)
		return;
	v->index = 0;
	v->next = NULL;

	// lista sąsiedztwa - v0 na razie brak sąsiadów, reszta - każdy ma za sąsiada v0
	adjacencyLists[0] = NULL;
	for (int i = 1; i < allVertex; i++)
	{
		adjacencyLists[i] = v;
	}

	// zliczenie odległości od każdego po przodkach do v0 - później się to przyda
	//int* throughAncestors = (int*)calloc(MAXVERTEXES, sizeof(int));
	int throughAncestors[MAXVERTEXES];
	for (int i = 0; i < MAXVERTEXES; i++)
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
			v = malloc(sizeof(vertex));
			if (v == NULL)
				break;
			v->index = index;
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
			adjacencyMatrix[i][v->index] = 1;  // na liscie to byłoby trudne...
			adjacencyMatrix[v->index][i] = 1;
			v = v->next;
		}
	}


	// wyczyszczenie tymczasowej listy sąsiedztwa
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


	matrixToList(allVertex);

	int distanceSum = countDistances();
	printf("%i\n", distanceSum);

	//free(throughAncestors);
	deleteMatrix(adjacencyMatrix);
	deleteAdjacencyLists(adjacencyLists, allVertex);
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
	// Silny produkt grafowy jest operacją binarną na grafach G1 i G2, która daje w wyniku graf H o następujących własnościach:
	// - zbiór wierzchołków w grafie H jest iloczynem kartezjańskim V(G1) x V(G2), gdzie V(G1) i V(G2) są zbiorami wierzchołków
	// - dwa wierzchołki (u1,u2) i (v1,v2) z H są połączone krawędzią <=> gdy wierzchołki u1,u2,v1,v2 spełniają pewne warunki dot. krawędzi w G1 i G2
	// - warunek dot. krawędzi: u1 = v1 oraz u2v2 należy do E(G2) albo
	//                          u1v1 należy do E(G1) oraz u2 = v2 albo
	//                          u1v1 należy do E(G1) oraz u2v2 należy do E(G2)

	int k = 0;  //potęga i zarazem liczba kroków
	char buffor[100] = { 0 };
	scanf_s("%i", &k);
	scanf_s("%s", buffor, (unsigned)_countof(buffor));
#ifdef DEBUG
	printf("n = %i  buffor = %s\n", n, buffor);
#endif // DEBUG
	if (strlen(buffor) == 0)
		return;
	int startVertex = (int)sqrt(strlen(buffor));  // wejściowa liczba wierzchołków
#ifdef DEBUG
	printf("Liczba wierzcholkow: %i\n", startVertex);
#endif // DEBUG

	short** G1 = createMatrix(startVertex);
	short** G2 = createMatrix(startVertex);

	// wczytujemy graf podany w postaci macierzy sąsiedztwa
	// 2 razy, bo będziemy tworzyć silny produkt grafowy
	int nchar = 0;
	for (int i = 0; i < startVertex; ++i)
	{
		for (int j = 0; j < startVertex; ++j)
		{
			G1[i][j] = G2[i][j] = buffor[nchar++] - '0';
		}
	}
#ifdef DEBUG
	printMatrix(G1);
#endif // DEBUG

	short** H = NULL; // graf H - silny produkt

	allVertex = startVertex;  // allVertex - końcowa liczba wierzchołków
	for (int i = 1; i < k; i++)
	{
		allVertex *= startVertex;
	}

	int HVertex = startVertex;	// do śledzenia ilości wierzchołków w klejnych krokach (mnożeniach), czyli ilość wierzchołków grafu H - silnego produktu

	while (HVertex < allVertex)
	{
		// jeśli mamy kolejny krok (kolejne mnożenie), to musimy zwolnić poprzedną wejściową wersję grafu
		// i przypisać do niej graf H, by móc dalej mnożyć (kartezjańsko ofc)
		if (H)
		{
			deleteMatrix(G1);
			G1 = H;
		}

		// tworzenie grafu H - silny produkt
		HVertex *= startVertex; // nowa liczba wierzchołków
		H = createMatrix(HVertex);
		// krawędzie na podstawie trzech warunków
		int u1 = 0;
		int v1 = 0;
		int u2 = 0;
		int v2 = 0;
		for (int i = 0; i < HVertex; i++)
		{
			for (int j = 0; j < HVertex; j++)
			{
				// wierzchołek i (u1,u2), wierzchołek j (v1,v2)
				u1 = i / startVertex;
				v1 = j / startVertex;
				u2 = i % startVertex;
				v2 = j % startVertex;
				    
				    // u1 = v1 oraz u2v2 należy do E(G2) albo
				if (((u1 == v1) && (G2[u2][v2])) ||
					// u1v1 należy do E(G1) oraz u2 = v2 albo
					((G1[u1][v1]) && (u2 == v2)) ||
					// u1v1 należy do E(G1) oraz u2v2 należy do E(G2)
					((G1[u1][v1] == 1) && (G2[u2][v2] == 1)))
				{
					H[i][j] = 1;
				}
			}
		}
	}

	if (H == NULL)  // przypadek, gdy potęga = 1
	{
		H = G1;
	}

	// liczenie odległości
	// 𝑑𝐺1⊠𝐺2(𝑥, 𝑦) = 𝑚𝑎𝑥{ 𝑑𝐺1(𝑥1, 𝑦1), 𝑑𝐺2(𝑥2, 𝑦2) }
	// czyli potrzebujemy policzyć odległości w grafach G1 i G2 (przy k > 2 G1 już jest silnym produktem)
	int** distancesMatrix;
	adjacencyMatrix = G2;
	adjacencyLists = createAdjacencyLists(startVertex);
	matrixToList(startVertex);
	distancesMatrix = countDistancesReturnMatrix(startVertex);

	int distancesSum = 0;

	if (k == 1) // tu tylko zliczamy z macierzy odległości
	{
		for (int i = 0; i < startVertex; i++)
		{
			for (int j = i; j < startVertex; j++)
			{
				distancesSum += distancesMatrix[i][j];
			}
		}
	}
	else if (k > 1) // tu dla silnego produktu  TODO!
	{
	}

	printf("%i\n", distancesSum);

	deleteMatrix(G1);
	deleteMatrix(G2);
	deleteMatrixInt(distancesMatrix, startVertex);
	deleteAdjacencyLists(adjacencyLists, startVertex);
}

//short** createMatrix()
//{
//	short** matrix = (short**)calloc(allVertex, sizeof(short*));   // calloc od razu inicjalizuje 0
//	if (matrix != NULL)
//	{
//		for (int i = 0; i < allVertex; ++i)
//			matrix[i] = (short*)calloc(allVertex, sizeof(short));
//	}
//
//	return matrix;
//}

short** createMatrix(int n)
{
	short** matrix = (short**)calloc(n, sizeof(short*));   // calloc od razu inicjalizuje 0
	if (matrix != NULL)
	{
		for (int i = 0; i < n; ++i)
			matrix[i] = (short*)calloc(n, sizeof(short));
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

int** createMatrixInt(int n)
{
	int** matrix = (int**)calloc(n, sizeof(int*));   // calloc od razu inicjalizuje 0
	if (matrix != NULL)
	{
		for (int i = 0; i < n; ++i)
			matrix[i] = (int*)calloc(n, sizeof(int));
	}

	return matrix;
}

void deleteMatrixInt(int** matrix, int n)
{
	if (matrix != NULL)
	{
		for (int i = 0; i < n; ++i)
			free(matrix[i]);
		free(matrix);
	}
}


vertex** createAdjacencyLists(int n)
{
	vertex**  adjcLists = (vertex**)calloc(n, sizeof(vertex*));
	return adjcLists;
}

void deleteAdjacencyLists(vertex** adjcLists, int n)
{
	if (adjcLists != NULL)
	{
		vertex* v;
		vertex* vDelete;
		for (int i = 0; i < n; i++)
		{
			v = adjacencyLists[i];
			while (v)
			{
				vDelete = v;
				v = v->next;
				free(vDelete);
			}
		}
		//free(adjcLists);  // już wyżej zwolniliśmy wskaźniki, które są bezpośrednio w tablicy
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

	//result /= 2; // nasz graf nie jest kierunkowy, więc algorytm każdą krawędź liczy jak dwie w dwóch kierunkach, dlatego wynik trzeb apodzielić na 2

#ifdef DEBUG
	printf("Result = %i\n", result);
	printMatrix(distanceMatrix);
#else
	printf("%i\n", result);
#endif // DEBUG

	
}

void coutTempDistancesInMatrix(int lastIndex, int index1, int index2)
{
	for (int i = 0; i < lastIndex; i++)
	{
		short temp1 = 0;
		short temp2 = 0;
		temp1 = adjacencyMatrix[i][index2];
		temp2 = adjacencyMatrix[i][index1] + 1;

		if (temp1 == 0)
		{
			adjacencyMatrix[i][index2] = temp2;
			adjacencyMatrix[index2][i] = temp2;
		}
		if (temp1 == 1)
		{
			continue;
		}
		if (temp1 > temp2)
		{
			adjacencyMatrix[i][index2] = temp2;
			adjacencyMatrix[index2][i] = temp2;
			continue; //czy to potrzebne?
		}
	}
}

// zamiana macierzy sąsiedztwa na listę
void matrixToList(int n) 
{
#ifdef DEBUG
	printMatrix(adjacencyMatrix);
#endif // DEBUG

	for (int i = n - 1; i >= 0; i--) 
	{
		for (int j = n - 1; j >= 0; j--) 
		{
			if (adjacencyMatrix[i][j] == 1) 
			{
				vertex* v = malloc(sizeof(vertex));
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

int** countDistancesReturnMatrix(int n)
{
	int** distancesMatrix = createMatrixInt(n);
	for (int v = 0; v < n; v++)
	{
		// suma odleglosci między wierzchołkiem v a pozostałymi (kolejnymi, unikamy tu powrórnego liczenia odległości w drugą str)
		BFSvertex* sum = BFS(v, allVertex);
		for (int i = v; i < n; i++)
		{
			//i sumuje te odległości i wpisujemy w macierz
			distancesMatrix[v][i] += sum[i].distance;

		}
		free(sum);
	}
	// uwaga! po BFS mamy macierz połówkową!
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			distancesMatrix[j][i] = distancesMatrix[i][j];
		}
	}

	return distancesMatrix;
}

int countDistances()
{
	int distanceSum = 0;
	for (int v = 0; v < allVertex; v++)
	{
		// suma odleglosci między wierzchołkiem v a pozostałymi (kolejnymi, unikamy tu powrórnego liczenia odległości w drugą str)
		BFSvertex* sum = BFS(v, allVertex);
		for (int i = v; i < allVertex; i++)
		{
			//i sumuje te odległości
			distanceSum += sum[i].distance;

		}
		free(sum);
	}
	return distanceSum;
}

BFSvertex* BFS(int start, int n) // tu wrzucamy listę sąsiedztwa
{
	vertex* v;
	BFSvertex* tab = malloc(sizeof(BFSvertex) * n);

	if (tab == NULL)
		return NULL;

	for (int i = 0; i < n; i++) 
	{
		tab[i].distance = MAXVAL;
		tab[i].visited = false;
	}
	
	tab[start].distance = 0;
	tab[start].visited = true;


	queue *q = createQueue();  // tworzymy kolejkę
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
	// dla wejścia: 1 6 | wyjscie: 20
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
		vertex* ptr = adjacencyLists[i];

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
