#include <iostream>
#include "../headers/process.h"
using namespace std;

int findNextProcess(vector<Process> process, int currTime, vector<bool> completed)
{
    int minRem = INT_MAX;
    int idx = -1;
    for (int i = 0; i < process.size(); i++)
    {
        if (process[i].AT <= currTime && !completed[i] && process[i].BT < minRem)
        {
            minRem = process[i].BT;
            idx = i;
        }
    }
    return idx;
}

void SJFNonPreemptive(vector<Process> &processes)
{
    int n = processes.size();
    vector<bool> completed(n, false);
    vector<GanttChart> ganttchart;

    int i = 0;
    int complete = 0;
    int currentTime = 0;
    while (complete < n)
    {
        if (i != -1)
        {

            i = findNextProcess(processes, currentTime, completed);
            int startTime = currentTime;
            int endTime = currentTime + processes[i].BT;
            currentTime = endTime;
            processes[i].CT = currentTime;
            processes[i].remainingTime = 0;
            completed[i] = true;
            complete++;
            ganttchart.push_back({i + 1, startTime, endTime});
        }
        else
        {
            currentTime++;
        }
    }
    WT_TT(processes);
    showProcess(processes);
    printGanttChart(ganttchart);
}

int main()
{
    int n = 5;
    // cout << "Enter the number of processes:" << endl;
    // cin >> n;
    // vector<Process> processes(n, {0, 0, 0});
    // inputProcess(processes, n);
    SJFNonPreemptive(allProcesses);
    return 0;
}