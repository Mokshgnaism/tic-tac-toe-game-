#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

char player = 'X', ai = 'O';
char empty = ' ';

// Function to print the board
void printBoard(const vector<vector<char>>& board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << "|";
        }
        cout << endl;
        if (i < 2) cout << "-----" << endl;
    }
}

// Function to check if the current player has won
bool isWinner(const vector<vector<char>>& board, char player) {
    for (int i = 0; i < 3; i++) {
        // Check rows and columns
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) || 
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || 
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    return false;
}

// Function to check if the board is full (draw condition)
bool isBoardFull(const vector<vector<char>>& board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == empty) return false;
        }
    }
    return true;
}

// Minimax algorithm to find the best move for AI
int minimax(vector<vector<char>>& board, int depth, bool isMaximizing) {
    if (isWinner(board, ai)) return 10 - depth;
    if (isWinner(board, player)) return depth - 10;
    if (isBoardFull(board)) return 0;

    if (isMaximizing) {
        int best = INT_MIN;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == empty) {
                    board[i][j] = ai;
                    best = max(best, minimax(board, depth + 1, false));
                    board[i][j] = empty;
                }
            }
        }
        return best;
    } else {
        int best = INT_MAX;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == empty) {
                    board[i][j] = player;
                    best = min(best, minimax(board, depth + 1, true));
                    board[i][j] = empty;
                }
            }
        }
        return best;
    }
}

// Function to find the best move for the AI
pair<int, int> bestMove(vector<vector<char>>& board) {
    int bestVal = INT_MIN;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == empty) {
                board[i][j] = ai;
                int moveVal = minimax(board, 0, false);
                board[i][j] = empty;

                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

// Function to play the game
void playGame() {
    vector<vector<char>> board(3, vector<char>(3, empty));
    bool isPlayerTurn = true;
    int row, col;

    while (true) {
        printBoard(board);
        
        if (isPlayerTurn) {
            cout << "Your move (Enter row and column): ";
            cin >> row >> col;
            if (board[row][col] == empty) {
                board[row][col] = player;
                if (isWinner(board, player)) {
                    printBoard(board);
                    cout << "You win!" << endl;
                    break;
                }
                isPlayerTurn = false;
            } else {
                cout << "Invalid move, try again!" << endl;
            }
        } else {
            cout << "AI's move..." << endl;
            pair<int, int> move = bestMove(board);
            board[move.first][move.second] = ai;
            if (isWinner(board, ai)) {
                printBoard(board);
                cout << "AI wins!" << endl;
                break;
            }
            isPlayerTurn = true;
        }

        if (isBoardFull(board)) {
            printBoard(board);
            cout << "It's a draw!" << endl;
            break;
        }
    }
}

int main() {
    cout << "Welcome to Tic-Tac-Toe!" << endl;
    playGame();
    return 0;
}
