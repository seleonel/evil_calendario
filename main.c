#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "funcoes.h"
#include "estrutura.h"
int main()
{
	/*
	 * Inicializadas os dados necessários das structs
	 */

	anos ano;
	short int year = 2400;
	ano.bissexto = ehBissexto(year);
	definirNomes(&ano);
	definirDatas(&ano);
	definirFeriados(&ano);
	imprimirFeriados(&ano);

	return 0;
}
