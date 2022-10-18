#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdbool.h>

int allVertex;
int** adjacencyMatrix;					// ktora na poczatku jest zwykla macieza sasiedztwa
int** indexMatrix;						// identyfikatory przedostatnich punktów na œcie¿ce ³¹cz¹cej punkty - do F-W
adjacencyListVertex** adjacencyList;	//tablica wskaŸników

#define MAXVAL  INT_MAX / 3  // imituje nieskonczonosc w algorytmie
//#define DEBUG


typedef struct vertex 
{
	int index;							// indeks wierzcho³ka
	bool new;							// czy wierzcho³ek jest nowy?
	vertex* next;						// wskaŸnik na nastêpny wierzcho³ek w liœcie s¹siedztwa
}vertex;

// do Lu-Su-Guo_v2
typedef struct adjacencyListVertex		// wierzcholek przechowywany w liscie sasiedztwa
{
	int index;							// indeks wierzcho³ka
	bool bottom;						// czy jest dolnym wierzcho³kiem?
	struct adjacencyListVertex* next;	// wskaŸnik na nastêpny wierzcho³ek w liœcie s¹siedztwa 
}adjacencyListVertex;


void getModel(int model);

void Barabasi_Ravasz_Vicsek();
void Lu_Su_Guo();
void Lu_Su_Guo_v2();
void Simplical();
void Wzrostowo_iteracyjny();
void DCN();
void GFG();
void Kronecker();

int** createMatrix();
void deleteMatrix(int** matrix);
void addInfinity(int** distanceMatrix);
void Floyd_Warshall(int** distanceMatrix);

void matrixToList();

// POMOCNICZE
void matrixForTest();
void printMatrix(int** matrix);

#endif // !FUNCTIONS_H
