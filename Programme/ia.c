#include "prototype.h"

// Fonction test IA

int minimax(char board[8][8], int depth, int alpha, int beta, int maximizingPlayer) {
    if (depth == MAX_DEPTH) {
        return evaluate(board); // Évaluation de l'état actuel du jeu
    }
    
    if (maximizingPlayer) {
        int maxScore = NEG_INFINITY;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (isValidMove(board, i, j, BLACK)) {
                    char tempBoard[8][8];
                    copyBoard(board, tempBoard);
                    makeMove(tempBoard, i, j, BLACK);
                    int score = minimax(tempBoard, depth+1, alpha, beta, 0);
                    maxScore = max(maxScore, score);
                    alpha = max(alpha, score);
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
        }
        return maxScore;
    } else {
        int minScore = INFINITY;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (isValidMove(board, i, j, WHITE)) {
                    char tempBoard[8][8];
                    copyBoard(board, tempBoard);
                    makeMove(tempBoard, i, j, WHITE);
                    int score = minimax(tempBoard, depth+1, alpha, beta, 1);
                    minScore = min(minScore, score);
                    beta = min(beta, score);
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
        }
        return minScore;
    }
}

void computerPlay(char board[8][8]) {
    int bestScore = NEG_INFINITY;
    int bestRow, bestCol;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (isValidMove(board, i, j, BLACK)) {
                char tempBoard[8][8];
                copyBoard(board, tempBoard);
                makeMove(tempBoard, i, j, BLACK);
                int score = minimax(tempBoard, 0, NEG_INFINITY, INFINITY, 0);
                if (score > bestScore) {
                    bestScore = score;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }