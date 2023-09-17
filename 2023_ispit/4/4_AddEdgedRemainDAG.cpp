#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Graph
{
    int V;
    vector<vector<int>> adjacency;
    vector<bool> visited;
    vector<int> in_degrees;
    vector<int> topological_sort;

    vector<pair<int, int>> added_edges;
};

void initialize_graph(Graph &g, int V) {
    g.V = V;
    g.adjacency.resize(V);
    g.visited.resize(V, false);
    g.in_degrees.resize(V, 0);
}

void add_edge(Graph &g, int u, int v) {
    g.adjacency[u].push_back(v);
    g.in_degrees[v]++;
}

void topological_kan(Graph &g) {
    queue<int> red;

    for (int i = 0; i < g.V; i++) {
        if (g.in_degrees[i] == 0)
            red.push(i);
    }

    int tmp_node;
    while (red.size()) {
        tmp_node = red.front();
        red.pop();

        g.topological_sort.push_back(tmp_node);

        for (int neig : g.adjacency[tmp_node]) {
            g.in_degrees[neig]--;

            if (g.in_degrees[neig] == 0)
                red.push(neig);
        }
    }
}

void dodaj_grane(Graph &g) {
    topological_kan(g);

    int x_val, y_val;
    for (int i = 0; i < g.V - 1; i++) {
        x_val = g.topological_sort[i];
        for (int xx : g.adjacency[x_val])
            g.visited[xx] = true;

        for (int j = i + 1; j < g.V; j++) {
            y_val = g.topological_sort[j];

            if (g.visited[y_val] == false) {
                g.added_edges.push_back(make_pair(x_val, y_val));
            }

            g.visited[y_val] = false;
        }
    }

    for (auto &iter : g.added_edges)
        cout << iter.first << " -> " << iter.second << "\n";
}

int main() {
    Graph g;
    initialize_graph(g, 6);

    add_edge(g, 2, 3);
    add_edge(g, 3, 1);
    add_edge(g, 4, 0);
    add_edge(g, 4, 1);
    add_edge(g, 5, 0);
    add_edge(g, 5, 2);

    dodaj_grane(g);

    return 0;
}
