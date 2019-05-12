#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <iup/iup.h>
#include "lua.h"
#include "funcoes.h"
#include "estrutura.h"
#define ANO_DEFAULT 2019
#define MES_DEFAULT 1
Ihandle * sem[9],* lbl_fer[5];
static unsigned short int cont = MES_DEFAULT;
char fork_prog[60];
char placeholder[40];
int main(int argc, char** argv);
void continhas(int yr)
{
	zerarMatrizes(&ano);
	// leitura do ano por fgets ou scanf
	//anoUser(&ano);
	ano.ano = yr;
	// primeira checagem se bissexto ou não
	ano.bissexto = ehBissexto(ano.ano);
	definirNomes(&ano);
	definirDatas(&ano);
	definirFeriados(&ano);

}
int trocar_mesant( Ihandle *self)
{
	char comando[10];
	--cont;
	if (cont > MES)
		cont = 1;
	else if( cont <= 0)
		cont = MES;
	sprintf(comando, " %d %d", ano.ano, cont);
        strcat(fork_prog, comando);
	IupClose();
   	system(fork_prog);
	return IUP_CLOSE;	

}
int trocar_ano(Ihandle *self )
{
	char comando[10];
	if(!IupGetParam("Novo ano", 0, 0,
			"Bt %u[, MyCancel]\n"
			"Insira um ano: %i\n",
			&(ano.ano)));
	sprintf(comando, " %d", ano.ano);
	strcat(fork_prog, comando);
	IupClose();
	system(fork_prog);
	return IUP_CLOSE;	
}
int trocar_mesprox( Ihandle *self)
{

	char comando[10];
	++cont;
	if (cont > MES)
		cont = 1;
	else if( cont <= 0)
		cont = MES;
	sprintf(comando, " %d %d", ano.ano, cont);
        strcat(fork_prog, comando);
	IupClose();
   	system(fork_prog);
	return IUP_CLOSE;
}
void printarMes()
{

}
// passagem de parametros pro main por argc e argv

int main(int argc, char** argv)
{
	Ihandle *mes, *espacador,*feriado_lbl, *dialogo, *espaco, *tela, *bot_prevmes, *bot_nextmes, *mes_atual, *superior, *bot_ano, *inferior_esq, *semanas, *wrapper, *sem_lab, *vazio, *lista_fer, *wrapper_top, *label_ano;

	IupOpen(&argc, &argv);
	switch(argc)
	{
		case 1: 
			ano.ano = ANO_DEFAULT;
			IupMessage("AVISO:\n", "Feriados dinâmicos para anos anteriores a 1583 podem apresentar problemas quanto a sua precisão");    

			cont = MES_DEFAULT;
			break;
		case 2:
			ano.ano = strtol(argv[1], NULL, 10);
			cont = MES_DEFAULT;
			break;
		case 3:
			ano.ano = strtol(argv[1], NULL, 10);
			cont = strtol(argv[2], NULL, 10);	
			break;
		default:
			IupClose();
			return EXIT_FAILURE;
	}
	strcpy(fork_prog, argv[0]);
  	IupSetGlobal("UTF8MODE", "Yes");
	sprintf(placeholder, "%d", ano.ano);
	label_ano	= IupHbox(
				IupLabel("\t"),
				IupLabel(placeholder),
				NULL);
	IupSetAttributes(label_ano, "ALIGNMENT=ACENTER, FGCOLOR=\"#ff00e5\", FONTSIZE=20, MARGIN=20x20");



	continhas(ano.ano);	
	feriado_lbl 	= IupLabel("Feriados e luas");
	mes_atual	= IupLabel(ano.mes.nome_mes[cont]);
	bot_prevmes	= IupButton("Anterior", NULL);
	bot_nextmes	= IupButton("Prox", NULL);
	bot_ano		= IupButton("Ano", NULL);	
	// menu superior 
	superior = 
		IupHbox(	
			    mes_atual,
			    bot_prevmes,
			    bot_ano,
			    bot_nextmes,
			    NULL) ;
	//setar espaços
	IupSetAttribute(superior, "ALIGNMENT", "ACENTER");
	IupSetAttribute(superior, "GAP", "150");
	IupSetAttribute(superior, "MARGIN", "10x10");
	
	
	//semanas
	vazio = IupLabel("\t\t\t\t\t");
	sem_lab = IupLabel("\t\tD\t\tS\t\tT\t\tQ\t\tQ\t\tS\t\tS");
	IupSetAttributes(sem_lab, "ALIGNMENT=ARIGHT, FONTSIZE=12");
	semanas = IupHbox(
			vazio,
			NULL);
	IupSetAttribute(vazio, "ALIGNMENT", "ALEFT"); 
	IupSetAttributes(semanas, "MARGIN=10x10, FONTSIZE= \"11\", FGCOLOR=\"#f442ad\"");
	IupSetAttribute(semanas, "GAP", "100");
	
	
	converterFeriados(&ano, cont, sem, lbl_fer);
	
	lista_fer = IupVbox(
			feriado_lbl,
			lbl_fer[0],
			lbl_fer[1],
			lbl_fer[2],
			lbl_fer[3],
			lbl_fer[4],
			lbl_fer[5],
			NULL	);

	IupSetAttributes(sem_lab, "ALIGNMENT=ACENTER, FGCOLOR=\"#ff0059\"");
	IupSetAttributes(lista_fer, "ALIGNMENT=ALEFT, FGCOLOR=\"#ff0059\", FONTSIZE=14" );
	IupSetAttribute(feriado_lbl, "FGCOLOR", "#f442ad");
	mes = IupVbox( 
			sem_lab,
			sem[1],
		       sem[2],
	       		sem[3],
	 		sem[4],
			sem[5],
			sem[6],
			NULL);		
	espacador = IupLabel("\t\t\t\t\t\t");
	IupSetAttributes(mes, "FONTSIZE=\"15\", FGCOLOR=\"#ffffff\"ALIGNMENT=ACENTER");
	espaco = IupVbox( espacador,
			NULL);
	wrapper_top = IupHbox(lista_fer, espaco,mes, NULL);	
	
	IupSetAttributes(wrapper_top, "GAP=40, ALIGNMENT=ARIGHT, MARGIN=10x10");
	IupSetAttributes(superior, "FONTSIZE=14, MARGIN=10x10, TITLE=\"Calendário\", BGCOLOR=\"#000000\", FGCOLOR=\"#f442ad\", ALIGNMENT=ARIGHT");
	wrapper = IupVbox(
			label_ano,
			superior,
			semanas,
			wrapper_top, 
			NULL);
	dialogo = IupDialog(wrapper);
	IupSetAttribute(dialogo, "BGCOLOR", "#000000");
	// callbacks dos botoes
	IupSetCallback(bot_prevmes, "ACTION", (Icallback) trocar_mesant);	
	IupSetCallback(bot_ano, "ACTION", (Icallback) trocar_ano);	
	IupSetCallback(bot_nextmes, "ACTION", (Icallback) trocar_mesprox);	
	IupShowXY(dialogo, IUP_CENTER, IUP_CENTER);

	IupMainLoop();
	IupClose();
	return EXIT_SUCCESS;
}
