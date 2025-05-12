#include <stdio.h>
#define MAX 100
#define INT_MAX 100000
//do not use INT_MAX from limits.h other it will cause overflow

int min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

int main(){

    int m, sum;
    // m is the number of denominations
    // sum is the total amount of coins

    int coins[MAX];
    // here we are using a 2D array to store values of different denominations

    int table[MAX][MAX];
    // memoization array to store the solution
    // in table we will store minimum number of coins needed to make each amount

    int solution[MAX];
    // here we are using a 1D array to store the solution

    printf("Enter the number of coin denominations: ");
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        printf("Enter coin denomination %d: ", i + 1);
        scanf("%d", &coins[i]);
    }

    printf("Enter the total amount: ");
    scanf("%d", &sum);

    // Initialize the table
    for (int i = 0; i <= m; i++) {
        table[i][0] = 0;
    }
    // Because we need 0 coins to make 0 amount
    for (int j = 1; j <= sum; j++) { //note we start from j = 1 because pf case [0][0] where we need 0 coins to make 0 amount
        table[0][j] = INT_MAX;
    }
    // Because we need infinite coins to make any amount with 0 denominations

    // Fill the table
    for (int i = 1; i <= m; i++){ // we start from 1 because we need to use the first denomination
        // we are taking = because we have covered the case of 0 coins
        for (int j = 1; j <= sum; j++) { // we start from 1 because we need to use the first amount
            // we are taking = because we have covered the case of 0 amount
            if (coins[i - 1] > j){// if the denomination is greater than the amount
                // suppose we have 2 as denomination and 1 as amount
                // we cannot use the denomination so we will use the previous denomination in this case 0 denomination
                table[i][j] = table[i - 1][j]; // we can only use the previous denomination
            }
            else {
                table[i][j] = min(table[i - 1][j], 1 + table[i][j - coins[i - 1]]);
                // to select the minimum number of coins we can use
                //we either take the current coin or we skip it
            }
        }
    }

    printf("\nDP Table:\n");
    for (int i = 0; i <= m; i++){
        for (int j = 0; j <= sum; j++){
            if (table[i][j] == INT_MAX){
                printf("INF ");
            }
            else{
                printf("%d ", table[i][j]); 
            }
        }
        printf("\n");
    }

    if (table[m][sum] == INT_MAX){
        printf("\nIt is not possible to form the sum %d with the given denominations.\n", sum);
        // for example we have coins 2, 5 but we need to make 3
        // so we cannot make 3 with the given denominations hence we will return INF
    }
    else{
        printf("\nMinimum number of coins required: %d\n", table[m][sum]);
        // now we will derive the solution from the table
        int p = 0, i = m, j = sum;
        // start from the last cell of the table
        while (j > 0 && i > 0) {
            if (table[i][j] == table[i - 1][j]) {
                i = i - 1;
            }
            else{
                solution[p] = coins[i - 1];
                // we will store the denomination used
                j = j - coins[i - 1];
                p++;
            }
        }
        printf("Coins used: ");
        for (int k = 0; k < p; k++) {
            printf("%d ", solution[k]);
        }
        printf("\n");
    }
    
    return 0;
}


