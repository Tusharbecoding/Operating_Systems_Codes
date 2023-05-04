//WAP to show round robin scheduling algorithm 
#include<iostream>
#include<queue>
using namespace std;


struct Process {
    int id;
    int bt;
};

void findWaitingTime(Process processes[], int n, int bt[], int wt[], int quantum) {
    int rem_bt[n];
    for (int i = 0; i < n; i++)
    {
        rem_bt[i] = processes[i].bt;
    }

    int t = 0;
    queue<int> q;

    for (int i = 0; i < n; i++)
    {
        q.push(i);
    }

    while(!q.empty()) {
        int i = q.front();
        q.pop();

        if (rem_bt[i] <= quantum) {
            t += rem_bt[i];
            wt[i] = t - processes[i].bt;
            rem_bt[i] = 0;
        }
        else{
            t += quantum;
            rem_bt[i] -= quantum;
            q.push(i);
        }    
    }
}

void findAvgTime(Process processes[], int n, int quantum) {
    int bt[n], wt[n], total_wt = 0;
    findWaitingTime(processes, n, bt, wt, quantum);

    cout<<"Process ID\tBurst Time\tWaiting Time\n";
    for (int i = 0; i < n; i++)
    {
        cout<< processes[i].id << "\t\t" << processes[i].bt << "\t\t" << wt[i] << endl;
        total_wt += wt[i];
    }

    float avg_wt = (float) total_wt / (float) n;
    cout<< "Avg waiting time is: "<<avg_wt<<endl;
    
}

int main() {
    int n, quantum;
    cout<<"Enter the number of processes: ";
    cin>>n;
    cout<<"Enter the time quantum: ";
    cin>>quantum;
    Process processes[n];
    for (int i = 0; i < n; i++)
    {
        cout<<"Enter the burst time for process "<<i+1<<": ";
        cin>>processes[i].bt;
        processes[i].id = i+1;
    }

    findAvgTime(processes, n, quantum);
    return 0;
}