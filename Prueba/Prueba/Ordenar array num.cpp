#include <stdio.h>
#define NUMELEMENTOS 5
int main()
{
	int arr[NUMELEMENTOS];
	int numPasada;
	int numComparacion;
	int aux;
	int i;

	// Obtener los valores
	for (i = 0; i < NUMELEMENTOS; i++)
	{
		printf("Dato %i: ", i + 1);
		scanf_s("%i", &arr[i]);
	}
	// ordenamos por burbuja sencilla
	for (numPasada = 0; numPasada < NUMELEMENTOS - 1; numPasada++)
	{
		for (numComparacion = 0; numComparacion < NUMELEMENTOS - 1; numComparacion++)
		{
			if (arr[numComparacion] > arr[numComparacion + 1])
			{
				//intercambia i con i+1
				aux = arr[numComparacion + 1];
				arr[numComparacion + 1] = arr[numComparacion];
				arr[numComparacion] = aux;
			}
		}
	}

	for (i = 0; i < NUMELEMENTOS ; i++)
		printf("%i ", arr[i]);
}

