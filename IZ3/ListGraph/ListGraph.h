#ifndef GRAPHS_LISTGRAPH_H
#define GRAPHS_LISTGRAPH_H
#include "IGraph.h"
#include <vector>
using std::vector;
class ListGraph : public IGraph {
public:
    ListGraph(int count);
    ListGraph(const IGraph& graph);

    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const  override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;
    virtual std::vector<int> GetPrevVertices(int vertex) const override;
private:
    vector<vector<int>> adjList;
    vector<vector<int>> prevList;
};


#endif //GRAPHS_LISTGRAPH_H
