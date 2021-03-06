//
// Created by Huawei on 02.06.2022.
//

#ifndef GRAPHS_ARCGRAPH_H
#define GRAPHS_ARCGRAPH_H
#include "IGraph.h"
#include "cassert"

class ArcGraph : public IGraph {
public:
    explicit ArcGraph(int count);
    explicit ArcGraph(const IGraph& graph);

    void AddEdge(int from, int to) override;

    int VerticesCount() const  override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;
private:
    vector<int> vertices;
    vector<std::pair<int,int>> edges;
};


#endif //GRAPHS_ARCGRAPH_H
