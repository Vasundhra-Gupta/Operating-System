#include <iostream>
#include "../headers/maxHeap.h"
using namespace std;

int findNextProcess(vector<Process> &process, int currTime)
{
    int minPrior = INT_MAX;
    int idx = -1;
    for (int i = 0; i < process.size(); i++)
    {
        if (process[i].AT <= currTime && process[i].remainingTime > 0 && process[i].priority < minPrior)
        {
            minPrior = process[i].priority;
            idx = i;
        }
    }
    return idx;
}

void PriorityPreemptive(vector<Process> &process)
{
    int n = process.size();
    vector<GanttChart> ganttchart;

    int currentTime = 0;
    int i = 0;
    int complete = 0;
    int prevProcess = -1;// for gantt chart
    int startTime = 0;

    while (complete < n)
    {
        int i = findNextProcess(process, currentTime);
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

            currentTime++;
            process[i].remainingTime--;

            if (process[i].remainingTime == 0)
            {
                process[i].CT = currentTime;
                complete++;
            }
        }
        else
        {
            if (prevProcess != -1)
            {
                ganttchart.push_back({prevProcess + 1, startTime, currentTime});
                prevProcess = -1;
            }
            currentTime++;
        }

        if(prevProcess!=-1){
            ganttchart.push_back({prevProcess + 1, startTime, currentTime});
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
    PriorityPreemptive(allProcesses);

    return 0;
}