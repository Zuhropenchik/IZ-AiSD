#include "MatrixGraph.h"
MatrixGraph::MatrixGraph(int count) {
    matrix.resize(count);
    for(auto& i: matrix)
        i.resize(count);
}

MatrixGraph::MatrixGraph(const IGraph &graph) {
    matrix.resize(graph.VerticesCount());
    for(auto& i: matrix)
        i.resize(graph.VerticesCount());
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        vector<int> temp = graph.GetNextVertices(i);
        for(int j = 0; j< temp.size(); ++j){
            matrix[i][temp[j]] = 1;
        }
    }
}

void MatrixGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < matrix.size());
    assert(to >= 0 && to < matrix.size());
    matrix[from][to] = 1;
}

int MatrixGraph::VerticesCount() const {
    return matrix.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < matrix.size());
    vector<int> temp;
    for(int i=0; i<VerticesCount(); ++i){
        if(matrix[vertex][i] == 1)
            temp.push_back(i);
    }
    return temp;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < matrix.size());
    vector<int> prevVertices;
    for (int from = 0; from < matrix.size(); ++from) {
            if(matrix[vertex][from]==1)
                prevVertices.push_back(from);
    }
    return prevVertices;
}
