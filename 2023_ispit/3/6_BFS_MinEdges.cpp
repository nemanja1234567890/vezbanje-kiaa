#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Graph
{
    int V;
    vector<vector<int>> adjacency;
    vector<bool> visited;
    vector<int> parents;
};

void initialize_graph(Graph &g, int V) {
    g.V = V;
    g.adjacency.resize(V);
    g.visited.resize(V, false);
    g.parents.resize(V, -1);
}

void add_edge(Graph &g, int u, int v) {
    g.adjacency[u].push_back(v);
    g.adjacency[v].push_back(u);
}

void BFS(Graph &g, int u, int v) {
    queue<int> red;

    g.visited[u] = true;
    red.push(u);

    int path_found = false;
    int tmp_node;
    while (red.size()) {
        tmp_node = red.front();
        red.pop();

        if (tmp_node == v) {
            path_found = true;
            break;
        }

        for (int neig : g.adjacency[tmp_node]) {
            if (!g.visited[neig]) {
                g.visited[neig] = true;
                g.parents[neig] = tmp_node;
                red.push(neig);
            }
        }
    }

    if (path_found == false) {
        cout << "Ne postoje grane!\n";
        return;
    }

    int node = v;
    int brojac = 0;
    while (node != -1) {
        brojac++;
        node = g.parents[node];
    }

    cout << "Minimalni broj grana: " << brojac - 1 << "\n";
}

int main() {
    Graph g;
    initialize_graph(g, 5);

    add_edge(g, 0, 1);
    add_edge(g, 1, 2);
    add_edge(g, 1, 4);
    add_edge(g, 2, 3);
    add_edge(g, 2, 4);
    add_edge(g, 3, 4);

    int u, v;
    cout << "Unesi cvorove: ";
    cin >> u >> v;

    BFS(g, u, v);

    return 0;
}
