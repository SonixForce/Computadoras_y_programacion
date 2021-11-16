#include<stdio.h>
#include<math.h>

int main() {
	//Declaración de variables que almacenaran los datos a introducir
	double limInicio;
	double limFinal;
	double incremento;
	//Declaración de variables que almacenaran los resultados a mostrar
	double resulExp;
	double resulE = 0;
	//Declaración de variables para calcular el exponencial de euler a mano
	int c;
	int f;
	int fact;

	//Detectar datos a introducir
	scanf_s("%lf", &limInicio);
	scanf_s("%lf", &limFinal);
	scanf_s("%lf", &incremento);

	//Calcular cuál va a ser el conteo para la serie de euler
	int conteo = (limFinal - limInicio) / incremento;

	//Si el limite inicial es menor o igual al limite final...
	if (limInicio == 0 && limFinal == 0) {
		resulExp = 1;
		resulE = 1;
		printf("%f %f %f", limInicio, resulE, resulExp);
		return 0;
	}
	else if (incremento == 0) {
		return 1;
	}
		//Ejecutar while mientras lim inicial sea menor o igual al lim final mas incremento
		while (limInicio <= limFinal + incremento) {

			//Calculo de exponencial sin la función exp
			//Conteo de la serie
			for (c = 0; c <= conteo; c++) {
				fact = 1;
				//Calculo del factorial
				for (f = 1; f <= c; f++) {
					fact = fact * f;
				}
				//Almacenar resultado periodicamente
				resulE = resulE + (pow(limInicio, c)) / fact;
			}
			//Funcion exponencial de math.h, guardada en resultadoExponencial
			resulExp = exp(limInicio);
			//Imprimir resultados
			printf("%f %f %f\n", limInicio, resulE, resulExp);
			//Limite inicial incrementará con forme al incremento introducido
			limInicio = limInicio + incremento; 
			resulE = 0;
		}
	}