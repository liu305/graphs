#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

struct single_vertex{
    vector<int> adj;
    int dist = -1;
};

int distance(vector<single_vertex> &graph, int s, int t) {
    for (auto &elem : graph) {
        elem.dist=-1;
    }
    graph[s].dist=0;
    queue<int> tmp_queue;
    tmp_queue.push(s);
    int tmp_index;
    while (!tmp_queue.empty()){
        tmp_index = tmp_queue.front();
        tmp_queue.pop();
        for (auto &adj_index : graph[tmp_index].adj) if (graph[adj_index].dist==-1){
            tmp_queue.push(adj_index);
            graph[adj_index].dist = graph[tmp_index].dist + 1;
        }
    }
    return graph[t].dist;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<single_vertex> graph;
    graph.resize(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        graph[x-1].adj.push_back(y-1);
        graph[y-1].adj.push_back(x-1);
    }
    int s, t;
    std::cin >> s >> t;
    s--, t--;
    std::cout << distance(graph, s, t);
}
