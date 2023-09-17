#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <stack>

#define INFINITY 999999999999

struct Graph
{
  vector<vector<pair<int, int>>> adjacency_list;
  int V;
  vector<int> distances;
  vector<int> parents;
};

void initialize_graph (Graph &g, int V)
{
  g.V = V;
  g.adjacency_list.resize(V);
  g.distances.resize(V, INFINITY);
  g.parents.resize(V, -1);
}

void add_edge(Graph &g, int u, int v, int weight)
{
  g.adjacency_list[u].push_back(make_pair(v, weight));
}

void bellman_ford(Graph &g, int u) {
    g.distances[u] = 0;

    // V - 1 put
    for (int j = 0; j < g.V - 1; j++) {
        // Prolazimo kroz sve grane
        for (int i = 0; i < g.V; i++) {
            for (auto p : g.adjacency_list[i]) {
                if (g.distances[p.first] > g.distances[i] + p.second) {
                    g.distances[p.first] = g.distances[i] + p.second;
                    g.parents[p.first] = i;
                }
            }
        }
    }

    for (int i = 0; i < g.V; i++) {
        cout << i << ": " << g.distances[i] << "\n";
    }
}

int main ()
{
  Graph g;

  initialize_graph(g, 6);

  add_edge(g, 0, 1, 4);
  add_edge(g, 0, 2, 5);
  add_edge(g, 0, 3, 6);
  add_edge(g, 1, 2, -3);
  add_edge(g, 2, 5, 4);
  add_edge(g, 3, 4, 2);
  add_edge(g, 4, 5, 2);
  add_edge(g, 5, 4, 1);

  bellman_ford(g, 0);

  return 0;
}
