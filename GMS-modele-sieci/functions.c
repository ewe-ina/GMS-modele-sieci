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

void Barabasi_Ravasz_Vicsek_v2() // mo�na jeszcze zapami�tywa� macierz z poprzedniego kroku
{
#ifdef DEBUG
	printf("Barabasi-Ravasz-Vicsek\n");
#endif // DEBUG

	int k = 0;
	scanf_s("%i", &k);
#ifdef DEBUG
	printf("k = %i\n", k);
#endif // DEBUG
	if (k > 7) return;  // BEZPIECZNIK !!! przy k==8 na STOSie exception ACCESS_VIOLATION przy wype�nianiu (a nie wychodzimy indeksami poza zakres!)
							// malloc przyc=dzielil za malo pamieci - zmiana int na short pomogla, ale wciaz dziala za wolno dla k=8

	allVertex = 1; // w�ze� w kroku 0

	// LICZBA WIERZCHO�K�W 
	if (k > 0)
	{
		for (int i = 0; i < k; i++)
			allVertex = allVertex * 3;
	}
#ifdef DEBUG
	printf("Liczba wierzcholkow: %i\n", allVertex);

	int m = 0;
	// LICZBA KRAWE�DZI                 
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

	// zbudowa� graf --> macierz s�siedztwa i macierz identyfikator�w
	// je�li jest krawedz: macierzSasiedztwa[i][j] = 1
	// indexMatrix[i][j] = i <=> macierzSasiedztwa[i][j] = 1
	// je�li nie ma krawedzi to macierzSasiedztwa[i][j] = niesko�czono��, a indexMatrix[i][j] jest niezainicjalizowana

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
			// czyli te, kt�re do�o�one w poprzednim kroku by�y po��czone z korzeniem, z przesuni�ciem o copyVertex i 2*copyVertex
			// czyli zaczynami nie od 0, a od prevCopyIndex;


			// na ko�cu p�tli
			prevCopyIndex = copyVertex;
			copyVertex *= 3;
		}
	}

	// przepisanie macierzy do list s�siedztwa
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

	allVertex = 1; // w�ze� w kroku 0

	// LICZBA WIERZCHO�K�W 
	if (k > 0)
	{
		for (int i = 0; i < k; i++)
			allVertex = allVertex * 3;
	}
