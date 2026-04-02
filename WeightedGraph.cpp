#include "WeightedGraph.h"
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

WeightedGraph::WeightedGraph(int vertices) {
    V = vertices;
    adj.resize(V);
}

void WeightedGraph::addEdge(int from, int to, int weight) {
    adj[from].push_back({to, weight});
}

void WeightedGraph::printGraph() const {
    for (int i = 0; i < V; i++) {
        std::cout << i << ": ";
        for (auto edge : adj[i]) {
            std::cout << "(" << edge.to << ", " << edge.weight << ") ";
        }
        std::cout << "\n";
    }
}

std::vector<int> WeightedGraph::dijkstra(int src) const {
    std::vector<int> dist(V, INT_MAX);
    std::vector<int> prev(V, -1);

    std::priority_queue
        std::pair<int,int>,
        std::vector<std::pair<int,int>>,
        std::greater<std::pair<int,int>>
    > pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto edge : adj[u]) {
            int v = edge.to;
            int w = edge.weight;

            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.push({dist[v], v});
            } else if (dist[u] != INT_MAX && dist[u] + w == dist[v] && u < prev[v]) {
                prev[v] = u;
            }
        }
    }

    return dist;
}

void WeightedGraph::printShortestPaths(int src) const {
    std::vector<int> dist = dijkstra(src);

    for (int i = 0; i < V; i++) {
        std::cout << src << " -> " << i << " : ";
        if (dist[i] == INT_MAX)
            std::cout << "INF";
        else
            std::cout << dist[i];
        std::cout << "\n";
    }
}

std::vector<int> WeightedGraph::getPath(int src, int dest) const {
    std::vector<int> dist(V, INT_MAX);
    std::vector<int> prev(V, -1);

    std::priority_queue
        std::pair<int,int>,
        std::vector<std::pair<int,int>>,
        std::greater<std::pair<int,int>>
    > pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto edge : adj[u]) {
            int v = edge.to;
            int w = edge.weight;

            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.push({dist[v], v});
            } else if (dist[u] != INT_MAX && dist[u] + w == dist[v] && u < prev[v]) {
                prev[v] = u;
            }
        }
    }

    if (src == dest) return {src};
    if (dist[dest] == INT_MAX) return {};

    std::vector<int> path;
    for (int cur = dest; cur != -1; cur = prev[cur]) {
        path.push_back(cur);
    }

    std::reverse(path.begin(), path.end());
    return path;
}

void WeightedGraph::printPath(int src, int dest) const {
    std::vector<int> path = getPath(src, dest);

    std::cout << "Path " << src << " -> " << dest << " : ";

    if (path.empty()) {
        std::cout << "UNREACHABLE\n";
        return;
    }

    for (int i = 0; i < (int)path.size(); i++) {
        if (i > 0) std::cout << " -> ";
        std::cout << path[i];
    }
    std::cout << "\n";
}
