#include <iostream>
#include <algorithm>
#include "../headers/maxHeap.h"
using namespace std;
//💡Concept💡
//

void FCFS(vector<Process> &processes)
{
    int n = processes.size();
    vector<GanttChart> ganttchart;
    // heapSort(processes);
    int currentTime = 0;
    for (int i = 0; i < n; i++)
    {
        int startTime = max(currentTime, processes[i].AT) ;
        int endTime = startTime+ processes[i].BT;
        currentTime = endTime;
        processes[i].CT = currentTime;
        ganttchart.push_back({i+1, startTime, endTime});
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
    // inputProcess(proc(esses, n);

    FCFS(allProcesses);

    return 0;
}