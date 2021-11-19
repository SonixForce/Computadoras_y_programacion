#include <stdio.h>

#define CANTIDAD 2000

int main() {

	//Variables
	int cantAlum, cuentAlum[CANTIDAD] = {}, tempCuent, alumnFin = 1;
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

					tempCalif = califAlum[c + 1];
					califAlum[c + 1] = califAlum[c];
					califAlum[c] = tempCalif;
				}
			}
		}
		//Eliminar numeros de cuenta repetidos y dejar solamente la calificación más alta.
		for (int i = cantAlum; i != 0; i--) {
			for (int c = 0; c + 1 <= i; c++) {
				for(int b = c; cuentAlum[b] == cuentAlum[b + 1]; b++){
					if (califAlum[b] > califAlum[b + 1]) {
						califAlum[b + 1] = califAlum[b];
						califAlum[b] = NULL;
					}
					if (califAlum[b] < califAlum[b + 1])
						califAlum[b] = NULL;
					cuentAlum[c] = NULL;
				}
				
			}
		}

		//Pasar registros vacíos hasta el final de cada arreglo
		for (int i = cantAlum; i != 0; i--) {
			for (int c = 0; c + 1 <= i; c++) {
				if (cuentAlum[c] == NULL && cuentAlum[c + 1] != NULL && califAlum[c] == NULL && califAlum[c + 1] != NULL) {
					cuentAlum[c] = cuentAlum[c + 1];
					califAlum[c] = califAlum[c + 1];
					cuentAlum[c + 1] = NULL;
					califAlum[c + 1] = NULL;
				}
			}
		}

		//Reconteo de la cantidad de alumnos final
		for (int i = cantAlum; i != 0; i--) {
			if (cuentAlum[i] != 0)
				alumnFin += 1;
		}
		
		//Iprimir cantidad de alumnos, numeros de cuenta y calificaciones.
		printf("%i\n", alumnFin);

		for (int p = 0; p < cantAlum; p++) {
			printf("%i ", cuentAlum[p]);
			printf("%f\n", califAlum[p]);
			if (cuentAlum[p + 1] == NULL && califAlum[p + 1] == NULL)
				break;
		}
	}
	else {
		return 0;
	}
	return 0;
}