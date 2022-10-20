#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"


//#define QSIZE 200

//int Q[QSIZE];
//int head;
//int tail;

int allVertex;
int** adjacencyMatrix;					// ktora na poczatku jest zwykla macieza sasiedztwa
int** indexMatrix;						// identyfikatory przedostatnich punktów na œcie¿ce ³¹cz¹cej punkty - do F-W
struct _adjacencyListVertex** adjacencyLists;	// tablica list s¹siedztwa (tablica wskaŸników)

#define MAXVAL  INT_MAX / 3  // imituje nieskonczonosc w algorytmie
#define DEBUG


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
adjacencyListVertex** createAdjacencyLists(); // to te¿ tablica 2 wymiarowa
void deleteAdjacencyLists(adjacencyListVertex** adjacencyLists);


void addInfinity(int** distanceMatrix);
void Floyd_Warshall(int** distanceMatrix);

void matrixToList();

BFSvertex* BFS(int start);

// POMOCNICZE
void matrixForTest();
void printMatrix(int** matrix);
void printAdjacencyList();

#endif // !FUNCTIONS_H
