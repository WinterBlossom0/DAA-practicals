#include<stdio.h>
#define MAX 100

void mcoloring(int adjacency_matrix[MAX][MAX], int *color, int n, int m, int k, int *found);
int nextValue(int adjacency_matrix[MAX][MAX], int *color, int n, int m, int k);
void printSolution(int *color, int n);

int main(){
    int n; // number of vertices
    int m = 1; // Start with minimum possible colors (1)
    int adjacency_matrix[MAX][MAX];
    int color[MAX]; 
    int found = 0; // Flag to indicate if a solution was found
    
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    
    printf("Enter adjacency matrix:\n");
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf("%d", &adjacency_matrix[i][j]);
        }
    }
    
    // Try with increasing number of colors until a solution is found
    // Example: For a graph that needs 3 colors, this loop will:
    // 1. Try with m=1 (fails because adjacent nodes need different colors)
    // 2. Try with m=2 (fails if graph has odd cycles)
    // 3. Try with m=3 (succeeds and exits loop)
    while (!found && m <= n) {
        // Reset colors for each new attempt
        // Example: If n=4, this sets color[0]=0, color[1]=0, color[2]=0, color[3]=0
        for(int i=0; i<n; i++){
            color[i] = 0; // 0 means uncoloured
        }
        
        // Try to color the graph with m colors starting from vertex 0
        mcoloring(adjacency_matrix, color, n, m, 0, &found);
        
        if (found) {
            printf("\nMinimum number of colors required: %d\n", m);
        } else {
            m++; // Try with one more color if current attempt failed
        }
    }
    
    if (!found) {
        printf("No solution exists.\n");
    }
    
    return 0;
}

// Recursive function to assign colors to vertices
// Parameters:
// - adjacency_matrix: Graph representation (1 means connected, 0 means not connected)
// - color: Array storing color of each vertex (1 to m are valid colors, 0 means uncolored)
// - n: Total number of vertices 
// - m: Maximum number of colors allowed
// - k: Current vertex being processed (0 to n-1)
// - found: Flag to track if a valid coloring has been found
void mcoloring(int adjacency_matrix[MAX][MAX], int *color, int n, int m, int k, int *found){
    if (*found) return; // If solution already found, don't continue
    
    // Try assigning each available color to vertex k
    // Example: If m=3, try colors 1, 2, and 3 for vertex k
    for (int c = 1; c <= m; c++) {
        // Try color c for vertex k
        color[k] = c;
        
        // Check if this color is valid by ensuring no adjacent vertex has the same color
        // Example: If vertex 2 is connected to vertex 0, check that color[2] ≠ color[0]
        int valid = 1;
        for (int j = 0; j < k; j++) {
            // If vertices k and j are adjacent (edge exists) and have same color
            if (adjacency_matrix[k][j] == 1 && color[j] == color[k]) {
                valid = 0;
                break;
            }
        }
        
        if (valid) {
            if (k == n-1) {
                // If reached last vertex with valid coloring, solution found!
                // Example: With n=4, once color[0], color[1], color[2], and color[3] are validly assigned
                printf("Solution found with %d colors:\n", m);
                printSolution(color, n);
                *found = 1;
                return;
            } else {
                // Move to next vertex if current color assignment is valid
                // Example: If color[0]=1 is valid, recursively try to color vertex 1
                mcoloring(adjacency_matrix, color, n, m, k+1, found);
            }
        }
    }
    
    // If we reach here, no valid coloring was found for this vertex with current assignments
    // Backtrack by resetting the color of vertex k
    // Example: If vertex 2 can't be colored with any color, reset color[2]=0 and backtrack to vertex 1
    color[k] = 0;
}

// Function to print a valid coloring solution
// Example output for n=4:
// Vertex  Color
// 1       2
// 2       1
// 3       3
// 4       1
void printSolution(int *color, int n) {
    printf("Vertex\tColor\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\n", i+1, color[i]);
    }
    printf("\n");
}