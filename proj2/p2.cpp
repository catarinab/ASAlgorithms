#include <stdio.h>
#include <vector>
#include <math.h>
#include <iostream>
#include <limits.h>
#include <queue>
#include <cstring>

using namespace std;

class Graph {
    public:
        int numNodes;
        vector<vector<int>> adj;

    public:
        Graph(int n) {
            numNodes = n;
            adj.resize(n);
            for (int i = 0; i < numNodes; i++) {
                adj[i].resize(n, 0);
            }
        }
        
        int getNumNodes() {
            return numNodes;
        }

        void addEdge(int v1, int v2, int weight) {
            adj[v1][v2] = weight;
        }

        bool bfs(int s, int t, int parent[]) {
            bool visited[numNodes];
            memset(visited, 0, sizeof(visited));
            
            queue<int> q;
            q.push(s);
            visited[s] = true;
            parent[s] = -1;
        
            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int v = 0; v < numNodes; v++) {
                    if (visited[v] == false && adj[u][v] > 0) {
                        if (v == t) {
                            parent[v] = u;
                            return true;
                        }
                        q.push(v);
                        parent[v] = u;
                        visited[v] = true;
                    }
                }
            }
        
            return false;
        }
        
        int fordFulkerson(int s, int t) {
            int u, v;
            int parent[numNodes];
            int max_flow = 0;
        
            while (bfs(s, t, parent)) {
                int path_flow = INT_MAX;
                for (v = t; v != s; v = parent[v]) {
                    u = parent[v];
                    path_flow = min(path_flow, adj[u][v]);
                }
        
                for (v = t; v != s; v = parent[v]) {
                    u = parent[v];
                    adj[u][v] -= path_flow;
                    adj[v][u] -= path_flow;
                }
                max_flow += path_flow;
            }
        
            return max_flow;
        } 
};


class Program {
    public:
        int nProcesses;
        Graph *processes;

    public:
        Program(int n) {
            processes = new Graph(n + 2);
            nProcesses = n;
        }
        
        void addProcess(int id, int xCost, int yCost) {
            processes->addEdge(0, id, xCost);
            processes->addEdge(id, processes->getNumNodes() - 1, yCost);
        }

        void addComCost(int id1, int id2, int comCost) {
            if (comCost > 0) {
                processes->addEdge(id1, id2, comCost);
                processes->addEdge(id2, id1, comCost);
            }
        }
       
        int getMinCost() {
            return processes->fordFulkerson(0, nProcesses + 1);
        }        
};

Program buildProgram() {
    int nProcesses, nComCosts, i;
    scanf("%d %d", &nProcesses, &nComCosts);
    
    Program program(nProcesses);

    for(i = 0; i < nProcesses; i++) {
        int xCost, yCost;
        scanf("%d %d", &xCost, &yCost);
        program.addProcess(i+1, xCost, yCost);
    }

    for(i = 0; i < nComCosts; i++) {
        int id1, id2, comCost;
        scanf("%d %d %d", &id1, &id2, &comCost);
        program.addComCost(id1, id2, comCost);
    }

    return program;
}

int main() {
    printf("%d\n", buildProgram().getMinCost());
    return 0;
}