#include<iostream>
#include<vector>
using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
};

void fcfs(vector<Process>& processes) {
    int current_time = 0;
    int total_wait_time = 0;
    int total_turnaround_time = 0;

    for (auto& process : processes)
    {
        if (current_time < process.arrival_time) {
            current_time = process.arrival_time;
        }
        int wait_time = current_time - process.arrival_time;
        total_wait_time = total_wait_time + wait_time;

        int turnaround_time = wait_time + process.burst_time;
        total_turnaround_time = total_turnaround_time + turnaround_time;

        cout<<"Process "<< process.id << ": " << "arrival time = " << process.arrival_time << ", burst time = " << process.burst_time << ", wait time = " << wait_time << ", turnaround time = " << turnaround_time << endl;
    }

    double avg_wait_time = (double) total_wait_time / (double) processes.size();
    double avg_turnaround_time = (double) total_turnaround_time / (double) processes.size();

    cout<<"Average wait time = "<<avg_wait_time<<endl;
    cout<<"Average turnaround time = "<<avg_turnaround_time<<endl;
    
}

int main() {
    vector<Process> processes = {
        {1, 0, 5},
        {2, 1, 3},
        {3, 2, 8},
        {4, 3, 6},
        {5, 4, 4}
    };

    fcfs(processes);
    return 0;
}