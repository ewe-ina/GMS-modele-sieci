#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int allVertex;
int** distanceMatrix;  // ktora na poczatku jest zwykla macieza sasiedztwa
int** indexMatrix;  // identyfikatory przedostatnich punktów na œcie¿ce ³¹cz¹cej punkty
#define MAXVAL  INT_MAX / 3  // imituje nieskonczonosc w algorytmie
#define DEBUG


void getModel(int model);

void Barabasi_Ravasz_Vicsek();
void Lu_Su_Guo();
void Simplical();
void Wzrostowo_iteracyjny();
void DCN();
void GFG();
void Kronecker();

int** createMatrix();
void deleteMatrix(int** matrix);
void Floyd_Warshall();

// POMOCNICZE
void matrixForTest();
void printMatrix(int** matrix);

#endif // !FUNCTIONS_H
