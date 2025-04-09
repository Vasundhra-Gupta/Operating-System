#include <iostream>
#include <vector>
#include "process.h"
using namespace std;
// heap sort using max heap acc to AT
// void heapify(vector<Process> &process, int n, int i)
// {
//     int large = i;
//     int left = 2 * i + 1;
//     int right = 2 * i + 2;
//     if (left < n && process[left].AT > process[large].AT)
//     {
//         large = left;
//     }
//     if (right < n && process[right].AT > process[large].AT)
//     {
//         large = right;
//     }
//     if (large != i)
//     {
//         swap(process[large], process[i]);
//         heapify(process, n, large);
//     }
// }

//sort acc to BT
void heapify(vector<Process> &process, int n, int i)
{
    int large = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && process[left].BT > process[large].BT)
    {
        large = left;
    }
    if (right < n && process[right].BT > process[large].BT)
    {
        large = right;
    }
    if (large != i)
    {
        swap(process[large], process[i]);
        heapify(process, n, large);
    }
}

//sort acc to priority
// void heapify(vector<Process> &process, int n, int i)
// {
//     int large = i;
//     int left = 2 * i + 1;
//     int right = 2 * i + 2;
//     if (left < n && process[left].priority > process[large].priority)
//     {
//         large = left;
//     }
//     if (right < n && process[right].priority > process[large].priority)
//     {
//         large = right;
//     }
//     if (large != i)
//     {
//         swap(process[large], process[i]);
//         heapify(process, n, large);
//     }
// }

void heapSort(vector<Process> &process){
    int size = process.size()-1;
    for(int i= size/2 - 1; i>=0; i--){
        cout<<i<<endl;
        heapify(process,process.size(), i);
    }
    for(int i=size; i>0; i--){
        swap(process[0], process[i]);
        heapify(process, size, 0);
        size--;
    }
}

// int main()
// {
//     vector<int> arr = {
//         10, 6, 9, 2, 4, 7, 1};
//     // heapify(arr, arr.size(), 2);
//     heapSort(arr);
//     for (int i = 0; i < arr.size(); i++)
//     {
//         cout << arr[i] << "\t";
//     }
//     return 0;
// }