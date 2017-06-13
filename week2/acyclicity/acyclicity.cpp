#include <iostream>
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

int acyclic(vector<single_vertex> &graph, vector<single_vertex> &reverse_graph) {
    int count = 0;
    vector<int> order (graph.size());
    size_t n(0);
    std::generate(std::begin(order),std::end(order),[&]{return n++;});
    for (auto &x : reverse_graph) if (!x.visited) {
        explore(x,reverse_graph,true);
    }
    for (int i = 0; i < graph.size(); ++i){
        graph[i].post_order = reverse_graph[i].post_order;
    }
    std::sort(std::begin(order),std::end(order),[&](int i1, int i2) {return graph[i1].post_order < graph[i2].post_order;});
    for (int i = graph.size()-1 ; i >=0 ; --i)
    {
        if (graph[order[i]].visited) {return 1;}
        else {
            explore(graph[order[i]],graph);
        }
    }
    return 0;

}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<single_vertex> graph(n);
    vector<single_vertex> reverse_graph(n);
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        graph[x-1].adj.push_back(y-1);
        reverse_graph[y-1].adj.push_back(x-1);
    }
    std::cout << acyclic(graph,reverse_graph);
}
