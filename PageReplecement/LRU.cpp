#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4};
    int size = 3;
    vector<int> frames;
    int faults = 0;
    unordered_map<int, int> last_used;

    for (int i = 0; i < pages.size(); ++i) {
        int p = pages[i];
        last_used[p] = i;  // Update the last used index

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
                // Find LRU page in frames
                int lru = frames[0];
                for (int f : frames) {
                    if (last_used[f] < last_used[lru]) {
                        lru = f;
                    }
                }

                // Remove LRU and append the new page
                vector<int> new_frames;
                for (int f : frames) {
                    if (f != lru) {
                        new_frames.push_back(f);
                    }
                }
                new_frames.push_back(p);
                frames = new_frames;
            }

            cout << "Miss: " << p << " | ";
            for (int f : frames) cout << f << " ";
            cout << endl;
        }
    }

    cout << "Total Page Faults: " << faults << endl;
    return 0;
}
