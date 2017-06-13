#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>

using std::vector;


struct single_vertex {
    double x=0;
    double y=0;
    double cost = std::numeric_limits<double>::max();
    int parent = -1;
};

double distance(single_vertex &a1, single_vertex &a2)
{
    return sqrt((a1.x - a2.x)*(a1.x-a2.x)+(a1.y-a2.y)*(a1.y-a2.y));
}

double minimum_distance(vector<single_vertex> &graph) {
    for (int i=0;i<graph.size();++i)
    {
        graph[i].cost = std::numeric_limits<int>::max();
        graph[i].parent = -1;
    }
    graph[0].cost=0;
    vector<int> index_queue(graph.size());
    int n = 0;
    std::generate(index_queue.begin(),index_queue.end(),[&]{return n++;});
    std::make_heap (index_queue.begin(),index_queue.end(),[&](int a1, int a2)
                    {return graph[a1].cost > graph[a2].cost;});
    int tmp_index;
    while (!index_queue.empty())
    {
        tmp_index = index_queue.front();
        std::pop_heap(index_queue.begin(),index_queue.end());
        index_queue.pop_back();
        vector<int> tmp_index_queue = index_queue;
        for (auto &elem: tmp_index_queue)
            if (graph[elem].cost > distance(graph[tmp_index],graph[elem]))
            {
                graph[elem].cost = distance(graph[tmp_index],graph[elem]);
                graph[elem].parent = tmp_index;
                std::make_heap (index_queue.begin(),index_queue.end(),[&](int a1, int a2)
                                {return graph[a1].cost > graph[a2].cost;});
            }
    }
    double total_distance=0;
    for (int i=1;i<graph.size();++i)
    {
        total_distance+=distance(graph[graph[i].parent],graph[i]);
    }
    return total_distance;
} 

int main() {
    size_t n;
    std::cin >> n;
    vector<single_vertex> graph;
    graph.resize(n);
    for (size_t i = 0; i < n; ++i)
    {
        std::cin >> graph[i].x >> graph[i].y;
    }
    std::cout << std::setprecision(10) << minimum_distance(graph) << std::endl;
}
