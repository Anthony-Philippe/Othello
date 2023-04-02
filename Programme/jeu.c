#include "prototype.h"

void init_board(char board[TAILLE][TAILLE]){
    for (int Ligne = 0; Ligne < TAILLE; Ligne++) {
        for (int Col = 0; Col < TAILLE; Col++) {
            if ((Ligne == 3 && Col == 3) || (Ligne == 4 && Col == 4)) board[Ligne][Col] = P1;
            else if ((Ligne == 3 && Col == 4) || (Ligne == 4 && Col == 3)) board[Ligne][Col] = P2;
            else board[Ligne][Col] = VIDE;
        }
    }
}

void disp_board(char board[TAILLE][TAILLE]){
    printf("\n  ");
    for (int Col = 0; Col < TAILLE; Col++) printf("%d ", Col);
    printf("\n");
    for (int Ligne = 0; Ligne < TAILLE; Ligne++) {
        printf("%d ", Ligne);
        for (int Col = 0; Col < TAILLE; Col++) {
            if(board[Ligne][Col] == P1) couleur("31");
            if(board[Ligne][Col] == P2) couleur("34");
            printf("%c ", board[Ligne][Col]);
            couleur("0");
        }
        printf("%d ", Ligne);
        printf("\n");
    }
    printf("  ");
    for (int Col = 0; Col < TAILLE; Col++) printf("%d ", Col);
    printf("\n");
}

void game_JvJ(Partie * p, char board[TAILLE][TAILLE]){
    bool end_Game = false;
    bool quitter_partie = false;
    char Pstart = joueur_Aléatoire();
    if (p->dernier != p->premier) Pstart = (p->dernier->who_played == P1) ? P2 : P1;
    while (!end_Game) {
        CleanWindows
        check_Pos_Jouable(board, Pstart);
        disp_board(board);
        quitter_partie = pos_Selection(p, board, Pstart);
        if(quitter_partie) break;
        end_Game = check_Gagnant(board);
        Pstart = (Pstart == P1) ? P2 : P1;
    }
    CleanWindows
    save_Partie(p, "Partie.txt");
    disp_resultat(board, quitter_partie);
}

char joueur_Aléatoire(){
    srand(time(NULL));
    char Pstart = (rand()%2 == 0) ? P1 : P2;
    return Pstart;
}

