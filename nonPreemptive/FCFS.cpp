#include <iostream>
#include <vector>
#include "../headers/process.h"
using namespace std;

void CT(vector<Process> &processes, int n)
{
    int currentTime = 0;
    for (int i = 0; i < n; i++)
    {
        currentTime = max(currentTime, processes[i].AT) + processes[i].BT;
        processes[i].CT = currentTime;
    }
}

void FCFS(vector<Process> &processes, int n)
{
    for (int i = 0; i < n; i++)
    {
        processes[i].WT = processes[i].CT - processes[i].BT - processes[i].AT;
        processes[i].TT = processes[i].CT - processes[i].AT;
    }
}

int main()
{
    // cout << "Enter the number of processes:" << endl;
    int n = 5;
    // cin >> n;
    // vector<Process> processes(n, {0, 0, 0});
    vector<Process> processes = {
        {1, 0, 10},
        {2, 1, 1},
        {3, 2, 2},
        {4, 3, 1},
        {5, 4, 5}};
    // inputProcess(processes, n);
    CT(processes, n);
    FCFS(processes, n);
    showProcess(processes, n);

    return 0;
}