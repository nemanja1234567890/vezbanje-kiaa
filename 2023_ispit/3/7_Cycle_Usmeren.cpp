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

bool DFS(Graph &g, int u) {
    g.visited[u] = true;

    for (int neig : g.adjacency[u]) {
        if (g.visited[neig] == true)
            return true;
        else if (DFS(g, neig))
            return true;
    }

    g.visited[u] = false;
    return false;
}

int main() {
     Graph g;

//     initialize_graph(g, 4);
//     add_edge(g, 0, 1);
//     add_edge(g, 0, 2);
//     add_edge(g, 1, 2);
//     add_edge(g, 2, 3);
//     add_edge(g, 3, 0);


    initialize_graph(g, 3);
    add_edge(g, 0, 1);
    add_edge(g, 1, 2);
    add_edge(g, 0, 2);

    cout << "Usmeren ciklus: " << boolalpha << DFS(g, 0) << "\n";


    return 0;
}
