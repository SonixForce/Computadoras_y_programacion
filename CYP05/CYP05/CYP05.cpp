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
		for (int i = cantAlum; i != 0; i--) {
			for (int c = 0; c + 1 <= i; c++) {
				if (cuentAlum[c] > cuentAlum[c + 1] && cuentAlum[c + 1] != 0) {
					tempCuent = cuentAlum[c + 1];
					cuentAlum[c + 1] = cuentAlum[c];
					cuentAlum[c] = tempCuent;
				}
			}
		}
		//Eliminar numeros de cuenta repetidos y dejar solamente la calificación más alta.
		for (int i = cantAlum; i != 0; i--) {
			for (int c = 0; c + 1 <= i; c++) {
				for (int b = c; cuentAlum[b] == cuentAlum[b + 1]; b++) {
					if (califAlum[b] > califAlum[b + 1]) {
						califAlum[b + 1] = califAlum[b];
						califAlum[b] = NULL;
					}
					cuentAlum[c] = NULL;
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
	return 0;
}