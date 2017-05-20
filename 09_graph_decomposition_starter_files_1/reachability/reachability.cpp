#include <iostream>
#include <vector>

using std::vector;
using std::pair;

struct vertex {
    vector<int> adjacent;
    bool visited=false;
};

void explore(int index, vector<vertex> &graph)
{
    graph[index].visited=true;
    for (auto &x : graph[index].adjacent) if (graph[x].visited==false)
        explore(x,graph);
}

int reach(vector<vertex> &graph, int x, int y) {
   explore(x,graph);
   if (graph[y].visited) {return 1;}
   else {return 0;}
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
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(graph, x - 1, y - 1);
}
