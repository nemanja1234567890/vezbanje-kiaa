#include <iostream>
#include <vector>

using namespace std;

struct Graph
{
    int V;
    vector<vector<int>> adjacency;
    vector<bool> visited;
    vector<int> parents;

    int time;
    vector<int> times;
    vector<int> lower_times;
};

void initialize_graph(Graph &g, int V) {
    g.V = V;
    g.adjacency.resize(V);
    g.visited.resize(V, false);
    g.parents.resize(V, -1);

    g.time = 0;
    g.times.resize(V, -1);
    g.lower_times.resize(V, -1);
}

void add_edge(Graph &g, int u, int v) {
    g.adjacency[u].push_back(v);
    g.adjacency[v].push_back(u);
}

void DFS(Graph &g, int u) {
    g.visited[u] = true;
    g.times[u] = g.lower_times[u] = g.time;
    g.time++;

    for (int neig : g.adjacency[u]) {
        if (!g.visited[neig]) {
            g.parents[neig] = u;
            DFS(g, neig);

            g.lower_times[u] = min(g.lower_times[u], g.lower_times[neig]);

            if (g.times[u] < g.lower_times[neig])
                cout << u << " -> " << neig << "\n";
        }
        else if (neig != g.parents[u]) {
            g.lower_times[u] = min(g.lower_times[u], g.times[neig]);
        }
    }
}

int main() {
    Graph g;

     // Mosotvi: 3->4, 0->3
//      initialize_graph(g, 5);
//      add_edge(g, 0, 2);
//      add_edge(g, 0, 3);
//      add_edge(g, 1, 0);
//      add_edge(g, 2, 1);
//      add_edge(g, 3, 4);

       // Mosotvi: 5->7, 3->4, 2->3
//     initialize_graph(g, 8);
//     add_edge(g, 0, 1);
//     add_edge(g, 0, 2);
//     add_edge(g, 1, 2);
//     add_edge(g, 2, 3);
//     add_edge(g, 3, 4);
//     add_edge(g, 4, 5);
//     add_edge(g, 4, 6);
//     add_edge(g, 5, 6);
//     add_edge(g, 5, 7);

       // Mosotvi: nema
//     initialize_graph(g, 5);
//     add_edge(g, 0, 1);
//     add_edge(g, 0, 2);
//     add_edge(g, 1, 2);
//     add_edge(g, 2, 3);
//     add_edge(g, 3, 1);
//     add_edge(g, 4, 0);
//     add_edge(g, 4, 1);

      // Mosotvi: nema
    initialize_graph(g, 4);
    add_edge(g, 0, 1);
    add_edge(g, 0, 3);
    add_edge(g, 1, 2);
    add_edge(g, 2, 3);

     cout << "Mostovi:\n";
     DFS(g, 0);

    return 0;
}
