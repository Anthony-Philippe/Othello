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
#define NEG_INFINITY -1000000 // Valeur moins l'infini

// * Interface
int menu();
void menu_Crédits();

// * Jeu
void init_board(char board[TAILLE][TAILLE]);
void disp_board(char board[TAILLE][TAILLE]);
char joueur_Aléatoire();
void pos_Selection(char board[TAILLE][TAILLE], char Player);
bool check_Coup(char board[TAILLE][TAILLE], char Player, int ligne, int col);
bool check_Direction(char board[TAILLE][TAILLE], char Player, int ligne, int col, int DirL, int DirC);
void effectuer_Coup(char board[TAILLE][TAILLE], char Player, int ligne, int col);
bool check_Gagnant(char board[TAILLE][TAILLE]);
void disp_resultat(char board[TAILLE][TAILLE]);

// * IA
int minimax(char board[8][8], int depth, int alpha, int beta, int maximizingPlayer);
void computerPlay(char board[8][8]);