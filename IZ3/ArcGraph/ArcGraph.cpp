#include "ArcGraph.h"
ArcGraph::ArcGraph(int count) {
    vertices.resize(count);
}

ArcGraph::ArcGraph(const IGraph &graph) {
    vertices.resize(graph.VerticesCount());
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        vector<int> temp = graph.GetNextVertices(i);
        for(int j = 0; j< temp.size(); ++j){
            edges.emplace_back(std::pair<int,int>(i, j));
        }
    }
}

void ArcGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < vertices.size());
    assert(to >= 0 && to < vertices.size());
    edges.emplace_back(std::pair<int, int>(from, to));
}

int ArcGraph::VerticesCount() const {
    return vertices.size();
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < vertices.size());
    vector<int> temp;
        for(auto& i: edges){
        if( i.first == vertex)
            temp.push_back(i.second);
    }
    return temp;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < vertices.size());
    vector<int> temp;
    for (auto &i: edges) {
        if (i.second == vertex)
            temp.push_back(i.first);
    }
    return temp;
}
