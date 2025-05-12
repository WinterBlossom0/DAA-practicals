#include <stdio.h>
#define MAX 100

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int main(){
    int n, capacity, p;
    int weights[MAX], profits[MAX];
    int table[MAX][MAX];
    int solution[MAX];
    // weights and profit arrays to store the weights and profit of each item

    printf("Enter the number of items: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter weight of item %d: ", i + 1);
        scanf("%d", &weights[i]);
        printf("Enter profit of item %d: ", i + 1);
        scanf("%d", &profits[i]);
    }
    printf("Enter the capacity of the knapsack: ");
    scanf("%d", &capacity);

    // Initialize the table
    for (int i = 0; i <= n; i++) {
        table[i][0] = 0;
    }
    // Because we need 0 capacity to make 0 profit
    for (int j = 1; j <= capacity; j++) { //note we start from j = 1 because pf case [0][0] where we need 0 profit to make 0 capacity
        table[0][j] = 0;
        // we use 0 because in knapsack goal is to maximize profit not fill the knapsack
    }
    
    // fill the table
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= capacity; j++){
            if(weights[i - 1] > j){
                table[i][j] = table[i - 1][j];
            }
            else {
                table[i][j] = max(table[i - 1][j], profits[i - 1] + table[i - 1][j - weights[i - 1]]);
            }
        }
    }

    printf("DP Table:\n");
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= capacity; j++){
            printf("%d\t", table[i][j]);
        }
        printf("\n");
    }

    printf("Maximum profit: %d\n", table[n][capacity]);
    printf("Items included in the knapsack:\n");
    p = capacity;
    for (int i = n; i > 0; i--){
        if (table[i][p] != table[i - 1][p]){
            solution[i] = 1;
            p -= weights[i - 1];
        }
        else {
            solution[i] = 0;
        }
    }
    for (int i = 1; i <= n; i++){
        if (solution[i] == 1){
            printf("Item %d: weight = %d, profit = %d\n", i, weights[i - 1], profits[i - 1]);
        }
    }
    return 0;

}