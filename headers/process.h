#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Process
{
public:
    int id, AT, BT, WT, TT, CT, priority, remainingTime = 0;
    Process(int pId, int arrival, int burst, int prior = 0)
    {
        this->id = pId;
        this->AT = arrival;
        this->BT = burst;
        this->priority = prior;
        this->CT = 0;
        this->WT = 0;
        this->TT = 0;
        this->remainingTime = burst;
    }
};

class GanttChart
{
public:
    string pid;
    int startTime;
    int endTime;

    GanttChart(int id, int start, int end)
    {
        this->pid = "P" + to_string(id);
        this->startTime = start;
        this->endTime = end;
    }
};

vector<Process> allProcesses = {
    {1, 0, 10, 3},
    {2, 1, 1, 1},
    {3, 2, 2, 3},
    {4, 3, 1, 4},
    {5, 4, 5, 2}};

void inputProcess(vector<Process> &processes, int n)
{
    cout << "Enter the arrival and burst time of the processes respectively one by one" << endl;
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        cout << "Process " << i + 1 << endl;
        cin >> processes[i].AT >> processes[i].BT;
    }
}

void showProcess(vector<Process> processes)
{
    cout << "Process\tAT\tBT\tPrior\tCT\tWT\tTT" << endl;
    for (auto &p : processes)
    {
        cout << p.id << "\t" << p.AT << "\t" << p.BT << "\t" << p.priority << "\t" << p.CT << "\t" << p.WT << "\t" << p.TT << endl;
    }
}

void WT_TT(vector<Process> &processes)
{
    int n = processes.size();
    for (int i = 0; i < n; i++)
    {
        processes[i].WT = processes[i].CT - processes[i].BT - processes[i].AT;
        processes[i].TT = processes[i].CT - processes[i].AT;
    }
    
}

void printGanttChart(vector<GanttChart> &ganttchart)
{
    cout << "\nGantt Chart:\n\n";
    
    for (auto &p : ganttchart)
    {
        cout << "|  " << p.pid << "  ";
    }
    cout << "|\n";

    cout << ganttchart[0].startTime;
    for (auto &p : ganttchart)
    {
        cout <<"      "<< p.endTime;
    }
    cout << endl;
}
