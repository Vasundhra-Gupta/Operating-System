#include <iostream>
#include "../headers/maxHeap.h"
using namespace std;

void RoundRobin(vector<Process> process, int quantum)
{
    int n = process.size();
    int currentTime = 0;
    vector<bool> complete(n, false);
    int completed = 0;
    int i = 0;
    while (completed < n)
    {
        if (!complete[i])
        {
            if (process[i].AT <= currentTime && process[i].remainingTime > 0)
            {
                currentTime += min(process[i].remainingTime, quantum);
                process[i].remainingTime -= min(process[i].remainingTime, quantum);
                cout << "process ongoing is " << i + 1 << endl;
            }
            if (process[i].remainingTime == 0)
            {
                cout << "process done is " << i + 1 << endl;
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
        // cout<<"Arrived"<<i<<endl;
        // cout<<(bool)complete[i]<<endl;
    }
    WT_TT(process);
    showProcess(process);
}

int main()
{
    int n;
    cout << "Enter quantum for round robin" << endl;
    cin >> n;
    RoundRobin(allProcesses, n);
    return 0;
}