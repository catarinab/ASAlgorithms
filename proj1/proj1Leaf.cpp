#include <stdio.h>
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <queue>

using namespace std;

class Graph {
    public:
        int nodes, edges, sources = 0, nLeaves = 0;
        vector<int> *adjList;
        vector<int> *adjListRev;
        queue<int> leaves;
        
    public:
        Graph(int n, int e) {
            nodes = n;
            edges = e;
            adjList = new vector<int>[nodes];
            adjListRev = new vector<int>[nodes];
        }

        void addEdge(int v1, int v2) {
            adjList[v1 - 1].push_back(v2 - 1);
            adjListRev[v2 - 1].push_back(v1 - 1);
        }

        void updateInfo() {
            for (int i = 0; i < nodes; i++) {
                if (adjListRev[i].empty()) {
                    sources++;
                }
                if (adjList[i].empty()) {
                    leaves.push(i);
                    nLeaves++;
                }
            }
        }

        int getMaxDepth();
};

int Graph::getMaxDepth() {
    int maxDepth = 0;
    vector<bool> visited(nodes, false);

    if (!leaves.empty()) {
        maxDepth = 1;
        while (!leaves.empty()) {
            int parents = 0;
            for (int i = 0; i < nLeaves; i++) {
                int leaf = leaves.front();
                printf("leaf: %d\n", leaf);
                leaves.pop();
                vector<int>::iterator j;
                for (j = adjListRev[leaf].begin(); j != adjListRev[leaf].end(); ++j) {
                    if(!visited[*j]){
                        printf("No %d nao foi visitado ainda\n", *j);
                        visited[*j] = true;
                        leaves.push(*j);
                        parents++; 
                    }
                    else {
                        printf("No %d ja tinha sido visitado\n", *j);
                    }
                    
                }
            }
            printf("parents: %d\n", parents);
            if (parents != 0) {
                maxDepth++;
                nLeaves = parents;
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
    g.updateInfo();
    int minIter = g.sources, size = g.getMaxDepth();
    
    return std::to_string(minIter) + " " + std::to_string(size);
}

int main() {
    printf("%s\n", domino().c_str());
    return 0;
}