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
        int nodes, edges, sources = 0;
        list<int> *adjList;
        list<int> *adjListRev;
        queue<int> leaves;
        
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

        void updateInfo() {
            for (int i = 0; i < nodes; i++) {
                if (adjListRev[i].empty()) {
                    sources++;
                }
                if (adjList[i].empty()) {
                    leaves.push(i);
                }
            }
        }

        int getMaxDepth();
};

int Graph::getMaxDepth() {
    int maxDepth = 0;
    
    if (!leaves.empty()) {
        maxDepth = 1;
        while (1) {
            //printf("while 1\n");
            queue<int> parents;
            while (!leaves.empty()) {
                //printf("while 2\n");
                int leaf = leaves.front();
                leaves.pop();
                list<int>::iterator i;
                for (i = adjListRev[leaf].begin(); i != adjListRev[leaf].end(); ++i) {
                    parents.push(*i);
                }
            }
            if (parents.empty()) {
                break;
            }
            maxDepth++;
            leaves = parents;
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