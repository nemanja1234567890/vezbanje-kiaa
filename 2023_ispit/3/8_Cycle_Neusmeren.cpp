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

bool BFS(Graph &g, int u) {
    queue<int> red;

    g.visited[u] = true;
    red.push(u);

    int tmp_node;
    while (red.size()) {
        tmp_node = red.front();
        red.pop();

        for (int neig : g.adjacency[tmp_node]) {
            if (!g.visited[neig]) {
                g.visited[neig] = true;
                g.parents[neig] = tmp_node;
                red.push(neig);
            }
            else if (neig != g.parents[tmp_node]) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    Graph g;

    // true
    initialize_graph(g, 4);
    add_edge(g, 0, 1);
    add_edge(g, 0, 2);
    add_edge(g, 1, 2);
    add_edge(g, 2, 3);
    add_edge(g, 3, 0);

    // false
//     initialize_graph(g, 3);
//     add_edge(g, 0, 1);
//     add_edge(g, 1, 2);

    cout << "Ciklus NEusmeren: " << boolalpha << BFS(g, 0) << "\n";

    return 0;
}
