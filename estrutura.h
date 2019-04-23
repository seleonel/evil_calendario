#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

typedef struct {
	bool ha_feriado;
	char nome_fer[11][30];
} feriados;

typedef struct {
	short int qtd;
	feriados fer;
} dias;

typedef struct {
	short int qtd;
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
