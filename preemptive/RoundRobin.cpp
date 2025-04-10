#include <iostream>
#include "../headers/maxHeap.h"
using namespace std;

void RoundRobin(vector<Process> process, int quantum)
{
    int n = process.size();
    int currentTime = 0;

    vector<GanttChart> ganttchart;

    vector<bool> complete(n, false);
    int completed = 0;

    int i = 0;
    while (completed < n)
    {
        if (!complete[i])
        {
            if (process[i].AT <= currentTime && process[i].remainingTime > 0)
            {
                int startTime = currentTime;
                int endTime = startTime + min(process[i].remainingTime, quantum);
                currentTime = endTime;
                process[i].remainingTime -= min(process[i].remainingTime, quantum);
                ganttchart.push_back({i + 1, startTime, endTime});
            }
            if (process[i].remainingTime == 0)
            {
                process[i].CT = currentTime;
                completed++;
                complete[i] = true;
            }
            i++;
            i = i % n;
        }
        else
        {
            i++;
            i = i % n;
        }
    }
    WT_TT(process);
    showProcess(process);
    printGanttChart(ganttchart);
}

int main()
{
    int n;
    cout << "Enter quantum for round robin" << endl;
    cin >> n;
    RoundRobin(allProcesses, n);
    return 0;
}