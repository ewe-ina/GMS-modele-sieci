#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "queue.h"
#include "stack.h"

int allVertex;
short** adjacencyMatrix;					// ktora na poczatku jest zwykla macieza sasiedztwa
short** indexMatrix;						// identyfikatory przedostatnich punkt�w na �cie�ce ��cz�cej punkty - do F-W


#define MAXVAL  SHRT_MAX / 3  // imituje nieskonczonosc w algorytmie
#define MAXVERTEXES 1000
//#define DEBUG


typedef struct _vertex 
{
	int index;							// indeks wierzcho�ka
	bool new;							// czy wierzcho�ek jest nowy?
	struct _vertex* next;						// wska�nik na nast�pny wierzcho�ek w li�cie s�siedztwa
}vertex;

typedef struct _edge
{
	int index;
	int v1index;
	int v2index;
	bool new;
	struct _edge* next;
} edge;


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
void Barabasi_Ravasz_Vicsek_v3();
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

int** countDistancesReturnMatrix(int n); // zwraca macierz odleg�o�ci, do Knockera
int distanceOfStrongProductDigraphs(int** matrix, int n, int i, int j, int k);

// POMOCNICZE
#ifdef DEBUG
void matrixForTest();
void printMatrix(short** matrix);
void printAdjacencyList();
#endif // DEBUG

#endif // !FUNCTIONS_H
