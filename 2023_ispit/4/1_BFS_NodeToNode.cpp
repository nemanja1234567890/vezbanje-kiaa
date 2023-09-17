#include <iostream>
#include <vector>
#include <queue>
#include <stack>

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

    int tmp_node;
    bool path_found = false;
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
        cout << "Ne postoji putanja\n";
        return;
    }

    stack<int> stek;
    int node = v;
    while (node != -1) {
        stek.push(node);
        node = g.parents[node];
    }

    int n = stek.size();
    int x;
    while (n) {
        x = stek.top();
        stek.pop();

        if (n > 1)
            cout << x << " -> ";
        else
            cout << x << "\n";

        n--;
    }
}



int main() {
    Graph g;
    initialize_graph(g, 8);

    add_edge(g, 0, 1);
    add_edge(g, 0, 3);
    add_edge(g, 1, 2);
    add_edge(g, 3, 4);
    add_edge(g, 3, 7);
    add_edge(g, 4, 5);
    add_edge(g, 4, 6);
    add_edge(g, 4, 7);
    add_edge(g, 5, 6);
    add_edge(g, 6, 7);

    int u, v;
    cout << "Unesi cvorove: ";
    cin >> u >> v;

    BFS(g, u, v);

    return 0;
}