#ifdef DEBUG
	printf("Liczba wierzcholkow: %i\n", allVertex);

	int m = 0;
	// LICZBA KRAW�DZI                 
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

	// zbudowa� graf --> macierz s�siedztwa i macierz identyfikator�w
	// je�li jest krawedz: macierzSasiedztwa[i][j] = 1
	// indexMatrix[i][j] = i <=> macierzSasiedztwa[i][j] = 1
	// je�li nie ma krawedzi to macierzSasiedztwa[i][j] = niesko�czono��, a indexMatrix[i][j] jest niezainicjalizowana

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
			// czyli te, kt�re do�o�one w poprzednim kroku by�y po��czone z korzeniem, z przesuni�ciem o copyVertex i 2*copyVertex
			// czyli zaczynami nie od 0, a od prevCopyIndex;


			// na ko�cu p�tli
			prevCopyIndex = copyVertex;
			copyVertex *= 3;
		}

		// przej�� po ca�ej distanceMartix, je�li nie ma kraw�dzi oraz i != j to niesko�czono��
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

	//wska�niki pomocnicze
	vertex* v1;
	vertex* v2;
	vertex* v3;
	vertex* vTemp;
	vertex* listHead;	// wska�nik na list� nowych w�z��w

	//vertex** adjacencyList;	//tablica wska�nik�w
	//vertex* aLVertex;			// wska�nik nawierzcho�ek w li�cie s�siedztwa

	adjacencyMatrix = createMatrix();	// pusta macierz s�siedztwa

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
		// nowy wierzcho�ek - korze�
		v1 = malloc(sizeof(vertex)); // wska�nik
		if (v1 == NULL)
			return;
		v1->index = 0;
		v1->new = false; // bo to korze�

		listHead = v1; // g�owa listy

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

		// aktualna lista nowych w�z��w
		// head->1->2


		// wypelnienie macierzy s�siedztwa dla kroku 1
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

			stack* s = createStack();  // na stosie b�d� nowe wierzcho�ki

			while (vTemp && vTemp->new == true && vertexCounter < allVertex)
			{
				// tworzymy nowy wierzcho�ek i wrzucamy go na stos
				v1 = malloc(sizeof(vertex));
				if (v1 == NULL)
					return;
				v1->index = vertexCounter;
				v1->new = true;
				v1->next = NULL;
				vertexCounter++;
				push(s, v1); // wrzucamy na stos

				// po��czenie z rodzicem (jeden wy�ej)
				adjacencyMatrix[vTemp->index][v1->index] = 1;
				adjacencyMatrix[v1->index][vTemp->index] = 1;

				// po��czenie z przodkiem
				ancesorIndex = ((v1->index - 1) / 2) % (k - 1);
				adjacencyMatrix[v1->index][ancesorIndex] = 1;
				adjacencyMatrix[ancesorIndex][v1->index] = 1;

				if (vertexCounter < allVertex) // spr czy dodajemy drugi wierzcho�ek
				{
					// tworzymy nowy wierzcho�ek i wrzucamy go na stos
					v2 = malloc(sizeof(vertex));
					if (v2 == NULL)
						return;
					v2->index = vertexCounter;
					v2->new = true;
					v2->next = NULL;
					vertexCounter++;
					push(s, v2);

					// po��czenie z rodzicem (jeden wy�ej)
					adjacencyMatrix[vTemp->index][v2->index] = 1;
					adjacencyMatrix[v2->index][vTemp->index] = 1;

					// po��czenie z przodkiem
					ancesorIndex = ((v2->index - 1) / 2) % (k - 1);
					adjacencyMatrix[v2->index][ancesorIndex] = 1;
					adjacencyMatrix[ancesorIndex][v2->index] = 1;

					// po��czenie 2 nowych ze sob� nawzajem
					adjacencyMatrix[v1->index][v2->index] = 1;
					adjacencyMatrix[v2->index][v1->index] = 1;


				}
				vTemp->new = false;
				vTemp = vTemp->next;  // przechodzimy do kolejnego
			}
			k++;

			while (!empty(s))  // dop�ki stos nie jest pusty
			{
				v1 = top(s);
				pop(s);
				v1->next = listHead;
				listHead = v1;
				vTemp = listHead;
			}
		}


		// macierz jest gotowa, czyli nie potrzebuj� tych list powy�ej (chyba, �e b�dzie co� nie tak, to trzeba si� przyjrze�
		// przepisanie macierzy do list s�siedztwa
		adjacencyLists = createAdjacencyLists();
		matrixToList();

		// TODO algorytm BFS dla list s�siedztwa (dla macierzy na za du�� z�ozono�� czasow�) DONE
		// zapisywanie wynik�w do tablicy
		int resultsMemo[MAXVERTEXES];	// zapami�tanie wynik�w test�w, indeks w tablicy to liczba zadanych wierzcho�k�w
								// to do, spr jaka jest faktycznie najwieksza liczba tych wierzcho�k�w?				
		for (int i = 0; i < MAXVERTEXES; i++)
			resultsMemo[i] = -1;  // -1 to brak wyniku

		resultsMemo[0] = 0;
		resultsMemo[1] = 0;
		resultsMemo[2] = 1;
		resultsMemo[3] = 3;

		// je�li wyniku w tabali brak (sprawdzenie to O(1), to liczymy 
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

