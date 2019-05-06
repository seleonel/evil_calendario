#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

typedef struct {
	unsigned int dia_ferfix[12][2];
	char nome_ferfix[12][100];
	unsigned int dia_ferdim[12][8];
	char nome_ferdim[12][100];
	unsigned int luas[24][2];
} feriados;

typedef struct {
	feriados fer;
	unsigned short int qtd;
} dias;

typedef struct {
	short int qtd;
	short int dias[14][6][7];
	short int qtd_dias[14];
	short int ultimo_dia[14];
	char nome_semana[8][30];
	char nome_mes[13][30];
	dias dia;
} meses;

typedef struct{ 
	long int ano;
	bool bissexto;
	meses mes;
} anos;

#endif
