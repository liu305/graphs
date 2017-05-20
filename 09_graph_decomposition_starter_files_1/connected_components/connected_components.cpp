#include <iostream>
#include <vector>

using std::vector;
using std::pair;

struct vertex {
    vector<int> adjacent;
    bool visited=false;
    int label;
};

void explore(int index, int label, vector<vertex> &graph)
{
    graph[index].visited=true;
    graph[index].label = label;
    for (auto &x : graph[index].adjacent) if (graph[x].visited==false)
        explore(x,label,graph);
}

int number_of_components(vector<vertex> &graph) {
  int res = 0;
    for (int i = 0; i<graph.size(); ++i) if (graph[i].visited==false)
    {
        explore(i,res,graph);
        ++res;
    }
  return res;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vertex> graph(n);
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        graph[x-1].adjacent.push_back(y-1);
        graph[y-1].adjacent.push_back(x-1);
    }
    std::cout << number_of_components(graph);
}
