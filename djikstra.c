#include <stdio.h>
#define MAX 100
#define INT_MAX 9999  

int distance[MAX]; // distance from source to each vertex
int visited[MAX]; // visited array
int parent[MAX]; // parent array

void djikstra(int n, int source, int adjacency[MAX][MAX]){
    for(int i = 0; i < n; i++){
        distance[i] = INT_MAX; // Initialize distances to infinity
        visited[i] = 0; // Mark all vertices as unvisited
        parent[i] = -1; // Initialize parent array
    }
    distance[source] = 0; // Distance to source is 0

    for(int count = 0; count < n - 1; count++){ // here count is the number of vertices
        int min_dist = INT_MAX;
        int u = -1; 
        
        // Find the vertex with minimum distance
        for(int v = 0; v < n; v++){
            if(!visited[v] && distance[v] < min_dist){ // 0 is considered as false
                min_dist = distance[v]; // Find the vertex with minimum distance
                u = v; // Update u to the vertex with minimum distance
            }
        }
        
        // If no vertex is found, break
        if (u == -1){ 
            // this means all vertices are visited or unreachable
            break;
        }
        
        visited[u] = 1; // Mark u as visited
        
        // Update distances of adjacent vertices
        for(int v = 0; v < n; v++){ // we need to check all vertices
            // Check if vertex is not visited, there is an edge from u to v,
            // and the path through u is better than the current path
            if(!visited[v] && adjacency[u][v] && adjacency[u][v] != INT_MAX && 
               distance[u] != INT_MAX && distance[u] + adjacency[u][v] < distance[v]){
                distance[v] = distance[u] + adjacency[u][v]; // Update distance
                parent[v] = u; // Update parent
            }
        }
    }
}

void printPath(int vertex){
    if(parent[vertex] == -1){ // Base case: if parent is -1, we are at the source
        printf("%d ", vertex);
        return;
    }
    printPath(parent[vertex]); // Recursive call to print the path
    printf("-> %d ", vertex); // Print the current vertex
}

int main(){
    int n, source; // number of vertices and source vertex
    int adjacency[MAX][MAX];
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    printf("Enter the adjacency matrix:\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &adjacency[i][j]);
        }
    }
    printf("Enter the source vertex: ");
    scanf("%d", &source);
    
    // Call the function
    djikstra(n, source, adjacency);

    printf("\nShortest paths from vertex %d:\n", source);
    for(int i = 0; i < n; i++) {
        if(distance[i] == INT_MAX)
            printf("To %d: No path exists\n", i);
        else {
            printf("To %d (distance = %d): ", i, distance[i]);
            printPath(i);
            printf("\n");
        }
    }

    return 0;
}