#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void getModel(int model)
{
	switch (model)
	{
	case 0:
		Barabasi_Ravasz_Vicsek();
		break;
	case 1:
		Lu_Su_Guo();
		break;
	case 2:
		Simplical();
		break;
	case 3:
		Wzrostowo_iteracyjny();
		break;
	case 4:
		DCN();
		break;
	case 5:
		GFG();
		break;
	case 6:
		Kronecker();
		break;
	default:
		break;
	}
}

	void Barabasi_Ravasz_Vicsek()
	{
		printf("Barabasi-Ravasz-Vicsek\n");
	}

	void Lu_Su_Guo()
	{
		printf("Lu-Su-Guo\n");
	}

	void Simplical()
	{
		printf("Simplical\n");
	}

	void Wzrostowo_iteracyjny()
	{
		printf("Wzrostowo-iteracyjny\n");
	}

	void DCN()
	{
		printf("DCN\n");
	}

	void GFG()
	{
		printf("GFG\n");
	}
	void Kronecker()
	{
		printf("Kronecker\n");
	}
