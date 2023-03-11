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

int menu_Crédits(){
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