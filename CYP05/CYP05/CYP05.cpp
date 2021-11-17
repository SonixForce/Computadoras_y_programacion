#include <stdio.h>

#define CANTIDAD 2000

int main() {

	//Variables
	int cantAlum, cuentAlum[CANTIDAD] = {}, tempCuent;
	float califAlum[CANTIDAD] = {}, tempCalif;


	//Detectar cantidad de alumnos, y con base a ello detectar poco a poco cada numero de cuenta y calificación.
	scanf_s("%i", &cantAlum);

	if (cantAlum != 0) {
		for (int i = 0; i < cantAlum; i++) {
			scanf_s("%i", &cuentAlum[i]);
			scanf_s("%f", &califAlum[i]);
		}

		//Ordenar arreglos.

		for (int i = 0; i < cantAlum; i++) {
			for (int c = 0; c+1 <= i; c++) {
				if (cuentAlum[c] == cuentAlum[c+1]) {
					cuentAlum[c] = cuentAlum[c+1];
				}
				else if (cuentAlum[c] > cuentAlum[c+1]) {
					tempCuent = cuentAlum[c+1];
					cuentAlum[c+1] = cuentAlum[c];
					cuentAlum[c] = tempCuent;
				}
			}
		}


		//Iprimir cantidad de alumnos, numeros de cuenta y calificaciones.
		printf("%i\n", cantAlum);

		for (int p = 0; p < cantAlum; p++) {
			printf("%i ", cuentAlum[p]);
			printf("%f\n", califAlum[p]);
		}
	}
	else {
		return 0;
	}
}