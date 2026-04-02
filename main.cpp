#include "weighted_graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>

using namespace std;

void printPath(WeightedGraph& graph, int src, int dst) {
    if (graph.getDistance(dst) == INT_MAX) {
        cout << "No path from " << src << " to " << dst << endl;
        return;
    }
    
    cout << "Path from " << src << " to " << dst << ": ";
    
    // Build path by following parents
    vector<int> path;
    int current = dst;
    
    while (current != -1) {
        path.push_back(current);
        current = graph.getParent(current);
    }
    
    // Print in reverse order (from src to dst)
    for (int i = path.size() - 1; i >= 0; i--) {
        cout << path[i];
        if (i > 0) cout << " -> ";
    }
    cout << endl;
    
    cout << "Total cost: " << graph.getDistance(dst) << endl;
}

int main() {
    // Create a weighted graph with 5 vertices
    WeightedGraph graph(5);
    
    // Add edges based on the example in the lab
    // A=0, B=1, C=2, D=3, E=4
    graph.addEdge(0, 1, 2);  // A -> B (cost 2)
    graph.addEdge(0, 2, 1);  // A -> C (cost 1)
    graph.addEdge(1, 3, 4);  // B -> D (cost 4)
    graph.addEdge(2, 3, 2);  // C -> D (cost 2)
    graph.addEdge(2, 4, 1);  // C -> E (cost 1)
    graph.addEdge(4, 3, 1);  // E -> D (cost 1)
    
    cout << "=== Weighted Graph ===" << endl;
    graph.printGraph();
    cout << endl;
    
    cout << "=== Dijkstra's Algorithm ===" << endl;
    int source = 0;
    graph.dijkstra(source);
    
    // Print distances from source
    cout << "Shortest distances from node " << source << ":" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "To node " << i << ": ";
        if (graph.getDistance(i) == INT_MAX) {
            cout << "INF" << endl;
        } else {
            cout << graph.getDistance(i) << endl;
        }
    }
    cout << endl;
    
    // Print paths to all nodes
    for (int i = 0; i < 5; i++) {
        if (i != source) {
            printPath(graph, source, i);
            cout << endl;
        }
    }
    
    // Write output to file
    ofstream outfile("output.txt");
    if (outfile.is_open()) {
        outfile << "=== Weighted Graph ===" << endl;
        outfile << "Vertices: 5" << endl;
        outfile << "Edges:" << endl;
        outfile << "0 -> 1 (2)" << endl;
        outfile << "0 -> 2 (1)" << endl;
        outfile << "1 -> 3 (4)" << endl;
        outfile << "2 -> 3 (2)" << endl;
        outfile << "2 -> 4 (1)" << endl;
        outfile << "4 -> 3 (1)" << endl;
        outfile << endl;
        
        outfile << "=== Dijkstra's Shortest Path from Node 0 ===" << endl;
        for (int i = 0; i < 5; i++) {
            outfile << "To node " << i << ": ";
            if (graph.getDistance(i) == INT_MAX) {
                outfile << "INF" << endl;
            } else {
                outfile << graph.getDistance(i) << endl;
            }
        }
        outfile << endl;
        
        for (int i = 1; i < 5; i++) {
            outfile << "Path to node " << i << ": ";
            vector<int> path;
            int current = i;
            while (current != -1) {
                path.push_back(current);
                current = graph.getParent(current);
            }
            for (int j = path.size() - 1; j >= 0; j--) {
                outfile << path[j];
                if (j > 0) outfile << " -> ";
            }
            outfile << " (Cost: " << graph.getDistance(i) << ")" << endl;
        }
        
        outfile.close();
        cout << "Output written to output.txt" << endl;
    }
    
    return 0;
}