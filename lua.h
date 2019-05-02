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

double correcaoLC(double lcheia[], double senos[])
{	
	double soma = 0;
	for(int i = 0; i < LINHAS ; i++)
		soma += lcheia[i]*senos[i];
	return soma;
}
double correcaoLN(double lnova[], double senos[])
{	
	double soma = 0;
	for(int i = 0; i < LINHAS ; i++)
		soma += lnova[i]*senos[i];
	return soma;
}
double correcQt(double lua_qt[], double senos[], int j, double m, double ml, double e, double f )
{
    double soma = 0;
    double w = 0.00306 - 0.00038 * e * cos(m) + 0.00026 * cos(ml) - 0.00002 * cos(ml - m) + 0.00002* cos(ml + m) + 0.00002 * cos(2*f);
	for(int i = 0; i < LINHAS ; i++)
		soma += lua_qt[i]*senos[i];
    
    if(j == 0.25)
        soma += w;
    else
        soma -= w;
	return soma;
    
    
}



double correcaoGer(double arg[])
{
	const double vetor_correc[] = {0.000325, 0.000165, 0.000164, 0.000126, 0.000110, 0.000062, 0.000060, 0.000056, 0.000047, 0.000042, 0.000040, 0.000037, 0.000035, 0.000023};

	double corr = 0;
	for(int i = 0 ;i < 14 ; i++)
		corr += vetor_correc[i]*sin((arg[i]*FATOR));
	return corr;

}

void calculoLunar(anos* ano, int mes, int soma_dias, double luas[])
{   
    double e, m, ml,j, f, ohm, jde,
           cor_luan, cor_luac, 
           cor_1quarto, cor_uquarto, 
           k, t, constante_bis,
	   k_anterior,
           correc_plan, correc_lua;
    int i;
    if(ano->bissexto)
        constante_bis = 365;
    else
        constante_bis = 366;
    
    for( i = 1,  j = 0.25 ; i <= 4; i++, j += 0.25){
        double casa_dec, year;
	casa_dec =  (soma_dias + j*(ano->mes.qtd_dias[mes]))/constante_bis;
	year = ano->ano + casa_dec;
        k  = (year - 2000) * 12.3685;
	float fases_lun = j - 0.25;
	k = floor(k) + fases_lun;
       	t = k / 1236.85;
	if(mes == 12)
	{
		printf("%lf\n%lf\n%lf\n%d\n",k, year, casa_dec, soma_dias);
	}	
        //calcular jde
        jde = 2451550.09766 + 29.530588861 * k + 0.00015437 * pow(t, 2) - 0.000000150 * pow(t, 3) + 0.00000000073 * pow(t, 4);
        // calcular E
        e = 1 - 0.002516 * t  - 0.0000074 * pow(t, 2);
        double lista_ln[] = {-0.40720, 0.17241*e, 0.01608, 0.01039, 0.00739*e, -0.00514*e, 0.00208*pow(e, 2), -0.00111, -0.00057, 0.00056 * e, -0.00042, 0.00042 *e, 0.00038*e, -0.00024*e, -0.00017, -0.00007, 0.00004, 0.00004, 0.00003, 0.00003, -0.00003, 0.00003, -0.00002, -0.00002, 0.00002 };

        double lista_lc[] = {-0.40614, 0.17302*e, 0.01614, 0.01043, 0.00734*e, -0.00515*e, 0.00209*pow(e, 2), -0.00111, -0.00057, 0.00056 * e, -0.00042, 0.00042 *e, 0.00038*e, -0.00024*e, -0.00017, -0.00007, 0.00004, 0.00004, 0.00003, 0.00003, -0.00003,0.00003, -0.00002, -0.00002, 0.00002 };
        double arg_plan[] = {(299.77 + 0.107408*k - 0.009173 * pow(t, 2)), (251.88 + 0.016321* k), (251.83 + 26.651886*k), (349.42 + 36.412478 * k), (84.66 + 18.206239*k), (141.74 + 53.303711 *k), (207.14 + 2.453732*k), (153.84 + 7.306860*k), (34.52 + 27.261239*k), (207.19 + 0.121824 * k), (291.34 + 1.844379*k), (161.72 + 24.198154 *k), (239.56 + 25.513099 *k),  (331.55+ 3.592518*k)};	

        double lista_qt[] = {-0.62801, 0.17172*e, -0.01183*e, 0.00862, 0.00804, 0.00454 *e, 0.00204*pow(e, 2), -0.00180, -0.00070, -0.00040, -0.00034*e, 0.00032*e, 0.00032*e, -0.00028*pow(e, 2), 0.00027*e, -0.00017, -0.00005, 0.00004, -0.00004, 0.00004, 0.00003, 0.00003, 0.00002, 0.00002, -0.00002};
        // calcular m
        m = (2.5534 + 29.10535670 * k - 0.0000014 * pow(t, 2) - 0.00000011 * pow(t, 3)) * FATOR;

        // calcular m'
        ml =  (201.5643 + 385.81693528 * k + 0.0107582 * pow(t, 2) + 0.00001238 * pow(t, 3) - 0.000000058 * pow(t, 4) ) * FATOR;	
        // calcular F
        f = (160.7108 + 390.67050284 * k - 0.0016118 * pow(t, 2) + 0.00000227 * pow(t, 3) + 0.000000011 * pow(t, 4)) * FATOR;	

        // calcular ohm
        ohm  = (124.7746 - 1.56375588 * k + 0.0020672 * pow(t, 2)+ 0.00000215 * pow(t, 3)) * FATOR;

        double senos_c[] = {sin(ml), sin(m), sin(2*ml), sin(2 *f), sin(ml - m), sin(ml + m), sin(2*m), sin(ml - 2*f), sin(ml + 2*f), sin(2*ml + m), sin(3*ml), sin(m + 2*f), sin(m - 2*f), sin(2*ml - m), sin(ohm), sin(ml + 2*m), sin(2*ml - 2*f), sin(3*m), sin(ml + m - 2*f), sin(2*ml + 2*f), sin(ml + m + 2*f), sin(ml - m + 2*f), sin(2*ml - m - 2*f), sin(3*ml + m), sin(4*ml)};
        double senos_qt[] = {sin(ml), sin(m), sin(ml + m), sin(2*ml), sin(2*f), sin(ml - m), sin(2*m), sin(ml - 2*f), sin(ml + 2*f), sin(3*ml), sin(2*ml - m), sin(m + 2*f),sin(m - 2*f), sin(ml + 2*m), sin(2*ml + m), sin(ohm), sin(ml - m - 2*f), sin(2*ml + 2*f), sin(ml + m + 2*f), sin(ml - 2*m), sin(ml + m - 2*f), sin(3*m), sin(2*ml - 2*f), sin(ml - m + 2*f), sin(3*ml + m)};

        if(fases_lun == 0)
           correc_lua = correcaoLN(lista_ln, senos_c);
          
        else if(fases_lun ==  0.25)
                correc_lua = correcQt(lista_qt,senos_qt, fases_lun, m, ml, e, f);
             
        else if(fases_lun == 0.50)
                correc_lua = correcaoLC(lista_lc, senos_c);
               
        else if(fases_lun == 0.75)
                correc_lua = correcQt(lista_qt,senos_qt, fases_lun, m, ml, e, f);
             
        
        double coisa= jde + correc_lua + correcaoGer(arg_plan);
	printf("Lua: %lf fase: %f\n", coisa, fases_lun);
    }
    
}
#endif
