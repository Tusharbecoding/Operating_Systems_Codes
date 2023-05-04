#include <iostream>
#include <queue>

using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
};

void round_robin_scheduling(Process processes[], int num_processes, int time_quantum) {
    queue<Process> q;
    int current_time = 0;
    int completed_processes = 0;
    int waiting_time = 0;
    int turnaround_time = 0;

    // Create a circular queue to avoid copying elements
    Process circular_queue[num_processes];
    int front = 0;
    int rear = -1;
    int size = 0;

    // Add all processes to the queue
    for (int i = 0; i < num_processes; i++) {
        q.push(processes[i]);
    }

    // Run the scheduling algorithm until all processes are completed
    while (completed_processes < num_processes) {
        // Get the next process in the queue
        Process current_process = q.front();
        q.pop();

        // Add the process to the circular queue
        rear = (rear + 1) % num_processes;
        circular_queue[rear] = current_process;
        size++;

        // Check if the process has completed
        if (current_process.burst_time <= time_quantum) {
            current_time += current_process.burst_time;
            completed_processes++;
            waiting_time += (current_time - current_process.arrival_time - current_process.burst_time);
            turnaround_time += (current_time - current_process.arrival_time);
        } else {
            current_time += time_quantum;
            // Update the remaining burst time of the process
            circular_queue[rear].burst_time -= time_quantum;
        }

        // Add any new processes that have arrived during this time slice
        for (int i = 0; i < num_processes; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].burst_time > 0) {
                q.push(processes[i]);
            }
        }

        // Move any remaining processes in the circular queue to the back of the regular queue
        while (size > 0) {
            front = (front + 1) % num_processes;
            Process p = circular_queue[front];
            size--;
            if (p.burst_time > 0) {
                q.push(p);
                break;
            } else {
                completed_processes++;
                waiting_time += (current_time - p.arrival_time - p.burst_time);
                turnaround_time += (current_time - p.arrival_time);
            }
        }
    }

    // Print the results
    cout << "Average waiting time: " << ((float) waiting_time / num_processes) << endl;
    cout << "Average turnaround time: " << ((float) turnaround_time / num_processes) << endl;
}

int main() {
    // Define some sample processes
    Process processes[] = {
        {1, 0, 8},
        {2, 1, 4},
        {3, 2, 9},
        {4, 3, 5},
        {5, 4, 2}
    };

    // Run the scheduling algorithm with a time quantum of 2
    round_robin_scheduling(processes, 5, 2);

    return 0;
}
