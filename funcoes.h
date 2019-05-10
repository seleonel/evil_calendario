#ifndef FUNCOES_H 
#define FUNCOES_H
#include "estrutura.h"
#include "lua.h"
#include "astronomia.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#define CARCT 30
#define MES 12
#define SEM 7
#define QTD_DIM 6
void calculoLuaCheia(anos*);
void calculoGreg( double, long int, FILE*, char*);
void anoUser(anos* ano)
{
	puts("Por favor, digite o ano que deseja saber os feriados: ");
	scanf("%d", &ano->ano);

}
void zerarMatrizes(anos* ano)
{
	for(int i = 0; i < 14; i ++)
		for(int j = 0; j < 6; j++)
			for(int k = 0; k < 7; k++)
				ano->mes.dias[i][j][k] = 0;

	for (int i = 0; i < 50; i++)
		for (int j = 0; j < 2; j++ )
			ano->mes.dia.fer.feriados_tot[i][j] = 0;
	for(int i = 0; i < 50; i++)
		for (int j = 0; j < 200; j++)
			ano->mes.dia.fer.nome_tot[i][j] = 0;
	

		
}	
void feriadosSep(anos* ano, char* nome_arq, int controle)
{
	static unsigned int contador = 0;
	char delimit[] 		= "\t"; // no caso, tab é o separador do arquivo
	FILE* fer	= fopen(nome_arq, "r");
	char linha[100];
	char * ponteiro		= NULL;	
	for(int i = 1; 
	    fgets(linha,100, fer); 
	    i++)
	{
		ponteiro = strtok(linha, delimit);
		for(int k = 0; ponteiro ; ponteiro = strtok(NULL, delimit), k++)
		{
			switch(k)
			{
				case 0: ano->mes.dia.fer.feriados_tot[contador][0] =  strtol(ponteiro, NULL, 10);
					break;
				case 1: ano->mes.dia.fer.feriados_tot[contador][1] = strtol(ponteiro, NULL, 10);
					break;
				case 2: if(controle)
						strcpy(ano->mes.dia.fer.nome_tot[contador], "Lua cheia\n");
					else
						strcpy(ano->mes.dia.fer.nome_tot[contador], ponteiro);
					break;
			
			}
		}

		contador++;
	}
	fclose(fer);
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
	
	feriadosSep(ano, "fixos", 0);
}
bool ehBissexto(long int ano)
{
	return ((ano % 4 == 0 && ano % 100 != 0) || ( ano % 400 == 0));
}

void definirNomes(anos* ano)
{	
	leitura(ano);
}
void organizarBolha(anos* ano)
{
	unsigned short int count = 0;
	char temp[100];
	int mes_temp	= 0;
	int dia_temp	= 0;
	int qtd		= 0;
	for(int j = 0; ano->mes.dia.fer.feriados_tot[j][1] != 0; j++, qtd++);

	for(int i = 0; i < qtd - 1 ; i++ ) 
		{
			for(int j = 0; j < qtd - i - 1; j++)
			{
				if(ano->mes.dia.fer.feriados_tot[j][1] > ano->mes.dia.fer.feriados_tot[j+1][1]  )
				{
					// mes
					mes_temp = ano->mes.dia.fer.feriados_tot[j][0];
					ano->mes.dia.fer.feriados_tot[j][0] = ano->mes.dia.fer.feriados_tot[j+1][0]; 
					ano->mes.dia.fer.feriados_tot[j+1][0] = mes_temp;

					// dia
					dia_temp =  ano->mes.dia.fer.feriados_tot[j][1]; 
					ano->mes.dia.fer.feriados_tot[j][1] =  ano->mes.dia.fer.feriados_tot[j+1][1];
 					ano->mes.dia.fer.feriados_tot[j + 1][1] = dia_temp;
					// chars
 					strcpy(temp ,ano->mes.dia.fer.nome_tot[j]);
					strcpy(ano->mes.dia.fer.nome_tot[j], ano->mes.dia.fer.nome_tot[j+1]);
					strcpy(ano->mes.dia.fer.nome_tot[j+1], temp );
				}
			}
		}
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
		if(ano->bissexto){
			ano->mes.dia.qtd = 29;
			ano->mes.qtd_dias[mes] = ano->mes.dia.qtd;
		}else{
			ano->mes.dia.qtd = 28;
			ano->mes.qtd_dias[mes] = ano->mes.dia.qtd;
		}}else if(mes == 1 || mes == 3 
	    || mes == 5 || mes == 7 
	    || mes == 8 || mes == 10
	    || mes == 12){
		ano->mes.dia.qtd = 31;
		ano->mes.qtd_dias[mes] = ano->mes.dia.qtd;
	}else{
		ano->mes.dia.qtd = 30;
		ano->mes.qtd_dias[mes] = ano->mes.dia.qtd;
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
	
	fprintf(arq_dim, "%d\t\%d\tQuarta-feira de cinzas\n", mquarta, dia_quarta);

	fprintf(arq_dim, "%d\t\%d\tPaixão de Cristo\n", msanta, dia_santa);

	fprintf(arq_dim, "%d\t\%d\tDomingo de páscoa\n", mpasc, pascoa);
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
	definirRelacionados(p, n, ano);
}
void tabela27A(double eq[][1], short int ano)
{
	double y = (double)ano/1000;

	eq[0][0] =	1721139.29189
	       		+ 365242.13740 * y
			+ 0.06134 * pow(y, 2)
			+ 0.00111 * pow(y, 3)
			- 0.00071 * pow(y, 4);
	eq[1][0] =	1721325.70455
			+ 365242.49558 * y
			- 0.11677 * pow(y, 2)
			- 0.00297 * pow(y, 3)
			+ 0.00074 * pow(y, 4);
}

