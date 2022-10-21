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
short** indexMatrix;						// identyfikatory przedostatnich punkt�w na �cie�ce ��cz�cej punkty - do F-W


#define MAXVAL  SHRT_MAX / 3  // imituje nieskonczonosc w algorytmie
//#define DEBUG


typedef struct _vertex 
{
	int index;							// indeks wierzcho�ka
	bool new;							// czy wierzcho�ek jest nowy?
	struct _vertex* next;						// wska�nik na nast�pny wierzcho�ek w li�cie s�siedztwa
}vertex;


// do BFS
typedef struct _BFSvertex 
{
	int distance;						// odleg�o��
	bool visited;						// czy wierzcho�ek zosta� ju� odwiedzony?
}BFSvertex;


vertex** adjacencyLists;	// tablica list s�siedztwa (tablica wska�nik�w)

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
vertex** createAdjacencyLists(); 
void deleteAdjacencyLists(vertex** adjcLists);


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
