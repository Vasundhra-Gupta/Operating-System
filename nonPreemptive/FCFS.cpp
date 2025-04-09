#include <iostream>
#include <vector>
#include <algorithm>
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
    // inputProcess(proc(esses, n);
    // sort(processes[1][].begin(), processes[1].end());
    CT(processes, n);
    WT_TT(processes, n);
    showProcess(processes, n);

    return 0;
}