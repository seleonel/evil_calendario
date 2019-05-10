#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

typedef struct {
	// total de feriados serao guardados aqui
	unsigned short int feriados_tot[50][2];
	char nome_tot[50][200];
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
