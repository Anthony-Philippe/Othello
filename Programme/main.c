#include "prototype.h"

int main(void){
    while(1){
        CleanWindows
		int choix = menu();
		switch(choix){
			case 1:
				CleanWindows
				choix = menu_Start1();

				if(choix == 1){
					CleanWindows
					choix = menu_Start2();

					char board[TAILLE][TAILLE];
					init_board(board);
					if(choix == 1){
                        Partie * p = malloc(sizeof(Partie));
                        init_Partie(p, board);
                        printf("partie IA");
                    }
                    else if(choix == 2){
                        Partie * p = malloc(sizeof(Partie));
                        init_Partie(p, board);
                        game_JvJ(p, board);
                    }
				}

				else if(choix == 2){
					Partie * p = import_Partie("partie.txt");
					if(p == NULL) break;

					char board[TAILLE][TAILLE];
					init_board(board);
					charger_Partie(p, board);
					game_JvJ(p, board);
					free_Partie(p);
				}
				break;

            case 2:
                menu_Crédits();
				break;

			default:
				couleur("31");
				printf("\t Fermeture \n");
				couleur("0");
				return 0;
		}
	}

    return 0;
}