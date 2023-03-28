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

void game_JvJ(liste_Coup * C_board, char board[TAILLE][TAILLE]){
    bool end_Game = false;
    bool quitter_partie = false;
    char Pstart = joueur_Aléatoire();
    while (!end_Game) {
        CleanWindows
        check_Pos_Jouable(board, Pstart);
        disp_board(board);
        quitter_partie = pos_Selection(C_board, board, Pstart);
        if(quitter_partie) break;
        if(check_Gagnant(board)) end_Game = true;
        Pstart = (Pstart == P1) ? P2 : P1;
    }
    CleanWindows
    disp_resultat(board, quitter_partie);
}

char joueur_Aléatoire(){
    srand(time(NULL));
    int Paléatoire = rand() % 2;
    char Pstart = ' ';
    return Pstart = (Paléatoire == 0) ? P1 : P2;
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

bool pos_Selection(liste_Coup * C_board, char board[TAILLE][TAILLE], char Player){
    int ligne, col;
    bool quitter_partie = false;
    while (1){
        printf("P%c, Entrez position: Ligne Colonne → ", Player);
        scanf("%d %d", &ligne, &col);
        if(col == 0) return quitter_partie = true;
        if(board[ligne][col] == '~') break;
        else printf("Coup invalide\n");
    }
    place_Selection(board, ligne, col, Player);
    //ajout_Coup_liste(C_board, ligne, col, Player);
    return quitter_partie;
}

void place_Selection(char board[TAILLE][TAILLE], int ligne, int col, char Player){
    board[ligne][col] = Player;
    char Player2 = (Player == 'X') ? 'O' : 'X';
    for (int DirH = -1; DirH <= 1; DirH++) {
        for (int DirL = -1; DirL <= 1; DirL++) {
            if (DirL == 0 && DirH == 0) continue;
            bool capture = check_Direction(board, Player, ligne, col, DirL, DirH);
            if (capture) {
                int i = ligne + DirL;
                int j = col + DirH;
                while ((i < TAILLE || j < TAILLE) && board[i][j] != VIDE) {
                    if(board[i][j] == Player2) board[i][j] = Player;
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
    bool capture = false;
    while (i >= 0 && i < TAILLE && j >= 0 && j < TAILLE && board[i][j] != VIDE) {
        if (board[i][j] == Player) {
            capture = true;
            break;
        }
        i += DirL;
        j += DirH;
    }
    return capture;
}

bool check_Gagnant(char board[TAILLE][TAILLE]){
    bool Gagnant = false;
    int compteur = 0;
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            if (board[i][j] == '~') board[i][j] = VIDE;
            if (board[i][j] != VIDE) compteur++;
        }
    }
    if (compteur == TAILLE * TAILLE+4) Gagnant = true;
    return Gagnant;
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
    p->nbCoups = 0;
    p->premier = NULL;
    p->dernier = NULL;

    liste_Coup* plateau_Debut = malloc(sizeof(liste_Coup));
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            plateau_Debut->board[i][j] = board[i][j];
        }
    }

    plateau_Debut->who_played = ' ';
    plateau_Debut->prec = NULL;
    plateau_Debut->suiv = NULL;
    p->premier = plateau_Debut;
    p->dernier = plateau_Debut;
}

void ajout_Coup_Partie(Partie * p, char board[TAILLE][TAILLE], char Player){
    liste_Coup* new_Coup = malloc(sizeof(liste_Coup));
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            new_Coup->board[i][j] = board[i][j];
        }
    }
    new_Coup->who_played = Player;
    new_Coup->prec = p->dernier;
    new_Coup->suiv = NULL;

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
    FILE* fichier = fopen(name, "w");
    if (fichier == NULL) return;

    fprintf(fichier, "%d\n", p->nbCoups);
    liste_Coup * coup = p->premier;
    while (coup != NULL) {
        fprintf(fichier, "%c ", coup->who_played);
        for (int i = 0; i < TAILLE; i++) {
            for (int j = 0; j < TAILLE; j++) {
                fprintf(fichier, "%c", coup->board[i][j]);
            }
        }
        fprintf(fichier, "\n");
        coup = coup->suiv;
    }
    fclose(fichier);
}

