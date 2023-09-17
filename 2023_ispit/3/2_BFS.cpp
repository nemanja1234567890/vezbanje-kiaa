#include <iostream>
#include <vector>
#include <queue>

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

void BFS(Graph &g, int u) {
    queue<int> red;

    g.visited[u] = true;
    red.push(u);

    int tmp_node;
    while (red.size()) {
        tmp_node = red.front();
        red.pop();

        cout << tmp_node << " ";

       for (int neig : g.adjacency[tmp_node]) {
            if (!g.visited[neig]) {
                g.visited[neig] = true;
                red.push(neig);
            }
       }
    }
}

int main() {
    Graph g;
    initialize_graph(g, 6);

    add_edge(g, 0, 1);
    add_edge(g, 0, 2);
    add_edge(g, 1, 2);
    add_edge(g, 2, 0);
    add_edge(g, 2, 3);
    add_edge(g, 3, 3);

    int u;
    cout << "u = ";
    cin >> u;

    cout << "BFS: ";
    BFS(g, u);
    cout << "\n";

    return 0;
}
