#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Graph
{
    int V;
    vector<vector<int>> adjacency;
    vector<int> in_degrees;
    vector<int> pos_in_topological;

    vector<pair<int, int>> added_edges;
    vector<pair<int, int>> undirected_edges;
};

void initialize_graph(Graph &g, int V) {
    g.V = V;
    g.adjacency.resize(V);
    g.in_degrees.resize(V, 0);
    g.pos_in_topological.resize(V, -1);
}

void add_directed_edge(Graph &g, int u, int v) {
    g.adjacency[u].push_back(v);
    g.in_degrees[v]++;
}

void add_undirected_edge(Graph &g, int u, int v) {
    g.undirected_edges.push_back(make_pair(u, v));
}

void topological_kan(Graph &g) {
    queue<int> red;

    for (int i = 0; i < g.V; i++) {
        if (!g.in_degrees[i])
            red.push(i);
    }

    int tmp_node;
    int brojac = 0;
    while (red.size()) {
        tmp_node = red.front();
        red.pop();

        g.pos_in_topological[tmp_node] = brojac;
        brojac++;

        for (int neig : g.adjacency[tmp_node]) {
            g.in_degrees[neig]--;

            if (!g.in_degrees[neig])
                red.push(neig);
        }
    }
}

void usmeri(Graph &g) {
    int x_val, y_val, x_pos, y_pos;

    topological_kan(g);
    for (auto &u_edge : g.undirected_edges) {
        x_val = u_edge.first;
        y_val = u_edge.second;

        x_pos = g.pos_in_topological[x_val];
        y_pos = g.pos_in_topological[y_val];

        if (x_pos < y_pos) {
            g.added_edges.push_back(make_pair(x_val, y_val));
        }
        else {
            g.added_edges.push_back(make_pair(y_val, x_val));
        }
    }

    for (auto &edge : g.added_edges)
        cout << edge.first << " -> " << edge.second << "\n";
}

int main() {
    Graph g;
    initialize_graph(g, 6);

    add_directed_edge(g, 0, 1);
    add_directed_edge(g, 0, 5);
    add_directed_edge(g, 1, 2);
    add_directed_edge(g, 1, 3);
    add_directed_edge(g, 1, 4);
    add_directed_edge(g, 2, 3);
    add_directed_edge(g, 2, 4);
    add_directed_edge(g, 3, 4);
    add_directed_edge(g, 5, 1);
    add_directed_edge(g, 5, 2);

    add_undirected_edge(g, 0, 2);
    add_undirected_edge(g, 0, 3);
    add_undirected_edge(g, 4, 5);

    // 0 -> 2
    // 0 -> 3
    // 4 <- 5
    usmeri(g);

    return 0;
}
