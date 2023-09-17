#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Graph
{
    int V;
    vector<vector<int>> adjacency;
    vector<int> in_degrees;
};

void initialize_graph(Graph &g, int V) {
    g.V = V;
    g.adjacency.resize(V);
    g.in_degrees.resize(V, 0);
}

void add_edge(Graph &g, int u, int v) {
    g.adjacency[u].push_back(v);
    g.in_degrees[v]++;
}

void topological_kan(Graph &g) {
    queue<int> red;

    for (int i = 0; i < g.V; i++) {
        if (!g.in_degrees[i])
            red.push(i);
    }

    int tmp_node;
    while (red.size()) {
        tmp_node = red.front();
        red.pop();

        cout << tmp_node << " ";

        for (int neig : g.adjacency[tmp_node]) {
            g.in_degrees[neig]--;

            if (!g.in_degrees[neig])
                red.push(neig);
        }
    }
    cout << "\n";
}

int main() {
    Graph g;
    initialize_graph(g, 6);

    add_edge(g, 0, 1);
    add_edge(g, 1, 4);
    add_edge(g, 2, 4);
    add_edge(g, 3, 0);
    add_edge(g, 3, 2);
    add_edge(g, 5, 3);
    add_edge(g, 5, 4);

    cout << "Topoloski(Kan): ";
    topological_kan(g);

    return 0;
}
