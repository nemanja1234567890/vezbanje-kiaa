#include <iostream>
#include <vector>
#include <queue>
#include <climits>

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

void add_edge(Graph &g, int u, int v, int w) {
    g.adjacency[u].push_back(make_pair(v, w));
    g.adjacency[v].push_back(make_pair(u, w));
}

int dajikstra(Graph &g, int u, int v, int avoid) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, my_compare> min_heap;

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
            if (iter.first == avoid)
                continue;

            if (g.distances[iter.first] > g.distances[tmp_pair.first] + iter.second) {
                g.distances[iter.first] = g.distances[tmp_pair.first] + iter.second;
                min_heap.push(make_pair(iter.first, g.distances[iter.first]));
            }
        }
    }

    return g.distances[v];
}

void reset_graph(Graph &g) {
    fill(g.distances.begin(), g.distances.end(), INFINITY);
    fill(g.visited.begin(), g.visited.end(), false);
}

int avion_preko(Graph &g, int u, int v, int middle) {
    int rez = dajikstra(g, u, middle, -1);
    reset_graph(g);
    rez += dajikstra(g, middle, v, -1);

    return rez;
}

int avion_izbegni(Graph &g, int u, int v, int avoid) {
    return dajikstra(g, u, v, avoid);
}

int main() {
    Graph g;
    initialize_graph(g, 5);

    add_edge(g, 0, 1, 10);
    add_edge(g, 0, 2, 2);
    add_edge(g, 1, 3, 9);
    add_edge(g, 2, 3, 7);
    add_edge(g, 2, 4, 5);
    add_edge(g, 3, 4, 6);

    // Najkraci put od cvora 0 do cvora 1 preko cvora 4             rez = 22
//     cout << "Avion 0 do 1 preko 4: " << avion_preko(g, 0, 1, 4) << "\n";

    // Najkraci put od cvora 0 do cvora 3 izbegavajuci cvor 2       rez = 19
    cout << "Avion 0 do 3 izbeaga 2: " << avion_izbegni(g, 0, 3, 2) << "\n";


    return 0;
}
