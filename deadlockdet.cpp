#include<iostream>
#include<vector>
using namespace std;

bool isResourceAllocated(vector<vector<int>>& allocation, int process, int resource) {
    return allocation[process][resource] > 0;
}

bool isResourceRequested(vector<vector<int>>& request, int process, int resource) {
    return request[process][resource] > 0;
}

bool isDeadlock(vector<vector<int>>& allocation, vector<vector<int>>& request, vector<int>& available, int numProcesses, int numResources) {
    vector<bool> visited(numProcesses, false);
    vector<int> work(available);
    vector<vector<int>> tempAllocation(allocation);

    bool hasDeadlock = false;
    while(true) {
        bool found = false;

        for (int i = 0; i < numProcesses; i++)
        {
            if (!visited[i])
            {
                bool canExecute = true;
                for (int j = 0; j < numResources; j++)
                {
                    if(isResourceRequested(request, i, j) && request[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }

                if (canExecute)
                {
                    found = true;
                    visited[i] = true;
                    for (int j = 0; j < numResources; j++)
                    {
                        work[j] += allocation[i][j];
                    }
                    break;   
                } 
            }
        }
        if (!found)
        {
            break;
        }
    }
    for (bool v : visited)
    {
        if (!v)
        {
            hasDeadlock = true;
            break;
        }
        
    }
    return hasDeadlock;
}

int main() {
    int numProcesses = 5;
    int numResources = 5;

    vector<vector<int>> allocation = {{0,1,0}, {2,0,0}, {3,0,3}, {2,1,1}, {0,0,2}};
    vector<int> available = {0,0,0};
    vector<vector<int>> request = {{0,0,0}, {2,0,2}, {0,0,0}, {1,0,0}, {0,0,2}};

    if (isDeadlock(allocation, request, available, numProcesses, numResources))
    {
        cout<<"Deadlock detected"<<endl;
    }
    else {
        cout<<"No deadlock detected"<<endl;
    }

    return 0;
    
}