#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Graph {
    int V;
    vector<int> *adj;

public:
    Graph(int V) {
        this->V = V;
        adj = new vector<int>[V];
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void BFS_Normal(int start) {
        unordered_set<int> visited;
        queue<int> q;
        visited.insert(start);
        q.push(start);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cout << u << " ";

            for (int v : adj[u]) {
                if (visited.find(v) == visited.end()) {
                    visited.insert(v);
                    q.push(v);
                }
            }
        }
        cout << endl;
    }

    void BFS_Parallel(int start) {
        unordered_set<int> visited;
        queue<int> q;
        visited.insert(start);
        q.push(start);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cout << u << " ";

            #pragma omp parallel for
            for (size_t i = 0; i < adj[u].size(); i++) {
                int v = adj[u][i];
                if (visited.find(v) == visited.end()) {
                    #pragma omp critical
                    {
                        if (visited.find(v) == visited.end()) {
                            visited.insert(v);
                            q.push(v);
                        }
                    }
                }
            }
        }
        cout << endl;
    }

    void DFS_Normal(int start) {
        vector<bool> visited(V, false);
        DFSUtil(start, visited);
        cout << endl;
    }

    void DFS_Parallel(int start) {
        vector<bool> visited(V, false);
        #pragma omp parallel
        {
            #pragma omp single nowait
            {
                DFSUtil(start, visited);
            }
        }
        cout << endl;
    }

private:
    void DFSUtil(int u, vector<bool>& visited) {
        visited[u] = true;
        cout << u << " ";

        for (int v : adj[u]) {
            if (!visited[v]) {
                DFSUtil(v, visited);
            }
        }
    }
};

int main() {
    int V, edgeCount;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> edgeCount;

    Graph g(V);
    cout << "Provide edges (u v):\n";
    for (int i = 0; i < edgeCount; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    // Measure BFS Normal Time
    auto start = high_resolution_clock::now();
    g.BFS_Normal(0);
    auto stop = high_resolution_clock::now();
    cout << "BFS (Normal) Time: " << duration_cast<microseconds>(stop - start).count() << "μs\n";

    // Measure BFS Parallel Time
    start = high_resolution_clock::now();
    g.BFS_Parallel(0);
    stop = high_resolution_clock::now();
    cout << "BFS (Parallel) Time: " << duration_cast<microseconds>(stop - start).count() << "μs\n";

    // Measure DFS Normal Time
    start = high_resolution_clock::now();
    g.DFS_Normal(0);
    stop = high_resolution_clock::now();
    cout << "DFS (Normal) Time: " << duration_cast<microseconds>(stop - start).count() << "μs\n";

    // Measure DFS Parallel Time
    start = high_resolution_clock::now();
    g.DFS_Parallel(0);
    stop = high_resolution_clock::now();
    cout << "DFS (Parallel) Time: " << duration_cast<microseconds>(stop - start).count() << "μs\n";

    return 0;
}
