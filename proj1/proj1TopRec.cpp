#include <stdio.h>
#include <list>
#include <vector>
#include <string>
#include <stack>
#include <iostream>
#include <tuple>
#include <limits.h>
#define NINF INT_MIN

using namespace std;

class Graph {
    public:
        int nodes, edges, nSources = 0;
        list<int> *adjList;
        list<int> *adjListRev;
        stack<int> Stack;

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

        void topologicalSortUtil(int v, bool visited[]);
        int longestPath(int s);
        void topOrder();
};

void Graph::topologicalSortUtil(int v, bool visited[]){
    visited[v] = true;
   
    list<int>::iterator i;
    for (i = adjList[v].begin(); i != adjList[v].end(); ++i) {
        int node = *i;
        if (!visited[node])
            topologicalSortUtil(node, visited);
    }
    printf("elemento da stack: %d\n", v);
    Stack.push(v);
}

void Graph::topOrder(){
    printf("Top order\n");
    bool* visited = new bool[nodes];
    for (int i = 0; i < nodes; i++)
        visited[i] = false;
    for (int i = 0; i < nodes; i++)
        topologicalSortUtil(i, visited);
    delete [] visited;
}

int Graph::longestPath(int s){
    int dist[nodes];
   
    for (int i = 0; i < nodes; i++)
        dist[i] = NINF;
    dist[s] = 1;
    while (Stack.empty() == false) {
        int u = Stack.top();
        Stack.pop();
   
        list<int>::iterator i;
        if (dist[u] != NINF) {
            for (i = adjList[u].begin(); i != adjList[u].end(); ++i){
                printf("Distancia de %d (i): %d e distancia de %d (u): %d\n", *i, dist[*i], u, dist[u]);
                if (dist[*i] <= dist[u])
                    dist[*i] = dist[u] +1;
            }
        }
    }
   
    int longestPath = 0;
    for (int i = 0; i < nodes; i++){
        if(dist[i] != NINF && dist[i] > longestPath)
            longestPath = dist[i];
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
    vector<int> sources = g.getSources();
    int minIter = g.nSources, maxSize = 0;
    g.topOrder();
    for (int i = 0; i < g.nSources; i++) {
        int size;
        g.topOrder();
        printf("Source: %d\n", i);
        size = g.longestPath(sources[i]);
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