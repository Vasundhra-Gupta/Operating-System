#include <iostream>
#include "../headers/maxHeap.h"
using namespace std;
int findNextProcess(vector<Process> process, int currTime, vector<bool> completed)
{
    int minPrior = INT_MAX;
    int idx = -1;
    for (int i = 0; i < process.size(); i++)
    {
        if (process[i].AT <= currTime && !completed[i] && process[i].priority < minPrior)
        {
            minPrior = process[i].priority;
            idx = i;
        }
    }
    return idx;
}
void PriorityNonPreemptive(vector<Process> process)
{
    int n = process.size();
    int currentTime = 0;
    int i = 0;
    int complete = 0;
    vector<bool> completed(n, false);
    vector<GanttChart> ganttchart;
    while (complete < n)
    {
        int i = findNextProcess(process, currentTime, completed);
        if (i != -1)
        {
            int startTime = currentTime;
            int endTime = currentTime + process[i].BT;
            currentTime = endTime;
            process[i].CT = currentTime;
            process[i].remainingTime = 0;
            completed[i] = true;
            complete++;
            ganttchart.push_back({i + 1, startTime, endTime});
        }
        else
        {
            currentTime++;
        }
    }

    WT_TT(process);
    showProcess(process);
    printGanttChart(ganttchart);
}
int main()
{
    int n = 5;
    // cout << "Enter the number of processes:" << endl;
    // cin >> n;
    // vector<Process> processes(n, {0, 0, 0})
    // inputProcess(processes, n);
    PriorityNonPreemptive(allProcesses);

    return 0;
}