#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::pair;

struct single_vertex {
    bool visited=false;
    int post_order = 0;
    vector<int> adj;
    static int clock_num;
};
int single_vertex::clock_num = 1;

void explore(single_vertex &one, vector<single_vertex> &graph, bool do_po=false){
    one.visited=true;
    for (auto &x : one.adj) if (!graph[x].visited) {
        explore(graph[x],graph,do_po);
    }
    if (do_po) {
        one.post_order = single_vertex::clock_num;
        ++single_vertex::clock_num;
    }
}

vector<int> toposort(vector<single_vertex> &graph) {
    vector<int> order (graph.size());
    size_t n(0);
    std::generate(std::begin(order),std::end(order),[&]{return n++;});
    for (auto &x : graph) if (!x.visited) {
        explore(x,graph,true);
    }
    std::sort(std::begin(order),std::end(order),[&](int i1, int i2) {return graph[i1].post_order > graph[i2].post_order;});
    return order;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<single_vertex> graph(n);
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        graph[x - 1].adj.push_back(y - 1);
    }
    vector<int> order = toposort(graph);
    for (size_t i = 0; i < order.size(); i++) {
        std::cout << order[i] + 1 << " ";
    }
}
