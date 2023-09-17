#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <stack>

#define INFINITY INT_MAX

using namespace std;

struct Graph
{
    int V;
    vector<vector<pair<int,int>>> adjacency;
    vector<bool> visited;
    vector<int> distances_weig;
    vector<int> distances_edges;
    vector<int> parents;
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
    g.distances_edges.resize(V, INFINITY);
    g.distances_weig.resize(V, INFINITY);
    g.parents.resize(V, -1);
}

void add_edge(Graph &g, int u, int v, int weig) {
    g.adjacency[u].push_back(make_pair(v, weig));
    g.adjacency[v].push_back(make_pair(u, weig));
}

void dajikstra(Graph &g, int u, int v) {
    priority_queue<pair<int,int>, vector<pair<int,int>>, my_compare> min_heap;

    g.distances_edges[u] = 0;
    g.distances_weig[u] = 0;
    min_heap.push(make_pair(u, g.distances_weig[u]));

    pair<int,int> tmp_pair;
    while (min_heap.size()) {
        tmp_pair = min_heap.top();
        min_heap.pop();

        if (g.visited[tmp_pair.first] == true)
            continue;
        g.visited[tmp_pair.first] = true;


        for (auto &iter : g.adjacency[tmp_pair.first]) {
            if (g.distances_weig[iter.first] > g.distances_weig[tmp_pair.first] + iter.second ||
                (g.distances_weig[iter.first] == g.distances_weig[tmp_pair.first] + iter.second &&
                 g.distances_edges[iter.first] > g.distances_edges[tmp_pair.first] + 1
                )
            ) {
                g.distances_weig[iter.first] = g.distances_weig[tmp_pair.first] + iter.second;
                g.distances_edges[iter.first] = g.distances_edges[tmp_pair.first] + 1;
                g.parents[iter.first] = tmp_pair.first;

                min_heap.push(make_pair(iter.first, g.distances_weig[iter.first]));
            }
        }
    }



    cout << "Izlaz: ";
    int node = v;
    stack<int> stek;
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
            cout << x << " ";

        n--;
    }
    cout << g.distances_weig[v] << "\n";
}

int main() {
    Graph g;
    initialize_graph(g, 9);

    add_edge(g, 0, 1, 4);
    add_edge(g, 0, 7, 8);
    add_edge(g, 1, 7, 11);
    add_edge(g, 1, 2, 8);
    add_edge(g, 2, 8, 3);
    add_edge(g, 2, 3, 7);
    add_edge(g, 7, 8, 7);
    add_edge(g, 7, 6, 1);
    add_edge(g, 8, 6, 6);
    add_edge(g, 2, 5, 4);
    add_edge(g, 6, 5, 2);
    add_edge(g, 3, 5, 14);
    add_edge(g, 3, 4, 9);
    add_edge(g, 4, 5, 10);

    // najkraci put od 0 do 8,     REZ: 0 -> 7 -> 8 (15)
    dajikstra(g, 0, 8);

    return 0;
}
