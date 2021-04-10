#include <stdio.h>
#include <list>
#include <vector>
#include <string>
#include <stack>
#include <iostream>
#include <tuple>

using namespace std;

class Graph {
    public:
        int nodes, edges, nSources;
        list<int> *adjList;
        vector<bool> visited;
        vector<bool> sources;
        vector<int> depth;
        
    public:
        Graph(int n, int e) {
            nodes = n;
            edges = e;
            nSources = nodes;
            adjList = new list<int>[nodes];
            visited.resize(nodes, false);
            sources.resize(nodes, true);
            depth.resize(nodes, 0);
        }

        void addEdge(int v1, int v2) {
            adjList[v1 - 1].push_front(v2 - 1);
            if (sources[v2 -1]) {
                sources[v2 - 1] = false;
                nSources--;
            }
        }

        int pseudoDFS(int s);
};

int Graph::pseudoDFS(int s) {
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
    int minIter = g.nSources, maxSize = 0, indice = 0, source = 0;

    for (int i = 0; i < minIter; i++) {
        for (int j = indice; j < g.nodes; j++) {
            if (g.sources[j]) {
                source = j;
                indice = j + 1;
                break;
            }
        }
        int size = g.pseudoDFS(source);
        if (size > maxSize) {
            maxSize = size;
        }
    }
    
    return to_string(minIter) + " " + to_string(maxSize);
}

int main() {
    printf("%s\n", domino().c_str());
    return 0;
}