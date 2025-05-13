#include <stdio.h>
#define MAX 100

int board[MAX][MAX];
int solutions = 0;

// Function to check if a queen can be placed at board[row][col]
int isSafe(int row, int col, int n) {
    int i, j;
    
    // Check column
    for (i = 0; i < row; i++)
        if (board[i][col])
            return 0;
    //checks if the column is safe
            
    // Check upper left diagonal
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return 0;
            
    // Check upper right diagonal
    for (i = row, j = col; i >= 0 && j < n; i--, j++)
        if (board[i][j])
            return 0;
            
    return 1;
}

// Recursive function to solve N Queens
void solveNQueens(int row, int n) {
    // Base case: If all queens are placed
    if (row == n) {
        solutions++;
        printf("\nSolution %d:\n", solutions);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 1) {
                    printf("Q ");
                } else {
                    printf(". ");
                }
            }
            printf("\n");
        }
        return;
    }
    
    // Try placing queen in each column of current row
    for (int col = 0; col < n; col++) {
        if (isSafe(row, col, n)) {
            // Place the queen
            board[row][col] = 1;
            
            // Recur for next row
            solveNQueens(row + 1, n);
            
            // Backtrack: remove the queen (undo the choice)
            board[row][col] = 0;
        }
    }
}

int main() {
    int n;
    printf("Enter the number of queens: ");
    scanf("%d", &n);
    
    // Initialize board
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = 0;
    
    solveNQueens(0, n);
    
    printf("\nTotal solutions: %d\n", solutions);
    return 0;
}