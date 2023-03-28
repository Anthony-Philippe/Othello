#include "prototype.h"

int main(void){
    char board[TAILLE][TAILLE];
    init_board(board);
	Partie * p;
	init_Partie(p, board);
    
    while(1){
        CleanWindows
		int choix = menu();
		switch(choix){
			default:
				couleur("31");
				printf("\t Fermeture \n");
				couleur("0");
				return 0;
				break;
			case 1:
				choix = menu_Start1();
				if(choix == 1){
					choix = menu_Start2();
					if(choix == 1) printf("partie IA");
					else if(choix == 2) game_JvJ(p, board);
				}
				else if(choix == 2){
					p = import_Partie("partie.txt");
					charger_Partie(p, board);
					game_JvJ(p, board);
				}
				break;
            case 2:
                menu_Crédits();
				break;
		}
	}

    return 0;
}