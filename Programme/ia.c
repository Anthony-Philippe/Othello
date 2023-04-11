#include "prototype.h"

void valid_moves(char board[TAILLE][TAILLE], char Player, int moves[TAILLE * TAILLE][2], int *move_count) {
    *move_count = 0;
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            if (check_Coup(board, Player, i, j)) {
                moves[*move_count][0] = i;
                moves[*move_count][1] = j;
                (*move_count)++;
            }
        }
    }
}

int eval_board(char board[TAILLE][TAILLE], char Player) {
    int score = 0;
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            if (board[i][j] == Player) {
                score++;
            } else if (board[i][j] != VIDE) {
                score--;
            }
        }
    }
    return score;
}

int minimax(char board[TAILLE][TAILLE], char Player, int depth, int alpha, int beta, bool maximizingPlayer) {
    if (depth == 0 || check_Gagnant(board)) {
        return eval_board(board, Player);
    }

    int moves[TAILLE * TAILLE][2], move_count;
    valid_moves(board, Player, moves, &move_count);
    char otherPlayer = (Player == P1) ? P2 : P1;

    if (maximizingPlayer) {
        int maxEval = INT_MIN;
        for (int i = 0; i < move_count; i++) {
            char temp_board[TAILLE][TAILLE];
            memcpy(temp_board, board, sizeof(temp_board));
            effectuer_Coup(temp_board, Player, moves[i][0], moves[i][1]);

            int eval = minimax(temp_board, Player, depth - 1, alpha, beta, false);
            maxEval = (eval > maxEval) ? eval : maxEval;
            alpha = (alpha > eval) ? alpha : eval;
            if (beta <= alpha) {
                break;
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for (int i = 0; i < move_count; i++) {
            char temp_board[TAILLE][TAILLE];
            memcpy(temp_board, board, sizeof(temp_board));
            effectuer_Coup(temp_board, otherPlayer, moves[i][0], moves[i][1]);

            int eval = minimax(temp_board, Player, depth - 1, alpha, beta, true);
            minEval = (eval < minEval) ? eval : minEval;
            beta = (beta < eval) ? beta : eval;
            if (beta <= alpha) {
                break;
            }
        }
        return minEval;
    }
}

void ai_move(char board[TAILLE][TAILLE], char Player, int depth, int *chosen_move) {
    int moves[TAILLE * TAILLE][2], move_count;
    valid_moves(board, Player, moves, &move_count);

    int maxEval = INT_MIN;
    for (int i = 0; i < move_count; i++) {
        char temp_board[TAILLE][TAILLE];
        memcpy(temp_board, board, sizeof(temp_board));
        effectuer_Coup(temp_board, Player, moves[i][0], moves[i][1]);

        int eval = minimax(temp_board, Player, depth - 1, INT_MIN, INT_MAX, false);
        if (eval > maxEval) {
            maxEval = eval;
            chosen_move[0] = moves[i][0];
            chosen_move[1] = moves[i][1];
        }
    }
}

void ai (Partie* partie, char board[TAILLE][TAILLE]) {
    char currentPlayer = joueur_Aléatoire();

    while (!check_Gagnant(board)) {
        disp_board(board);

        if (currentPlayer == P1) { // P1 is human
            pos_Selection(partie, board, currentPlayer);
        } else { // P2 is AI
            int ai_move_choice[2];
            ai_move(board, currentPlayer, 4, ai_move_choice); // Depth 4 is an example
            effectuer_Coup(board, currentPlayer, ai_move_choice[0], ai_move_choice[1]);
        }

        currentPlayer = (currentPlayer == P1) ? P2 : P1;
    }
}
