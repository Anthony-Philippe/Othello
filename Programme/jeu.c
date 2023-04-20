#include "directive.h"
#include "prototype.h"

partie_Data start_Game(partie_Data game, int board[TAILLE][TAILLE], Partie * p){
    game = initialiser_la_Partie(game, board, p);
    if (game.Mode == JvsIA && game.Joueur == P2) game = IA_Niveau1(board, game, p);
    return game;
}

partie_Data initialiser_la_Partie(partie_Data game, int board[TAILLE][TAILLE], Partie * p){
    game.Joueur = joueur_Aléatoire();
    init_board(board);
    init_Partie(p, board);
    ajout_Coup_Partie(p, board, game);
    if(game.Mode == JvsJ) p->type = JvsJ;
    else if(game.Mode == JvsIA) p->type = JvsIA;
    game.partie_Started = true;
    return game;
}

int joueur_Aléatoire(){
    srand(time(NULL));
    return (rand()%2 == 0) ? P1 : P2;
}

int afficher_la_Partie(SDL_Renderer * Rendu, enum Pages index_PAGE, SDL_Texture ** Textures, int board[TAILLE][TAILLE], SDL_Texture ** Pion, partie_Data game){
    if(game.Mode == JvsJ) index_PAGE = (game.Joueur == P1) ? GAME_J1 : GAME_J2;
    else if(game.Mode == JvsIA) index_PAGE = GAME_IA;
    disp_Background(Rendu, Textures, index_PAGE);
    check_Pos_Jouable(board, game);
    disp_Plateau(Rendu, Pion, board);
    return index_PAGE;
}

int quitter_la_Partie(SDL_Renderer * Rendu, SDL_Event event, enum Pages index_PAGE, SDL_Texture ** Textures){
    if(check_POS(event, index_PAGE) == 3){
        index_PAGE = HOME;
        disp_Background(Rendu, Textures, index_PAGE);
    }
    return index_PAGE;
}

partie_Data gameplay(SDL_Renderer * Rendu, enum Pages *index_PAGE, SDL_Texture ** Textures, int board[TAILLE][TAILLE], SDL_Texture ** Pion, partie_Data game , Partie * p){
    if(poser_pion(board, game)){
        play_Sound(SOUND_Click);
        ajout_Coup_Partie(p, board, game);
        if(game.Mode == JvsJ) game.Joueur = (game.Joueur == P1) ? P2 : P1;
        else if(game.Mode == JvsIA){
            game.Joueur = P2;
            game = IA_Niveau1(board, game, p);
        }
        *index_PAGE = afficher_la_Partie(Rendu, *index_PAGE, Textures, board, Pion, game);
    
    }
    *index_PAGE = fin_de_partie(Rendu, *index_PAGE, Textures, board, Pion, game);
    return game;
}

partie_Data annuler_dernier_Coup(Partie * p, int board[TAILLE][TAILLE], partie_Data game){
    if(game.Mode == JvsIA) annuler_Coup(p);
    else game.Joueur = (game.Joueur == P1) ? P2 : P1;
    annuler_Coup(p);
    charger_Partie(p, board);
    return game;
}

int fin_de_partie(SDL_Renderer * Rendu, enum Pages index_PAGE, SDL_Texture ** Textures, int board[TAILLE][TAILLE], SDL_Texture ** Pion, partie_Data game){
    if(is_full_board(board)){
        index_PAGE = afficher_la_Partie(Rendu, index_PAGE, Textures, board, Pion, game);
        return ENDGAME;
    }
    return index_PAGE;
}

void init_board(int board[TAILLE][TAILLE]){
    for (int Ligne = 0; Ligne < TAILLE; Ligne++) {
        for (int Col = 0; Col < TAILLE; Col++) {
            if ((Ligne == 3 && Col == 3) || (Ligne == 4 && Col == 4)) board[Ligne][Col] = P1;
            else if ((Ligne == 3 && Col == 4) || (Ligne == 4 && Col == 3)) board[Ligne][Col] = P2;
            else board[Ligne][Col] = VIDE;
        }
    }
}

