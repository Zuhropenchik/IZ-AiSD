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
    SetGraph(int count);
    SetGraph(const IGraph& graph);

    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const  override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;
    virtual std::vector<int> GetPrevVertices(int vertex) const override;
private:
    vector<unordered_set<int>> adjList;
};


#endif //GRAPHS_SETGRAPH_H
