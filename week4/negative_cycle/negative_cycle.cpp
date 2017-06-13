#include <iostream>
#include <vector>
#include <limits>

using std::vector;

struct single_vertex{
    vector<int> adj;
    vector<int> cost;
    int dist = std::numeric_limits<int>::max();
    int prev = -1;
};

int naive(vector<single_vertex> &graph, int index)
{
    for (auto &elem : graph) {
        elem.dist = std::numeric_limits<int>::max();
        elem.prev = -1;
    }
    graph[index].dist = 0;
    for (int counter = 0; counter < graph.size()-1; ++counter)
    {
        for (int i = 0; i < graph.size(); ++i){
            for (int j = 0; j < graph[i].adj.size(); ++j)
            {
                if ((graph[graph[i].adj[j]].dist > graph[i].dist + graph[i].cost[j]) & (graph[i].dist != std::numeric_limits<int>::max())){
                    graph[graph[i].adj[j]].dist = graph[i].dist + graph[i].cost[j];
                    graph[graph[i].adj[j]].prev = i;
                }
            }
        }
    }
    for (int i = 0; i < graph.size(); ++i){
        for (int j = 0; j < graph[i].adj.size(); ++j)
        {
            if ((graph[graph[i].adj[j]].dist > graph[i].dist + graph[i].cost[j]) & (graph[i].dist != std::numeric_limits<int>::max())){
                return 1;
            }
        }
    }
    return 0;
}

int negative_cycle(vector<single_vertex> &graph) {
    for (int i = 0; i < graph.size(); ++i)
        if (naive(graph,i) == 1){
            return 1;
        }
    return 0;
}


int main() {
    int n, m;
    std::cin >> n >> m;
    vector<single_vertex> graph;
    graph.resize(n);
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        graph[x-1].adj.push_back(y - 1);
        graph[x-1].cost.push_back(w);
    }
    std::cout << negative_cycle(graph);
}