Partie * import_Partie(const char * name){
    FILE* fichier = fopen(name, "r");
    if (fichier == NULL) return NULL;

    char board[TAILLE][TAILLE];
    init_board(board);
	Partie * p;
	init_Partie(p, board);

    int nbCoups;
    fscanf(fichier, "%d\n", &nbCoups);
    for (int i = 0; i < nbCoups; i++){
        char who_played;
        fscanf(fichier, "%c ", &who_played);
        for (int j = 0; j < TAILLE; j++) {
            for (int k = 0; k < TAILLE; k++){
                char c;
                fscanf(fichier, "%c", &c);
                board[j][k] = c;
            }
        }
        ajouter_coup(p, board, who_played);
    }

    fclose(fichier);
    return p;
}

/*LISTE_coup * init_listeC(LISTE_coup * listeC){
    listeC = (LISTE_coup*)malloc(sizeof(LISTE_coup));
	listeC->premier = NULL;
	listeC->dernier = NULL;
	listeC->nbCoups = 0;
    return listeC;
}

void ajout_Coup_liste(LISTE_coup * listeC, int ligne, int col, char Player){
    FILE_coup * new_Coup = (FILE_coup*)malloc(sizeof(FILE_coup));
    new_Coup->coup_Joué[0] = ligne;
    new_Coup->coup_Joué[1] = col;
    new_Coup->Joueur = Player;
    new_Coup->prec = listeC->dernier;
    new_Coup->suiv = NULL;
    if (listeC->premier == NULL) {
        listeC->premier = new_Coup;
        new_Coup->prec = NULL;
    } else{
        listeC->dernier->suiv = new_Coup;
        new_Coup->prec = listeC->dernier;
    } 
    listeC->dernier = new_Coup;
    listeC->nbCoups++;
}

void annuler_Coup(LISTE_coup* listeC){
    if(listeC->dernier == NULL) return;

    FILE_coup * coupAnnuler = listeC->dernier;
    listeC->dernier = coupAnnuler->prec;

    if (listeC->dernier == NULL) listeC->premier = NULL;
    else listeC->dernier->suiv = NULL;

    free(coupAnnuler);
    listeC->nbCoups--;
}

void save_Liste(LISTE_coup * listeC, char* name){
    FILE* fichier = fopen(name, "w");
    if (fichier == NULL) return;

    FILE_coup * coupTPM = listeC->premier;
    while (coupTPM != NULL) {
        fprintf(fichier, "%d %d %c\n", coupTPM->coup_Joué[0], coupTPM->coup_Joué[1], coupTPM->Joueur);
        coupTPM = coupTPM->suiv;
    }
    fclose(fichier);
}

LISTE_coup * import_Liste_coup(LISTE_coup * listeC, char* name){
    FILE* fichier = fopen(name, "r");
    if (fichier == NULL) return NULL;

    int col, ligne;
    char Joueur;
    while (fscanf(fichier, "%d %d %c", &col, &ligne, &Joueur) == 3) {
        ajout_Coup_liste(listeC, ligne, col, Joueur);
        listeC->nbCoups++;
    }
    fclose(fichier);
    return listeC;
}

void save_Partie(char board[TAILLE][TAILLE], char Player, char* name){
    FILE* fichier = fopen(name, "r");
    if (fichier == NULL) return;

    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            if(board[i][j] == ' ') board[i][j] = '~';
            fprintf(fichier, "%c", board[i][j]);
        }
        fprintf(fichier, "\n");
    }
    fprintf(fichier, "%c", Player);
    fclose(fichier);
}

void import_Partie(char board[TAILLE][TAILLE], char* Player, char* name){
    FILE* fichier = fopen(name, "r");
    if (fichier == NULL) return;

    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            fscanf(fichier, " %c", &board[i][j]);
            if(board[i][j] == '~') board[i][j] = ' ';
        }
    }
    fscanf(fichier, " %c", Player);
    fclose(fichier);
}*/