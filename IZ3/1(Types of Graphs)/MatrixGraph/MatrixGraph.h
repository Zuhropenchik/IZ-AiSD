#ifndef GRAPHS_MATRIXGRAPH_H
#define GRAPHS_MATRIXGRAPH_H

#include "IGraph.h"
#include "cassert"

class MatrixGraph : public IGraph {
public:
    explicit MatrixGraph(int count);

    explicit MatrixGraph(const IGraph &graph);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    vector<int> GetNextVertices(int vertex) const override;

    vector<int> GetPrevVertices(int vertex) const override;

private:
    vector<vector<int>> matrix;
};


#endif //GRAPHS_MATRIXGRAPH_H
