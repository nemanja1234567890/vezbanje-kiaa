#include <iostream>
#include <vector>
#include <climits>
#include <queue>

#define INFINITY INT_MAX

using namespace std;

struct Graph
{
    int V;
    vector<vector<pair<int, int>>> adjacency;
    vector<bool> visited;
    vector<int> distances;
};

struct my_compare
{
    bool operator() (pair<int, int> p1, pair<int, int> p2) {
        return p1.second > p2.second;
    }
};

void initialize_graph(Graph &g, int V) {
    g.V = V;
    g.adjacency.resize(V);
    g.visited.resize(V, false);
    g.distances.resize(V, INFINITY);
}

void add_edge(Graph &g, int u, int v, int weig) {
    g.adjacency[u].push_back(make_pair(v, weig));
    g.adjacency[v].push_back(make_pair(u, weig));
}

void dajikstra(Graph &g, int u) {
    priority_queue<pair<int,int>, vector<pair<int,int>>, my_compare> min_heap;

    g.distances[u] = 0;
    min_heap.push(make_pair(u, g.distances[u]));

    pair<int, int> tmp_pair;
    while (min_heap.size()) {
        tmp_pair = min_heap.top();
        min_heap.pop();

        if (g.visited[tmp_pair.first] == true)
            continue;
        g.visited[tmp_pair.first] = true;

        for (auto &iter : g.adjacency[tmp_pair.first]) {
            if (g.distances[iter.first] > g.distances[tmp_pair.first] + iter.second) {
                g.distances[iter.first] = g.distances[tmp_pair.first] + iter.second;
                min_heap.push(make_pair(iter.first, g.distances[iter.first]));
            }
        }
    }

    for (int i = 0; i < g.V; i++)
        cout << u << " -> " << i << " = " << g.distances[i] << "\n";
}

int main() {
    Graph g;
    initialize_graph(g, 9);

    add_edge(g, 0, 1, 4);
    add_edge(g, 0, 7, 8);
    add_edge(g, 1, 7, 11);
    add_edge(g, 1, 2, 8);
    add_edge(g, 2, 8, 2);
    add_edge(g, 2, 3, 7);
    add_edge(g, 7, 8, 7);
    add_edge(g, 7, 6, 1);
    add_edge(g, 8, 6, 6);
    add_edge(g, 2, 5, 4);
    add_edge(g, 6, 5, 2);
    add_edge(g, 3, 5, 14);
    add_edge(g, 3, 4, 9);
    add_edge(g, 4, 5, 10);

    dajikstra(g, 0);

    return 0;
}
