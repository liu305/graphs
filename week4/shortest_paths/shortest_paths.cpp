#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

struct single_vertex{
    vector<int> adj;
    vector<int> cost;
    int dist = std::numeric_limits<int>::max();
    int elem_dist = -1;
    int prev = -1;
};

void shortest_paths(vector<single_vertex> &graph, int index, vector<long long> &distance,
    vector<int> &reachable, vector<int> &shortest) {
    queue<int> tmp_queue;
    for (auto &elem : graph) {
        elem.dist = std::numeric_limits<int>::max();
        elem.elem_dist = -1;
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
                tmp_queue.push(graph[i].adj[j]);
                graph[graph[i].adj[j]].elem_dist = 0;
            }
        }
    }
    int tmp_index;
    while (!tmp_queue.empty())
    {
        tmp_index = tmp_queue.front();
        tmp_queue.pop();
        for (auto &adj_index : graph[tmp_index].adj) if (graph[adj_index].elem_dist==-1)
        {
            tmp_queue.push(adj_index);
            graph[adj_index].elem_dist = graph[tmp_index].elem_dist + 1;
        }
    }
    for (int i = 0; i<graph.size(); ++i)
    {
        if (graph[i].elem_dist != -1) {shortest[i]=0;}
        if (graph[i].dist != std::numeric_limits<int>::max()) {reachable[i]=1;}
        distance[i]=graph[i].dist;
    }
}

int main() {
    int n, m, s;
    std::cin >> n >> m;
    vector<single_vertex> graph;
    graph.resize(n);
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        graph[x-1].adj.push_back(y - 1);
        graph[x-1].cost.push_back(w);
    }
    std::cin >> s;
    s--;
    vector<long long> distance(n, std::numeric_limits<long long>::max());
    vector<int> reachable(n, 0);
    vector<int> shortest(n, 1);
    shortest_paths(graph, s, distance, reachable, shortest);
    for (int i = 0; i < n; i++) {
        if (!reachable[i]) {
            std::cout << "*\n";
        } else if (!shortest[i]) {
            std::cout << "-\n";
        } else {
            std::cout << distance[i] << "\n";
        }
    }
}
