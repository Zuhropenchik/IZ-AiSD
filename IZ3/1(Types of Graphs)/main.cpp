#include <iostream>
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "ArcGraph.h"
#include "SetGraph.h"
void BFS(const IGraph &graph, int vertex, void (*visit)(int)) {
    vector<bool> visited(graph.VerticesCount(), false);
    queue<int> bfsQueue;
    bfsQueue.push(vertex);
    visited[vertex] = true;
    while (!bfsQueue.empty()) {
        int current = bfsQueue.front();
        bfsQueue.pop();
        visit(current);
        vector<int> adjList = graph.GetNextVertices(current);
        for (int i = 0; i < adjList.size(); ++i) {
            if (!visited[adjList[i]]) {
                bfsQueue.push(adjList[i]);
                visited[adjList[i]] = true;
            }
        }

    }
}
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
    BFS(*graph, 2, [](int v){std::cout << v << ' ';});
    delete graph;
    return 0;
}
