#include <iostream>
#include <vector>
#include <queue>
#include <climits>

#define INFINITY INT_MAX

using namespace std;

struct Graph
{
    int V;
    int **matrix;
    // vektor koji govori koji cvorovi su ukljuceni
    vector<bool> included_in_mst;
    vector<int> parents;
    // vektor koji govori tezine grana koje su ukljucene
    vector<int> edge_weig;
};

void initialize_graph(Graph &g, int V) {
    g.V = V;

    g.matrix = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++)
        g.matrix[i] = (int*)calloc(sizeof(int), V);

    g.included_in_mst.resize(V, false);
    g.parents.resize(V, -1);
    g.edge_weig.resize(V, INFINITY);
}

void add_edge(Graph &g, int u, int v, int w) {
    g.matrix[u][v] = w;
    g.matrix[v][u] = w;
}

int min_edge_not_included(Graph &g) {
    int min = INFINITY;
    int min_index = -1;

    for (int i = 0; i < g.V; i++) {
        if (g.included_in_mst[i] == false && g.edge_weig[i] < min) {
            min_index = i;
            min = g.edge_weig[i];
        }
    }

    return min_index;
}

void prim(Graph &g, int u) {
    // posto krecemo od 0
    g.edge_weig[u] = 0;

    int node;
    // MST ima ukupno n-1 granu pa zbog toga idemo do n-1
    for (int i = 0; i < g.V - 1; i++) {
        node = min_edge_not_included(g);
        g.included_in_mst[node] = true;

        for (int v = 0; v < g.V; v++) {
            // postoji grana, nije ukljucen taj cvor, vrednost je manja od trenutne
            if (g.matrix[node][v] && g.included_in_mst[v] == false && g.matrix[node][v] < g.edge_weig[v]) {
                g.parents[v] = node;
                g.edge_weig[v] = g.matrix[node][v];
            }
        }
    }

    // Cena MST je na pocetku 0
    int cena = 0;
    for (int i = 0; i < g.V; i++) {
        if (i != u)
            cena += g.edge_weig[i];
    }
    cout << "Cena primov: " << cena << "\n";
}

int main() {
    Graph g;
    initialize_graph(g, 5);

    add_edge(g, 0, 1, 1);
    add_edge(g, 0, 2, 5);
    add_edge(g, 0, 3, 10);
    add_edge(g, 0, 4, 4);
    add_edge(g, 1, 2, 2);
    add_edge(g, 1, 4, 1);
    add_edge(g, 2, 3, 4);

    // rez = 8
    prim(g, 0);

    return 0;
}
