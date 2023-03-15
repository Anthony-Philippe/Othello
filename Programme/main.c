#include "prototype.h"

int main(void){
    char board[TAILLE][TAILLE];
    init_board(board);
    
    while(1){
        CleanWindows
		int choix = menu();
		switch(choix){
			case 1:
				choix = menu_Start1();
				if(choix == 1){
					choix = menu_Start2();
					if(choix == 1) printf("partie IA");
					else if(choix == 2) game_JvJ(board);
				}
				else if(choix == 2) printf("charger partie");
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