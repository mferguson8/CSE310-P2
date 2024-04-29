
#include <iostream>
#include <fstream>
#include <limits>
#include "Edge.h"

using namespace std;

class Graph
{
    int V;
    int **adj;

public:
    Graph(int vertices) : V(vertices)
    {
        adj = new int *[V];
        for (int i = 0; i < V; ++i)
        {
            adj[i] = new int[V];
            for (int j = 0; j < V; ++j)
            {
                adj[i][j] = 0;
            }
        }
    }

    ~Graph()
    {
        for (int i = 0; i < V; ++i)
        {
            delete[] adj[i];
        }
        delete[] adj;
    }

    void addEdge(int u, int v)
    {
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    void printAdjacencyMatrix()
    {
        cout << "Adjacency matrix of G:" << endl;
        for (int i = 0; i < V; ++i)
        {
            for (int j = 0; j < V; ++j)
            {
                cout << adj[i][j] << " ";
            }
            cout << endl;
        }
    }

    int *findOddDegreeVertices()
    {
        int *oddVertices = new int[V];
        int count = 0;
        for (int i = 0; i < V; ++i)
        {
            int degree = 0;
            for (int j = 0; j < V; ++j)
            {
                degree += adj[i][j];
            }
            if (degree % 2 != 0)
            {
                oddVertices[count++] = i + 1;
            }
        }
        oddVertices[count] = -1; // Mark end of array
        return oddVertices;
    }

    int *dijkstra(int src)
    {
        int *dist = new int[V];
        bool *visited = new bool[V];

        for (int i = 0; i < V; ++i)
        {
            dist[i] = numeric_limits<int>::max();
            visited[i] = false;
        }

        dist[src] = 0;

        for (int count = 0; count < V - 1; ++count)
        {
            int u = minDistance(dist, visited);
            visited[u] = true;
            for (int v = 0; v < V; ++v)
            {
                if (!visited[v] && adj[u][v] && dist[u] != numeric_limits<int>::max() && dist[u] + 1 < dist[v])
                {
                    dist[v] = dist[u] + 1;
                }
            }
        }

        delete[] visited;
        return dist;
    }

private:
    int minDistance(const int *dist, const bool *visited)
    {
        int minDist = numeric_limits<int>::max();
        int minIndex = -1;
        for (int v = 0; v < V; ++v)
        {
            if (!visited[v] && dist[v] <= minDist)
            {
                minDist = dist[v];
                minIndex = v;
            }
        }
        return minIndex;
    }
};

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Usage: ./dijkstra <graph_file>" << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    if (!infile)
    {
        cout << "Error: Unable to open file " << argv[1] << endl;
        return 1;
    }

    int n, m;
    infile >> n >> m;

    Graph g(n);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        infile >> u >> v;
        g.addEdge(u - 1, v - 1);
    }

    g.printAdjacencyMatrix();

    int *oddVertices = g.findOddDegreeVertices();
    cout << "\nThe odd degree vertices in G:" << endl;
    cout << "O = { ";
    for (int i = 0; oddVertices[i] != -1; ++i)
    {
        cout << oddVertices[i] << " ";
    }
    cout << "}" << endl;

    for (int i = 0; oddVertices[i] != -1; ++i)
    {
        int vertex = oddVertices[i];
        cout << "\nSingle source shortest path lengths from node " << vertex << endl;
        int *shortestPaths = g.dijkstra(vertex - 1);
        for (int j = 0; j < n; ++j)
        {
            cout << "  " << j + 1 << ": ";
            if (shortestPaths[j] == numeric_limits<int>::max())
            {
                cout << "INF" << endl;
            }
            else
            {
                cout << shortestPaths[j] << endl;
            }
        }
        delete[] shortestPaths;
    }

    delete[] oddVertices;

    return 0;
}
