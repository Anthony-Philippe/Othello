#include "prototype.h"

int menu(){
	printf("\n════════════════════════════════════════════════════════════════════════════\n");
    printf("                              |      MENU      |\n");
	printf("════════════════════════════════════════════════════════════════════════════\n\n");
	printf("\t1 ▸ Lancer partie\n");
	printf("\t2 ▸ Crédits\n");
	printf("\tAutres ▸ Quitter le programme\n");
    printf("\n");
	Cursor

	int choix = 0;
	scanf("%d", &choix);
                         
	return choix;
}

void menu_Crédits(){
	printf("\n════════════════════════════════════════════════════════════════════════════\n");
    printf("                            |      Crédits      |\n");
	printf("════════════════════════════════════════════════════════════════════════════\n\n");
	printf("\tbablabla\n");
	printf("\tAutres ▸ Retour\n");
    printf("\n");
	Cursor

	int choix = 0;
	scanf("%d", &choix);
}

int menu_Start1(){
	printf("\n════════════════════════════════════════════════════════════════════════════\n");
    printf("                           |      Start Game      |\n");
	printf("════════════════════════════════════════════════════════════════════════════\n\n");
	printf("\t1▸ Nouvelle partie\n");
	printf("\t2▸ Charger partie\n");
	printf("\tAutres ▸ Retour\n");
    printf("\n");
	Cursor

	int choix = 0;
	scanf("%d", &choix);
	return choix;
}

int menu_Start2(){
	printf("\n════════════════════════════════════════════════════════════════════════════\n");
    printf("                           |      Start Game      |\n");
	printf("════════════════════════════════════════════════════════════════════════════\n\n");
	printf("\t1▸ Défier l'ordinateur\n");
	printf("\t2▸ 2 Joueurs\n");
	printf("\tAutres ▸ Retour\n");
    printf("\n");
	Cursor

	int choix = 0;
	scanf("%d", &choix);
	return choix;
}