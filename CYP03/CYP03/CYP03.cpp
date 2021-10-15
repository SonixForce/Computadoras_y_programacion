#include <stdio.h>

int main() {


	//Se declaran las variables para cada dato de la fecha
	int dia, mes, ano;

	//Se detectan los valores para las variables
	scanf_s("%d", &dia);
	scanf_s("%d", &mes);
	scanf_s("%d", &ano);

	//Se le suma 1 al día para calcular el día siguiente
	dia++;

	//Detecta si el útlimo día de febrero sea el 29 mientras no sea año biciesto
	if (!((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0) && mes == 2) {
		if (dia == 29 && mes == 2) {
			//El día se restea a 1 y se le suma 1 al mes
			dia = 1;
			mes++;
			printf("%d %d %d", dia, mes, ano);
		}
		else {
			printf("%d %d %d", dia, mes, ano);
		}
	}


	//Detecta si el útlimo día de febrero sea el 29 mientras sea año biciesto
	else if (((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0) && mes == 2) {
		if (dia == 30) {
			//El día se restea a 1 y se le suma 1 al mes
			dia = 1;
			mes++;
			printf("%d %d %d", dia, mes, ano);
		}
		else {
			printf("%d %d %d", dia, mes, ano);
		}
	}


	//Detecta si el año es bisiesto o no, también excluye que el mes sea febrero
	else if (!((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0) || (((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0) && mes != 2)){
		//Se detectan los meses con 31 días
		if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12) {
			//Se detecta si el día vale 32, entonces resetear el día a 1 y sumar 1 al mes
			if (dia == 32) {
				dia = 1;
				mes++;
			}
			//Si el mes es 13 entonces se resetea a 1 y se le suma 1 al año
			if (mes == 13) {
				mes = 1;
				ano++;
				printf("%d %d %d", dia, mes, ano);
			}
			else {
				printf("%d %d %d", dia, mes, ano);
			}
		}
		//Se detectan los meses con 30 días
		else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
			//Se detecta si el día vale 31, entonces resetear el día a 1 y sumar 1 al mes
			if (dia == 31) {
				dia = 1;
				mes++;
			}
			printf("%d %d %d", dia, mes, ano);
		}
	}
	return(0);
}