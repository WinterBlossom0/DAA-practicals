#include <stdio.h>
#include <limits.h>
// for INT_MAX

#define MAX 100

void matrixChain(int dimensions[], int n){
    int m[MAX][MAX] = {0};  // Cost table
    // we are putting 0 in the table because we are not using the first row and column
    int s[MAX][MAX] = {0}; // K-table

    int i, j, k, L, cost;
    // L is the length of the chain

    for(i = 1 ; i < n; i++){
        m[i][i] = 0; // cost of multiplying one matrix is 0
        // diagonal elements are 0
    }

    for(L = 2; L < n; L++){
        for(i = 1; i < n - L + 1; i++){
            // n - L + 1 is the number of matrices we can multiply
            // suppose we have 4 matrices and we want to multiply 3 matrices
            // we can multiply 1st, 2nd and 3rd matrix or 2nd, 3rd and 4th matrix
            // so here n will be 4 and L will be 3 n - L + 1 will be 2 
            // which is the number of matrices we can multiply
            j = i + L -1; // j is the last matrix in the chain
            m[i][j] = INT_MAX; // we are putting max value in the table
            // because we want to find the minimum cost
            for(k = i; k < j; k++){
                cost = m[i][k] + m[k + 1][j] + dimensions[i - 1] * dimensions[k] * dimensions[j];
                // cost of multiplying the matrices
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("\nMinimum number of multiplications: %d\n", m[1][n-1]); 
    // since there are n - 1 matrices
    printf("\n");

    printf("Cost Table:\n");
    for(i = 1; i < n; i++){
        for(j = 1; j < n; j++){
            if(j >= i)
                printf("|%d|\t", m[i][j]);
            else
                printf("|0|\t");
        }
        printf("\n");
    }

    printf("\nK-table :\n");
    for(i = 1; i < n; i++){
        for(j = 1; j < n; j++){
            if(j > i)
                printf("|%d|\t", s[i][j]);
            else
                printf("|0|\t");
                // in k table we didnt made diagonals explicitly 0 earlier'
                // because we didnt use them for any calculation
        }
        printf("\n");
    }

}

int main(){
    int dimensions[MAX], n;
    printf("Enter the number of dimensions: ");
    scanf("%d", &n);
    printf("\nEnter the dimensions: ");
    for (int i = 0; i < n; i++) {
        printf("\nP%d = ", i);
        scanf("%d", &dimensions[i]);
    }
    matrixChain(dimensions, n);
    return 0;
}