#include <stdio.h>
#include <list>
#include <vector>
#include <string>
#include <stack>
#include <iostream>
#include <tuple>
#include <queue>

using namespace std;

class Graph {
    public:
        int nodes, edges;
        list<int> *adjList;
        list<int> *adjListRev;
        
    public:
        Graph(int n, int e) {
            nodes = n;
            edges = e;
            adjList = new list<int>[nodes];
            adjListRev = new list<int>[nodes];
        }

        void addEdge(int v1, int v2) {
            adjList[v1 - 1].push_front(v2 - 1);
            adjListRev[v2 - 1].push_front(v1 - 1);
        }

        vector<int> sources() {
            vector<int> sources;
            for (int i = 0; i < nodes; i++) {
                if (adjListRev[i].empty())
                    sources.push_back(i);
            }
            return sources;
        }

        int topologicalSort();

        int pseudoDFS(int s);
};

int Graph::topologicalSort() {
    // Create a vector to store
    // indegrees of all
    // vertices. Initialize all
    // indegrees as 0.
    vector<int> in_degree(nodes, 0);
  
    // Traverse adjacency lists
    // to fill indegrees of
    // vertices.  This step
    // takes O(V+E) time
    for (int u = 0; u < nodes; u++) {
        list<int>::iterator itr;
        for (itr = adjList[u].begin();
             itr != adjList[u].end(); itr++)
            in_degree[*itr]++;
    }
  
    // Create an queue and enqueue
    // all vertices with indegree 0
    queue<int> q;
    for (int i = 0; i < nodes; i++)
        if (in_degree[i] == 0)
            q.push(i);
    
    int node = 0;
    
    // One by one dequeue vertices
    // from queue and enqueue
    // adjacents if indegree of
    // adjacent becomes 0
    while (!q.empty()) {
        // Extract front of queue
        // (or perform dequeue)
        // and add it to topological order
        int u = q.front();
        q.pop();
  
        // Iterate through all its
        // neighbouring nodes
        // of dequeued node u and
        // decrease their in-degree
        // by 1
        list<int>::iterator itr;
        for (itr = adjList[u].begin();
             itr != adjList[u].end(); itr++)
  
            // If in-degree becomes zero,
            // add it to queue
            if (--in_degree[*itr] == 0){
                node = *itr;
                break;
            }  
    }

    int source = 0;
    list<int>::iterator itr;
    for (itr = adjListRev[node].begin(); itr != adjListRev[node].end(); ++itr) {
        if (adjListRev[*itr].empty())
            source = *itr;
    }

    return source;
}

int Graph::pseudoDFS(int s) {
    vector<bool> visited(nodes, false);
    vector<int> depth(nodes, 0);
    stack<int> toVisit;
    int maxDepth = 0;
    
    depth[s] = 1;
    toVisit.push(s);
    while (!toVisit.empty()) {
        int v = toVisit.top();
        toVisit.pop();
        if (!visited[v]) {
            visited[v] = true;
            if (depth[v] > maxDepth)
                maxDepth = depth[v];

            list<int>::iterator i;
            for (i = adjList[v].begin(); i != adjList[v].end(); ++i) {
                int depthNode = depth[v] + 1;
                if (!visited[*i] || depth[*i] < depthNode) {
                    visited[*i] = false;
                    depth[*i] = depthNode;
                    toVisit.push(*i);
                }
            }
        }
        
    }
    return maxDepth;
}

Graph buildGraph() {
    int nodes, edges;
    scanf("%d %d", &nodes, &edges);
    Graph g(nodes, edges);
    for (int i = 0; i < edges; i++) {
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        g.addEdge(v1, v2);
    }
    return g;
}

string domino() {
    Graph g = buildGraph();
    vector<int> sources = g.sources();
    int minIter = sources.size(), source = g.topologicalSort(), size = g.pseudoDFS(source);
    
    return std::to_string(minIter) + " " + std::to_string(size);
}

int main() {
    printf("%s\n", domino().c_str());
    return 0;
}