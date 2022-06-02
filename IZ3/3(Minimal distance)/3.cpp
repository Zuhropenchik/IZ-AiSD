#include <iostream>
#include<vector>
#include<queue>
#include<cassert>

using std::vector;
using std::queue;

struct IGraph {
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to, int weight) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;

    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;

    virtual std::vector<int> GetDistances(int vertex) const = 0;

protected:
    bool isOriented;
};


using std::vector;

class ListGraph : public IGraph {
public:
    explicit ListGraph(int count);

    void AddEdge(int from, int to, int weight) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

    std::vector<int> GetDistances(int vertex) const override;

private:
    vector<vector<int>> adjList;
    vector<vector<int>> distances;
};

ListGraph::ListGraph(int count) {
    adjList.resize(count);
    distances.resize(count);
    for(auto& i: distances){
        i.resize(count);
    }
    isOriented = false;
}

void ListGraph::AddEdge(int from, int to, int weight) {
    assert(from >= 0 && from < adjList.size());
    assert(to >= 0 && to < adjList.size());
    adjList[from].push_back(to);
    distances[from][to] = weight;
    if (!isOriented) {
        adjList[to].push_back(from);
        distances[to][from] = weight;
    }
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
std::vector<int> ListGraph::GetDistances(int vertex) const{
    return distances[vertex];
}
int minimum_distance(const IGraph &graph, int source, int destination) {
    vector<bool> visited(graph.VerticesCount(), false);
    vector<int> min_dist(graph.VerticesCount(), 0);
    queue<int> bfsQueue;
    bfsQueue.push(source);
    visited[source] = true;
    while (!bfsQueue.empty()) {
        int current = bfsQueue.front();
        if(current==destination){
            return min_dist[current];
        }
        bfsQueue.pop();
        vector<int> adjList = graph.GetNextVertices(current);
        vector<int> distList = graph.GetDistances(current);
        for (int i = 0; i < adjList.size(); ++i) {
            if (!visited[adjList[i]]) {
                min_dist[i]+=distList[i];
                bfsQueue.push(adjList[i]);
                visited[adjList[i]] = true;
            }
        }
    }
    return  -1;
}

int main() {
    int verticesCount, edgesCount;
    std::cin >> verticesCount;
    IGraph *graph = new ListGraph(verticesCount);
    std::cin >> edgesCount;
    for (int i = 0; i < edgesCount; ++i) {
        int to, from, weight;
        std::cin >> from >> to >> weight;
        graph->AddEdge(from, to, weight);
    }
    int source, destination;
    std::cin >> source >> destination;
    std::cout << minimum_distance(*graph, source, destination);
    delete graph;
    return 0;
}
