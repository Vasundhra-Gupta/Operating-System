#include <iostream>
#include <vector>
using namespace std;

class Process
{
public:
    int id, AT, BT, WT, TT, CT, priority;
    Process(int pId, int arrival, int burst, int prior = 0)
    {
        this->id = pId;
        this->AT = arrival;
        this->BT = burst;
        this->priority = prior;
        this->CT = 0;
        this->WT = 0;
        this->TT = 0;
    }
};

void inputProcess(vector<Process> &processes, int n)
{
    cout << "Enter the arrival and burst time of the processes respectively one by one" << endl;
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        cout << "Process " << i + 1 << endl;
        cin >> processes[i].AT >> processes[i].BT;
    }
}
void showProcess(vector<Process> processes, int n)
{
    cout << "Process\tAT\tPrior\tBT\tCT\tWT\tTT" << endl;
    for (auto &p : processes)
    {
        cout << p.id << "\t" << p.AT << "\t"<< p.priority << "\t" << p.BT << "\t" << p.CT << "\t" << p.WT << "\t" << p.TT << endl;
    }
}

void WT_TT(vector<Process> &processes, int n)
{
    for (int i = 0; i < n; i++)
    {
        processes[i].WT = processes[i].CT - processes[i].BT - processes[i].AT;
        processes[i].TT = processes[i].CT - processes[i].AT;
    }
}