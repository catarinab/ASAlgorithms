#include <stdio.h>
#include <list>
#include <vector>
#include <string>
#include <stack>
#include <iostream>

using namespace std;

class Graph {
    public:
        int nodes, edges, nSources;
        vector<vector<int>> adjList;
        vector<int> inDegree, sources, topOrder;

    public:
        Graph(int n, int e) {
            nodes = n;
            edges = e;
            nSources = nodes;
            adjList.resize(nodes);
            inDegree.resize(nodes, 0);
        }

        void addEdge(int v1, int v2) {
            adjList[v1 - 1].push_back(v2 - 1);
            if (inDegree[v2 - 1] == 0) {
                nSources--;
            }
            inDegree[v2 - 1]++;
        }

        void topologicalSort();

        int longestPath(int s);
};

void Graph::topologicalSort(){
    int iter = 0;
    for (int i = 0; i < nodes; i++) {
        if (inDegree[i] == 0) {
            iter++;
            sources.push_back(i);
            topOrder.push_back(i);
        }
        if (iter == nSources) {
            break;
        }
    }

    int quantity = nSources, indice = 0;
    while (quantity != nodes) {
        int v = topOrder[indice];
        indice++;

        vector<int>::iterator itr;
        for (itr = adjList[v].begin(); itr != adjList[v].end(); itr++) {
            if (--inDegree[*itr] == 0) {
                topOrder.push_back(*itr);
                quantity++;
            }
        }
    }
}

int Graph::longestPath(int s){
    vector<int> depth(nodes, 0);
    depth[s] = 1;

    int longestPath = depth[s];
    for (int i = 0; i < nodes; i++) {
        int v = topOrder[i];
        if (depth[v] != 0) {
            vector<int>::iterator i;
            for (i = adjList[v].begin(); i != adjList[v].end(); ++i){
                if (depth[*i] <= depth[v]) {
                    depth[*i] = depth[v] + 1;
                    if (depth[*i] > longestPath) {
                        longestPath = depth[*i];
                    }
                }
            }
        }
    }
    
    return longestPath;
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
    int minIter = g.nSources, maxSize = 0, source;

    g.topologicalSort();
    for (int i = 0; i < minIter; i++) {
        source = g.sources[i];
        int size = g.longestPath(source);
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