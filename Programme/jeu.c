#include "prototype.h"

void init_board(char board[TAILLE][TAILLE]) {
    for (int Ligne = 0; Ligne < TAILLE; Ligne++) {
        for (int Col = 0; Col < TAILLE; Col++) {
            if ((Ligne == 3 && Col == 3) || (Ligne == 4 && Col == 4)) board[Ligne][Col] = P1;
            else if ((Ligne == 3 && Col == 4) || (Ligne == 4 && Col == 3)) board[Ligne][Col] = P2;
            else board[Ligne][Col] = VIDE;
        }
    }
}

void disp_board(char board[TAILLE][TAILLE]) {
    char col_Board[TAILLE] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    printf("\n  ");
    for (int Col = 0; Col < TAILLE; Col++) printf("%c ", col_Board[Col]);
    printf("\n");
    for (int Ligne = 0; Ligne < TAILLE; Ligne++) {
        printf("%d ", Ligne+1);
        for (int Col = 0; Col < TAILLE; Col++) {
            if(board[Ligne][Col] == P1) couleur("31");
            if(board[Ligne][Col] == P2) couleur("34");
            printf("%c ", board[Ligne][Col]);
            couleur("0");
        }
        printf("%d ", Ligne+1);
        printf("\n");
    }
    printf("  ");
    for (int Col = 0; Col < TAILLE; Col++) printf("%c ", col_Board[Col]);
    printf("\n");
}

char joueur_Aléatoire(){
    srand(time(NULL));
    int Paléatoire = rand() % 2;
    char Pstart = ' ';
    return Pstart = (Paléatoire == 0) ? P1 : P2;
}

void pos_Selection(char board[TAILLE][TAILLE], char Player) {
    int ligne, col;
    char colChar;
    char col_Board[TAILLE] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    bool coup_valide = false;
    while (!coup_valide){
        printf("P%c, Entrez position: Colonne Ligne → ", Player);
        scanf("%c %d", &colChar, &ligne);
        for (int n = 0; n < TAILLE; n++) {
            if (colChar == col_Board[n]) col = n;
        }
        ligne--;
        coup_valide = check_Coup(board, Player, ligne, col);
        if (!coup_valide) printf("Coup invalide\n");
    }
    effectuer_Coup(board, Player, ligne, col);
}

bool check_Coup(char board[TAILLE][TAILLE], char Player, int ligne, int col){
    if (board[ligne][col] != VIDE) return false;
    bool capture_Valide = false;
    for (int DirL = -1; DirL <= 1; DirL++) {
        for (int DirC = -1; DirC <= 1; DirC++) {
            if (DirL == 0 && DirC == 0) continue;
            bool capture = check_Direction(board, Player, ligne, col, DirL, DirC);
            if (capture) {
                capture_Valide = true;
                break;
            }
        }
        if (capture_Valide) break;
    }
    return capture_Valide;
}

bool check_Direction(char board[TAILLE][TAILLE], char Player, int ligne, int col, int DirL, int DirC){
    int i = ligne + DirL;
    int j = col + DirC;
    bool capture = false;
    while (i >= 0 && i < TAILLE && j >= 0 && j < TAILLE && board[i][j] != VIDE) {
        if (board[i][j] == Player) {
            capture = true;
            break;
        }
        i += DirL;
        j += DirC;
    }
    return capture;
}

void effectuer_Coup(char board[TAILLE][TAILLE], char Player, int ligne, int col) {
    board[ligne][col] = Player;
    for (int DirL = -1; DirL <= 1; DirL++) {
        for (int DirC = -1; DirC <= 1; DirC++) {
            if (DirL == 0 && DirC == 0) continue;
            bool capture = check_Direction(board, Player, ligne, col, DirL, DirC);
            if (capture) {
                int i = ligne + DirL;
                int j = col + DirC;
                while ((i < TAILLE || j < TAILLE) && board[i][j] != VIDE) {
                    if(board[i][j] != Player) board[i][j] = Player;
                    i += DirL;
                    j += DirC;
                }
            }
        }
    }
}

bool check_Gagnant(char board[TAILLE][TAILLE]) {
    bool full_Board = true;
    bool coup_Possible = false;
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            if (board[i][j] == VIDE) {
                full_Board = false;
                if (check_Coup(board, P1, i, j) || check_Coup(board, P2, i, j)) {
                    coup_Possible = true;
                    break;
                }
            }
        }
        if (coup_Possible) break;
    }
    return full_Board || !coup_Possible;
}

void disp_resultat(char board[TAILLE][TAILLE]) {
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
}