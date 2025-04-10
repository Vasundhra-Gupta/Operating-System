#include <iostream>
#include <algorithm>
#include "../headers/maxHeap.h"
using namespace std;
//💡Concept💡
//

void FCFS(vector<Process> &processes, int n)
{
    heapSort(processes);
    int currentTime = 0;
    for (int i = 0; i < n; i++)
    {
        currentTime = max(currentTime, processes[i].AT) + processes[i].BT;
        processes[i].CT = currentTime;
    }
    WT_TT(allProcesses);
    showProcess(allProcesses);
}

int main()
{
    int n = 5;
    // cout << "Enter the number of processes:" << endl;
    // cin >> n;
    // vector<Process> processes(n, {0, 0, 0});
    // inputProcess(proc(esses, n);

    FCFS(allProcesses, n);

    return 0;
}