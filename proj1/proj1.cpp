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
        int nodes, edges;
        list<int> *adjList;
        list<int> *adjListRev;
        vector<bool> visited;
    public:
        Graph(int n, int e) {
            nodes = n;
            edges = e;
            adjList = new list<int>[nodes];
            adjListRev = new list<int>[nodes];
            visited.resize(nodes, false);
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

        void visit(int v) {
            visited[v] = true;
        }

        std::tuple<vector<int>, int> pseudoDFS(int s);
};

std::tuple<vector<int>, int> Graph::pseudoDFS(int s) {
    vector<bool> visited(nodes, false);
    vector<int> depth(nodes, 0);
    stack<int> toVisit;
    vector<int> path;
    int maxDepth = 0;

    depth[s] = 0;
    toVisit.push(s);
    while (!toVisit.empty()) {
        int v = toVisit.top();
        toVisit.pop();
        if (!visited[v]) {
            visited[v] = true;
            path.push_back(v);
            if (depth[v] > maxDepth)
                maxDepth = depth[v];
        }
        list<int>::iterator i;
        for (i = adjList[v].begin(); i != adjList[v].end(); ++i)
            if (!visited[*i]) {
                depth[*i] = depth[v] + 1;
                toVisit.push(*i);
            }
    }
    return std::make_tuple(path, maxDepth);
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
    int maxMaxSize = 0, minIter = 0;
    vector<int> maxMaxPath;
    Graph g = buildGraph();
    vector<int> sources = g.sources();

    while (!sources.empty()) {
        int maxSize = 0, maxSourceIndex;
        vector<int> maxPath;
        for (int i = 0; i < (int) sources.size(); i++) {
            int size;
            vector<int> path;
            tie(path, size) = g.pseudoDFS(sources[i]);
            if (++size > maxSize) {
                maxPath = path;
                maxSize = size;
                maxSourceIndex = i;
            }
        }
        
        for (int i = 0; i < maxSize; i++) {
            g.visit(maxPath[i]);
        }

        if (maxSize > maxMaxSize) {
            maxMaxSize = maxSize;
        }

        sources.erase(sources.begin() + maxSourceIndex);
        minIter++;
    }
    return std::to_string(minIter) + " " + std::to_string(maxMaxSize);
}

int main() {
    printf("%s\n", domino().c_str());
    return 0;
}