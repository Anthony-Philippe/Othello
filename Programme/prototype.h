#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <limits.h>

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

typedef struct liste_Coup liste_Coup;
struct liste_Coup{
    char board[TAILLE][TAILLE];
    char who_played;
    liste_Coup* prec;
    liste_Coup* suiv;
};

typedef struct Partie Partie;
struct Partie{
    int nbCoups;
    liste_Coup* premier;
    liste_Coup* dernier;
};

// * Interface
int menu();
void menu_Crédits();
int menu_Start1();
int menu_Start2();

// * Jeu
void init_board(char board[TAILLE][TAILLE]);
void disp_board(char board[TAILLE][TAILLE]);
void game_JvJ(Partie * p, char board[TAILLE][TAILLE]);
char joueur_Aléatoire();
void check_Pos_Jouable(char board[TAILLE][TAILLE], char Player);
bool pos_Selection(Partie * p, char board[TAILLE][TAILLE], char Player);
void place_Selection(char board[TAILLE][TAILLE], int ligne, int col, char Player);
bool check_Direction(char board[TAILLE][TAILLE], char Player, int ligne, int col, int DirL, int DirH);
bool check_Gagnant(char board[TAILLE][TAILLE]);
void disp_resultat(char board[TAILLE][TAILLE], bool quitter_partie);

void init_Partie(Partie * p, char board[TAILLE][TAILLE]);
void ajout_Coup_Partie(Partie * p, char board[TAILLE][TAILLE], char Player);
void annuler_Coup(Partie * p);
void save_Partie(Partie * p, const char* name);
Partie * import_Partie(const char * name);
void charger_Partie(Partie * p, char board[TAILLE][TAILLE]);
void free_Partie(Partie * p);

// * IA
void valid_moves(char board[TAILLE][TAILLE], char Player, int moves[TAILLE * TAILLE][2], int *move_count);
int eval_board(char board[TAILLE][TAILLE], char Player);
int minimax(char board[TAILLE][TAILLE], char Player, int depth, int alpha, int beta, bool maximizingPlayer);
void ai_move(char board[TAILLE][TAILLE], char Player, int depth, int *chosen_move);

