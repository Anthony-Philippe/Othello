#include "directive.h"
#include "prototype.h"

void init_Partie(Partie * p, int board[TAILLE][TAILLE]){
    liste_Coup * plateau_Debut = malloc(sizeof(liste_Coup));
    plateau_Debut->who_played = VIDE;
    plateau_Debut->prec = NULL;
    plateau_Debut->suiv = NULL;
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            plateau_Debut->board[i][j] = board[i][j];
        }
    }

    p->nbCoups = 0;
    p->type = 1;
    p->premier = NULL;
    p->dernier = NULL;
    p->premier = plateau_Debut;
    p->dernier = plateau_Debut;
}

void ajout_Coup_Partie(Partie * p, int board[TAILLE][TAILLE], partie_Data game){
    liste_Coup * new_Coup = malloc(sizeof(liste_Coup));
    new_Coup->who_played = game.Joueur;
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
    FILE* fichier = fopen(name, "w");
    if (fichier == NULL) return;

    p->nbCoups--;
    fprintf(fichier, "%d %d\n", p->nbCoups, p->type);
    for (liste_Coup * coup = p->premier->suiv; coup != NULL; coup = coup->suiv) {
        fprintf(fichier, "%d\n", coup->who_played);
        for (int i = 0; i < TAILLE; i++) {
            for (int j = 0; j < TAILLE; j++) {
                if(coup->board[i][j] == case_Jouable) coup->board[i][j] = VIDE;
                fprintf(fichier, "%d", coup->board[i][j]);
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

    int board[TAILLE][TAILLE];
    init_board(board);
	Partie * p = malloc(sizeof(Partie));
	init_Partie(p, board);

    int nbCoups;
    fscanf(fichier, "%d %d\n", &nbCoups, &p->type);
    for (int i = 0; i <= nbCoups; i++){
        int who_played;
        fscanf(fichier, "%d\n", &who_played);
        
        for (int j = 0; j < TAILLE; j++) {
            for (int k = 0; k < TAILLE; k++){
                int c;
                fscanf(fichier, "%1d", &c);
                board[j][k] = c;
            }
        }
        partie_Data game;
        game.Joueur = who_played;
        ajout_Coup_Partie(p, board, game);
    }

    fclose(fichier);
    return p;
}

void charger_Partie(Partie * p, int board[TAILLE][TAILLE]){
    if (p->nbCoups == 0) return;
    
    liste_Coup * last_Coup = p->dernier;
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            board[i][j] = last_Coup->board[i][j];
        }
    }
}

partie_Data chargement_Partie_data(Partie * p, int board[TAILLE][TAILLE], partie_Data game){
    charger_Partie(p, board);
    game.Joueur = (p->dernier->who_played == P1) ? P2 : P1;
    game.Mode = p->type;
    game.partie_Started = true;
    return game;
}

void free_Partie(Partie * p){
    if (p->premier == NULL) return;
    liste_Coup * coup = p->premier;
    while (coup != NULL) {
        liste_Coup * next = coup->suiv;
        free(coup);
        coup = next;
    }
    p->premier = NULL;
    p->dernier = NULL;
    free(p);
}