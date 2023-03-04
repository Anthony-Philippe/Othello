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

int menu();
char joueur_Aléatoire();

void init_board(char board[TAILLE][TAILLE]);
void disp_board(char board[TAILLE][TAILLE]);
void pos_Selection(char board[TAILLE][TAILLE], char Player);
bool check_Coup(char board[TAILLE][TAILLE], char Player, int ligne, int col);
void effectuer_Coup(char board[TAILLE][TAILLE], char Player, int ligne, int col);
bool check_Gagnant(char board[TAILLE][TAILLE]);
void disp_resultat(char board[TAILLE][TAILLE]);