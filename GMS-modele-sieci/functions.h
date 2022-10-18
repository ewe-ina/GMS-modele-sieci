#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdbool.h>

int allVertex;
int** adjacencyMatrix;					// ktora na poczatku jest zwykla macieza sasiedztwa
int** indexMatrix;						// identyfikatory przedostatnich punkt�w na �cie�ce ��cz�cej punkty - do F-W
adjacencyListVertex** adjacencyList;	//tablica wska�nik�w

#define MAXVAL  INT_MAX / 3  // imituje nieskonczonosc w algorytmie
//#define DEBUG


typedef struct vertex 
{
	int index;							// indeks wierzcho�ka
	bool new;							// czy wierzcho�ek jest nowy?
	vertex* next;						// wska�nik na nast�pny wierzcho�ek w li�cie s�siedztwa
}vertex;

// do Lu-Su-Guo_v2
typedef struct adjacencyListVertex		// wierzcholek przechowywany w liscie sasiedztwa
{
	int index;							// indeks wierzcho�ka
	bool bottom;						// czy jest dolnym wierzcho�kiem?
	struct adjacencyListVertex* next;	// wska�nik na nast�pny wierzcho�ek w li�cie s�siedztwa 
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
