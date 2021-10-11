#include <stdio.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "");

	float base;
	float altura;
	float area;

	printf("Bienvenido a este programa el cual calculará el valor del área de un rectángulo.\n\nPor favor, introduce el valor de la base del rectángulo: ");

	scanf_s("%f", &base);

	printf("\n\nAhora introduce el valor de la altura del rectángulo: ");
	
	scanf_s("%f", &altura);

	
	area = base * altura;


	printf("\n\nEsta es el área del rectángulo: %10.2f\n\n", area);
}