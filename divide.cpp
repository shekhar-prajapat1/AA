#include<bits/stdc++.h>
using namespace std;
long num_edges=0;
// Function to calculate the median degree of the graph
double calculate_median_degree(const vector<vector<int>>& adjacency_matrix) {
    int num_vertices = adjacency_matrix.size();
    vector<int> degrees;

    for (int i = 0; i < num_vertices; ++i) {
        int degree = accumulate(adjacency_matrix[i].begin(), adjacency_matrix[i].end(), 0);
        degrees.push_back(degree);
    }

    sort(degrees.begin(), degrees.end());

    if (num_vertices % 2 == 0) {
        return (degrees[num_vertices / 2] + degrees[num_vertices / 2 - 1]) / 2.0;
    } else {
        return degrees[num_vertices / 2];
    }
}

// Function to generate an adjacency matrix
vector<vector<int>> generate_adjacency_matrix(int num_vertices) {
         vector<vector<int>> adjacency_matrix(num_vertices,vector<int>(num_vertices, 0));
    // Generate the adjacency matrix with the specified condition
    for (int i = 0; i < num_vertices; ++i) {
        for (int j = i + 1; j < num_vertices; ++j) {
            int rm = (rand()%100>=49);
            // Check if the difference between vertex indices is less than or equal to heuristic_value
            if (rm) {
                adjacency_matrix[i][j] = 1;
                adjacency_matrix[j][i] = 1;
                num_edges++;
            }
        }
    }

    return adjacency_matrix;
}

// Function to color the graph using the specified algorithm
vector<int> color_graph(const vector<vector<int>>& adjacency_matrix, double heuristic_value) {
       int num_vertices = adjacency_matrix.size();
       vector<int> color(num_vertices, 0);
        int min_color = 3;

    // Greedy coloring algorithm
    for (int i = 0; i < num_vertices; ++i) {
        if ( accumulate(adjacency_matrix[i].begin(), adjacency_matrix[i].end(), 0) >= heuristic_value) {
            for (int j = 1; j <= min_color; ++j) {
                bool is_conflict = false;
                for (int k = 0; k < num_vertices; ++k) {
                    if (adjacency_matrix[i][k] && color[k] == j) {
                        is_conflict = true;
                        break;
                    }
                }
                if (!is_conflict) {
                    color[i] = j;
                    break;
                }
            }
        }
    }

    // Resolve conflicts and increment min_color if necessary
    bool conflicts_exist = true;
    while (conflicts_exist) {
        conflicts_exist = false;
        for (int i = 0; i < num_vertices; ++i) {
            if (accumulate(adjacency_matrix[i].begin(), adjacency_matrix[i].end(), 0) < heuristic_value && color[i] == 0) {
                for (int j = 1; j <= min_color; ++j) {
                    bool is_conflict = false;
                    for (int k = 0; k < num_vertices; ++k) {
                        if (adjacency_matrix[i][k] && color[k] == j) {
                            is_conflict = true;
                            break;
                        }
                    }
                    if (!is_conflict) {
                        color[i] = j;
                        conflicts_exist = true;
                        break;
                    }
                }
            }
        }
        if (conflicts_exist) {
            ++min_color;
        }
    }

    return color;
}

// Function to divide the graph into two subsets
pair<vector<vector<int>>,vector<vector<int>>> divide_graph(const vector<vector<int>>& adjacency_matrix) {
       int num_vertices = adjacency_matrix.size();
        int mid = num_vertices / 2;
       vector<vector<int>> left_adjacency_matrix(adjacency_matrix.begin(), adjacency_matrix.begin() + mid);
        vector<vector<int>> right_adjacency_matrix(adjacency_matrix.begin() + mid, adjacency_matrix.end());
        return make_pair(left_adjacency_matrix, right_adjacency_matrix);
}

// Function to merge colors of two subsets
vector<int> merge_colors(const vector<int>& left_colors, const vector<int>& right_colors) {
   int num_vertices = left_colors.size() + right_colors.size(); // Total number of vertices in both subsets
    vector<int> merged_colors(num_vertices, 0);

    // Copy colors from left subset
    for (int i = 0; i < left_colors.size(); ++i) {
        merged_colors[i] = left_colors[i];
    }

    // Copy colors from right subset, adjusting index by the size of left subset
    for (int i = 0; i < right_colors.size(); ++i) {
        merged_colors[i + left_colors.size()] = right_colors[i];
    }

    return merged_colors;
}

// Function to resolve conflicts between subsets
vector<int> resolve_conflicts(const vector<vector<int>>& left_adjacency_matrix, const vector<vector<int>>& right_adjacency_matrix,
                                   const vector<int>& left_colors, const vector<int>& right_colors) {
       vector<int> merged_colors = merge_colors(left_colors, right_colors);
       vector<int> final_colors = merged_colors;

    return final_colors;
}

// Function to recursively color the graph using divide and conquer
      vector<int> color_graph_divide_and_conquer(const vector<vector<int>>& adjacency_matrix, double heuristic_value) {
    int num_vertices = adjacency_matrix.size();

    if (num_vertices <= 100) {
        return color_graph(adjacency_matrix, heuristic_value);
    }

    auto subsets = divide_graph(adjacency_matrix);
    const auto& left_adjacency_matrix = subsets.first;
    const auto& right_adjacency_matrix = subsets.second;

    double left_heuristic = calculate_median_degree(left_adjacency_matrix);
    double right_heuristic = calculate_median_degree(right_adjacency_matrix);

        vector<int> left_colors = color_graph_divide_and_conquer(left_adjacency_matrix, left_heuristic);
        vector<int> right_colors = color_graph_divide_and_conquer(right_adjacency_matrix, right_heuristic);

    return resolve_conflicts(left_adjacency_matrix, right_adjacency_matrix, left_colors, right_colors);
}

int main() {
    // Input parameters
    int num_vertices;  // Number of vertices
    cout<<"No of Vertices for Graph:"<<endl;
     cin >> num_vertices;
    cout<<"Constructing grapgh by making an adjacency matrix:"<<endl;

    // Generate adjacency matrix
    vector<vector<int>> adjacency_matrix = generate_adjacency_matrix(num_vertices);

    // Calculate the median degree of the graph
    double mean_degree = calculate_median_degree(adjacency_matrix);

    // Color the graph using divide and conquer strategy
     vector<int> colors = color_graph_divide_and_conquer(adjacency_matrix, mean_degree);

    // // Print the adjacency matrix
    //  cout << "Adjacency Matrix:" <<endl;
    // for (const auto& row : adjacency_matrix) {
    //     for (int val : row) {
    //         cout << val << " ";
    //     }
    //      cout <<endl;
    // }
cout<<endl;
cout<<"No of edges is :"<<num_edges<<endl;
    // Print the colors of vertices
    cout << "\nColors of Vertices:" << endl;
    int maxcol=0;
    for (int i = 0; i < num_vertices; ++i) {
        //  cout << "Vertex " << i << ": Color " << colors[i] <<endl;
         maxcol=max(maxcol,colors[i]);
    }
    cout<<"Total no of colors used is :"<<maxcol<<endl;
    return 0;
}