void check_Pos_Jouable(char board[TAILLE][TAILLE], char Player){
    char Player2 = (Player == 'X') ? 'O' : 'X';
    for (int Lig = 0; Lig < TAILLE; Lig++) {
        for (int Col = 0; Col < TAILLE; Col++) {
            if (board[Lig][Col] == '~') board[Lig][Col] = VIDE;
            if (board[Lig][Col] == VIDE) {
                for (int DirH = -1; DirH <= 1; DirH++) {
                    for (int DirL = -1; DirL <= 1; DirL++) {
                        if ((DirH != 0 || DirL != 0)
                            && (Lig + DirH >= 0 && Lig + DirH < 8 && Col + DirL >= 0 && Col + DirL < 8)
                            && board[Lig + DirH][Col + DirL] == Player2) {
                                for (int PosX = Lig + DirH, PosY = Col + DirL; PosX >= 0 && PosX < 8 && PosY >= 0 && PosY < 8; PosX += DirH, PosY += DirL) {
                                    if (board[PosX][PosY] == ' ') break;
                                    else if (board[PosX][PosY] == Player) {
                                        board[Lig][Col] = '~';
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

bool pos_Selection(Partie * p, char board[TAILLE][TAILLE], char Player){
    int ligne, col;
    while (1){
        printf("P%c, Entrez position: Ligne Colonne → ", Player);
        scanf("%d %d", &ligne, &col);
        if(col == -1 || ligne == -1) return true;
        else if(col == -2 || ligne == -2){
            if(p->nbCoups == 1) printf("Impossible d'annuler le coup\n");
            else{
                annuler_Coup(p);
                charger_Partie(p, board);
                Player = (Player == P1) ? P2 : P1;
                check_Pos_Jouable(board, Player);
                disp_board(board);
            }
        }
        else if(board[ligne][col] == '~') break;
        else printf("Coup invalide\n");
    }
    place_Selection(board, ligne, col, Player);
    ajout_Coup_Partie(p, board, Player);
    return false;
}

void place_Selection(char board[TAILLE][TAILLE], int ligne, int col, char Player){
    board[ligne][col] = Player;
    char Player2 = (Player == 'X') ? 'O' : 'X';
    for (int DirH = -1; DirH <= 1; DirH++) {
        for (int DirL = -1; DirL <= 1; DirL++) {
            if (DirL == 0 && DirH == 0) continue;
            if (check_Direction(board, Player, ligne, col, DirL, DirH)){
                int i = ligne + DirL;
                int j = col + DirH;
                while (i < TAILLE && j < TAILLE && board[i][j] == Player2) {
                    board[i][j] = Player;
                    i += DirL;
                    j += DirH;
                }
            }
        }
    }
}

bool check_Direction(char board[TAILLE][TAILLE], char Player, int ligne, int col, int DirL, int DirH){
    int i = ligne + DirL;
    int j = col + DirH;
    while (i >= 0 && i < TAILLE && j >= 0 && j < TAILLE){
        if (board[i][j] == Player) return true;
        if (board[i][j] == VIDE) return false;
        i += DirL;
        j += DirH;
    }
    return false;
}

bool check_Gagnant(char board[TAILLE][TAILLE]){
    int compteur = 0;
    for (int i = 0; i < TAILLE; i++){
        for (int j = 0; j < TAILLE; j++){
            if (board[i][j] == '~') board[i][j] = VIDE;
            if (board[i][j] != VIDE) compteur++;
        }
    }
    if (compteur == TAILLE * TAILLE+4) return true;
    return false;
}

void disp_resultat(char board[TAILLE][TAILLE], bool quitter_partie){
    if(quitter_partie) return;
    int score_P1 = 0;
    int score_P2 = 0;
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            if (board[i][j] == P1) score_P1++;
            else if (board[i][j] == P2) score_P2++;
        }
    }
    printf("P1: %d\n", score_P1);
    printf("P2: %d\n", score_P2);
    if (score_P1 > score_P2) printf("Le P1 gagne !\n");
    else if (score_P2 > score_P1) printf("Le P2 gagne !\n");
    else printf("Egalité\n");
    int waitTemp = scanf("%d", &waitTemp);
}

void init_Partie(Partie * p, char board[TAILLE][TAILLE]){
    liste_Coup * plateau_Debut = malloc(sizeof(liste_Coup));
    plateau_Debut->who_played = ' ';
    plateau_Debut->prec = NULL;
    plateau_Debut->suiv = NULL;
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            plateau_Debut->board[i][j] = board[i][j];
        }
    }

    p->nbCoups = 0;
    p->premier = NULL;
    p->dernier = NULL;
    p->premier = plateau_Debut;
    p->dernier = plateau_Debut;
}

void ajout_Coup_Partie(Partie * p, char board[TAILLE][TAILLE], char Player){
    liste_Coup * new_Coup = malloc(sizeof(liste_Coup));
    new_Coup->who_played = Player;
    new_Coup->prec = p->dernier;
    new_Coup->suiv = NULL;
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            new_Coup->board[i][j] = board[i][j];
        }
    }

    if (p->dernier != NULL) p->dernier->suiv = new_Coup;
    else p->premier = new_Coup;
    p->dernier = new_Coup;
    p->nbCoups++;
}

void annuler_Coup(Partie * p){
    if (p->dernier == NULL) return;

    liste_Coup * last_Coup = p->dernier;
    p->dernier = last_Coup->prec;
    if (p->dernier != NULL) p->dernier->suiv = NULL;
    else p->premier = NULL;
    p->nbCoups--;

    free(last_Coup);
}

void save_Partie(Partie * p, const char * name){
    FILE* fichier = fopen(name, "w+");
    if (fichier == NULL) return;

    fprintf(fichier, "%d", p->nbCoups);
    for (liste_Coup * coup = p->premier; coup != NULL; coup = coup->suiv) {
        fprintf(fichier, "%c\n", coup->who_played);
        for (int i = 0; i < TAILLE; i++) {
            for (int j = 0; j < TAILLE; j++) {
                if(coup->board[i][j] == VIDE) coup->board[i][j] = '~';
                fprintf(fichier, "%c", coup->board[i][j]);
            }
            fprintf(fichier, "\n");
        }
        fprintf(fichier, "\n");
    }
    fclose(fichier);
}

Partie * import_Partie(const char * name){
    FILE* fichier = fopen(name, "r");
    if (fichier == NULL) return NULL;

    char board[TAILLE][TAILLE];
    init_board(board);
	Partie * p = malloc(sizeof(Partie));
	init_Partie(p, board);

    int nbCoups;
    fscanf(fichier, "%d", &nbCoups);
    for (int i = 0; i <= nbCoups; i++){
        char who_played;
        fscanf(fichier, "%c\n", &who_played);
        
        for (int j = 0; j < TAILLE; j++) {
            for (int k = 0; k < TAILLE; k++){
                char c;
                fscanf(fichier, "%c ", &c);
                board[j][k] = c;
                if(board[j][k] == '~') board[j][k] = VIDE;
            }
        }
        ajout_Coup_Partie(p, board, who_played);
    }

    fclose(fichier);
    return p;
}

void charger_Partie(Partie * p, char board[TAILLE][TAILLE]){
    if (p->nbCoups == 0) return;
    
    liste_Coup * last_Coup = p->dernier;
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            board[i][j] = last_Coup->board[i][j];
        }
    }
}

void free_Partie(Partie * p){
    liste_Coup * coup = p->premier;
    while (coup != NULL) {
        liste_Coup * next = coup->suiv;
        free(coup);
        coup = next;
    }
    free(p);
}