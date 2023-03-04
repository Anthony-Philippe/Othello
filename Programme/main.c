#include "prototype.h"

int main(void){
    char board[TAILLE][TAILLE];
    init_board(board);
    
    bool end_Game = false;
    char Pstart = joueur_Aléatoire();
    
    while(1){
        CleanWindows
		int choix = menu();
		switch(choix){
			case 1:
                while (!end_Game) {
                    CleanWindows
                    disp_board(board);
                    pos_Selection(board, Pstart);
                    if(check_Gagnant(board)) end_Game = true;
                    Pstart = (Pstart == P1) ? P2 : P1;
                }
                disp_resultat(board);
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