#include <stdio.h>
#define MAX 100

int min(int a, int b){
    if (a < b){
        return a;
    }
    return b;
}

int main(){
    int n; // number of vertices
    int k; // number of iterations
    int adjacency_matrix[MAX][MAX];
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    printf("Enter the adjacency matrix:\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &adjacency_matrix[i][j]);
        }
    }
    for (k = 0; k < n; k++){
        for (int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                adjacency_matrix[i][j] = min(adjacency_matrix[i][j], adjacency_matrix[i][k] + adjacency_matrix[k][j]);
            }
        }
    }
    printf("The distance matrix is:\n");
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", adjacency_matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}