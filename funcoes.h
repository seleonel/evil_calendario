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
void feriadosFixos(anos* ano)
{
	char delimit[] 		= "\t"; // no caso, tab é o separador do arquivo
	FILE * fer_fixos 	= fopen("fixos", "r");
	char linha[100];
	char * ponteiro		= NULL;	
	for(int i = 0; 
	    fgets(linha,100, fer_fixos); 
	    i++)
	{
		ponteiro = strtok(linha, delimit);
		for(int k = 0; ponteiro ; ponteiro = strtok(NULL, delimit), k++)
		{
			switch(k)
			{
				case 0: 
					ano->mes.dia.fer.dia_ferfix[i] =  strtol(ponteiro, NULL, 10);
					break;
				case 1: 
					ano->mes.dia.fer.mes_ferfix[i] = strtol(ponteiro, NULL, 10);
					break;
				case 2: 
					strcpy(ano->mes.dia.fer.nome_ferfix[i], ponteiro);
					break;
			
			}
		}
	}
	fclose(fer_fixos);
}

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
	for(i = 1; 
	    i <= MES && fgets(meses, CARCT, arq_datas);
	    i++)
		strcpy(ano->mes.nome_mes[i], meses);
	fclose(arq_datas);

	arq_datas = fopen("semanas", "r");
	if(arq_datas == NULL)
		exit(EXIT_FAILURE);

	for(i = 1; 
	    i <= SEM && fgets(semanas, CARCT, arq_datas); 
	    i++)
		strcpy(ano->mes.nome_semana[i], semanas);
		fclose(arq_datas);
	
	feriadosFixos(ano);
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
void preencherDias()
{


}
#endif
