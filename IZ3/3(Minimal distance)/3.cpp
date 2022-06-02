#include <iostream>
#include<vector>
#include<queue>
#include<cassert>
using std::pair;
using std::vector;
using std::queue;

struct IGraph {
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to, int weight) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<std::pair<int, int>> GetNextVertices(int vertex) const = 0;

    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;

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
//    for(auto& i: GetNextVertices(from)){
//        if(i.first == to) {
//            if(i.second > weight) {
//                i.second = weight;
//                if(!isOriented) {
//                    for (auto &j: GetNextVertices(to)) {
//                        if (j.first == from) {
//                            j.second = weight;
//                        }
//                    }
//                }
//            }
//            return;
//        }
//    }
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
int minimum_distance(const IGraph &graph, int source, int destination) {
    vector<int> minDist(graph.VerticesCount(), 0);
    queue<int> tempQueue;
    tempQueue.push(source);
    minDist[source] = 0;
    int current = 0;
    while (!tempQueue.empty()) {
        current = tempQueue.front();
        tempQueue.pop();
        for (auto &i: graph.GetNextVertices(current)) {
            if ((minDist[i.first] == 0 && i.first != source) || minDist[i.first] > minDist[current] + i.second) {
                minDist[i.first] = minDist[current] + i.second;
                tempQueue.push(i.first);
            }
        }
    }
    return minDist[destination];
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
