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
int** indexMatrix;						// identyfikatory przedostatnich punkt�w na �cie�ce ��cz�cej punkty - do F-W
struct _adjacencyListVertex** adjacencyLists;	// tablica list s�siedztwa (tablica wska�nik�w)

#define MAXVAL  INT_MAX / 3  // imituje nieskonczonosc w algorytmie
#define DEBUG


typedef struct _vertex 
{
	int index;							// indeks wierzcho�ka
	bool new;							// czy wierzcho�ek jest nowy?
	struct _vertex* next;						// wska�nik na nast�pny wierzcho�ek w li�cie s�siedztwa
}vertex;

// do Lu-Su-Guo_v2
typedef struct _adjacencyListVertex		// wierzcholek przechowywany w liscie sasiedztwa
{
	int index;							// indeks wierzcho�ka
	bool bottom;						// czy jest dolnym wierzcho�kiem?
	struct _adjacencyListVertex *next;	// wska�nik na nast�pny wierzcho�ek w li�cie s�siedztwa 
}adjacencyListVertex;

// do BFS
typedef struct _BFSvertex 
{
	int distance;						// odleg�o��
	bool visited;						// czy wierzcho�ek zosta� ju� odwiedzony?
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
adjacencyListVertex** createAdjacencyLists(); // to te� tablica 2 wymiarowa
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