void tabela27B(double eq[][1], short int ano)
{
	
	double y = ((double)ano - 2000)/1000;

	eq[0][0] =	2451623.80984
	       		+ 365242.37404 * y
			+ 0.05169 * pow(y, 2)
			+ 0.00411 * pow(y, 3)
			- 0.00057 * pow(y, 4);
	eq[1][0] =	2451810.21715
			+ 365242.01767 * y
			- 0.11575 * pow(y, 2)
			- 0.00337 * pow(y, 3)
			+ 0.00078 * pow(y, 4);

}
double somasEq(double t)
{
	double resultado = 0;
	for(int i = 0; i < 24; i++)
		resultado += a[i]*cos(b[i]+ c[i]*t*FATOR);
	return resultado;
}

double calcularEquinocios(double jde)
{
	double t, w, delta, s;
	t = (jde - 2451545.0)/ 36525;
	w = (35999.373*t - 2.47) * FATOR;
	delta = 1 + 0.0334 * cos(w) + 0.0007* cos(2*w);
	s = somasEq(t);
	return  jde + (0.00001*s)/delta;
}
void definirEquinocios(anos* ano)
{
	double equinocios[2][1] = {};
	double jde;
	FILE * arq_dinamicos = fopen("dinamicos", "a");
	if(!arq_dinamicos)
		exit(EXIT_FAILURE);

	if (ano->ano >= 1000)
		 tabela27B(equinocios, ano->ano);
	else	
		 tabela27A(equinocios, ano->ano);

	for(int i = 0; i< 2; i++){
		if(i == 0)
			calculoGreg(calcularEquinocios(equinocios[i][0]), ano->ano, arq_dinamicos, "Equinocio de marco");	
		else
			calculoGreg(calcularEquinocios(equinocios[i][0]), ano->ano, arq_dinamicos, "Equinocio de setembro");	
	}
	fclose(arq_dinamicos);
	


}
void organizarDinamicos(anos* ano)
{
	feriadosSep(ano, "dinamicos", 0);
	feriadosSep(ano, "luas", 1);	
/*	unsigned short int vetor_qtd[MES] = {0};
	unsigned int tam = sizeof(ano->mes.dia.fer.feriados_tot)/sizeof(ano->mes.dia.fer.feriados_tot[0]);
	for(int k = 1; k <= MES; k++){
	for(int i = 0 ; i < tam ; i++){
		if(ano->mes.dia.fer.feriados_tot[i][0] == k) {
			vetor_qtd[k] += 1;}
	}}
	for(int i = 0 ; i < MES ; i++)
		printf("%d\n", vetor_qtd[i]);
*/				
	organizarBolha(ano);
}
void definirFeriados(anos* ano)
{
	definirPascoa(ano);
	definirEquinocios(ano);
	calculoLuaCheia(ano);	
	organizarDinamicos(ano);

}
void imprimirFeriados(anos* ano)
{
	unsigned int tam = sizeof(ano->mes.dia.fer.feriados_tot)/sizeof(ano->mes.dia.fer.feriados_tot[0]);
	for(int i = 1; i <= MES; i++){
		printf("       	   %s\n", ano->mes.nome_mes[i]);
		puts("   D   S   T   Q   Q   S   S");
		for(int j = 1; j <= 6; j++){
			for(int k = 1; k <= 7; k++){
				if(!ano->mes.dias[i][j][k])
					printf("    ");
				else
					printf("%4d", ano->mes.dias[i][j][k]);

			}
			puts("");
		}
		puts("Feriados e/ou luas:");
		for (int l = 0; l < tam; l++ ){
			if(ano->mes.dia.fer.feriados_tot[l][0] == i)
				printf("%3d %s", ano->mes.dia.fer.feriados_tot[l][1], ano->mes.dia.fer.nome_tot[l]);
			}
			puts("");

			}

}

#endif
