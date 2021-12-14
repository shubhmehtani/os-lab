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
    cout << "PID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurn Around Time\tWaiting Time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << processes[i].pid << "\t\t" << processes[i].arrivalTime << "\t\t" << processes[i].burstTime << "\t\t" << processes[i].priority << "\t\t" << processes[i].completionTime << "\t\t" << processes[i].turnAroundTime << "\t\t" << processes[i].waitingTime << endl;
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
    int currentTime = processes[0].arrivalTime;
    int processIndex = 0, minPriority = -1, completed = 0;
    while (completed != n)
    {
        // Find process with highest priority among the processes that have arrived
        for (int j = 0; j < n; j++)
        {
            if (processes[j].arrivalTime <= currentTime && processes[j].priority > minPriority && processes[j].remainingTime > 0)
            {
                processIndex = j;
                minPriority = processes[j].priority;
            }
        }
        processes[processIndex].remainingTime--;

        // If process is completed
        if (processes[processIndex].remainingTime == 0)
        {
            processes[processIndex].completionTime = currentTime + 1;
            completed++;
            minPriority = -1;
        }

        currentTime++;
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
    cout << "Average Turn Around Time : " << (float)totalTurnAroundTime / n << endl;
}

void calculateWaitingTime(Process *processes, int n)
{
    int totalWaitingTime = 0;
    for (int i = 0; i < n; i++)
    {
        processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
        totalWaitingTime += processes[i].waitingTime;
    }
    cout << "Average Waiting Time : " << (float)totalWaitingTime / n << endl;
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