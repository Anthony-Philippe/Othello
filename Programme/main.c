#include "prototype.h"

int main(void){
    char board[TAILLE][TAILLE];
    init_board(board);
    
    while(1){
        CleanWindows
		int choix = menu();
		switch(choix){
			case 1:
                game_JvJ(board);
				break;
            case 2:
                menu_Crédits();
				break;
			default:
				couleur("31");
				printf("\t Fermeture \n");
				couleur("0");
				return 0;
				break;
		}
	}

    return 0;
}