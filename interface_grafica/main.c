#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <iup/iup.h>
#include "lua.h"
#include "funcoes.h"
#include "estrutura.h"
#define ANO_DEFAULT 2019
#define MES_DEFAULT 1
Ihandle * sem[7][9],* lbl_fer[5];
static unsigned short int cont = MES_DEFAULT;
void continhas()
{
	zerarMatrizes(&ano);
	// leitura do ano por fgets ou scanf
	//anoUser(&ano);
	ano.ano = ANO_DEFAULT;
	// primeira checagem se bissexto ou não
	ano.bissexto = ehBissexto(ano.ano);
	definirNomes(&ano);
	definirDatas(&ano);
	definirFeriados(&ano);

}
int trocar_mesant( Ihandle *self)
{
	--cont;
	if (cont > MES)
		cont = 1;
	else if( cont <= 0)
		cont = MES;
	converterFeriados(&ano, cont, sem, lbl_fer);
	return IUP_DEFAULT;	

}
int trocar_ano(Ihandle *self )
{
	if(!IupGetParam("Novo ano", 0, 0,
			"Bt %u[, MyCancel]\n"
			"Insira um ano: %i\n",
			&(ano.ano)));
	continhas();
	converterFeriados(&ano, cont, sem, lbl_fer);
	return IUP_DEFAULT;	
}
int trocar_mesprox( Ihandle *self)
{

	++cont;
	if (cont > MES)
		cont = 1;
	else if( cont <= 0)
		cont = MES;
	converterFeriados(&ano, cont, sem, lbl_fer);
	return IUP_DEFAULT;
}
void printarMes()
{

}
// passagem de parametros pro main por argc e argv

int main(int argc, char** argv)
{
	Ihandle *mes, *feriado_lbl, *dialogo, *tela, *bot_prevmes, *bot_nextmes, *mes_atual, *superior, *bot_ano, *inferior_esq, *semanas, *wrapper, *sem_lab, *vazio;

    
	IupOpen(&argc, &argv);
  	IupSetGlobal("UTF8MODE", "Yes");
	IupMessage("AVISO:\n", "Feriados dinâmicos para anos anteriores a 1583 podem apresentar problemas quanto a sua precisão");    

	continhas();	
	feriado_lbl 	= IupLabel("Feriado");
	mes_atual	= IupLabel("Mês");
	bot_prevmes	= IupButton("Anterior", NULL);
	bot_nextmes	= IupButton("Prox", NULL);
	bot_ano		= IupButton("Ano", NULL);	
	// menu superior 
	superior = IupHbox(feriado_lbl,
			    mes_atual,
			    bot_prevmes,
			    bot_ano,
			    bot_nextmes,
			    NULL);
	//setar espaços
	IupSetAttribute(superior, "ALIGNMENT", "ACENTER");
	IupSetAttribute(superior, "GAP", "100");
	IupSetAttribute(superior, "MARGIN", "10x10");
	
	
	//semanas
	vazio = IupLabel("   				");
	sem_lab = IupLabel("D\t\tS\t\tT\t\tQ\t\tQ\t\tS\t\tS");
	semanas = IupHbox(vazio,
			sem_lab,
			NULL);
	IupSetAttribute(vazio, "ALIGNMENT", "ALEFT"); 
	IupSetAttribute(sem_lab, "ALIGNMENT", "ARIGHT");
	IupSetAttributes(semanas, "MARGIN=10x10, FONTSIZE= \"11\", FGCOLOR=\"#f442ad\"");
	IupSetAttribute(semanas, "GAP", "100");
	converterFeriados(&ano, cont, sem, lbl_fer);
	mes = IupHbox( sem[4][6], sem[3][6], NULL);
			
			
		
	IupSetAttributes(mes, "FONTSIZE=\"24\" ,ALIGNMENT=\"ARIGHT\", FGCOLOR=\"#ffffff\"");
   	
	
	IupSetAttributes(superior, "FONTSIZE=11, MARGIN=10x10, TITLE=\"Calendário\", BGCOLOR=\"#000000\", FGCOLOR=\"#f442ad\"");
	wrapper = IupVbox(
			superior,
			semanas,
			mes, 
			NULL);
	dialogo = IupDialog(wrapper);
	// callbacks dos botoes
	IupSetCallback(bot_prevmes, "ACTION", (Icallback) trocar_mesant);	
	IupSetCallback(bot_ano, "ACTION", (Icallback) trocar_ano);	
	IupSetCallback(bot_nextmes, "ACTION", (Icallback) trocar_mesprox);	
	IupShowXY(dialogo, IUP_CENTER, IUP_CENTER);

	IupMainLoop();
	IupClose();
	return EXIT_SUCCESS;
}
