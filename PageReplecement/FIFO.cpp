#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4};
    int size = 3;
    vector<int> frames;
    int faults = 0;

    for (int i = 0; i < pages.size(); ++i) {
        int p = pages[i];

        bool hit = false;
        for (int f : frames) {
            if (f == p) {
                hit = true;
                break;
            }
        }

        if (hit) {
            cout << "Hit: " << p << " | ";
            for (int f : frames) cout << f << " ";
            cout << endl;
        } else {
            ++faults;
            if (frames.size() < size) {
                frames.push_back(p);  // Append if space is available
            } else {
                frames.erase(frames.begin());  // Remove the first frame (FIFO)
                frames.push_back(p);  // Add the new page
            }

            cout << "Miss: " << p << " | ";
            for (int f : frames) cout << f << " ";
            cout << endl;
        }
    }

    cout << "Total Page Faults: " << faults << endl;
    return 0;
}
