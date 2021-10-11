#include <stdio.h>

int main() {
	//Estas variables guardan el tamaño de la pantalla del teléfono.
	int pantallaX;
	int pantallaY;

	//Estas variables guardan las coordenadas del objeto a mostrar, proporcional al tamaño de la pantalla del teléfono.
	float posX;
	float posY;

	//Estas variables guardan el tamaño del objeto, proporcional al tamaño de la pantalla del teléfono.
	float escX;
	float escY;

	//Estas variables guardan las coordenadas de la esquina superior izquierda del objeto a mostrar.
	int coordiX;
	int coordiY;

	//Estas variables guardan las coordenadas de la esquina inferior derecha del objeto a mostrar.
	int coorddX;
	int coorddY;

	//Detectar y guardar datos.
	scanf_s("%i", &pantallaX);
	scanf_s("%i", &pantallaY);

	scanf_s("%f", &posX);
	scanf_s("%f", &posY);

	scanf_s("%f", &escX);
	scanf_s("%f", &escY);

	//Operaciones para calcular las coordenadas exactas.
	coordiX = pantallaX * posX;
	coordiY = pantallaY * posY;

	coorddX = pantallaX * escX + coordiX;
	coorddY = pantallaY * escY + coordiY;
	
	//Imprimir datos.
	printf("%i %i %5.2f %5.2f %5.2f %5.2f %i %i %i %i", pantallaX, pantallaY, posX, posY, escX, escY, coordiX, coordiY, coorddX, coorddY);

	//Devolver 0 al sistema.
	return(0);
}