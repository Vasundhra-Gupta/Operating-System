#include <iostream>
#include "../headers/process.h"
using namespace std;

//we r checking things only when remaintime>0;

void SJFPreemptive(vector<Process> &process)
{
    int n = process.size();
    int currentTime = 0;
    int completed = 0;
    int i = 0;
    while (completed < n)
    {
        i = findNextProcess(process, currentTime);
        if (i != -1)
        {
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
            currentTime++;
        }
    }

    WT_TT(process);
    showProcess(process);
}

int main()
{
    SJFPreemptive(allProcesses);
    return 0;
}