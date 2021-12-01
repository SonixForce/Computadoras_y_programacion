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
	char texto[NUMPALABRAS][TAMTOKEN] = {};
	char textoLimpio[NUMPALABRAS][TAMTOKEN] = {};
	char temp[NUMPALABRAS][TAMTOKEN] = {};
	
	//Conteo de palabras que hay en el archivo sin modificar
	int palabras = 0;

	//El archivo xd
	FILE* archivo;
	fopen_s(&archivo, szNombre, "r");
	
	//Checar si se pudo abrir el archivo
	if (archivo != NULL) {

		//Leer todo el archivo hasta su final, guardando todo el texto del mismo en un array
		while (!feof(archivo)) {
			for (int i = 0; i != NUMPALABRAS; i++) {
				//fgets(texto[i], NUMPALABRAS, archivo);
				fscanf(archivo, "%s", texto[i]);
				//printf("%s\n", texto[i]);
			}
		}

		//Conteo de cuantas palabras sin modificar hay en el archivo
		int j = 0;
		int conteo = 0;
		while (texto[j][0] != NULL) {
			conteo++;
			j++;
		}

		iEstadisticas[conteo];

		//Ciclo principal para el procesado de arrays
		for (int i = 0; i <= conteo; i++) {

			//Este ciclo detecta los carácteres especiales y mayúsculas en el array y los quita
			for (int c = 0; c <= TAMTOKEN; c++) {
				if (texto[i][c] != '(' && texto[i][c] != ')' && texto[i][c] != ',' && texto[i][c] != '.' && texto[i][c] != '-' && texto[i][c] != '_' && texto[i][c] != '¿' && texto[i][c] != '?' && texto[i][c] != '¡' && texto[i][c] != '!' && texto[i][c] != '"' && texto[i][c] != ':' && texto[i][c] != '\'')
					textoLimpio[i][c] = texto[i][c];
				textoLimpio[i][c] = towlower(textoLimpio[i][c]);
			}

			//Este ciclo detecta los espacios vacíos dejados por los carácteres especiales y los quita
			for (int c = 0; c <= TAMTOKEN; c++) {
				if (textoLimpio[i][c] == NULL) {
					temp[i][c] = textoLimpio[i][c];
					textoLimpio[i][c] = textoLimpio[i][c + 1];
					textoLimpio[i][c + 1] = temp[i][c];
				}
			}
		}

		//Este no sirve ayuda por favor no se por que no sirve
		for (int i = 0; i <= conteo; i++) {
			//int comp = strcmp(szPalabras[i], textoLimpio[i]);
			if (szPalabras[i] == textoLimpio[i]) {
					iEstadisticas[i] = 1;
			}
			else if (szPalabras[i] != textoLimpio[i])
				for (int c = 0; c <= TAMTOKEN; c++) {
					szPalabras[i][c] = textoLimpio[i][c];
					iEstadisticas[i] = 0;
				}
			//printf("%s\t\t\t%i\n", szPalabras[i], iEstadisticas[i]);
		}

		for (int i = 0; i <= conteo; i++) 
			printf("%s\t\t\t%i\n", szPalabras[i], iEstadisticas[i]);
	}
	else {
		printf("El nombre del archivo es incorrecto.");
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
