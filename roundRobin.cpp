#include<iostream>
#include<queue>
using namespace std;

struct Process {
    int id;
    int bt;
};

void findWaitingTime(Process processes[], int n, int bt[], int wt[], int quantum) {
    int rem_bt[n]; //copy of burst time for each process
    for (int i = 0; i < n; i++) {
        rem_bt[i] = processes[i].bt;
    }

    int t = 0; //setting current time to zero
    queue<int> q;

    for (int i = 0; i < n; i++)
    {
        q.push(i); //pushing all waiting processes to queue
    }
    
    while (!q.empty())
    {
        int i = q.front(); //first process ko utha liya
        q.pop();

        //agr time quantum se kum time me hojayega
        if (rem_bt[i] <= quantum)
        {
            t += rem_bt[i];
            wt[i] = t - processes[i].bt;
            rem_bt[i] = 0;
        }
        else
        {
            t += quantum;
            rem_bt[i] -= quantum;
            q.push(i); //queue me wapas daldo simple
        }
        
    }
    
}

void findTurnAroundTime(Process processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i];
    }
    
}

void findAvgTime(Process processes[], int n, int quantum) {
    int bt[n], wt[n], tat[n], total_wt = 0, total_tat = 0;

    findWaitingTime(processes, n, bt, wt, quantum);
    findTurnAroundTime(processes, n, bt, wt, tat);

    cout<<"Process ID\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++)
    {
        cout<< processes[i].id << "\t\t" << processes[i].bt << "\t\t" << wt[i] << "\t\t" << tat[i] << endl;
        total_wt += wt[i];
        total_tat += tat[i];
    }

    float avg_wt = (float) total_wt / (float) n;
    float avg_tat = (float) total_tat / (float) n;

    cout<< "Avg wait time: "<< avg_wt << endl;
    cout<< "Avg turn around time: "<< avg_tat << endl;
    
}

int main()
{
    int n, quantum;
    cout<< "Enter number of processes: ";
    cin>> n;
    cout<< "Enter time quantum: ";
    cin>> quantum;

    Process processes[n];
    for (int i = 0; i < n; i++)
    {
        cout<< "Enter burst time for process " << i+1 << ": ";
        cin>> processes[i].bt;
        processes[i].id = i+1;
    }
    
    findAvgTime(processes, n, quantum);
    return 0;
}