void Wzrostowo_iteracyjny_v2()  // drugie podej�cie -> zliczanie odleg�o�ci na bie��co
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

	adjacencyMatrix = createMatrix();

	// pos�ugujemy si� kraw�dziami
	edge* e1;
	edge* e2;
	edge* eTemp;
	edge* listHead;

	// krok 0 tworzymy 1 kradz�d� z dwoma wierzcho�kami
	e1 = malloc(sizeof(edge));
	if (e1 == NULL)
		return;
	e1->index = 0;
	e1->v1index = 0;
	e1->v2index = 1;
	e1->new = true;
	e1->next = NULL;
	// uzupe�niamy macierz s�siedztwa
	adjacencyMatrix[0][1] = 1;
	adjacencyMatrix[1][0] = 1;
	// kraw�d� na pocz�tek listy
	listHead = e1;

	// krok > 0
	int lastVertexIndex = e1->v2index; // 1
	int lastEdgeIndex = e1->index;     // 0
	int prevStep = 0;

	while (prevStep < k)
	{
		eTemp = listHead;

		while (eTemp && eTemp->new)  // dop�ki mamy wierzcho�ki w li�cie i s� one nowe (nowe w poprzednik kroku)
		{
			for (int i = 0; i < r; i++) // tyle dochodzi wierzcho�k�w da jedn� kraw�d� z poprzedniego kroku
			{
				// tworzymy now� kraw�d� po��czon� z v1index poprzedniej kraw�dzi i  z nowym wierzcho�kiem
				e1 = malloc(sizeof(edge));
				e1->index = lastEdgeIndex + 1;  // wiem, �e mo�na to zapisa� ++lastEdge, ale tak jak jest, jest bardziej czytelnie
				lastEdgeIndex++;
				e1->v1index = eTemp->v1index;
				e1->v2index = lastVertexIndex + 1; // nowy wierzcho�ek
				lastVertexIndex++;
				e1->new = true;
				e1->next = NULL;
				// uzupe�niamy macierz s�siedztwa
				adjacencyMatrix[e1->v1index][e1->v2index] = 1;
				adjacencyMatrix[e1->v2index][e1->v1index] = 1;
				// zliczamy na bie��co bezpo�rednio w macierzy s�siedztwa - na ko�cu b�dziemy mie� macierz odleg�o�ci!
				coutTempDistancesInMatrix(lastVertexIndex, e1->v1index, e1->v2index);

				// druga kraw�d� (e1 i e2 maj� wsp�lny wierzcho�ek v2index) ��czymy z nowym wierzcho�kiem i v2index poprzedniej kraw�dzi
				e2 = malloc(sizeof(edge));
				e2->index = lastEdgeIndex + 1;
				lastEdgeIndex++;
				e2->v1index = eTemp->v2index;
				e2->v2index = lastVertexIndex;
				e2->new = true;
				e2->next = NULL;
				// uzupe�niamy macierz s�siedztwa
				adjacencyMatrix[e2->v1index][e2->v2index] = 1;
				adjacencyMatrix[e2->v2index][e2->v1index] = 1;
				// zliczamy na bie��co bezpo�rednio w macierzy s�siedztwa - na ko�cu b�dziemy mie� macierz odleg�o�ci!
				coutTempDistancesInMatrix(lastVertexIndex, e2->v1index, e2->v2index);

				// nowe kraw�dzie na pocz�tek listy
				e1->next = listHead;
				e2->next = e1;
				listHead = e2;
			}

			// kraw�dz, do kt�rej do��czylismy ju� komplet ju� nie jest nowa i przechodzimy do kolejnej
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


void Wzrostowo_iteracyjny()  // za wolne, trzeba inaczej -> zlicza� odleg�o�ci na bie��co?
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

	adjacencyMatrix = createMatrix();

	// pos�ugujemy si� kraw�dziami
	edge* e1;
	edge* e2;
	edge* eTemp;
	edge* listHead;

	// krok 0 tworzymy 1 kradz�d� z dwoma wierzcho�kami
	e1 = malloc(sizeof(edge));
	if (e1 == NULL)
		return;
	e1->index = 0;
	e1->v1index = 0;
	e1->v2index = 1;
	e1->new = true;
	e1->next = NULL;
	// uzupe�niamy macierz s�siedztwa
	adjacencyMatrix[0][1] = 1;
	adjacencyMatrix[1][0] = 1;
	// kraw�d� na pocz�tek listy
	listHead = e1;

	// krok > 0
	int lastVertexIndex = e1->v2index; // 1
	int lastEdgeIndex = e1->index;     // 0
	int prevStep = 0;

	while (prevStep < k)
	{
		eTemp = listHead;

		while (eTemp && eTemp->new)  // dop�ki mamy wierzcho�ki w li�cie i s� one nowe (nowe w poprzednik kroku)
		{
			for (int i = 0; i < r; i++) // tyle dochodzi wierzcho�k�w da jedn� kraw�d� z poprzedniego kroku
			{
				// tworzymy now� kraw�d� po��czon� z v1index poprzedniej kraw�dzi i  z nowym wierzcho�kiem
				e1 = malloc(sizeof(edge));
				e1->index = lastEdgeIndex + 1;  // wiem, �e mo�na to zapisa� ++lastEdge, ale tak jak jest, jest bardziej czytelnie
				lastEdgeIndex++;
				e1->v1index = eTemp->v1index;
				e1->v2index = lastVertexIndex + 1; // nowy wierzcho�ek
				lastVertexIndex++;
				e1->new = true;
				e1->next = NULL;
				// uzupe�niamy macierz s�siedztwa
				adjacencyMatrix[e1->v1index][e1->v2index] = 1;
				adjacencyMatrix[e1->v2index][e1->v1index] = 1;

				// druga kraw�d� (e1 i e2 maj� wsp�lny wierzcho�ek v2index) ��czymy z nowym wierzcho�kiem i v2index poprzedniej kraw�dzi
				e2 = malloc(sizeof(edge));
				e2->index = lastEdgeIndex + 1;
				lastEdgeIndex++;
				e2->v1index = eTemp->v2index;
				e2->v2index = lastVertexIndex;
				e2->new = true;
				e2->next = NULL;
				// uzupe�niamy macierz s�siedztwa
				adjacencyMatrix[e2->v1index][e2->v2index] = 1;
				adjacencyMatrix[e2->v2index][e2->v1index] = 1;

				// nowe kraw�dzie na pocz�tek listy
				e1->next = listHead;
				e2->next = e1;
				listHead = e2;
			}

			// kraw�dz, do kt�rej do��czylismy ju� komplet ju� nie jest nowa i przechodzimy do kolejnej
			eTemp->new = false;
			eTemp = eTemp->next;
		}

		prevStep++;
	}

	adjacencyLists = createAdjacencyLists();
	matrixToList();

	int distanceSum = countDistances();
	printf("%i\n", distanceSum);

	deleteMatrix(adjacencyMatrix);
	deleteAdjacencyLists(adjacencyLists);
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
	vertex* v;

	// krok 0
	// nowy wierzcho�ek - korze�
	v = malloc(sizeof(vertex)); // wska�nik
	if (v == NULL)
		return;
	v->index = 0;
	v->next = NULL;

	// lista s�siedztwa - v0 na razie brak s�siad�w, reszta - ka�dy ma za s�siada v0
	adjacencyLists[0] = NULL;
	for (int i = 1; i < allVertex; i++)
	{
		adjacencyLists[i] = v;
	}

	// zliczenie odleg�o�ci od ka�dego po przodkach do v0 - p�niej si� to przyda
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
			adjacencyMatrix[i][v->index] = 1;  // na liscie to by�oby trudne...
			adjacencyMatrix[v->index][i] = 1;
			v = v->next;
		}
	}


	// wyczyszczenie tymczasowej listy s�siedztwa
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

	int n = 0;  //pot�ga
	char buffor[100] = { 0 };
	scanf_s("%i", &n);
	scanf_s("%s", buffor, (unsigned)_countof(buffor));
