#include <iostream>
using namespace std;

class Process
{
public:
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingTime;
    int waitingTime;
    int turnAroundTime;
    int completionTime;
    Process(int pid = 0, int arrivalTime = 0, int burstTime = 0, int priority = 0)
    {
        this->pid = pid;
        this->arrivalTime = arrivalTime;
        this->burstTime = burstTime;
        this->priority = priority;
        this->remainingTime = burstTime;
        this->waitingTime = 0;
        this->turnAroundTime = 0;
        this->completionTime = 0;
    }
};

void input(Process *processes, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "Enter pid, arrival time, burst time and priority of process " << i + 1 << ": ";
        cin >> processes[i].pid >> processes[i].arrivalTime >> processes[i].burstTime >> processes[i].priority;
        processes[i].remainingTime = processes[i].burstTime;
    }
}

void display(Process *processes, int n)
{
    cout << "PID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tWaiting Time\tTurn Around Time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << processes[i].pid << "\t" << processes[i].arrivalTime << "\t\t" << processes[i].burstTime << "\t\t" << processes[i].priority << "\t\t" << processes[i].completionTime << "\t\t" << processes[i].waitingTime << "\t\t" << processes[i].turnAroundTime << endl;
    }
}

void swap(Process *a, Process *b)
{
    Process temp = *a;
    *a = *b;
    *b = temp;
}

void sortByArrivalTime(Process *processes, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime)
            {
                swap(&processes[j], &processes[j + 1]);
            }
            else if (processes[j].arrivalTime == processes[j + 1].arrivalTime)
            {
                if (processes[j].priority < processes[j + 1].priority)
                {
                    swap(&processes[j], &processes[j + 1]);
                }
            }
        }
    }
}

void sortByPid(Process *processes, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].pid > processes[j + 1].pid)
            {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}

void calculateCompletionTime(Process *processes, int n)
{
    sortByArrivalTime(processes, n);
    processes[0].completionTime = processes[0].arrivalTime + processes[0].burstTime;
    int time = processes[0].completionTime;
    int processIndex = 0, minPriority;
    for (int i = 0; i < n; i++)
    {
        minPriority = 999;

        // Find process with highest priority among the processes that have arrived
        for (int j = 1; j < n; j++)
        {
            if (processes[j].arrivalTime <= time && processes[j].priority < minPriority && processes[j].remainingTime > 0)
            {
                processIndex = j;
                minPriority = processes[j].priority;
            }
        }
        
        if (processes[processIndex].remainingTime > 0)
        {
            processes[processIndex].completionTime = time + processes[processIndex].burstTime;
            processes[processIndex].remainingTime = 0;
            time = processes[processIndex].completionTime;
        }
    }
}

void calculateTurnAroundTime(Process *processes, int n)
{
    int totalTurnAroundTime = 0;
    for (int i = 0; i < n; i++)
    {
        processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
        totalTurnAroundTime += processes[i].turnAroundTime;
    }
}

void calculateWaitingTime(Process *processes, int n)
{
    int totalWaitingTime = 0;
    for (int i = 0; i < n; i++)
    {
        processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
        totalWaitingTime += processes[i].waitingTime;
    }
    cout << "Average waiting time: " << (float)totalWaitingTime / n << endl;
}

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    Process *processes = new Process[n];
    input(processes, n);
    calculateCompletionTime(processes, n);
    calculateTurnAroundTime(processes, n);
    calculateWaitingTime(processes, n);
    sortByPid(processes, n);
    display(processes, n);
    return 0;
}