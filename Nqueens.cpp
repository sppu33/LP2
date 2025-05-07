#include <iostream>
#include <vector>
using namespace std;

int N;

//================ BACKTRACKING =================

bool isSafe(int row, int col, vector<vector<char>> &board) {
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 'Q') return false;
    }
    for (int i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++) {
        if (board[i][j] == 'Q') return false;
    }
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q') return false;
    }
    return true;
}

void backTracking(int row, vector<vector<char>> &board, vector<vector<vector<char>>> &solutions) {
    if (row == N) {
        solutions.push_back(board);
        return;
    }

    for (int j = 0; j < N; j++) {
        if (isSafe(row, j, board)) {
            board[row][j] = 'Q';
            backTracking(row + 1, board, solutions);
            board[row][j] = '.';
        }
    }
}

//================ BRANCH AND BOUND =================

int totalBB = 0;

void printSol(const vector<vector<char>> &board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << "----------------" << endl;
}

void solveBB(int row, vector<vector<char>> &board, vector<bool> &cols, vector<bool> &diag1, vector<bool> &diag2) {
    if (row == N) {
        totalBB++;
        printSol(board);
        return;
    }

    for (int col = 0; col < N; col++) {
        if (!cols[col] && !diag1[row + col] && !diag2[row - col + N - 1]) {
            board[row][col] = 'Q';
            cols[col] = diag1[row + col] = diag2[row - col + N - 1] = true;

            solveBB(row + 1, board, cols, diag1, diag2);

            board[row][col] = '.';
            cols[col] = diag1[row + col] = diag2[row - col + N - 1] = false;
        }
    }
}

//================ MAIN =================

int main() {
    cout << "Enter the size of the chessboard (N): ";
    cin >> N;

    int choice;
    cout << "\nN-Queens Problem Solver\n";
    cout << "Choose solving method:\n";
    cout << "1. Backtracking\n";
    cout << "2. Branch and Bound\n";
    cout << "Enter your choice: ";
    cin >> choice;

    vector<vector<char>> board(N, vector<char>(N, '.'));

    if (choice == 1) {
        vector<vector<vector<char>>> solutions;
        backTracking(0, board, solutions);

        cout << "\nTotal solutions: " << solutions.size() << endl;
        for (auto &b : solutions) {
            cout << "***********************\n";
            for (auto &row : b) {
                for (auto &cell : row) {
                    cout << cell << " ";
                }
                cout << endl;
            }
        }

    } else if (choice == 2) {
        vector<bool> cols(N, false);
        vector<bool> leftDiag(2 * N - 1, false);
        vector<bool> rightDiag(2 * N - 1, false);
        solveBB(0, board, cols, leftDiag, rightDiag);
        cout << "\nTotal solutions: " << totalBB << endl;
    } else {
        cout << "Invalid choice!\n";
    }

    return 0;
}
