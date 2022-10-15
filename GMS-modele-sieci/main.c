#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

/*
 * WEJ�CIE
 * W kolejnych liniach.
 * Indeks modelu. Po spacji/spacjach parametr/parametry modelu.
 * 
 * WYJ�CIE
 * W kolejnych liniach.
 * Suma wszystkich odleg�o�ci grafu, kt�ry powsta� z modelu. (czyli liczba kraw�dzi?)
 * 
 * Oblicz sum� wszystkich odleg�o�ci w grafach powsta�ych za pomoc� modeli przedstawionych na wyk�adzie 
 * Uwaga ka�dy model musi generowa� sie�, tzn. jakakolwiek reprezentacja grafu ma znajdowa� si� w pami�ci, 
 * a nast�pnie, ma zosta� wyliczona suma odleg�o�ci.
 *
 * MODELE
 * 0) Barabasi�Ravasz�Vicsek
 * 1) Lu�Su�Guo (parametrem modelu jest liczba wierzcho�k�w, patrz wyk�ad: Modyfikacja modelu Lu�Su�Guo).
 * 2) Simplical
 * 3) Wzrostowo-iteracyjny
 * 4) DCN (parametrem modelu jest liczba wierzcho�k�w, patrz wyk�ad: Modyfikacja modelu Lu�Su�Guo).
 * 5) GFG
 * 6) Kronecker (parametrami modelu s� pot�ga oraz graf zapisany za pomoc� macierzy s�siedztwa od lewej do prawej bez spacji).
 *   (patrz silny produkt dw�ch graf�w z ostatniego wyk�adu, zdefiniuj pot�g� grafow� dla silnego produktu to jest G[x]G[x]G[x]..[x]G).
*/


int main()
{
	printf("Hello!\n");

	int noOfModel = 0;
	int retval;


	while (retval = scanf_s("%i", &noOfModel)) //scanf - may be unsafe // EOL == Ctrl+D, Enter  (lub Ctr+Z)
	{
		if (retval == EOF)
			break;
		getchar(); // spacja


		getModel(noOfModel);
	}

	printf("Bye!\n");

	
	return 0;
}

