#include <iostream>
using namespace std;

int N;              // user will input N
int board[20][20];  // supports up to 20x20 board

bool isSafe(int row, int col) {
    // Check column
    for (int i = 0; i < row; i++)
        if (board[i][col]) return false;

    // Check upper-left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j]) return false;

    // Check upper-right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++)
        if (board[i][j]) return false;

    return true;
}

bool solveNQ(int row) {
    if (row >= N) return true;

    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            board[row][col] = 1;

            if (solveNQ(row + 1))
                return true;

            board[row][col] = 0; // backtrack
        }
    }
    return false;
}

void printSolution() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
}

int main() {
    cout << "Enter value of N (board size): ";
    cin >> N;

    // Initialize board
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = 0;

    if (solveNQ(0))
        printSolution();
    else
        cout << "No solution exists\n";

    return 0;
}




/*Pseudocode
N-Queens(n):
    board[n][n] = 0
    solve(0)

solve(row):
    if row >= n:
        print board
        return True

    for col in 0 to n-1:
        if isSafe(row, col):
            place queen at (row, col)
            if solve(row + 1) == True:
                return True
            remove queen from (row, col)    // BACKTRACK

    return False

isSafe(row, col):
    check same column above
    check upper-left diagonal
    check upper-right diagonal

    if no conflict:
        return True
    else:
        return False


*/


/*| Type                 | Complexity | Explanation                                               |
| -------------------- | ---------- | --------------------------------------------------------- |
| **Time Complexity**  | **O(N!)**  | Each queen placement tries multiple positions recursively |
| **Space Complexity** | **O(N²)**  | To store the chessboard and recursion stack               |
*/


/*
Algorithm
1. Start with an empty n×n chessboard.

2. Place queens row-by-row:
     - For each row, try all columns (0 to n−1).
     - For each position (row, col), check if it is safe using:
           a) No queen in the same column above
           b) No queen in upper-left diagonal
           c) No queen in upper-right diagonal

3. If the position is safe:
       Place the queen and recursively solve the next row.

4. If the next rows cannot place a queen:
       Remove the queen (backtrack) and try the next column.

5. If all rows (0 to n−1) are filled:
       A valid N-Queens solution is found.

6. If no column works for any row:
       Return failure (no solution).
*/