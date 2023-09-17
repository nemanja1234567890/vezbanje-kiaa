#include <iostream>
#include <vector>

using namespace std;

struct Graph
{
    int V;
    vector<vector<int>> adjacency;
    vector<bool> visited;
};

void initialize_graph(Graph &g, int V) {
    g.V = V;
    g.adjacency.resize(V);
    g.visited.resize(V, false);
}

void add_edge(Graph &g, int u, int v) {
    g.adjacency[u].push_back(v);
    g.adjacency[v].push_back(u);
}

void DFS(Graph &g, int u) {
    g.visited[u] = true;

    for (int neig : g.adjacency[u])
        if (!g.visited[neig])
            DFS(g, neig);
}

void br_komponenti(Graph &g) {
    int brojac = 0;
    for (int i = 0; i < g.V; i++) {
        if (!g.visited[i]) {
            DFS(g, i);
            brojac++;
        }
    }

    cout << "Broj komponenti: " << brojac << "\n";
}

int main() {
    Graph g;
    initialize_graph(g, 6);

    add_edge(g, 0, 1);
    add_edge(g, 0, 2);
    add_edge(g, 1, 2);
    add_edge(g, 2, 3);
    add_edge(g, 3, 3);
    add_edge(g, 4, 5);
    add_edge(g, 4, 4);
    add_edge(g, 5, 4);
    // Dodaj ovu granu da vidis rezultat
    add_edge(g, 3, 4);

    br_komponenti(g);

    return 0;
}
