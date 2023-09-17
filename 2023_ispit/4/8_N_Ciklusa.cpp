#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct Graph
{
    int V;
    vector<vector<int>> adjacency;
    vector<bool> visited;
    int brojac;
};

void initialize_graph(Graph &g, int V) {
    g.V = V;
    g.adjacency.resize(V);
    g.visited.resize(V, false);
    g.brojac = 0;
}

void add_edge(Graph &g, int u, int v) {
    g.adjacency[u].push_back(v);
    g.adjacency[v].push_back(u);
}

void DFS(Graph &g, int u, int start, int n) {
    g.visited[u] = true;
    if (n == 0) {
        if (find(g.adjacency[u].begin(), g.adjacency[u].end(), start) != g.adjacency[u].end()) {
            g.brojac++;
        }

        g.visited[u] = false;
        return;
    }

    for (int neig : g.adjacency[u]) {
        if (!g.visited[neig])
            DFS(g, neig, start, n - 1);
    }

    g.visited[u] = false;
}

void ispisiIzlaz(Graph &g, int n) {
    for (int i = 0; i < g.V - (n - 1); i++) {
        DFS(g, i, i, n - 1);
        g.visited[i] = true;
    }

    cout << "Izlaz: " << g.brojac / 2 << "\n";
}

int main() {
    int n;
    cout << "Unesi n: ";
    cin >> n;

    Graph g;

    initialize_graph(g, 7);
    add_edge(g, 0, 1);
    add_edge(g, 1, 2);
    add_edge(g, 2, 3);
    add_edge(g, 3, 0);
    add_edge(g, 3, 4);
    add_edge(g, 4, 6);
    add_edge(g, 6, 5);
    add_edge(g, 5, 3);

//     initialize_graph(g, 5);
//     add_edge(g, 0, 1);
//     add_edge(g, 0, 3);
//     add_edge(g, 1, 2);
//     add_edge(g, 1, 4);
//     add_edge(g, 2, 3);
//     add_edge(g, 3, 4);

    ispisiIzlaz(g, n);

    return 0;
}
