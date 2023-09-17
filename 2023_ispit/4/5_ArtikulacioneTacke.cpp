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

set<int> art_tacke;
void DFS(Graph &g, int u) {
    g.visited[u] = true;
    g.times[u] = g.lower_times[u] = g.time;
    g.time++;

    int children = 0;
    for (int neig : g.adjacency[u]) {
        if (!g.visited[neig]) {
            g.parents[neig] = u;
            DFS(g, neig);

            children++;
            g.lower_times[u] = min(g.lower_times[u], g.lower_times[neig]);

            if (g.parents[u] == -1 && children > 1)
                art_tacke.insert(u);
            if (g.parents[u] != -1 && g.times[u] <= g.lower_times[neig])
                art_tacke.insert(u);
        }
        else if (neig != g.parents[u]) {
            g.lower_times[u] = min(g.lower_times[u], g.times[neig]);
        }
    }
}

void ispisi_tacke(Graph &g) {
    DFS(g, 0);
    cout << "Artikulacione tacke: ";
    for (int x : art_tacke)
        cout << x << " ";
    cout << "\n";
}

int main() {
    Graph g;

    // art_tacke: 0 3
//      initialize_graph(g, 5);
//      add_edge(g, 0, 2);
//      add_edge(g, 0, 3);
//      add_edge(g, 1, 0);
//      add_edge(g, 2, 1);
//      add_edge(g, 3, 4);

         // art_tacke: 2 3 4 5
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

        // art_tacke: nema
//     initialize_graph(g, 5);
//     add_edge(g, 0, 1);
//     add_edge(g, 0, 2);
//     add_edge(g, 1, 2);
//     add_edge(g, 2, 3);
//     add_edge(g, 3, 1);
//     add_edge(g, 4, 0);
//     add_edge(g, 4, 1);

        // art_tacke: nema
    initialize_graph(g, 4);
    add_edge(g, 0, 1);
    add_edge(g, 0, 3);
    add_edge(g, 1, 2);
    add_edge(g, 2, 3);

     ispisi_tacke(g);

    return 0;
}
