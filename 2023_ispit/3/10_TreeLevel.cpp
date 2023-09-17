#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Graph
{
    int V;
    vector<vector<int>> adjacency;
    vector<bool> visited;
    vector<int> levels;
};

void initialize_graph(Graph &g, int V) {
    g.V = V;
    g.adjacency.resize(V);
    g.visited.resize(V, false);
    g.levels.resize(V, -1);
}

void add_edge(Graph &g, int u, int v) {
    g.adjacency[u].push_back(v);
    g.adjacency[v].push_back(u);
}

void BFS(Graph &g, int u, int level) {
    queue<int> red;

    g.visited[u] = true;
    g.levels[u] = 0;
    red.push(u);

    int tmp_node;
    int brojac = 0;
    while (red.size()) {
        tmp_node = red.front();
        red.pop();

        if (level == g.levels[tmp_node]) {
            brojac++;
        }
        else if (level < g.levels[tmp_node]) {
            break;
        }

        for (int neig : g.adjacency[tmp_node]) {
            if (!g.visited[neig]) {
                g.visited[neig] = true;
                g.levels[neig] = g.levels[tmp_node] + 1;
                red.push(neig);
            }
        }
    }

    cout << "Broj cvorova: " << brojac << "\n";
}

int main() {
    Graph g;
    initialize_graph(g, 8);

    add_edge(g, 0, 1);
    add_edge(g, 0, 4);
    add_edge(g, 0, 7);
    add_edge(g, 4, 6);
    add_edge(g, 4, 5);
    add_edge(g, 4, 2);
    add_edge(g, 7, 3);

    int level;
    cout << "Unesi level: ";
    cin >> level;

    BFS(g, 0, level);

    return 0;
}
