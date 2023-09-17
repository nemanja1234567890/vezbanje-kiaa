#include <iostream>
#include <vector>
#include <set>

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

int brojac = 0;
void DFS(Graph &g, int u) {
    g.visited[u] = true;
    g.times[u] = g.lower_times[u] = g.time;
    g.time++;

    int children = 0;
    for (int neig : g.adjacency[u]) {
        if (!g.visited[neig]) {
            g.parents[neig] = u;
            DFS(g, neig);

            g.lower_times[u] = min(g.lower_times[u], g.lower_times[neig]);
            children++;

            if (g.parents[u] != -1 && g.times[u] <= g.lower_times[neig])
                brojac++;
            if (g.parents[u] == -1 && children > 1)
                brojac++;
        }
        else if (neig != g.parents[u]) {
            g.lower_times[u] = min(g.lower_times[u], g.times[neig]);
        }
    }
}

void ispisiIzlaz(Graph &g) {
    DFS(g, 0);

    if (brojac > 0) {
        cout << "NIJE bipartitni\n";
        return;
    }

    for (int i = 0; i < g.V; i++) {
        if (!g.visited[i]) {
            cout << "NIJE bipartitni\n";
            return;
        }
    }

    cout << "JESTE bipartitni\n";
}

int main() {
    Graph g;

//     initialize_graph(g, 5);
//     add_edge(g, 1, 0);
//     add_edge(g, 0, 2);
//     add_edge(g, 2, 1);
//     add_edge(g, 0, 3);
//     add_edge(g, 3, 4);
//     add_edge(g, 2, 4);


    initialize_graph(g, 5);
    add_edge(g, 1, 0);
    add_edge(g, 0, 2);
    add_edge(g, 2, 1);
    add_edge(g, 0, 3);
    add_edge(g, 3, 4);

    ispisiIzlaz(g);

    return 0;
}
