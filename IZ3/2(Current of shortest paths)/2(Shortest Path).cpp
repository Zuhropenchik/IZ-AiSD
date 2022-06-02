#include <iostream>
#include<vector>
#include<queue>
#include<cassert>

using std::vector;
using std::queue;

struct IGraph {
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;

    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;

protected:
    bool isOriented;
};


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

ListGraph::ListGraph(int count) {
    adjList.resize(count);
    isOriented = false;
}

ListGraph::ListGraph(const IGraph &graph) {
    adjList.resize(graph.VerticesCount());
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        adjList[i] = graph.GetNextVertices(i);
    }
}

void ListGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < adjList.size());
    assert(to >= 0 && to < adjList.size());
    adjList[from].push_back(to);
    if (!isOriented)
        adjList[to].push_back(from);
}

int ListGraph::VerticesCount() const {
    return adjList.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjList.size());
    return adjList[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjList.size());
    vector<int> prevVertices;
    for (int from = 0; from < adjList.size(); ++from) {
        for (int i = 0; i < adjList[from].size(); ++i) {
            if (adjList[from][i] == vertex)
                prevVertices.push_back(from);
        }
    }
    return prevVertices;
}

int currentOfShortestPaths(const IGraph &graph, int source, int destination) {
    if(source == destination)
        return 0;
    vector<int> count(graph.VerticesCount(), 0);
    vector<int> min_distance(graph.VerticesCount(), 0);
    queue<int> bfsQueue;
    bfsQueue.push(source);
    count[source] = 1;
    while (!bfsQueue.empty()) {
        int current = bfsQueue.front();
        bfsQueue.pop();
        vector<int> adjList = graph.GetNextVertices(current);
        for (auto &i: adjList) {
            if (count[i]==0) {
                min_distance[i] = min_distance[current] + 1;
                count[i]+=count[current];
                bfsQueue.push(i);
            } else if (min_distance[current] + 1 == min_distance[i])
                count[i]+=count[current];
            else if (min_distance[current] + 1 < min_distance[i]){
                count[i] = count[current];
                min_distance[i] = min_distance[current] + 1;
            }
        }
    }
    return count[destination];
}

int main() {
    int verticesCount, edgesCount;
    std::cin >> verticesCount;
    IGraph *graph = new ListGraph(verticesCount);
    std::cin >> edgesCount;
    for (int i = 0; i < edgesCount; ++i) {
        int to, from;
        std::cin >> from >> to;
        graph->AddEdge(from, to);
    }
    int source, destination;
    std::cin >> source >> destination;
    std::cout << currentOfShortestPaths(*graph, source, destination);
    delete graph;
    return 0;
}