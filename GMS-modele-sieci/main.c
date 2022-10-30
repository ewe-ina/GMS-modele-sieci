#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "functions.h"
#include "queue.h"
//#include "stack.h"

/* Ewelina Walkusz 101645
 * 
 * WEJŒCIE
 * W kolejnych liniach.
 * Indeks modelu. Po spacji/spacjach parametr/parametry modelu.
 * 
 * WYJŒCIE
 * W kolejnych liniach.
 * Suma wszystkich odleg³oœci grafu, który powsta³ z modelu. (czyli liczba krawêdzi?)
 * 
 * Oblicz sumê wszystkich odleg³oœci w grafach powsta³ych za pomoc¹ modeli przedstawionych na wyk³adzie 
 * Uwaga ka¿dy model musi generowaæ sieæ, tzn. jakakolwiek reprezentacja grafu ma znajdowaæ siê w pamiêci, 
 * a nastêpnie, ma zostaæ wyliczona suma odleg³oœci.
 *
 * MODELE
 * 0) Barabasi–Ravasz–Vicsek
 * 1) Lu–Su–Guo (parametrem modelu jest liczba wierzcho³ków, patrz wyk³ad: Modyfikacja modelu Lu–Su–Guo).
 * 2) Simplical
 * 3) Wzrostowo-iteracyjny
 * 4) DCN (parametrem modelu jest liczba wierzcho³ków, patrz wyk³ad: Modyfikacja modelu Lu–Su–Guo).
 * 5) GFG
 * 6) Kronecker (parametrami modelu s¹ potêga oraz graf zapisany za pomoc¹ macierzy s¹siedztwa od lewej do prawej bez spacji).
 *   (patrz silny produkt dwóch grafów z ostatniego wyk³adu, zdefiniuj potêgê grafow¹ dla silnego produktu to jest G[x]G[x]G[x]..[x]G).
*/


int main()
{
#ifdef DEBUG
	printf("Hello!\n");
#endif // DEBUG


	int noOfModel = 0;
	int retval = 0;


	while (retval = scanf_s("%i", &noOfModel)) //scanf - may be unsafe // EOL == Ctrl+D, Enter  (lub Ctr+Z)
	{
		if (retval == EOF)
			break;
		getchar(); // spacja


		getModel(noOfModel);
	}

//	do
//	{
//		retval = scanf_s("%i", &noOfModel);
//
//		if (retval == EOF)
//			break;
//		getchar(); // spacja
//
//		getModel(noOfModel);
//}
//	while (retval);

#ifdef DEBUG
	printf("Bye!\n");
#endif // DEBUG


	return 0;
}

