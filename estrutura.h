#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

typedef struct {
	bool ha_feriado;
	unsigned int dia_ferfix[3];
	unsigned int mes_ferfix[3];
	char nome_ferfix[3][100];
} feriados;

typedef struct {
	feriados fer;
	unsigned int fev_bis;
	unsigned int fev_nobis;
	unsigned int dias_30;
	unsigned int dias_31;
} dias;

typedef struct {
	short int qtd;
	short int dias[14][6][7];
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
