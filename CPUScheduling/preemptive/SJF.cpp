#include <iostream>
#include "../headers/process.h"
using namespace std;

// we r checking things only when remaintime>0;
int findNextProcess(vector<Process> process, int currTime)
{
    int minRem = INT_MAX;
    int idx = -1;
    for (int i = 0; i < process.size(); i++)
    {
        if (process[i].AT <= currTime && process[i].remainingTime > 0 && process[i].remainingTime < minRem)
        {
            minRem = process[i].remainingTime;
            idx = i;
        }
    }
    return idx;
}

void SJFPreemptive(vector<Process> &process)
{
    int n = process.size();
    vector<GanttChart> ganttchart;
    int currentTime = 0;
    int completed = 0;
    int prevProcess = 0;
    int startTime = 0;
    int i = 0;
    while (completed < n)
    {
        i = findNextProcess(process, currentTime);
        if (i != -1)
        {
            if (i != prevProcess)
            {
                if (prevProcess != -1)
                {
                    ganttchart.push_back({prevProcess + 1, startTime, currentTime});
                }
                startTime = currentTime;
                prevProcess = i;
            }
            process[i].remainingTime--;
            currentTime++;
            if (process[i].remainingTime == 0)
            {
                process[i].CT = currentTime;
                completed++;
            }
        }
        else
        {
            if (prevProcess != -1)
            {
                ganttchart.push_back(GanttChart(prevProcess + 1, startTime, currentTime));
                prevProcess = -1;
            }
            currentTime++;
        }
        if (prevProcess != -1)
        {

            ganttchart.push_back({prevProcess + 1, startTime, currentTime});
        }
    }

    WT_TT(process);
    showProcess(process);
    printGanttChart(ganttchart);
}

int main()
{
    SJFPreemptive(allProcesses);
    return 0;
}