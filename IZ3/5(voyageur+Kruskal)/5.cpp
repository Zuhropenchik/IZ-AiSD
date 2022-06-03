#include <iostream>
#include<vector>
#include<cassert>
#include<algorithm>

using std::pair;
using std::vector;

class DSU {
public:
    explicit DSU(int count);

    int findParent(int v);

    void Union(int v1, int v2);

private:
    vector<int> parent;

};

DSU::DSU(int count) : parent(count) {
    for (int i = 0; i < parent.size(); ++i)
        parent[i] = i;
}

int DSU::findParent(int v) {
    if (v == parent[v])
        return v;
    parent[v] = findParent(parent[v]);
    return parent[v];
}

void DSU::Union(int v1, int v2) {
    int p1 = findParent(v1);
    int p2 = findParent(v2);
    if (p1 == p2)
        return;
    parent[p2] = p1;
}

struct IGraph {
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to, int weight) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<std::pair<int, int>> GetNextVertices(int vertex) const = 0;

    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;

    int minimumSpanningTree();

protected:
    bool isOriented;
};


using std::vector;

class ListGraph : public IGraph {
public:
    explicit ListGraph(int count);

    void AddEdge(int from, int to, int weight) override;

    int VerticesCount() const override;

    std::vector<std::pair<int, int>> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    vector<vector<pair<int, int>>> adjList;
};

ListGraph::ListGraph(int count) {
    adjList.resize(count);
    isOriented = false;
}

void ListGraph::AddEdge(int from, int to, int weight) {
    assert(from >= 0 && from < adjList.size());
    assert(to >= 0 && to < adjList.size());
    adjList[from].push_back(std::make_pair(to, weight));
    if (!isOriented) {
        adjList[to].push_back(std::make_pair(from, weight));
    }
}

int ListGraph::VerticesCount() const {
    return adjList.size();
}

std::vector<std::pair<int, int>> ListGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjList.size());
    return adjList[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjList.size());
    vector<int> prevVertices;
    for (int from = 0; from < adjList.size(); ++from) {
        for (int i = 0; i < adjList[from].size(); ++i) {
            if (adjList[from][i].first == vertex)
                prevVertices.push_back(from);
        }
    }
    return prevVertices;
}

struct Edge {
    int first;
    int second;
    int weight;

    Edge(int _f, int _s, int _w) : first(_f), second(_s), weight(_w) {}

    Edge(const Edge &e) : first(e.first), second(e.second), weight(e.weight) {}
};

bool EdgeCompare(const Edge &e1, const Edge &e2) {
    return e1.weight < e2.weight;
}

int IGraph::minimumSpanningTree() {
    DSU dsu(VerticesCount());
    vector<Edge> edges;
    for (int i = 0; i < VerticesCount(); i++) {
        vector<pair<int, int>> getNext = GetNextVertices(i);
        for (auto& j: getNext) {
                edges.emplace_back(Edge(i, j.first, j.second));
        }
    }
    bool (*cmp)(const Edge &, const Edge &) = &EdgeCompare;
    std::sort(edges.begin(), edges.end(), cmp);
    int result = 0;
    for(auto& i: edges){
        if(dsu.findParent(i.first) != dsu.findParent(i.second)){
            dsu.Union(i.first, i.second);
            result+= i.weight;
        }
    }
    return result;
}

int main() {
    int verticesCount, edgesCount;
    std::cin >> verticesCount;
    IGraph *graph = new ListGraph(verticesCount);
    std::cin >> edgesCount;
    for (int i = 0; i < edgesCount; ++i) {
        int to, from, weight;
        std::cin >> from >> to >> weight;
        graph->AddEdge(from-1, to-1, weight);
    }
    std::cout << graph->minimumSpanningTree();
    delete graph;
    return 0;
}
