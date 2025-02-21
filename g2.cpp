#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to generate a random adjacency matrix with given edges
void generateRandomGraph(vector<vector<int>>& graph, int V, int E) {
    srand(time(0));
    int edgeCount = 0;

    while (edgeCount < E) {
        int u = rand() % V;
        int v = rand() % V;

        // Avoid self-loops and duplicate edges
        if (u != v && graph[u][v] == 0) {
            graph[u][v] = 1;
            graph[v][u] = 1;
            edgeCount++;
        }
    }
}

// Function to print the adjacency matrix
void printAdjMatrix(vector<vector<int>>& graph) {
    cout << "\nAdjacency Matrix:\n";
    for (const auto& row : graph) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

// Function to print assigned colors
void printColors(vector<int>& color, int V) {
    cout << "\nColors of Vertices:\n";
    int maxColor = 0;
    for (int i = 0; i < V; i++) {
        cout << "Vertex " << i << ": Color " << color[i] << endl;
        maxColor = max(maxColor, color[i]);
    }
    cout << "Total colors used (Chromatic Number): " << maxColor << endl;
}

// Function to color the graph using the Welsh-Powell algorithm
void greedyColoring(vector<vector<int>>& graph, vector<int>& color) {
    int V = graph.size();
    vector<int> degree(V, 0);
    vector<int> vertices(V);

    // Compute the degree of each vertex
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (graph[i][j] == 1) degree[i]++;
        }
        vertices[i] = i;
    }

    // Sort vertices by degree in descending order
    sort(vertices.begin(), vertices.end(), [&](int a, int b) { return degree[a] > degree[b]; });

    // Color assignment using the greedy algorithm
    vector<bool> available(V + 1, false);

    for (int u : vertices) {
        // Mark colors of adjacent vertices as unavailable
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && color[v] != -1) {
                available[color[v]] = true;
            }
        }

        // Assign the first available color
        int col;
        for (col = 1; col <= V; col++) {
            if (!available[col]) break;
        }
        color[u] = col;

        // Reset availability array
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && color[v] != -1) {
                available[color[v]] = false;
            }
        }
    }
}

int main() {
    int V = 101, E = 1048;

    // Initialize adjacency matrix
    vector<vector<int>> graph(V, vector<int>(V, 0));

    // Generate random graph with 1048 edges
    generateRandomGraph(graph, V, E);

    vector<int> color(V, 1); // Color assignment array

    // Perform greedy graph coloring
    greedyColoring(graph, color);

    // Print adjacency matrix
   // printAdjMatrix(graph);

    // Print results
    printColors(color, V);

    return 0;
}
