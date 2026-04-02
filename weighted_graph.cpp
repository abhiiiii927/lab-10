#include "weighted_graph.h"
#include <iostream>
#include <queue>
#include <climits>

using namespace std;

WeightedGraph::WeightedGraph(int vertices) {
    this->vertices = vertices;
    adjList.resize(vertices);
    distance.resize(vertices, INT_MAX);
    parent.resize(vertices, -1);
    solved.resize(vertices, false);
}

void WeightedGraph::addEdge(int src, int dest, int weight) {
    weighted_edge edge;
    edge.dest = dest;
    edge.weight = weight;
    adjList[src].push_back(edge);
}

void WeightedGraph::printGraph() {
    for (int i = 0; i < vertices; i++) {
        cout << "Node " << i << ": ";
        for (auto &edge : adjList[i]) {
            cout << "-> " << edge.dest << "(" << edge.weight << ") ";
        }
        cout << endl;
    }
}

void WeightedGraph::dijkstra(int src) {
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    for (int i = 0; i < vertices; i++) {
        distance[i] = INT_MAX;
        parent[i] = -1;
        solved[i] = false;
    }

    distance[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (solved[u]) continue;
        solved[u] = true;

        for (auto &edge : adjList[u]) {
            int v = edge.dest;
            int w = edge.weight;

            if (!solved[v] && distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
                parent[v] = u;
                pq.push({distance[v], v});
            }
        }
    }
}

int WeightedGraph::getDistance(int node) {
    return distance[node];
}

int WeightedGraph::getParent(int node) {
    return parent[node];
}

bool WeightedGraph::isSolved(int node) {
    return solved[node];
}
