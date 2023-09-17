#include <iostream>
#include <vector>
#include <queue>
#include <climits>

#define INFINITY INT_MAX

using namespace std;

struct Graph
{
    int V;
    vector<vector<int>> adjacency;
    vector<bool> visited;
    vector<int> distances;

    vector<int> police_stations;
};

struct my_copmare
{
    bool operator() (pair<int,int> p1, pair<int,int> p2) {
        return p1.second > p2.second;
    }
};

void initialize_graph(Graph &g, int V) {
    g.V = V;
    g.adjacency.resize(V);
    g.visited.resize(V, false);
    g.distances.resize(V, INFINITY);
}

void add_edge(Graph &g, int u, int v) {
    g.adjacency[u].push_back(v);
    g.adjacency[v].push_back(u);
}

void add_police_station(Graph &g, int u) {
    g.police_stations.push_back(u);
}

void dajikstra(Graph &g) {
    priority_queue<pair<int,int>, vector<pair<int,int>>, my_copmare> min_heap;

    for (int x : g.police_stations) {
        g.distances[x] = 0;
        min_heap.push(make_pair(x, g.distances[x]));
    }

    pair<int,int> tmp_pair;
    while (min_heap.size()) {
        tmp_pair = min_heap.top();
        min_heap.pop();

        if (g.visited[tmp_pair.first] == true)
            continue;
        g.visited[tmp_pair.first] = true;

        for (int neig : g.adjacency[tmp_pair.first]) {
            if (g.distances[neig] > g.distances[tmp_pair.first] + 1) {
                g.distances[neig] = g.distances[tmp_pair.first] + 1;
                min_heap.push(make_pair(neig, g.distances[neig]));
            }
        }
    }

    cout << "Police stations: ";
    for (int x : g.police_stations)
        cout << x << " ";

    cout << "\n";
    for (int i = 0; i < g.V; i++)
        cout << i << ": " << g.distances[i] << "\n";
}

int main() {
    Graph g;
    initialize_graph(g, 7);

    add_edge(g, 0, 1);
    add_edge(g, 0, 5);
    add_edge(g, 1, 2);
    add_edge(g, 1, 5);
    add_edge(g, 2, 3);
    add_edge(g, 2, 4);
    add_edge(g, 2, 5);
    add_edge(g, 3, 4);
    add_edge(g, 2, 6);

    add_police_station(g, 0);
    add_police_station(g, 4);

    dajikstra(g);

    return 0;
}
