#include <iostream>
#include <vector>
using namespace std;

struct Graph {
    int** adjMatrix;
    int numVertices;
    bool isDirected;

// Initialize all elements to 0
    Graph(int vertices, bool directed) {
    	
        numVertices = vertices;
        isDirected = directed;
        adjMatrix = new int*[numVertices];
        
        for (int i = 0; i < numVertices; ++i) {
            adjMatrix[i] = new int[numVertices];
            for (int j = 0; j < numVertices; ++j) {
                adjMatrix[i][j] = 0;  
            }
        }
    }

    void addEdge(int start, int end) {
        if (start >= 0 && start < numVertices && end >= 0 && end < numVertices) {
            adjMatrix[start][end] = 1;
            if (!isDirected) {
                adjMatrix[end][start] = 1;  // For undirected graph
            }
        } else {
            cout << "Invalid vertices!" << endl;
        }
    }

    void findDegree(int vertex) {
        int degree = 0;
        for (int i = 0; i < numVertices; ++i) {
            if (adjMatrix[vertex][i] == 1) {
                degree++;
            }
        }
        cout << "Degree of vertex " << vertex << ": " << degree << endl;
    }

    bool findPath(int start, int end, vector<int>& visited) {
        if (start == end) {
            return true;  // Found a path
        }
        visited[start] = 1;
        for (int i = 0; i < numVertices; ++i) {
            if (adjMatrix[start][i] == 1 && !visited[i]) {
                if (findPath(i, end, visited)) {
                    return true;  // Path found through this vertex
                }
            }
        }
        return false;  // No path found
    }

    bool isCyclicUtil(int v, bool visited[], int parent) {
        visited[v] = true;
        for (int i = 0; i < numVertices; ++i) {
            if (adjMatrix[v][i] == 1) {
                if (!visited[i]) {
                    if (isCyclicUtil(i, visited, v)) {
                        return true;
                    }
                } else if (isDirected && i != parent) {
                    return true;
                }
            }
        }
        return false;
    }

    bool isCyclic() {
        bool* visited = new bool[numVertices];
        for (int i = 0; i < numVertices; ++i) {
            visited[i] = false;
        }
        for (int i = 0; i < numVertices; ++i) {
            if (!visited[i]) {
                if (isCyclicUtil(i, visited, -1)) {
                    delete[] visited;
                    return true;
                }
            }
        }
        delete[] visited;
        return false;
    }

    void displayGraph() {
        cout << "Adjacency Matrix:" << endl;
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < numVertices; ++j) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    ~Graph() {
        for (int i = 0; i < numVertices; ++i) {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
    }
};

int main() {
    int vertices, edges;
    bool directed;
    char choice;

    cout << "Enter the number of vertices: ";
    cin >> vertices;

    cout << "Directed or undirected graph? (Enter 'd' for directed, 'u' for undirected): ";
    cin >> choice;

    directed = (choice == 'd' || choice == 'D');

    Graph graph(vertices, directed);

    cout << "Enter the number of edges: ";
    cin >> edges;

    cout << "Enter edges (format: start end):" << endl;
    for (int i = 0; i < edges; ++i) {
        int start, end;
        cin >> start >> end;
        graph.addEdge(start, end);
    }

    graph.displayGraph();

    cout << "Enter a vertex to find its degree: ";
    int vertex;
    cin >> vertex;
    graph.findDegree(vertex);

    cout << "Enter start and end vertices to find a path (format: start end): ";
    int start, end;
    cin >> start >> end;
    vector<int> visited(vertices, 0);
    if (graph.findPath(start, end, visited)) {
        cout << "Path exists between " << start << " and " << end << endl;
    } else {
        cout << "No path exists between " << start << " and " << end << endl;
    }

    if (graph.isCyclic()) {
        cout << "The graph contains cycles." << endl;
    } else {
        cout << "The graph is acyclic." << endl;
    }

    return 0;
}

