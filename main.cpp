#include "weighted_graph.h"
#include <iostream>
#include <fstream>
#include <climits>
#include <vector>

using namespace std;

void printPath(WeightedGraph& graph, int src, int dst) {
    if (graph.getDistance(dst) == INT_MAX) {
        cout << "No path from " << src << " to " << dst << endl;
        return;
    }

    vector<int> path;
    int current = dst;

    while (current != -1) {
        path.push_back(current);
        current = graph.getParent(current);
    }

    cout << "Path from " << src << " to " << dst << ": ";

    for (int i = path.size() - 1; i >= 0; i--) {
        cout << path[i];
        if (i > 0) cout << " -> ";
    }

    cout << "\nTotal cost: " << graph.getDistance(dst) << endl;
}

int main() {
    WeightedGraph graph(5);

    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 2, 1);
    graph.addEdge(1, 3, 4);
    graph.addEdge(2, 3, 2);
    graph.addEdge(2, 4, 1);
    graph.addEdge(4, 3, 1);

    cout << "=== Graph ===" << endl;
    graph.printGraph();

    int source = 0;
    graph.dijkstra(source);

    cout << "\n=== Shortest Distances ===" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "To node " << i << ": ";
        if (graph.getDistance(i) == INT_MAX)
            cout << "INF";
        else
            cout << graph.getDistance(i);
        cout << endl;
    }

    cout << "\n=== Paths ===" << endl;
    for (int i = 0; i < 5; i++) {
        if (i != source) {
            printPath(graph, source, i);
            cout << endl;
        }
    }

    return 0;
}
