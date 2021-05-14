#include <stdio.h>
#include <vector>
#include <math.h>
#include <iostream>

using namespace std;

class Process {
    public:
        int xCost, yCost;
    public:
        Process(int x, int y) {
            xCost = x;
            yCost = y;
        }
};


class Program {
    public:
        vector<Process> processes;
        vector<vector<int>> comCosts;
    public:
        Program(int nProcesses) {
            processes.resize(nProcesses, {0,0});
            comCosts.resize(nProcesses);
            for(int i = 0; nProcesses > 0; nProcesses--, i++) {
                comCosts[i].resize(nProcesses, 0);
            }
        }
        
       void addProcess(int id, int xCost, int yCost) {
           Process process(xCost, yCost);
           processes[id] = process;
       }

       void addComCost(int id1, int id2, int comCost) {
           comCosts[id1][id2] = comCost;
       }
       
       int getMinCost() {
           return 0;
       }        
};

Program buildProgram() {
    int nProcesses, nComCosts, i;
    scanf("%d %d", &nProcesses, &nComCosts);
    
    Program program(nProcesses);

    for(i = 0; i < nProcesses; i++) {
        int xCost, yCost;
        scanf("%d %d", &xCost, &yCost);
        program.addProcess(i, xCost, yCost);
    }

    for(i = 0; i < nComCosts; i++) {
        int id1, id2, comCost;
        scanf("%d %d %d", &id1, &id2, &comCost);
        if (id1 < id2) {
            program.addComCost(id1, id2, comCost);
        }
        else {
            program.addComCost(id2, id1, comCost);
        }
    }
    return program;
}

int main() {
    printf("%d\n", buildProgram().getMinCost());
    return 0;
}