#include <iostream>
#include <vector>
#include <queue>

#define INFINITY 9999

using namespace std;

struct Graph
{
    int V;
    int **matrix;
};

void initialize_graph(Graph &g, int V) {
    g.V = V;

    g.matrix = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        g.matrix[i] = (int*)calloc(sizeof(int), V);
    }

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            if (i == j)
                g.matrix[i][j] = 0;
            else
                g.matrix[i][j] = INFINITY;
}

void add_edge(Graph &g, int u, int v, int weight) {
    g.matrix[u][v] = weight;
}

void flojd_varsal(Graph &g) {
    for (int m = 0; m < g.V; m++) {
        for (int i = 0; i < g.V; i++) {
            for (int j = 0; j < g.V; j++) {
                if (g.matrix[i][j] > g.matrix[i][m] + g.matrix[m][j]) {
                    g.matrix[i][j] = g.matrix[i][m] + g.matrix[m][j];
                }
            }
        }
    }

    cout << "Izlaz: ";
    for (int i = 0; i < g.V; i++)
        if (g.matrix[i][i] == 0) {
            cout << "NO\n";
            return;
        }
    cout << "YES\n";
}


// usmeren
int main() {
    Graph g;
    initialize_graph(g, 4);

    add_edge(g, 0, 1, 1);
    add_edge(g, 1, 2, -1);
    add_edge(g, 2, 3, -1);
    add_edge(g, 3, 0, -1);

    flojd_varsal(g);

    return 0;
}
