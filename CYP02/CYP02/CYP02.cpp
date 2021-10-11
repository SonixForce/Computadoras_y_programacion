#include <stdio.h>

int main() {
	//Esta variable será la que recibirá el valor del tamaño del archivo BMP.
	int tamArch;

	//Esta variable será la que recibirá el valor de cuántos bits se dedicarán a los colores del archio BMP.
	int colArch;

	//Detección de valores.
	scanf_s("%d", &tamArch);
	scanf_s("%d", &colArch);


	//Imprimir resultado con el formato especificado en el PDF.
	printf("BM%08X00000000%08X", tamArch, colArch);

	//Devolver 0 al sistema.
	return(0);
}