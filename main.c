#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "funcoes.h"
#include "estrutura.h"
// passagem de parametros pro main por argc e argv
int main()
{

	/*
	 * Inicializadas os dados necessários das structs
	 */

	anos ano;
	// leitura do ano por fgets ou scanf
	short int year = 2400;
	// primeira checagem se bissexto ou não
	ano.bissexto = ehBissexto(year);
	definirNomes(&ano);
	definirDatas(&ano);
	definirFeriados(&ano);
	imprimirFeriados(&ano);

	return 0;
}
