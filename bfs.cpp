#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

const int MAX = 100000;
vector<int> graph[MAX];
bool visited[MAX];

void bfs(int start_node) {
    queue<int> q;
    q.push(start_node);
    visited[start_node] = true;

    while (!q.empty()) {
        int curr_node = q.front();
        q.pop();
        cout << curr_node << " ";

        // Traversing all adjacent nodes
        for (int i = 0; i < graph[curr_node].size(); i++) {
            int adj_node = graph[curr_node][i];
            if (!visited[adj_node]) {
                visited[adj_node] = true;
                q.push(adj_node);
            }
        }
    }
}

int main() {
    int n, m, start_node;
    cout << "Enter no. of Nodes, no. of Edges, and Starting Node of graph:\n";
    cin >> n >> m >> start_node;

    cout << "Enter pairs of nodes for edges:\n";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // Undirected graph
    }

    // Parallel initialization of visited array
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    cout << "\nBFS Traversal: ";
    bfs(start_node);
    cout << endl;

    return 0;
}
