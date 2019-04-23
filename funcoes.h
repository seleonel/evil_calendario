#ifndef FUNCOES_H 
#define FUNCOES_H
#include "estrutura.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#define CARCT 30
#define MES 12
#define SEM 7
void leitura(anos* ano)
{
	int i;
	char meses[CARCT];
	char semanas[CARCT];
	FILE * arq_datas = fopen("meses", "r");
	if (arq_datas == NULL)
		exit(EXIT_FAILURE);
	// utilizo arquivos para definir nomes de meses e semanas
	// evito trabalho excessivo e código sujo
	for(i = 1; i <= MES && fgets(meses, CARCT, arq_datas); i++)
		strcpy(ano->mes.nome_mes[i], meses);
	fclose(arq_datas);

	arq_datas = fopen("semanas", "r");
	if(arq_datas == NULL)
		exit(EXIT_FAILURE);

	for(i = 1; i <= SEM && fgets(semanas, CARCT, arq_datas); i++)
		strcpy(ano->mes.nome_semana[i], semanas);
		fclose(arq_datas);
	

}
bool ehBissexto(long int ano)
{
	return ((ano % 4 == 0 && ano % 100 != 0) || ( ano % 400 == 0));
}

void definirNomes(anos* ano)
{	
	leitura(ano);
}
void mostraMeses()
{



}
void definirDatas(anos* ano)
{


}
void definirFeriados(anos* ano)
{


}
void imprimirFeriados(anos* ano)
{



}
#endif
