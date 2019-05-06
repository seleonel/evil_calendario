#ifndef LUA_H 
#define LUA_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "funcoes.h"
#include "estrutura.h"
#define QTD_MESES 12
#define DIAS_BIS 366
#define DIAS_ANO 365
#define FATOR 0.01745
#define LINHAS 25
#define TAM_ARRAY 100
void convGreg(double *, long int, FILE *);
double correcaoLC(double lcheia[], double senos[])
{	
	double soma = 0;
	for(int i = 0; i < LINHAS ; i++)
		soma += lcheia[i] * sin(senos[i]);
	return soma;
}

double correcaoGer(double arg[])
{
	const double vetor_correc[] = {
		0.000325, 
		0.000165, 
		0.000164, 
		0.000126, 
		0.000110, 
		0.000062, 
		0.000060, 
		0.000056, 
		0.000047, 
		0.000042, 
		0.000040, 
		0.000037, 
		0.000035, 
		0.000023
	};

	double corr = 0;
	for(int i = 0 ;i < 14 ; i++)
		corr += vetor_correc[i]*sin((arg[i]*FATOR));
	return corr;

}

void calculoLunar(anos* ano, double luas[])
{   
    double temp = 0;
    static int contador = 0;
    const float fase_lc 	= 0.5f;
    double e, m, ml,j, f, ohm, jde,
	   cor_luac,  k,
	   t, constante_bis,
           correc_plan, correc_lua;
    if(ano->bissexto)
        constante_bis	 = DIAS_BIS;
    else
        constante_bis	 = DIAS_ANO;
    temp = 0;
    int i, l, soma_dias = 0;
    for(l = 1; l <= MES; l++){
	    soma_dias += ano->mes.qtd_dias[l-1];
        for( i = 1 , j = 0.25; i <= 4; i++, j += 0.25){
            double casa_dec, year;
            casa_dec =  (soma_dias + j*(ano->mes.qtd_dias[l]))/constante_bis;
            year = ano->ano + casa_dec;
            k  = (year - 2000) * 12.3685;
            k = floor(k) + fase_lc;
            t = k / 1236.85;
            //calcular jde
            jde = 2451550.09766 + 29.530588861 * k + 0.00015437 * pow(t, 2) - 0.000000150 * pow(t, 3) + 0.00000000073 * pow(t, 4);
            // calcular E
            e = 1 - 0.002516 * t  - 0.0000074 * pow(t, 2);

            double lista_lc[] = {
            -0.40614, 
            0.17302*e,
            0.01614, 
            0.01043,
            0.00734*e,
            -0.00515*e,
            0.00209*pow(e, 2),
            -0.00111,
            -0.00057,
            0.00056 * e,
            -0.00042, 
            0.00042 *e, 
            0.00038*e, 
            -0.00024*e, 
            -0.00017, 
            -0.00007, 
            0.00004, 
            0.00004, 
            0.00003, 
            0.00003, 
            -0.00003,
            0.00003, 
            -0.00002, 
            -0.00002, 
            0.00002 
            };
            double arg_plan[] = {
            (299.77 + 0.107408*k - 0.009173 * pow(t, 2)),
                (251.88 + 0.016321* k), 
            (251.83 + 26.651886*k), 
            (349.42 + 36.412478 * k),
                (84.66 + 18.206239*k),
                (141.74 + 53.303711 *k), 
            (207.14 + 2.453732*k), 
            (153.84 + 7.306860*k), 
            (34.52 + 27.261239*k), 
            (207.19 + 0.121824 * k), 
            (291.34 + 1.844379*k), 
            (161.72 + 24.198154 *k), 
            (239.56 + 25.513099 *k),  
            (331.55+ 3.592518*k)
            };	

            // calcular m
            m = (2.5534 + 29.10535670 * k - 0.0000014 * pow(t, 2) - 0.00000011 * pow(t, 3)) * FATOR;

            // calcular m'
            ml =  (201.5643 + 385.81693528 * k + 0.0107582 * pow(t, 2) + 0.00001238 * pow(t, 3) - 0.000000058 * pow(t, 4) ) * FATOR;	
            // calcular F
            f = (160.7108 + 390.67050284 * k - 0.0016118 * pow(t, 2) + 0.00000227 * pow(t, 3) + 0.000000011 * pow(t, 4)) * FATOR;	

            // calcular ohm
            ohm  = (124.7746 - 1.56375588 * k + 0.0020672 * pow(t, 2)+ 0.00000215 * pow(t, 3)) * FATOR;

            double senos_c[] = {
            (ml),
                (m), 
            (2*ml), 
            (2 *f),
            (ml - m),
            (ml + m),
            (2*m), 
            (ml - 2*f),
            (ml + 2*f), 
            (2*ml + m), 
            (3*ml), 
            (m + 2*f), 
            (m - 2*f), 
            (2*ml - m),
            (ohm), 
            (ml + 2*m), 
            (2*ml - 2*f), 
            (3*m), 
            (ml + m - 2*f), 
            (2*ml + 2*f), 
            (ml + m + 2*f),
            (ml - m + 2*f),
            (2*ml - m - 2*f),
                (3*ml + m),
            (4*ml)
            };
            
                
            double jde_dias = jde + correcaoLC(lista_lc, senos_c) + correcaoGer(arg_plan);
            if (jde_dias != temp)
            {
                luas[contador] = jde_dias;	
                temp = jde_dias;
                contador++;	
            }
        }
    }
}
void calculoGreg( double jd_lua, long int year, FILE * arq, char comentario[])
{
	jd_lua += 0.5f;
	double z = abs(jd_lua);
	double f = modf(jd_lua, &z);
	double a, alpha, b, c, d ,e;
	int dia, mes, ano;
	if(z < 2299161)
	{
		 a = z;
	}else
	{
		alpha = abs((z - 1867216.25)/36524.25);
		a = z + 1 + alpha - abs(alpha/4);	
	}
	b = a + 1524;
	c = abs((b - 122.1)/365.25);
	d = abs(365.25*c);
	e = abs((b - d)/ 30.6001);
	
	dia = b - d - abs(30.6001*e) + f;
	if(e < 14)
		mes = e - 1;
	else if(e == 14 || e == 15)
		mes = e - 13;
	if( mes > 2 )
		ano = c - 4716;
	else if( mes == 1 || mes == 2)
		ano = c - 4715;
	if(ano == year)
		fprintf(arq, "%d\t%d\t%s\n", dia, mes, comentario);
}

void convGreg(double luas[], long int year, FILE* arq)
{
	for(int i = 0; i < TAM_ARRAY ; i ++)
	{
		if(luas[i] > 0 )
			calculoGreg( luas[i], year, arq, "");
	}
}
void calculoLuaCheia(anos* ano)
{
	FILE* arq_lua = fopen("luas", "w");
	double luas_mes[TAM_ARRAY] = {-1};
	ano->mes.qtd_dias[0] = 0;
	calculoLunar(ano, luas_mes);
	convGreg(luas_mes, ano->ano, arq_lua);
	fclose(arq_lua);
}
#endif
