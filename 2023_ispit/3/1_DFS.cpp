#include<iostream>
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
}

void DFS(Graph &g, int u) {
    cout << u << " ";
    g.visited[u] = true;

    for (int neig : g.adjacency[u])
        if (g.visited[neig] == false)
            DFS(g, neig);
}

int main() {
    Graph g;
    initialize_graph(g, 4);

    add_edge(g, 0, 1);
    add_edge(g, 0, 2);
    add_edge(g, 1, 2);
    add_edge(g, 2, 0);
    add_edge(g, 2, 3);
    add_edge(g, 3, 3);

    int u;
    cout << "u = ";
    cin >> u;

    cout << "DFS: ";
    DFS(g, u);
    cout << "\n";

    return 0;
}