#ifdef DEBUG
	printf("n = %i  buffor = %s\n", n, buffor);
#endif // DEBUG
	if (strlen(buffor) == 0)
		return;
	allVertex = (int)sqrt(strlen(buffor));
#ifdef DEBUG
	printf("Liczba wierzcholkow: %i\n", allVertex);
#endif // DEBUG

	adjacencyMatrix = createMatrix();

	int nchar = 0;
	for (int i = 0; i < allVertex; ++i)
	{
		for (int j = 0; j < allVertex; ++j)
		{
			adjacencyMatrix[i][j] = buffor[nchar++] - '0';
		}
	}
#ifdef DEBUG
	printMatrix(adjacencyMatrix);
#endif // DEBUG



	deleteMatrix(adjacencyMatrix);
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


vertex** createAdjacencyLists()
{
	vertex**  adjcLists = (vertex**)calloc(allVertex, sizeof(vertex*));
	return adjcLists;
}

void deleteAdjacencyLists(vertex** adjcLists)
{
	if (adjcLists != NULL)
	{
		vertex* v;
		vertex* vDelete;
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
		//free(adjcLists);  // ju� wy�ej zwolnili�my wska�niki, kt�re s� bezpo�rednio w tablicy
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

	//result /= 2; // nasz graf nie jest kierunkowy, wi�c algorytm ka�d� kraw�d� liczy jak dwie w dw�ch kierunkach, dlatego wynik trzeb apodzieli� na 2

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

int countDistances()
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
	return distanceSum;
}

BFSvertex* BFS(int start) // tu wrzucamy list� s�siedztwa
{
	vertex* v;
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


	queue *q = createQueue();  // tworzymy kolejk�
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
