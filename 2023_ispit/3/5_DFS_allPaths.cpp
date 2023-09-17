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
}

void DFS(Graph &g, int u, int v, vector<int> path) {
    if (u == v) {
        path.push_back(v);
        for (int x : path)
            cout << x << " ";
        cout << "\n";

        return;
    }

    g.visited[u] = true;
    path.push_back(u);
    for (int neig : g.adjacency[u]) {
        if (!g.visited[neig])
            DFS(g, neig, v, path);
    }

    g.visited[u] = false;
}

int main() {
    Graph g;
    initialize_graph(g, 4);

    add_edge(g, 0, 1);
    add_edge(g, 0, 2);
    add_edge(g, 0, 3);
    add_edge(g, 2, 0);
    add_edge(g, 2, 1);
    add_edge(g, 1, 3);
    // skloni komentar da vidis rezultat
//     add_edge(g, 2, 3);

    int u, v;
    cout << "Unesi cvorove u, v: ";
    cin >> u >> v;

    vector<int> path;
    cout << "Sve putanje:\n";
    DFS(g, u, v, path);

    return 0;
}
