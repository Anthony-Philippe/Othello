#include "directive.h"
#include "prototype.h"

partie_Data IA_Niveau1(int board[TAILLE][TAILLE], partie_Data game, Partie * p){
    check_Pos_Jouable(board, game);
    int compteur = 0;
    for(int Lig = 0; Lig < TAILLE; Lig++){
        for(int Col = 0; Col < TAILLE; Col++){
            if(board[Lig][Col] == case_Jouable) compteur++;
        }
    }
    if(compteur <= 0) {
        game.Joueur = P1;
        return game;
    }
    int coup_Aléatoire = rand()%compteur;
    coup_Aléatoire++;
    int coup_Temp = 0;
    int pos_Case[2] = {-1, -1};
    for(int Lig = 0; Lig < TAILLE; Lig++){
        for(int Col = 0; Col < TAILLE; Col++){
            if(board[Lig][Col] == case_Jouable){
                coup_Temp++;
                if(coup_Temp == coup_Aléatoire){
                    pos_Case[1] = Lig;
                    pos_Case[0] = Col;
                    break;
                }
            }
        }
        if(pos_Case[1] >= 0 && pos_Case[0] >= 0) break;
    }
    place_Selection(board, game, pos_Case);
    ajout_Coup_Partie(p, board, game);
    game.Joueur = P1;
    return game;
}