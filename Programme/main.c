#include "prototype.h"

int main(void){
    char board[TAILLE][TAILLE];
    init_board(board);
    
    while(1){
        CleanWindows
		int choix = menu();
		switch(choix){
			case 1:
                //int choix_StartGame = menu_Start1();
                bool end_Game = false;
                char Pstart = joueur_Aléatoire();
                while (!end_Game) {
                    CleanWindows
                    disp_board(board);
                    pos_Selection(board, Pstart);
                    if(check_Gagnant(board)) end_Game = true;
                    Pstart = (Pstart == P1) ? P2 : P1;
                }
                CleanWindows
                disp_resultat(board);
                int waitTemp = scanf("%d", &waitTemp);
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