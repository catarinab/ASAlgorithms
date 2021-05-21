#include <stdio.h>
#include <vector>
#include <math.h>
#include <iostream>
#include <limits.h>
#include <queue>
#include <cstring>

using namespace std;

typedef struct {
    int maxCap;
    int flow;
    int rvFlow;
} edge;

class flowNetwork {
    public:
        int numNodes;
        vector<vector<edge>> adj;

    public:
        flowNetwork(int n) {
            numNodes = n;
            adj.resize(n);
            for (int i = 0; i < numNodes; i++) {
                edge e{0, 0, 0};
                adj[i].resize(n, e);
            }
        }
        
        int getNumNodes() {
            return numNodes;
        }

        void addEdge(int v1, int v2, int weight) {
            adj[v1][v2].maxCap = weight;
            adj[v1][v2].flow = 0;
            adj[v1][v2].rvFlow = 0;
        }

        bool bfs(int s, int t, int parent[]) {
            bool visited[numNodes];
            queue<int> toVisit;
            
            memset(visited, 0, sizeof(visited));
            
            toVisit.push(s);
            visited[s] = true;
            parent[s] = -1;
        
            while (!toVisit.empty()) {
                int u = toVisit.front();
                toVisit.pop();

                for (int v = 0; v < numNodes; v++) {
                    if (visited[v] == false && adj[u][v].maxCap != 0 && (adj[u][v].flow < adj[u][v].maxCap)) {
                        parent[v] = u;
                        if (v == t)
                            return true;
                        toVisit.push(v);
                        visited[v] = true;
                    }
                }
            }
        
            return false;
        }
        
        int fordFulkerson(int s, int t) {
            int vParent, v, maximumFlow = 0;
            int parent[numNodes];
        
            while (bfs(s, t, parent)) {
                int currentPathFlow = INT_MAX;
                for (v = t; v != s; v = parent[v]) {
                    vParent = parent[v];
                    currentPathFlow = min(currentPathFlow, adj[vParent][v].maxCap - adj[vParent][v].flow);
                }
        
                for (v = t; v != s; v = parent[v]) {
                    vParent = parent[v];
                    adj[vParent][v].flow += currentPathFlow;
                    adj[vParent][v].rvFlow -= currentPathFlow;
                }
                maximumFlow += currentPathFlow;
            }
        
            return maximumFlow;
        } 
};


class Program {
    public:
        int nProcesses;
        flowNetwork *processes;

    public:
        Program(int n) {
            processes = new flowNetwork(n + 2);
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