void check_Pos_Jouable(int board[TAILLE][TAILLE], partie_Data game){
    char Joueur2 = (game.Joueur == P1) ? P2 : P1;
    for (int Lig = 0; Lig < TAILLE; Lig++) {
        for (int Col = 0; Col < TAILLE; Col++) {
            if (board[Lig][Col] == case_Jouable) board[Lig][Col] = VIDE;
            if (board[Lig][Col] == VIDE) {
                for (int DirH = -1; DirH <= 1; DirH++) {
                    for (int DirL = -1; DirL <= 1; DirL++) {
                        if ((DirH != 0 || DirL != 0)
                            && (Lig + DirH >= 0 && Lig + DirH < 8 && Col + DirL >= 0 && Col + DirL < 8)
                            && board[Lig + DirH][Col + DirL] == Joueur2) {
                                for (int PosX = Lig + DirH, PosY = Col + DirL; PosX >= 0 && PosX < 8 && PosY >= 0 && PosY < 8; PosX += DirH, PosY += DirL) {
                                    if (board[PosX][PosY] == VIDE) break;
                                    else if (board[PosX][PosY] == game.Joueur) {
                                        board[Lig][Col] = case_Jouable;
                                        break;
                                    }
                                }
                        }
                    }
                }
            }
        }
    }
}

bool poser_pion(int board[TAILLE][TAILLE], partie_Data game){
    int x, y;
    SDL_GetMouseState(&x, &y);
    int plateau_x = 402 - OFFSET, plateau_y = 71 - OFFSET;
    int pos_Case[2] = {(x - plateau_x) / (size_CASE + 15), (y - plateau_y) / (size_CASE + 15)};
    if (pos_Case[0] >= 0 && pos_Case[0] < 8 && pos_Case[1] >= 0 && pos_Case[1] < 8){
        if (board[pos_Case[1]][pos_Case[0]] == case_Jouable) {
			place_Selection(board, game, pos_Case);
            return true;
        }
    }
    return false;
}

void place_Selection(int board[TAILLE][TAILLE], partie_Data game, int pos_Case[2]){
    board[pos_Case[1]][pos_Case[0]] = game.Joueur;
    int Joueur2 = (game.Joueur == P1) ? P2 : P1;
    int Direction[2];
    for (Direction[0] = -1; Direction[0] <= 1; Direction[0]++) {
        for (Direction[1] = -1; Direction[1] <= 1; Direction[1]++) {
            if (Direction[1] == 0 && Direction[0] == 0) continue;
            if (check_Direction(board, game, pos_Case, Direction)){
                int i = pos_Case[1] + Direction[1];
                int j = pos_Case[0] + Direction[0];
                while (i < TAILLE && j < TAILLE && board[i][j] == Joueur2) {
                    board[i][j] = game.Joueur;
                    i += Direction[1];
                    j += Direction[0];
                }
            }
        }
    }
}

bool check_Direction(int board[TAILLE][TAILLE], partie_Data game, int pos_Case[2], int Direction[2]){
    int i = pos_Case[1] + Direction[1];
    int j = pos_Case[0] + Direction[0];
    while (i >= 0 && i < TAILLE && j >= 0 && j < TAILLE){
        if (board[i][j] == game.Joueur) return true;
        if (board[i][j] == VIDE) return false;
        i += Direction[1];
        j += Direction[0];
    }
    return false;
}

bool is_full_board(int board[TAILLE][TAILLE]){
    int nb_Pions = 0, coup_Possible = 0;
    for (int i = 0; i < TAILLE; i++){
        for (int j = 0; j < TAILLE; j++){ 
            if (board[i][j] != VIDE && board[i][j] != case_Jouable) nb_Pions++;
            if (board[i][j] == case_Jouable) coup_Possible++;
        }
    }
    if(nb_Pions == TAILLE * TAILLE) return true;
    else if (coup_Possible == 0) return true;
    return false;
}

void ResultatsPartie(SDL_Renderer* Rendu, TTF_Font* police, int board[TAILLE][TAILLE]){
    int Résultats[3] = {0};
    Result(board, Résultats);
    afficherResultats(Rendu, police, Résultats);
}

void Result(int board[TAILLE][TAILLE], int Résultats[3]){
    for(int i = 0; i < TAILLE; i++){
        for(int j = 0; j < TAILLE; j++){
            if(board[i][j] == P1) Résultats[0]++;
            else if(board[i][j] == P2) Résultats[1]++;
        }
    }
    if(Résultats[0] > Résultats[1]) Résultats[2] = P1;
    else Résultats[2] = P2;
}