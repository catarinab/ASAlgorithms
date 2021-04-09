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
        int nodes, edges, nSources = 0;
        list<int> *adjList;
        list<int> *adjListRev;
        vector<bool> visited;
        vector<int> depth;
        
    public:
        Graph(int n, int e) {
            nodes = n;
            edges = e;
            adjList = new list<int>[nodes];
            adjListRev = new list<int>[nodes];
            visited.resize(nodes, false);
            depth.resize(nodes, 0);
        }

        void addEdge(int v1, int v2) {
            adjList[v1 - 1].push_front(v2 - 1);
            adjListRev[v2 - 1].push_front(v1 - 1);
        }

        vector<int> getSources() {
            vector<int> sources;
            for (int i = 0; i < nodes; i++) {
                if (adjListRev[i].empty()) {
                    sources.push_back(i);
                    nSources++;
                }
            }
            return sources;
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
    fill(visited.begin(), visited.end(), 0);
    fill(depth.begin(), depth.end(), 0);
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
    vector<int> sources = g.getSources();
    int minIter = g.nSources, maxSize = 0;

    for (int i = 0; i < g.nSources; i++) {
        int size;
        size = g.pseudoDFS(sources[i]);
        if (size > maxSize) {
            maxSize = size;
        }
    }
    
    return std::to_string(minIter) + " " + std::to_string(maxSize);
}

int main() {
    printf("%s\n", domino().c_str());
    return 0;
}