#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF INT_MAX

/**
 * Implementation of Prim's Algorithm to find Minimum Spanning Tree
 * 
 * graph: Adjacency matrix representation of the graph
 * capital v: Number of vertices in the graph
 * r: Starting vertex (root) for MST construction
 */
void primMST(int graph[MAX_VERTICES][MAX_VERTICES], int V, int r) {
    int parent[MAX_VERTICES]; // Array to store constructed MST
    int key[MAX_VERTICES];    // Key values used to pick minimum weight edge
    int inMST[MAX_VERTICES];  // To represent set of vertices included in MST
    
    /*
     * INITIALIZATION PHASE:
     * - Set all vertices' keys to infinity
     * - Set all parents to NIL
     * - Set starting vertex key to 0
     * 
     * Example with 5 vertices (0-4) and starting vertex r=0:
     * Initially:
     * Vertex | Key | Parent
     * -------------------
     *   0    |  0  |  NIL  (starting vertex)
     *   1    |  ∞  |  NIL
     *   2    |  ∞  |  NIL
     *   3    |  ∞  |  NIL
     *   4    |  ∞  |  NIL
     */
    for (int u = 0; u < V; u++) {
        key[u] = INF;      // Set key to infinity (∞)
        inMST[u] = 0;      // Mark vertex as not included in MST
        parent[u] = -1;    // Set parent to NIL
    }
    
    // Set key of starting vertex to 0 so it's picked first
    key[r] = 0;
    
    /*
     * MAIN LOOP:
     * While Q is not empty, extract vertex with minimum key,
     * add it to MST and update keys of adjacent vertices
     * 
     * For our implementation, Q is implicitly maintained by the inMST array
     * V iterations will ensure all vertices are processed
     * 
     * Example for graph:
     *      2
     *  0-------1
     *  |       | \
     *  |6      |  3
     *  |       |5  \
     *  3-------4----2
     *      9     7
     */
    for (int i = 0; i < V; i++) {
        /*
         * EXTRACT-MIN operation:
         * Find vertex with minimum key value that is not yet in MST
         * 
         * Example: First iteration will select vertex 0 (key=0)
         */
        int min = INF, u;
        for (int v = 0; v < V; v++) {
            if (inMST[v] == 0 && key[v] < min) {
                min = key[v];
                u = v;
            }
        }
        
        // Add the picked vertex to the MST
        inMST[u] = 1;
        
        /*
         * RELAXATION STEP:
         * For each adjacent vertex v of u:
         * If v is not in MST and weight of edge (u,v) < key[v],
         * update key[v] and set u as parent of v
         * 
         * Example: After selecting vertex 0 in first iteration:
         * - Check edge (0,1): Update key[1] = 2, parent[1] = 0
         * - Check edge (0,3): Update key[3] = 6, parent[3] = 0
         */
        for (int v = 0; v < V; v++) {
            // Update key[v] if:
            // 1. There is an edge from u to v (graph[u][v] != 0)
            // 2. v is not in MST yet (inMST[v] == 0)
            // 3. Weight of edge (u,v) is less than current key[v]
            if (graph[u][v] && inMST[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
    
    // Print the constructed MST
    printf("\nEdges in the Minimum Spanning Tree:\n");
    printf("Edge \tWeight\n");
    int total_weight = 0;
    for (int i = 1; i < V; i++) {
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
        total_weight += graph[i][parent[i]];
    }
    printf("Total weight of MST: %d\n", total_weight);
}

int main() {
    /*
     * Example graph represented as adjacency matrix:
     *      2
     *  0-------1
     *  |       | \
     *  |6      |  3
     *  |       |5  \
     *  3-------4----2
     *      9     7
     */
    int V = 5; // Number of vertices
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };
    
    // Display the graph
    printf("Graph represented as adjacency matrix:\n");
    printf("   ");
    for (int i = 0; i < V; i++)
        printf("%d  ", i);
    printf("\n");
    
    for (int i = 0; i < V; i++) {
        printf("%d: ", i);
        for (int j = 0; j < V; j++) {
            if (graph[i][j] == 0)
                printf("-  ");
            else
                printf("%d  ", graph[i][j]);
        }
        printf("\n");
    }
    
    // Run Prim's algorithm starting from vertex 0
    printf("\nRunning Prim's algorithm starting from vertex 0\n");
    primMST(graph, V, 0);
    
    return 0;
}