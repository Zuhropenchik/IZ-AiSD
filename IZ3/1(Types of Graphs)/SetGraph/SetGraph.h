#ifndef GRAPHS_SETGRAPH_H
#define GRAPHS_SETGRAPH_H

#include"IGraph.h"
#include<unordered_map>
#include<unordered_set>
#include"cassert"

using std::unordered_map;
using std::unordered_set;

class SetGraph : public IGraph {
public:
    explicit SetGraph(int count);

    explicit SetGraph(const IGraph &graph);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    vector<unordered_set<int>> adjList;
};


#endif //GRAPHS_SETGRAPH_H
