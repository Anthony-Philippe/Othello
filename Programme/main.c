#include "prototype.h"

int main(void){
    char board[TAILLE][TAILLE];
    init_board(board);

	//LISTE_coup * listeC = init_listeC(listeC);
	Partie * p = init_Partie(p, board);
    
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
					char Dernier_Joueur;
					//import_Partie(board, &Dernier_Joueur, "partie.txt");
					game_JvJ(p, board);
				}
				//save_Liste(C_board, "liste_Coup.txt");
				break;
            case 2:
                menu_Crédits();
				break;
		}
	}

    return 0;
}