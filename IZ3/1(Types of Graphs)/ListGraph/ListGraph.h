#ifndef GRAPHS_LISTGRAPH_H
#define GRAPHS_LISTGRAPH_H

#include "IGraph.h"
#include <vector>
#include "cassert"

using std::vector;

class ListGraph : public IGraph {
public:
    explicit ListGraph(int count);

    explicit ListGraph(const IGraph &graph);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    vector<vector<int>> adjList;
};


#endif //GRAPHS_LISTGRAPH_H
