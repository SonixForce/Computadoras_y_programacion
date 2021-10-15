// TestDataCYP03.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

#include <stdlib.h>
#include <time.h>
#include "../CYP03/CYP03Func.h"
int _tmain(int argc, _TCHAR* argv[])
{
	int iDia, iMes, iAnio;
	int isDia, isMes, isAnio;
	int a,m,d,iContaArchivo=1;
	FILE *fp;

	char szNombre[14]; //CYP03-##.dat
	char szNombrePrefijo[] = "CYP03-";
	char szBuffer[40];

	srand(time(NULL));
	for (a=1 ; a < 2015; a++)
		for (m = 1; m <= 12; m++)
			for (d = 1; d < 32; d++)
			{
				if (esFechaValida(d,m,a))
					if (rand() == 152 ||rand() == 256||rand() == 892  )
					{
						sprintf(szBuffer, "%s%02i.txt",szNombrePrefijo,iContaArchivo++);
						fp = fopen (szBuffer,"w");
						if (fp != NULL)
						{
							fprintf(fp,"%2i %2i %4i\n",d, m, a);
						}
						fclose(fp);
					}								
			}
	return 0;
}

