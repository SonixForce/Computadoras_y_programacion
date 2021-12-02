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
	char texto[1][TAMTOKEN] = {};
	memset(szPalabras, 0, TAMTOKEN);
	//char textoLimpio[60000][TAMTOKEN] = {};
	char temp[60000][TAMTOKEN] = {};

	//El archivo xd
	FILE* archivo;
	fopen_s(&archivo, szNombre, "r");
	
	//Checar si se pudo abrir el archivo
	
	if (archivo != NULL) {
		//Leer todo el archivo hasta su final, guardando todo el texto del mismo en un array
		while (!feof(archivo)) {
			for (int i = 0; i != NUMPALABRAS; i++) {
				//fgets(texto[i], NUMPALABRAS, archivo);
				fscanf(archivo, "%s", szPalabras[i]);
				//printf("%s\n", texto[i]);
			}
		}

		for (int i = 0; i = NUMPALABRAS; i++) {
			if (strlen(szPalabras[i]) == 0)
				szPalabras = NULL;

		}

		//Conteo de cuantas palabras sin modificar que hay en el archivo
		iNumElementos = 0;
		for (int j = 0; strlen(szPalabras[j]) != 0; j++) {
			iNumElementos++;
		}


		//Ciclo principal para el procesado de arrays
		for (int i = 0; i <= iNumElementos; i++) {

			//Este ciclo detecta los carácteres especiales y los quita
			for (int c = 0; c <= TAMTOKEN; c++) {
				if (szPalabras[i][c] == '(' || szPalabras[i][c] == ')' || szPalabras[i][c] == ',' || szPalabras[i][c] == '.' || szPalabras[i][c] == '-' || szPalabras[i][c] == '_' || szPalabras[i][c] == '¿' || szPalabras[i][c] == '?' || szPalabras[i][c] == '¡' || szPalabras[i][c] == '!' || szPalabras[i][c] == '"' || szPalabras[i][c] == ':' || szPalabras[i][c] == '\'' || szPalabras[i][c] == ';' || szPalabras[i][c] == '[' || szPalabras[i][c] == ']' || szPalabras[i][c] == '{' || szPalabras[i][c] == '}' || szPalabras[i][c] == '#' || szPalabras[i][c] == '&' || szPalabras[i][c] == '$' || szPalabras[i][c] == '%' || szPalabras[i][c] == '/')
					szPalabras[i][c] = NULL;
			}
			for (int c = 0; c <= TAMTOKEN; c++)
			if (szPalabras[i][c] == NULL) {
				szPalabras[i][c] = szPalabras[i][c + 1];
				szPalabras[i][c + 1] = NULL;
			}

			for (int c = 0; c <= iNumElementos; c++) {
				memcpy(temp[c], szPalabras[c], TAMTOKEN);
				printf("%s\n", temp[c]);
			}
				

			//Este ciclo detecta los espacios vacíos dejados por los carácteres especiales y los quita
			for (int c = 0; c <= iNumElementos - 1; c++) {
				if (strlen(szPalabras[c]) == 0) {
					memcpy(texto[c], szPalabras[c], TAMTOKEN);
					memcpy(szPalabras[c], szPalabras[c + 1], TAMTOKEN);
					memcpy(szPalabras[c + 1], texto[c], TAMTOKEN);
				}
			}

			//Quita las mayusculas del texto
			for (int c = 0; c <= TAMTOKEN; c++) {
				szPalabras[i][c] = towlower(szPalabras[i][c]);
			}
			memset(texto, 0, TAMTOKEN);
		}
		

		//Ordenar palabras alfabeticamente
		for (int i = 0; i <= iNumElementos; i++) {
			for (int c = 0; c < iNumElementos - 1; c++) {
				if (strcmp(szPalabras[c], szPalabras[c + 1]) > 0) {
					memcpy(texto, szPalabras[c], TAMTOKEN);
					memcpy(szPalabras[c], szPalabras[c + 1], TAMTOKEN);
					memcpy(szPalabras[c + 1], texto, TAMTOKEN);
				}
			}
		}
		//memset(temp, 0, TAMTOKEN);

		//Eliminar palabras repetidas del array
		for (int i = 0; i <= iNumElementos; i++) {
			for (int n = 0; n <= iNumElementos - 1; n++) {
				if (strcmp(szPalabras[n], szPalabras[n + 1]) != 0) {
					memcpy(texto[n], szPalabras[n], TAMTOKEN);
					iEstadisticas[n] += 1;
				}
			}
		}
		//memset(textoLimpio, 0, TAMTOKEN);

		//Mover espacios vacíos del array al final del mismo y mandar todos sus datos a la variable szPalabras
		for (int i = 0; i <= iNumElementos; i++) {
			for (int c = 0; c <= iNumElementos - 1; c++) {
				iEstadisticas[c] = 1;
				if (strlen(texto[c]) == 0) {
					iEstadisticas[c] = +1;
					memcpy(szPalabras[c], texto[c + 1], TAMTOKEN);
					memcpy(texto[c + 1], texto[c], TAMTOKEN);
					memcpy(texto[c], szPalabras[c], TAMTOKEN);
				}
			}
			memcpy(szPalabras[i], texto[i], TAMTOKEN);
		}
		memset(texto, 0, TAMTOKEN);

		//Recontar palabras
		iNumElementos = 0;
		for (int j = 0; szPalabras[j][0] != NULL; j++) {
			iNumElementos++;
		}
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
	strcpy(szListaFinal[0], szPalabrasSugeridas[ 0] ); //la palabra candidata
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
	strcpy(szPalabrasSugeridas[0], szPalabraLeida); //lo que sea que se capture, es sugerencia
	iNumSugeridas = 1;							//Una sola palabra sugerida
}
