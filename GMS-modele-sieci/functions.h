#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "stack.h"

int allVertex;
short** adjacencyMatrix;					// ktora na poczatku jest zwykla macieza sasiedztwa
short** indexMatrix;						// identyfikatory przedostatnich punktów na œcie¿ce ³¹cz¹cej punkty - do F-W


#define MAXVAL  SHRT_MAX / 3  // imituje nieskonczonosc w algorytmie
//#define DEBUG


typedef struct _vertex 
{
	int index;							// indeks wierzcho³ka
	bool new;							// czy wierzcho³ek jest nowy?
	struct _vertex* next;						// wskaŸnik na nastêpny wierzcho³ek w liœcie s¹siedztwa
}vertex;

// do Lu-Su-Guo_v2
typedef struct _adjacencyListVertex		// wierzcholek przechowywany w liscie sasiedztwa
{
	int index;							// indeks wierzcho³ka
	bool bottom;						// czy jest dolnym wierzcho³kiem?
	struct _adjacencyListVertex *next;	// wskaŸnik na nastêpny wierzcho³ek w liœcie s¹siedztwa 
}adjacencyListVertex;

// do BFS
typedef struct _BFSvertex 
{
	int distance;						// odleg³oœæ
	bool visited;						// czy wierzcho³ek zosta³ ju¿ odwiedzony?
}BFSvertex;


adjacencyListVertex** adjacencyLists;	// tablica list s¹siedztwa (tablica wskaŸników)

void getModel(int model);

void Barabasi_Ravasz_Vicsek();
void Barabasi_Ravasz_Vicsek_v2();
void Lu_Su_Guo();
void Lu_Su_Guo_v2();
void Simplical();
void Wzrostowo_iteracyjny();
void DCN();
void GFG();
void Kronecker();

short** createMatrix();
void deleteMatrix(short** matrix);
adjacencyListVertex** createAdjacencyLists(); 
void deleteAdjacencyLists(adjacencyListVertex** adjcLists);


void addInfinity(short** distanceMatrix);
void Floyd_Warshall(short** distanceMatrix);

void matrixToList();

int countDistances();
BFSvertex* BFS(int start);

// POMOCNICZE
#ifdef DEBUG
void matrixForTest();
void printMatrix(short** matrix);
void printAdjacencyList();
#endif // DEBUG

#endif // !FUNCTIONS_H
