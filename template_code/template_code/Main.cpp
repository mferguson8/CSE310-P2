#include "Edge.h"
#include <iostream>

int main() {

    // start of the initial pipeline that loads the test case file stream from std::cin

    int numOfVertices;
    int numOfEdges;

    if (!std::cin.eof()) {
        std::cin >> numOfVertices;
        std::cin >> numOfEdges;
    } else {
        std::cout << "Input not found!" << std::endl;
        return NULL;
    }

    while (!std::cin.eof()) {
        int startVertice;
        int endVertice;
        std::cin >> startVertice;
        std::cin >> endVertice;
        Edge *newEdge = new Edge(startVertice, endVertice);
        // Here is where you load up the Graph object
        const int MAX_VERTICES = 100;

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
        Graph myGraph(numOfVertices);
        myGraph.addEdge(startVertice, endVertice);
    }

    // And here is where you start working on the three tasks

    return 0;
}