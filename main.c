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
	zerarMatrizes(&ano);
	// leitura do ano por fgets ou scanf
	short int year = 2019;
	// primeira checagem se bissexto ou não
	ano.bissexto = ehBissexto(year);
	ano.ano = year;
	definirNomes(&ano);
	definirDatas(&ano);
	for(int i = 1; i <= 12; i++){
		printf("Mes %d\n", i);
		for(int j = 1; j <= 6; j++){
			for(int k = 1; k <= 7; k++){
				printf(" %d ", ano.mes.dias[i][j][k]);}
			puts("\n");}}
	//definirFeriados(&ano);
	//imprimirFeriados(&ano);

	return 0;
}
