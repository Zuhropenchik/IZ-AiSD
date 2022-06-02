#include "SetGraph.h"

SetGraph::SetGraph(int count) {
    adjList.resize(count);
}

SetGraph::SetGraph(const IGraph &graph) {
    adjList.resize(graph.VerticesCount());
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        for(auto &j: graph.GetNextVertices(i))
        adjList[i].insert(j);
    }
}

void SetGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < adjList.size());
    assert(to >= 0 && to < adjList.size());
    adjList[from].insert(to);
}

int SetGraph::VerticesCount() const {
    return adjList.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjList.size());
    vector<int> temp;
    for(auto &i: adjList[vertex]){
        temp.emplace_back(i);
    }
    return temp;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjList.size());
    vector<int> prevVertices;
    for (int from = 0; from < adjList.size(); ++from) {
        for (auto& i: adjList[from]) {
            if(i==vertex)
                prevVertices.push_back(from);
        }
    }
    return prevVertices;
}
