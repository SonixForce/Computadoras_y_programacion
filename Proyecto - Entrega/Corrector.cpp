/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion. 
	(c) Jesus Emilio Garces Zenil 422035587.
	
	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.
	
******************************************************************************************************************/


#include "stdafx.h"
#include <string.h>
#include "corrector.h"
#include <stdio.h>
//Funciones publicas del proyecto

//void buscador(char palabra[][TAMTOKEN], char dicc[][TAMTOKEN], int elementos, int *cantPalabra) {
//	bool palabraEncontrada = false;
//	char tempPalabra[1][TAMTOKEN];
//
//	for(int i = 0; i < elementos && !palabraEncontrada; i++)
//		if (strcmp(palabra[0], dicc[i]) < 0)
//		{
//			palabraEncontrada = true;
//		}
//		else {
//			strcpy(dicc[i], palabra[0]);
//		}
//}

void ordenar(char dicc[][TAMTOKEN], int elementos) {
	char temp[1][TAMTOKEN];
	for (int i = 0; i < elementos; i++)
		for (int c = 0; c < elementos - 1; c++)
			if (strcmp(dicc[c], dicc[c + 1]) > 0 && strlen(dicc[c+1]) != 0) {
				memcpy(temp[0], dicc[c + 1],TAMTOKEN);
				memcpy(dicc[c + 1], dicc[c], TAMTOKEN);
				memcpy(dicc[c], temp[0], TAMTOKEN);
				memset(temp[0], 0, TAMTOKEN);
			}
}


/*****************************************************************************************************************
	DICCIONARIO: Esta funcion crea el diccionario completo
	char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario	
	char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
	int		iEstadisticas[]			:	Arreglo con el numero de veces que aparecen las palabras en el diccionario
	int &	iNumElementos			:	Numero de elementos en el diccionario
******************************************************************************************************************/
void	Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos)
{
	//Variables de texto previas hechas para el procesado del texto del archivo
	char texto[2][TAMTOKEN] = {};
	bool palabraCopiada;
	memset(szPalabras, 0, TAMTOKEN);
	iNumElementos = 0;
	
	//El archivo xd
	FILE* archivo;
	fopen_s(&archivo, szNombre, "r");
	
	//Checar si se pudo abrir el archivo
	if (archivo != NULL) {
		//Leer todo el archivo hasta su final, guardando todo el texto del mismo en un array
		while (!feof(archivo)) {
			//fgets(texto[0], NUMPALABRAS, archivo);
			fscanf(archivo, "%s", texto[0]);
			iNumElementos += 1;
			palabraCopiada = false;

			//Este ciclo detecta los carácteres especiales y los quita
			for (int i = 0; i < TAMTOKEN && !palabraCopiada; i++) {
				if (texto[0][i] == '(' || texto[0][i] == ')' || texto[0][i] == ',' || texto[0][i] == '.' || texto[0][i] == ';')
					texto[0][i] = NULL;
				else if (texto[0][i] == NULL)
					palabraCopiada = true;
			}
			palabraCopiada = false;

			//Elimina cadenas y espacios vacios
			for (int i = 0; i < TAMTOKEN; i++)
				if (texto[0][i] == NULL) {
					texto[0][i] = texto[0][i + 1];
					texto[0][i + 1] = NULL;
				}

			//printf("%s\n", texto[0]);

		//Quita todas las mayusculas
			for (int i = 0; i < strlen(texto[0]); i++)
				texto[0][i] = towlower(texto[0][i]);

			//Se guarda palabra por palabra dentro del diccionario
			for (int i = 0; i < iNumElementos && !palabraCopiada; i++) {
				if (szPalabras[i][0] == 'Ì' || szPalabras[i][0] == '\0') {
					memcpy(szPalabras[i], texto[0], TAMTOKEN);
					memset(texto[0], 0, TAMTOKEN);
					//printf("%s\n", szPalabras[i]);
					palabraCopiada = true;
				}
			}

			//buscador(texto, szPalabras, iNumElementos, iEstadisticas);

			/*for (int i = 0; i < iNumElementos; i++) {
				if (strcmp(szPalabras[i], szPalabras[i + 1]) != 0) {

				}
			}*/

		}
		//printf("Palabras leidas\n");
		ordenar(szPalabras, iNumElementos);
		//printf("Palabras ordenadas\n");
		int buffer = 0;
		for (int i = 0; i < iNumElementos; i++) {
			if (strcmp(szPalabras[i], szPalabras[i + 1]) == 0) {
				memset(szPalabras[i], 0, TAMTOKEN);
			}
			if (strlen(szPalabras[i]) == 0) {
				iEstadisticas[i] = NULL;
				buffer++;
			}
			else {
				iEstadisticas[i] = 1 + buffer;
				buffer = 0;
			}
		}
		//printf("Palabras repetidas eliminadas\n");

		/*	for (int i = 0; i <= iNumElementos; i++) {
				iEstadisticas[i] = 1;
				if (strlen(szPalabras[i]) == 0) {
					iEstadisticas[i] += 1;
				}
		}*/
		buffer = 0;
		for (int c = 0; c < iNumElementos; c++) {
			for (int i = 0; i < iNumElementos - 1; i++) {
				if (strlen(szPalabras[i]) == 0) {
					strcpy_s(texto[0], szPalabras[i]);
					strcpy_s(szPalabras[i], szPalabras[i + 1]);
					strcpy_s(szPalabras[i + 1], texto[0]);
					buffer = iEstadisticas[i];
					iEstadisticas[i] = iEstadisticas[i + 1];
					iEstadisticas[i + 1] = buffer;
					memset(texto, 0, TAMTOKEN);
				}
			}
		}

		//printf("Fin\n");
		iNumElementos = 0;
		for (int i = 0; strlen(szPalabras[i]) != 0; i++)
			iNumElementos++;

			/*if (strlen(szPalabras[i]) == 0)
				strcpy(szPalabras[i], szPalabras[i + 1]);

		}*/

		fclose(archivo);
	}
}

/*****************************************************************************************************************
	ListaCandidatas: Esta funcion recupera desde el diccionario las palabras validas y su peso
	Regresa las palabras ordenadas por su peso
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
******************************************************************************************************************/
void	ListaCandidatas		(
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
{

	//Sustituya estas lineas por su código
	strcpy_s(szListaFinal[0], szPalabrasSugeridas[ 0] ); //la palabra candidata
	iPeso[0] = iEstadisticas[0];			// el peso de la palabra candidata
	
	iNumLista = 1;							//Una sola palabra candidata
}

/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/
void	ClonaPalabras(
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
{
	//Sustituya estas lineas por su código
	strcpy_s(szPalabrasSugeridas[0], szPalabraLeida); //lo que sea que se capture, es sugerencia
	iNumSugeridas = 1;							//Una sola palabra sugerida
}
