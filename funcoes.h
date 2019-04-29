#ifndef FUNCOES_H 
#define FUNCOES_H
#include "estrutura.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#define CARCT 30
#define MES 12
#define SEM 7
void zerarMatrizes(anos* ano)
{
	for(int i = 0; i < 14; i ++)
		for(int j = 0; j < 6; j++)
			for(int k = 0; k < 7; k++)
				ano->mes.dias[i][j][k] = 0;

}	
void feriadosFixos(anos* ano)
{
	char delimit[] 		= "\t"; // no caso, tab é o separador do arquivo
	FILE * fer_fixos 	= fopen("fixos", "r");
	char linha[100];
	char * ponteiro		= NULL;	
	for(int i = 1; 
	    fgets(linha,100, fer_fixos); 
	    i++)
	{
		ponteiro = strtok(linha, delimit);
		for(int k = 0; ponteiro ; ponteiro = strtok(NULL, delimit), k++)
		{
			switch(k)
			{
				case 0: 
					ano->mes.dia.fer.dia_ferfix[i][0] =  strtol(ponteiro, NULL, 10);
					break;
				case 1: 
					ano->mes.dia.fer.dia_ferfix[i][1] = strtol(ponteiro, NULL, 10);
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
unsigned short int congruenzaZell(anos* ano, int mes)
{
	unsigned short int primeiro_dia = 1;
	long int ano_copia = ano->ano;
	long int k, j, h;
	k = j = k = 0;

	// retirado de https://www.geeksforgeeks.org/zellers-congruence-find-day-date/

	if (mes == 1)
	{
		mes 	= 13;
		--ano_copia;
	}else if(mes == 2)
	{
		mes = 14;
		--ano_copia;
	}
	k 	= ano_copia % 100;
	j 	= ano_copia / 100;
	h 	= primeiro_dia + 13*(mes+1)/5 + k + k/4 + j/4 + 5*j; 
	h 	= h % 7; 
	if(h == 0)
		h 	= 7;
	return h;

}
void preencherDias(anos* ano, int mes, unsigned int prim_dia)
{
	unsigned short int cont = 1;
	for(int j = 1; j <= 6; j ++){
		for(int k = 1; k <= 7 ; k++){
			if (j == 1 && k < prim_dia){
				continue;
			}else{
				ano->mes.dias[mes][j][k] = cont;
			}
		
			cont += 1;
			if (cont > ano->mes.dia.qtd){
				ano->mes.ultimo_dia[mes] = cont - 1;
				return ;
			}
			
		}
	}
	
		

}
void definirDias(anos* ano, int mes, unsigned int prim_dia)
{
	if (mes == 2){
		if(ano->bissexto)
			ano->mes.dia.qtd = 29;
		else
			ano->mes.dia.qtd = 28;
	}else if(mes == 1 || mes == 3 
	    || mes == 5 || mes == 7 
	    || mes == 8 || mes == 10
	    || mes == 12){
		ano->mes.dia.qtd = 31;
	}else{
		ano->mes.dia.qtd = 30;
	}
	preencherDias(ano, mes, prim_dia);
	
}

void definirDatas(anos* ano)
{
	unsigned int prim_dia 	= 0;
	//definição de cada dia em específico 
	//congruencia de zeller
	for(int i = 1 ; i <= MES ; i++)
	{
		prim_dia = congruenzaZell(ano, i);
		definirDias(ano, i, prim_dia);
	}

}
void salvarRelacionados(int msanta,int dia_santa, int mquarta, int dia_quarta, int pascoa, int mpasc, anos* ano )
{
	FILE * arq_dim = fopen("dinamicos", "w");
 
	if(!arq_dim) 
		exit(EXIT_FAILURE);
	
	fprintf(arq_dim, "%d\t\%d\tQuarta-feira Santa\n", dia_quarta, mquarta);

	fprintf(arq_dim, "%d\t\%d\tPaixão de Cristo\n", dia_santa, msanta);

	fprintf(arq_dim, "%d\t\%d\tDomingo de páscoa\n", pascoa, mpasc);
	fclose(arq_dim);

}
void definirRelacionados(int dia_pasc, int mes_pasc, anos* ano)
{
	short int dias_cinza	 = 46;
	short int dias_sexta 	 = 2;
	int quartafeira_c	 = 0;
	int sexta_santa	         = 0;
	int mes_quarta		 = mes_pasc;
	int mes_santa		 = mes_pasc;
	
	quartafeira_c = dia_pasc - dias_cinza;
	sexta_santa = dia_pasc - dias_sexta;

	while( quartafeira_c < 1 )
	{
		--mes_quarta;
		quartafeira_c = ano->mes.ultimo_dia[mes_quarta] +  quartafeira_c;
	}
	while( sexta_santa < 1 )
	{
		--mes_santa;
		sexta_santa = ano->mes.ultimo_dia[mes_santa] + sexta_santa;
	}
	salvarRelacionados(mes_santa, sexta_santa, mes_quarta, quartafeira_c, dia_pasc, mes_pasc, ano );

}
void definirPascoa(anos* ano)
{
	// primeira tentativa, usar o metodo anonimo
	// tambem chamado de meeus/jones/butcher
	int a, b, c, d, e, f, g, 
	    h, i, k, l, m, n, p;
	a = b = c = d = e = f = g = 
	h = i = k = l = m = n = p = 0;

	a = ano->ano % 19;
	b = ano->ano / 100;
	c = ano->ano % 100;
	d = b / 4;
	e = b % 4;
	f = ( b + 8 ) / 25;
	g = ( b - f + 1) / 3;
	h = ( 19 * a + b - d - g + 15) % 30;
	i = c / 4;
	k = c % 4;
	l = ( 32 + 2 * e + 2 * i - h - k) % 7;
	m = ( a + 11 * h + 22 * l ) / 451;
	n = ( h + l - 7 * m + 114 ) / 31; // mes
	p = (( h + l - 7 * m + 114 ) % 31 ) + 1; // dia
	ano->mes.dia.fer.ha_feriado[n] = true;
	definirRelacionados(p, n, ano);
}

void definirFeriados(anos* ano)
{
	/* definir aqui os booleanos 
	 * dos fixos (TODO)*/

	definirPascoa(ano);
	//definirEquinocios();
	//definirEstacoes();
	//definirLuas();
	//finalizarBooleanos();

}
void imprimirFeriados(anos* ano)
{



}

#endif
