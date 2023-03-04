#include "prototype.h"

int main(void){
    char board[TAILLE][TAILLE];
    init_board(board);
    
    bool end_Game = false;
    char Pstart = P1;
    
    CleanWindows
    while (!end_Game) {
        disp_board(board);
        pos_Selection(board, Pstart);
        if(check_Gagnant(board)) end_Game = true;
        Pstart = (Pstart == P1) ? P2 : P1;
    }
    disp_resultat(board);

    return 0;
}