#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to print assigned colors
void printColors(vector<int>& color, int V) {
    cout << "\nColors of Vertices:\n";
    int maxColor = 0;
    for (int i = 0; i < V; i++) {
        cout << "Vertex " << i + 1 << ": Color " << color[i] << endl;
        maxColor = max(maxColor, color[i]);
    }
    cout << "Total colors used: " << maxColor << endl;
}

// Function to perform greedy graph coloring
void greedyColoring(vector<vector<int>>& graph, vector<int>& color, vector<int>& vertices) {
    int V = graph.size();
    vector<bool> available(V + 1, false); // Color availability array (1-based indexing)

    for (int u : vertices) {
        // Mark colors of adjacent vertices as unavailable
        for (int v = 0; v < V; v++) {
            if (graph[u][v] == 1 && color[v] != -1) {
                available[color[v]] = true;
            }
        }

        // Find the first available color
        int col = 1;
        while (available[col]) col++;

        color[u] = col; // Assign color

        // Reset the availability array for the next iteration
        for (int v = 0; v < V; v++) {
            if (graph[u][v] == 1 && color[v] != -1) {
                available[color[v]] = false;
            }
        }
    }
}

// Function to divide and conquer the graph coloring
void divideAndConquerColoring(vector<vector<int>>& graph, vector<int>& color, int V) {
    vector<int> degree(V, 0);
    vector<int> vertices(V);

    // Calculate degree of each vertex
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (graph[i][j] == 1) {
                degree[i]++;
            }
        }
        vertices[i] = i; // Store vertices
    }

    // Sort vertices by degree in descending order (higher degree first)
    sort(vertices.begin(), vertices.end(), [&](int a, int b) { return degree[a] > degree[b]; });

    // Perform greedy coloring
    greedyColoring(graph, color, vertices);
}

int main() {
    int V;
    cout << "Enter number of vertices: ";
    cin >> V;

    vector<vector<int>> graph(V, vector<int>(V));

    cout << "Enter adjacency matrix (" << V << "x" << V << "):\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cin >> graph[i][j];
        }
    }

    vector<int> color(V, 1); // Initialize color assignment

    // Perform divide and conquer graph coloring
    divideAndConquerColoring(graph, color, V);

    // Print the results
    printColors(color, V);

    return 0;
}
