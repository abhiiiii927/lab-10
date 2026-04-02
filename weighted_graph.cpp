#include "weighted_graph.h"
#include <iostream>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

WeightedGraph::WeightedGraph(int vertices) {
    this->vertices = vertices;
    adjList.resize(vertices);
    distance.resize(vertices, INT_MAX);
    parent.resize(vertices, -1);
    solved.resize(vertices, false);
    minCost = INT_MAX;
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
        for (auto& edge : adjList[i]) {
            cout << "-> " << edge.dest << "(" << edge.weight << ") ";
        }
        cout << endl;
    }
}

void WeightedGraph::dijkstra(int src) {
    // Min-heap priority queue: (distance, node)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    // Initialize
    for (int i = 0; i < vertices; i++) {
        distance[i] = INT_MAX;
        parent[i] = -1;
        solved[i] = false;
    }
    
    distance[src] = 0;
    pq.push(make_pair(0, src));
    
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        if (solved[u]) {
            continue;
        }
        
        solved[u] = true;
        
        // Check all neighbors of u
        for (auto& edge : adjList[u]) {
            int v = edge.dest;
            int weight = edge.weight;
            
            if (!solved[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
                pq.push(make_pair(distance[v], v));
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

int WeightedGraph::getMinCost() {
    int minDist = INT_MAX;
    for (int i = 0; i < vertices; i++) {
        if (distance[i] < minDist) {
            minDist = distance[i];
        }
    }
    return minDist;
}

bool WeightedGraph::isSolved(int node) {
    return solved[node];
}