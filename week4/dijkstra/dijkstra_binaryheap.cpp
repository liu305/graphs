#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using std::vector;
using std::queue;
using std::pair;

struct single_vertex{
    vector<std::pair<int,int>> adj_cost;
    int dist = std::numeric_limits<int>::max();
    int prev = -1;
};

int distance(vector<single_vertex> &graph, int s, int t)
{
    graph[s].dist=0;
    vector<std::pair<int,int>> tmp_queue;
    for (int i = 0; i < graph.size(); ++i)
    {
        tmp_queue.push_back(std::make_pair(i,graph[i].dist));
    }
    std::make_heap (tmp_queue.begin(),tmp_queue.end(),[](std::pair<int,int> &a1, std::pair<int,int> &a2){return a1.second>a2.second;});
    int tmp_index;
    while (!tmp_queue.empty()){
        tmp_index = tmp_queue.front().first;
        std::pop_heap(tmp_queue.begin(),tmp_queue.end());
        tmp_queue.pop_back();
        for (auto &elem_edge : graph[tmp_index].adj_cost){
            if ((graph[elem_edge.first].dist > graph[tmp_index].dist + elem_edge.second) & (graph[tmp_index].dist != std::numeric_limits<int>::max()))
            {
                graph[elem_edge.first].dist = graph[tmp_index].dist + elem_edge.second;
                graph[elem_edge.first].prev = tmp_index;
                for (int i = 0; i<tmp_queue.size(); ++i) if (tmp_queue[i].first == elem_edge.first){
                    tmp_queue[i].second = graph[elem_edge.first].dist;
                }
                std::make_heap (tmp_queue.begin(),tmp_queue.end(),[](std::pair<int,int> &a1, std::pair<int,int> &a2){return a1.second<a2.second;});
            }
        }
    }
    return ((graph[t].dist == std::numeric_limits<int>::max()) ? -1 : graph[t].dist);
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<single_vertex> graph;
    graph.resize(n);
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        graph[x-1].adj_cost.push_back(std::make_pair(y-1,w));
    }
    int s, t;
    std::cin >> s >> t;
    s--, t--;
    std::cout << distance(graph, s, t);
}
