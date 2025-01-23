#include <bits/stdc++.h>
using namespace std;

int qtime = 2; // quantum time

// structure for the process contain all of its characteristics
struct Process
{
    string name;        // Name of the process
    int pid;            // process ID
    int arrivalTime;    // Time at which the process arrives
    int burstTime;      // Total execution time required by the process
    int completionTime; // Time at which the process finish execution
    int turnAroundTime; // Total time from arrival to completion
    int waitingTime;    // total waiting time for the process in the ready queue
    int startTime;      // start time of running of the process
    int responseTime;   // time to arrive to the first execution
    bool started;       // check if the process has started or not
};

// function prototypes
vector<Process> getProcesses(int n);
void calculateTurnAroundTime(vector<Process> &p, int n);
void calculateWaitingTime(vector<Process> &p, int n);
queue<string> roundRobin(vector<Process> &p, int n, int q);
void printSolutionReport(vector<Process> &p, int n);
void drawGanttChart(queue<string> q);

int main()
{
    // Redirect input and output to the files
    freopen("Example.txt", "r", stdin);
    freopen("Solution.txt", "w", stdout);
    int number_of_processes;
    cin >> number_of_processes;
    // Read process data
    vector<Process> processes(number_of_processes);
    processes = getProcesses(number_of_processes);
    // perform round robin scheduling
    roundRobin(processes, number_of_processes, qtime);
    // calculate turnaround and waiting times
    calculateTurnAroundTime(processes, number_of_processes);
    calculateWaitingTime(processes, number_of_processes);
    // Draw gantt chart and print results
    drawGanttChart(roundRobin(processes, number_of_processes, qtime));
    printSolutionReport(processes, number_of_processes);
    return 0;
}

// Read process details from user
vector<Process> getProcesses(int n)
{
    vector<Process> p(n);
    for (int i = 0; i < n; i++)
    {
        cin >> p[i].name >> p[i].burstTime >> p[i].arrivalTime;
        p[i].pid = p[i].name[1] - '0'; // extract id from name (ex: P1 -> 1)
    }
    return p;
}

// calculates turnaround time for each process
void calculateTurnAroundTime(vector<Process> &p, int n)
{
    for (int i = 0; i < n; i++)
        p[i].turnAroundTime = p[i].completionTime - p[i].arrivalTime;
}

// calculate waiting time for each process
void calculateWaitingTime(vector<Process> &p, int n)
{
    for (int i = 0; i < n; i++)
        p[i].waitingTime = p[i].turnAroundTime - p[i].burstTime;
}

// implement round robin scheduling algorithm
queue<string> roundRobin(vector<Process> &p, int n, int q)
{
    queue<int> scheduling; // queue for peocess scheduling
    queue<string> gantt;   // queue for gantt chart representation
    int cnt = 0;
    bool existed[n] = {0}; // track the processes that has entered the queue
    vector<int> remainingTime(n);

    // initialize remainig burst time
    for (int i = 0; i < n; i++)
    {
        remainingTime[i] = p[i].burstTime;
    }

    int current = 0;
    bool finished = false;
    while (!finished)
    {
        // add process to the queue based on arrival time
        for (int i = 0; i < n; i++)
        {
            if (p[i].arrivalTime <= current && !existed[i])
            {
                scheduling.push(p[i].pid - 1);
                existed[i] = 1;
            }
        }

        // check if all processes are completed
        finished = true;
        for (int i = 0; i < n; i++)
        {
            if (remainingTime[i] > 0)
            {
                finished = false;
                break;
            }
        }

        // setting response time for the process
        if (remainingTime[cnt] == p[cnt].burstTime)
        {
            p[cnt].responseTime = current - p[cnt].arrivalTime;
        }
        if (remainingTime[cnt] > qtime)
        {
            gantt.push(p[cnt].name);
            current += qtime;
            // add newly arrived process to the queue
            for (int i = 0; i < n; i++)
            {
                if (p[i].arrivalTime <= current && !existed[i])
                {
                    scheduling.push(p[i].pid - 1);
                    existed[i] = 1;
                }
            }
            remainingTime[cnt] -= qtime;
            scheduling.pop();
            scheduling.push(p[cnt].pid - 1);
            if (!scheduling.empty())
            {
                cnt = scheduling.front();
            }
        }
        else
        {
            gantt.push(p[cnt].name);
            current += remainingTime[cnt];
            // add newly arrived process to the queue
            for (int i = 0; i < n; i++)
            {
                if (p[i].arrivalTime <= current && !existed[i])
                {
                    scheduling.push(p[i].pid - 1);
                    existed[i] = 1;
                }
            }
            remainingTime[cnt] = 0;
            p[cnt].completionTime = current;
            scheduling.pop();
            if (!scheduling.empty())
            {
                cnt = scheduling.front();
            }
        }
    }
    return gantt;
}

// prints the sceduling report
void printSolutionReport(vector<Process> &p, int n)
{
    int totalTurnAroundTime = 0;
    int totalWaitingTime = 0;
    int totalResponseTime = 0;
    for (int i = 0; i < n; i++)
    {
        totalTurnAroundTime += p[i].turnAroundTime;
        totalWaitingTime += p[i].waitingTime;
        totalResponseTime += p[i].responseTime;
    }
    cout << "Result report\n";
    cout << "name\t\twt\t\ttrt\t\t\trt\n";
    for (int i = 0; i < n; i++)
    {
        cout << p[i].name << "\t\t\t" << p[i].waitingTime << "\t\t" << p[i].turnAroundTime << "\t\t\t" << p[i].responseTime << "\n";
    }
    cout << "AVG\t\t " << (float)totalWaitingTime / n << "  " << (float)totalTurnAroundTime / n << "\t\t" << (float)totalResponseTime / n;
}

// draw the gantt chart
void drawGanttChart(queue<string> q)
{
    int n = q.size();
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
            cout << "|";
        else
            cout << "---|";
    }
    cout << "\n";
    for (int i = -1; i < n - 1; i++)
    {
        if (i == -1)
            cout << "|";
        else
        {
            cout << q.front() << " |";
            q.pop();
        }
    }
    cout << "\n";
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
            cout << "|";
        else
            cout << "---|";
    }
    cout << "\n\n";
}