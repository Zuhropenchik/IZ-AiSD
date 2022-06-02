#include <iostream>
#include "ListGraph.h"
int main() {
    IGraph * graph = new ListGraph(6);
    graph->AddEdge(1,3);
    graph->AddEdge(2,1);
    graph->AddEdge(2,3);
    graph->AddEdge(2,4);
    graph->AddEdge(3,4);
    graph->AddEdge(4,5);
    graph->AddEdge(5,3);
    graph->AddEdge(5,4);
    BFS(*graph, 1, [](int v){std::cout << v << ' ';});
    delete graph;
    return 0;
}
