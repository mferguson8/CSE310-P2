#include "Edge.h"
#include <iostream>
#include <limits>
#include <string>
#include <sstream>

using namespace std;

// Define MAX_VERTICES as a constant
const int MAX_VERTICES = 9999;

// Declare Graph structure and functions outside main
struct Graph {
    int numOfVertices;
    bool adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];

    //Initialize matrix
    Graph(int vertices) : numOfVertices(vertices) {
        for (int i = 0; i < numOfVertices; ++i) {
            for (int j = 0; j < numOfVertices; ++j) {
                adjacencyMatrix[i][j] = false;
            }
        }
    }

    // Method to add an edge to the graph
    void addEdge(int startVertex, int endVertex) {
        adjacencyMatrix[startVertex - 1][endVertex - 1] = true;
        adjacencyMatrix[endVertex - 1][startVertex - 1] = true;
    }
};

// Function to print the adjacency matrix of the graph
void printAdjacencyMatrix(Graph &graph) {
    cout << "\t\tThe adjacency matrix of G:\n";
    for (int i = 0; i < graph.numOfVertices; ++i) {
        for (int j = 0; j < graph.numOfVertices; ++j) {
            cout << graph.adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to print the odd degree vertices in the graph
void printOddDegreeVertices(Graph &graph) {
    cout << "\t\tThe odd degree vertices in G:\nO = { ";
    for (int i = 0; i < graph.numOfVertices; ++i) {
        int degree = 0;
        for (int j = 0; j < graph.numOfVertices; ++j) {
            if (graph.adjacencyMatrix[i][j]) {
                degree++;
            }
        }
        if (degree % 2 != 0) {
            cout << i + 1 << " ";
        }
    }
    cout << "}\n";
}

// Function to implement Dijkstra's algorithm
void dijkstra(Graph &graph, int startVertex) {
    const int INF = numeric_limits<int>::max();
    int dist[graph.numOfVertices];
    bool visited[graph.numOfVertices] = {false};

    for (int i = 0; i < graph.numOfVertices; ++i) {
        dist[i] = INF;
    }

    dist[startVertex - 1] = 0;

    for (int count = 0; count < graph.numOfVertices - 1; ++count) {
        int u = -1;
        for (int i = 0; i < graph.numOfVertices; ++i) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }

        visited[u] = true;

        for (int v = 0; v < graph.numOfVertices; ++v) {
            if (!visited[v] && graph.adjacencyMatrix[u][v] && dist[u] != INF &&
                dist[u] + 1 < dist[v]) {
                dist[v] = dist[u] + 1;
            }
        }
    }

    cout << "Single source shortest path lengths from node " << startVertex << endl;
    for (int i = 0; i < graph.numOfVertices; ++i) {
        cout << "  " << i + 1 << ": " << dist[i] << endl;
    }
    cout << endl;
}

int main() {
    // start of the initial pipeline that loads the test case file stream from std::cin
    int numOfVertices;
    int numOfEdges;

    if (!std::cin.eof()) {
        std::cin >> numOfVertices;
        std::cin >> numOfEdges;
    } else {
        std::cout << "Input not found!" << std::endl;
        return 0;
    }

    // Declare Graph object outside the loop
    Graph myGraph(numOfVertices);

    while (!std::cin.eof()) {
        int startVertice;
        int endVertice;
        std::cin >> startVertice;
        std::cin >> endVertice;
        Edge *newEdge = new Edge(startVertice, endVertice);
        // Here is where you load up the Graph object
        myGraph.addEdge(startVertice, endVertice);
    }

    // And here is where you start working on the three tasks
    // Call the functions to print adjacency matrix, odd degree vertices, and run Dijkstra's algorithm
    printAdjacencyMatrix(myGraph);
    printOddDegreeVertices(myGraph);
    // Assuming you have identified odd degree vertices
    for (int i = 1; i <= numOfVertices; ++i) {
        // Run Dijkstra's algorithm for each odd degree vertex
        int degreeCount = 0;

        for (int j = 0; j < numOfVertices; ++j) {
            if (myGraph.adjacencyMatrix[i - 1][j]) {
                degreeCount++;
            }
        }
        if (degreeCount % 2 != 0) {
            dijkstra(myGraph, i);
        }
    }

    return 0;
}