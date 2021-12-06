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
	char temp[1][TAMTOKEN] = {};
	bool palabraCopiada;
	iNumElementos = 0;
	int lonPalabra = 0;
	int tempo = 0;
	char* token;
	
	//El archivo xd
	FILE* archivo;
	fopen_s(&archivo, szNombre, "r");
	
	//Checar si se pudo abrir el archivo
	if (archivo != NULL && iNumElementos <= 16400) {
		palabraCopiada = false;
		token = {"1"};
		//Leer todo el archivo hasta su final, guardando todo el texto del mismo en un array

		for (int i = 0; !feof(archivo); i++) {
			
			//fgets(szPalabras[i],TAMTOKEN,archivo);
			if (szPalabras[i][0] < 32 && szPalabras[i][0] > 126);
				fscanf(archivo, "%50s", szPalabras[i]);

			//printf("%s\n", szPalabras[i]);
			lonPalabra = strlen(szPalabras[i]);


			iNumElementos++;

			//Quitar signos de puntuacion al inicio de todas las palabras

			for (int c = lonPalabra; c != -1; c--) {
				if (szPalabras[i][c] == '(' || szPalabras[i][c] == ')' || szPalabras[i][c] == ',' || szPalabras[i][c] == '.' || szPalabras[i][c] == ';') {
					szPalabras[i][c] = NULL;
				}
				//Quitar mayusculas
				if (szPalabras[i][c] >= 65 && szPalabras[i][c] <= 90)
					szPalabras[i][c] += 32;
			}

			//Este ciclo detecta los carácteres especiales y mayúsculas en el array y los quita
			/*for (int c = 0; c <= TAMTOKEN; c++) {
				
			}*/

			//Quitar espacios vacios dentro de cada palabra
			for (int c = 0; c < lonPalabra; c++) {
				if (szPalabras[i][c] == NULL) {
					temp[0][c] = szPalabras[i][c];
					szPalabras[i][c] = szPalabras[i][c + 1];
					szPalabras[i][c + 1] = temp[0][c];
				}
			}
			iEstadisticas[i] = 1;
			memset(temp, 0, TAMTOKEN);

			for (int c = 0; c < i; c++) {
				if (strcmp(szPalabras[i], szPalabras[c]) < 0) {
					strcpy_s(temp[0], szPalabras[c]);
					strcpy_s(szPalabras[c], szPalabras[i]);
					strcpy_s(szPalabras[i], temp[0]);

					tempo = iEstadisticas[c];
					iEstadisticas[c] = iEstadisticas[i];
					iEstadisticas[i] = tempo;

				}

				if (strcmp(szPalabras[i], szPalabras[c]) == 0) {
					memset(szPalabras[i], 0, TAMTOKEN);
					i--;
					iNumElementos--;
					iEstadisticas[c] += 1;
				}

				if (strlen(szPalabras[i]) == 0) {
					iEstadisticas[i] = 0;
				}
			}

			//printf("%s\n", szPalabras[i]);
		}
		memset(temp, 0, TAMTOKEN);

		fclose(archivo);

		if (strlen(szPalabras[0]) == 0) {
			for (int i = 0; i < iNumElementos; i++)
			{
				strcpy_s(temp[0], szPalabras[i + 1]);
				strcpy_s(szPalabras[i + 1], szPalabras[i]);
				strcpy_s(szPalabras[i], temp[0]);

				tempo = iEstadisticas[i];
				iEstadisticas[i] = iEstadisticas[i + 1];
				iEstadisticas[i + 1] = tempo;
			}
			iNumElementos--;
		}

	}
	else
		printf("Archivo no encontrado\n");
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
