#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <queue>
//#include "queue.h"
#include "stack.h"


#define MAXVAL  SHRT_MAX / 3  // imituje nieskonczonosc w algorytmie
#define MAXVERTEXES 1000
//#define DEBUG


typedef struct _vertex 
{
	unsigned short index;							// indeks wierzcho³ka
	bool isnew;							// czy wierzcho³ek jest nowy?
	struct _vertex* next;						// wskaŸnik na nastêpny wierzcho³ek w liœcie s¹siedztwa
}vertex;

typedef struct _edge
{
	int index;
	int v1index;
	int v2index;
	bool isnew;
	struct _edge* next;
} edge;


// do BFS
typedef struct _BFSvertex 
{
	int distance;						// odleg³oœæ
	bool visited;						// czy wierzcho³ek zosta³ ju¿ odwiedzony?
}BFSvertex;



void getModel(int model);

void Barabasi_Ravasz_Vicsek();
void Barabasi_Ravasz_Vicsek_v2();
void Lu_Su_Guo();
void Lu_Su_Guo_v2();
void Simplical();
void Wzrostowo_iteracyjny();
void Wzrostowo_iteracyjny_v2();
void DCN();
void GFG();
void Kronecker();

// C does not support overloading
//short** createMatrix();  // tworzy macierz o rozmiarze allVertex - zmienna globalna
short** createMatrix(int n); // towrzy macierz o zadanym rozmiarze n
void deleteMatrix(short** matrix, int n);
int** createMatrixInt(int n);
void deleteMatrixInt(int** matrix,int n);

vertex** createAdjacencyLists(int n); 
void deleteAdjacencyLists(vertex** adjcLists, int n);


void addInfinity(short** distanceMatrix);
void Floyd_Warshall(short** distanceMatrix);

void coutTempDistancesInMatrix(int lastIndex, int index1, int index2);  // do wzrostowo-iteracyjnego

void matrixToList(int n);

int countDistances();
BFSvertex* BFS(int start, int n);

int** countDistancesReturnMatrix(int n); // zwraca macierz odleg³oœci, do Knockera
int distanceOfStrongProductDigraphs(int** matrix, int n, int i, int j, int k);

// POMOCNICZE
#ifdef DEBUG
void matrixForTest();
void printMatrix(short** matrix);
void printAdjacencyList();
#endif // DEBUG

#endif // !FUNCTIONS_H
