#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Graph
{
    int V;
    vector<vector<int>> adjacency;
    vector<bool> visited;
    vector<int> colors;
};

void initialize_graph(Graph &g, int V) {
    g.V = V;
    g.adjacency.resize(V);
    g.visited.resize(V, false);
    g.colors.resize(V, -1);
}

void add_edge(Graph &g, int u, int v) {
    g.adjacency[u].push_back(v);
    g.adjacency[v].push_back(u);
}

bool BFS(Graph &g, int u) {
    queue<int> red;

    g.visited[u] = true;
    g.colors[u] = 1;
    red.push(u);

    int tmp_node;
    while (red.size()) {
        tmp_node = red.front();
        red.pop();

        for (int neig : g.adjacency[tmp_node]) {
            if (!g.visited[neig]) {
                g.visited[neig] = true;
                g.colors[neig] = !g.colors[tmp_node];
                red.push(neig);
            }
            else if (g.colors[neig] == g.colors[tmp_node]) {
                return false;
            }
        }
    }

    return true;
}

int main() {
      Graph g;
    initialize_graph(g, 6);

    add_edge(g, 0, 1);
    add_edge(g, 1, 2);
    add_edge(g, 2, 3);
    add_edge(g, 3, 4);
    add_edge(g, 4, 5);
    add_edge(g, 5, 0);
    // Dodati ovu granu u graf i videti rezultat
//     add_edge(g, 2, 0);

    cout << "Bipartitni: " << boolalpha << BFS(g, 0) << "\n";

    return 0;
}
