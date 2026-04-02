#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include <vector>
#include <list>
#include <climits>

struct weighted_edge {
    int dest;
    int weight;
};

class WeightedGraph {
private:
    int vertices;
    std::vector<std::list<weighted_edge>> adjList;
    std::vector<int> distance;
    std::vector<int> parent;
    std::vector<bool> solved;
    int minCost;

public:
    WeightedGraph(int vertices);
    void addEdge(int src, int dest, int weight);
    void printGraph();
    void dijkstra(int src);
    int getDistance(int node);
    int getParent(int node);
    int getMinCost();
    bool isSolved(int node);
};

#endif