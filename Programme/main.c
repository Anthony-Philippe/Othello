#include "prototype.h"

int main(void){
    while(1){
		char board[TAILLE][TAILLE];
		init_board(board);

        CleanWindows
		int choix = menu();
		switch(choix){
			default:
				//free_Partie(p);
				couleur("31");
				printf("\t Fermeture \n");
				couleur("0");
				return 0;
				break;
			case 1:
				choix = menu_Start1();
				if(choix == 1){
					choix = menu_Start2();
					Partie * p = malloc(sizeof(Partie));
					init_Partie(p, board);
					if(choix == 1) printf("partie IA");
					else if(choix == 2) game_JvJ(p, board);
				}
				else if(choix == 2){
					Partie * p2 = malloc(sizeof(Partie));
					p2 = import_Partie("partie.txt");
					charger_Partie(p2, board);
					game_JvJ(p2, board);
				}
				break;
            case 2:
                menu_Crédits();
				break;
		}
	}

    return 0;
}