// Ibrahim Gamal, ID: 320210145
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Structure to represent a process
struct Process
{
    int pid;
    int arrival_time;
    int brst_time;
    int priority;
};

// Function to implement First-Come, First-Served (FCFS) scheduling
void FCFS(vector<Process> &processes)
{
    int n = processes.size();
    int timee = 0;
    int tot_wa_time = 0;
    int total_turnaround_time = 0;

    for (int i = 0; i < n; i++)
    {
        if (timee < processes[i].arrival_time)
        {
            timee = processes[i].arrival_time;
        }
        tot_wa_time += timee - processes[i].arrival_time;
        timee += processes[i].brst_time;
        total_turnaround_time += timee - processes[i].arrival_time;
    }

    double avg_waiting_time = (double)tot_wa_time / n;
    double avg_turnaround_time = (double)total_turnaround_time / n;

    cout << "FCFS Scheduling:" << endl;
    cout << "Average waiting time: " << avg_waiting_time << endl;
    cout << "Average turnaround time: " << avg_turnaround_time << endl;
}

// Function to implement Shortest Job First (SJF) scheduling
void SJF(vector<Process> &processes)
{
    int n = processes.size();
    int timee = 0;
    int tot_wa_time = 0;
    int total_turnaround_time = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    for (int i = 0; i < n; i++)
    {
        while (!pq.empty() && timee < pq.top().first)
        {
            timee++;
        }
        pq.push({processes[i].brst_time, processes[i].pid});
        tot_wa_time += timee - processes[i].arrival_time;
        timee += processes[i].brst_time;
        total_turnaround_time += timee - processes[i].arrival_time;
    }

    double avg_waiting_time = (double)tot_wa_time / n;
    double avg_turnaround_time = (double)total_turnaround_time / n;

    cout << "SJF Scheduling:" << endl;
    cout << "Average waiting time: " << avg_waiting_time << endl;
    cout << "Average turnaround time: " << avg_turnaround_time << endl;
}

// Function to implement Round Robin scheduling
void RoundRobin(vector<Process> &processes, int time_quantum)
{
    int n = processes.size();
    int timee = 0;
    int tot_wa_time = 0;
    int total_turnaround_time = 0;
    queue<pair<int, int>> q;

    for (int i = 0; i < n; i++)
    {
        q.push({processes[i].brst_time, processes[i].pid});
    }

    while (!q.empty())
    {
        auto p = q.front();
        q.pop();
        int remaining_time = p.first - time_quantum;
        if (remaining_time <= 0)
        {
            timee += p.first;
            tot_wa_time += timee - processes[p.second].arrival_time - processes[p.second].brst_time;
            total_turnaround_time += timee - processes[p.second].arrival_time;
        }
        else
        {
            timee += time_quantum;
            while (!q.empty() && processes[q.front().second].arrival_time <= timee)
            {
                q.push({q.front().first, q.front().second});
                q.pop();
            }
            q.push({remaining_time, p.second});
        }
    }

    double avg_waiting_time = (double)tot_wa_time / n;
    double avg_turnaround_time = (double)total_turnaround_time / n;

    cout << "Round Robin Scheduling:" << endl;
    cout << "Average waiting time: " << avg_waiting_time << endl;
    cout << "Average turnaround time: " << avg_turnaround_time << endl;
}

// Function to implement Priority Scheduling
void PriorityScheduling(vector<Process> &processes)
{
    int n = processes.size();
    int timee = 0;
    int tot_wa_time = 0;
    int total_turnaround_time = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    for (int i = 0; i < n; i++)
    {
        while (!pq.empty() && timee < pq.top().first)
        {
            timee++;
        }
        pq.push({processes[i].priority, processes[i].pid});
    }

    double avg_waiting_time = (double)tot_wa_time / n;
    double avg_turnaround_time = (double)total_turnaround_time / n;

    cout << "Priority Scheduling:" << endl;
    cout << "Average waiting time: " << avg_waiting_time << endl;
    cout << "Average turnaround time: " << avg_turnaround_time << endl;
}

int main()
{
    vector<Process> processes = {
        {1, 0, 5, 3},
        {2, 1, 3, 2},
        {3, 2, 8, 5},
        {4, 3, 6, 1},
        {5, 4, 4, 4}};

    FCFS(processes);
    SJF(processes);
    RoundRobin(processes, 2);
    PriorityScheduling(processes);

    return 0;
}
