#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define couleur(param) printf("\033[%sm",param)
#define CleanWindows system("clear");
#define Cursor printf("\t→ ");


#define TAILLE 8
#define P1 'X'
#define P2 'O'
#define VIDE ' '

#define MAX_DEPTH 4 // Profondeur maximale de recherche
#define INFINITY 1000000 // Valeur infinie
#define NEG_INFINITY -1000000 // Valeur moins l'infini;

typedef struct FILE_coup FILE_coup; // ? Sauvegarde des coups joués durant une partie
struct FILE_coup{
    int coup_Joué[2];
    char Joueur;
    FILE_coup* prec;
    FILE_coup* suiv;
};

typedef struct LISTE_coup LISTE_coup;
struct LISTE_coup{
    int nbCoups;
    LISTE_coup* premier;
    LISTE_coup* dernier;
};

// * Interface
int menu();
void menu_Crédits();
int menu_Start1();
int menu_Start2();

// * Jeu
void init_board(char board[TAILLE][TAILLE]);
void disp_board(char board[TAILLE][TAILLE]);
void game_JvJ(char board[TAILLE][TAILLE]);
char joueur_Aléatoire();
bool pos_Selection(char board[TAILLE][TAILLE], char Player);
bool check_Coup(char board[TAILLE][TAILLE], char Player, int ligne, int col);
bool check_Direction(char board[TAILLE][TAILLE], char Player, int ligne, int col, int DirL, int DirC);
void effectuer_Coup(char board[TAILLE][TAILLE], char Player, int ligne, int col);
bool check_Gagnant(char board[TAILLE][TAILLE]);
void disp_resultat(char board[TAILLE][TAILLE], bool quitter_partie);
void ajout_Coup_liste(LISTE_coup * liste_Coups_Partie, char Player, int ligne, int col);
void annuler_Coup(LISTE_coup * liste_Coups_Partie); // TODO

// * IA
int minimax(char board[8][8], int depth, int alpha, int beta, int maximizingPlayer);
void computerPlay(char board[8][8]);