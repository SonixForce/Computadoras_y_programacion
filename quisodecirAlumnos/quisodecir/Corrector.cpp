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
	iNumElementos = 0;
	int lonPalabra;
	int tempo;
	char* token;
	char* sigToken;
	
	//El archivo xd
	FILE* archivo;
	fopen_s(&archivo, szNombre, "r");
	
	//Checar si se pudo abrir el archivo
	if (archivo != NULL) {
		token = {};
		//Leer todo el archivo hasta su final, guardando todo el texto del mismo en un array

		for (int i = 0; !feof(archivo); i++) {
			
			//fgets(szPalabras[i],TAMTOKEN,archivo);+
			
			//Antes de copiar las palabras, se checa si la nueva posición de i ya contiene una palabra valida.
			if (szPalabras[i][0] < 32 || szPalabras[i][0] > 126)
				fscanf_s(archivo, "%s", szPalabras[i],TAMTOKEN);

			//printf("%s\n", szPalabras[i]);
			lonPalabra = strlen(szPalabras[i]);

			iNumElementos++;

			//Detectar signos de puntuación dentro de las palabras y en caso de que haya alguno, se separa la palabra usando como base ese signo de puntuación
			for (int c = 0; c <= lonPalabra; c++) {
				if (szPalabras[i][c] == '(') {
					token = strtok_s(szPalabras[i], "(", &sigToken);
					if (token != NULL) {
						strcpy_s(szPalabras[i + 1], sigToken);
						//c--;
					}
					lonPalabra = strlen(szPalabras[i]);
					
				}
				else if (szPalabras[i][c] == ')') {
					token = strtok_s(szPalabras[i], ")", &sigToken);
					if (token != NULL) {
						strcpy_s(szPalabras[i + 1], sigToken);
						//c--;
					}
					lonPalabra = strlen(szPalabras[i]);
				}
				else if (szPalabras[i][c] == ',') {
					token = strtok_s(szPalabras[i], ",", &sigToken);
					if (token != NULL) {
						strcpy_s(szPalabras[i + 1], sigToken);
						//c--;
					}
					lonPalabra = strlen(szPalabras[i]);
				}
				else if (szPalabras[i][c] == '.') {
					token = strtok_s(szPalabras[i], ".", &sigToken);
					if (token != NULL) {
						strcpy_s(szPalabras[i + 1], sigToken);
						//c--;
					}
					lonPalabra = strlen(szPalabras[i]);
				}
				else if (szPalabras[i][c] == ';') {
					token = strtok_s(szPalabras[i], ";", &sigToken);
					if (token != NULL) {
						strcpy_s(szPalabras[i + 1], sigToken);
						//c--;
					}
					lonPalabra = strlen(szPalabras[i]);
				}
			}

			//Quitar signos de puntuacion en las palabras que no se pudieron separar, o a las cuales no hubo necesidad de hacerlo
			for (int c = 0; c <= lonPalabra; c++) {
				if (szPalabras[i][c] == '(' || szPalabras[i][c] == ')' || szPalabras[i][c] == ',' || szPalabras[i][c] == '.' || szPalabras[i][c] == ';') {
					szPalabras[i][c] = NULL;
				}
				//Quitar mayusculas
				if (szPalabras[i][c] >= 65 && szPalabras[i][c] <= 90)
					szPalabras[i][c] += 32;
			}

			//Quitar espacios vacios dentro de cada palabra
			for (int c = 0; c < lonPalabra; c++) {
				for (int n = 0; n < lonPalabra; n++) {
					if (szPalabras[i][n] == NULL) {
						temp[0][n] = szPalabras[i][n];
						szPalabras[i][n] = szPalabras[i][n + 1];
						szPalabras[i][n + 1] = temp[0][n];
					}
				}
			}
			iEstadisticas[i] = 1;
			memset(temp, 0, TAMTOKEN);

			//Las palabras se van ordenando a la vez que se van añadiendo al arreglo, a la vez que se quitan palabras repetidas y se detectan strings vacios.
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

		/*for (int i = 0; i < iNumElementos; i++)
		{
			printf("%s", szPalabras[i]);
		}*/
		
		//Se quitan los strings vacios resultantes de strings hechos puramente de símbolos de puntuación
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
	int lenPalabraBase = strlen(szPalabraLeida);
	int lenPalabraExp;
	char palabraOG[TAMTOKEN] = {};
	iNumSugeridas = 0;
	char temp;
	char tempStr[TAMTOKEN] = {};
	char alfabeto[32] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','ñ','o','p','q','r','s','t','u','v','w','x','y','z','á','é','í','ó','ú'};
	int i = 0;
	FILE* debug;

	strcpy_s(palabraOG, szPalabraLeida);
	
	//Eliminacion
	while (i < lenPalabraBase) {
		szPalabraLeida[i] = NULL;
		for (int c = 0; c < lenPalabraBase; c++) {
			if (szPalabraLeida[c] == NULL) {
				szPalabraLeida[c] = szPalabraLeida[c + 1];
				szPalabraLeida[c + 1] = NULL;
			}
		}
		strcpy_s(szPalabrasSugeridas[i], szPalabraLeida);
		iNumSugeridas++;
		strcpy(szPalabraLeida, palabraOG);
		i++;
	}
	lenPalabraExp = lenPalabraBase+lenPalabraBase;

	//Transposicion
	while (i < lenPalabraExp) {
		for (int c = 0; c < lenPalabraBase; c++){
			if (szPalabraLeida[c + 1] != NULL) {
				temp = szPalabraLeida[c];
				szPalabraLeida[c] = szPalabraLeida[c + 1];
				szPalabraLeida[c + 1] = temp;
				strcpy_s(szPalabrasSugeridas[i], szPalabraLeida);
				iNumSugeridas++;
				strcpy(szPalabraLeida, palabraOG);
			}
			i++;
		}
	}
	strcpy(szPalabraLeida, palabraOG);
	i--;

	lenPalabraExp += (lenPalabraBase * 32);

	//Sustitucion
	while (i < lenPalabraExp) {
		for (int c = 0; c < lenPalabraBase; c++){
			for (int n = 0; n < 32; n++){
				szPalabraLeida[c] = alfabeto[n];
				strcpy_s(szPalabrasSugeridas[i], szPalabraLeida);
				i++;
				iNumSugeridas++;
				strcpy(szPalabraLeida, palabraOG);
			}
		}
	}
	//Ordenar
	for (int c = 0; c < lenPalabraExp; c++) {
		for (int j = 0; j < lenPalabraExp; j++) {
			if (strcmp(szPalabrasSugeridas[j], szPalabrasSugeridas[j + 1]) > 0) {
				strcpy_s(tempStr, szPalabrasSugeridas[j]);
				strcpy_s(szPalabrasSugeridas[j], szPalabrasSugeridas[j + 1]);
				strcpy_s(szPalabrasSugeridas[j + 1], tempStr);
			}
		}
	}

	lenPalabraExp += ((lenPalabraBase + 1) * 32);

	//Adicion
	while (i < lenPalabraExp) {
		for (int c = 0; c < lenPalabraBase + 1; c++){
			for (int n = lenPalabraBase + 1; n != c - 1; n--) {
				temp = szPalabraLeida[n];
				szPalabraLeida[n] = szPalabraLeida[n - 1];
				szPalabraLeida[n + 1] = temp;
			}
			for (int n = 0; n < 32; n++) {
				szPalabraLeida[c] = alfabeto[n];
				strcpy_s(szPalabrasSugeridas[i], szPalabraLeida);
				i++;
				iNumSugeridas++;
			}
			strcpy(szPalabraLeida, palabraOG);
		}
	}

	lenPalabraExp = iNumSugeridas;

	//Ordenar
	for (int c = 0; c < lenPalabraExp; c++) {
		for (int j = 0; j < lenPalabraExp - 1; j++) {
			if (strcmp(szPalabrasSugeridas[j], szPalabrasSugeridas[j + 1]) > 0) {
				strcpy_s(tempStr, szPalabrasSugeridas[j]);
				strcpy_s(szPalabrasSugeridas[j], szPalabrasSugeridas[j + 1]);
				strcpy_s(szPalabrasSugeridas[j + 1], tempStr);
			}
		}
	}

	//debug
	fopen_s(&debug,"debug.txt", "w");
	for(int c = 0; c < iNumSugeridas; c++)
	fprintf(debug, "%s\n", szPalabrasSugeridas[c]);
	fclose(debug);
}
