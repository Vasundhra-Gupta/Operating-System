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
                // Find the page that will not be used for the longest time
                int farthest_index = -1;
                int farthest_distance = i;

                for (int f_idx = 0; f_idx < frames.size(); ++f_idx) {
                    int next_use = pages.size();  // Default: never used again

                    // Search future pages for this frame
                    for (int j = i + 1; j < pages.size(); ++j) {
                        if (pages[j] == frames[f_idx]) {
                            next_use = j;
                            break;
                        }
                    }

                    if (next_use > farthest_distance) {
                        farthest_distance = next_use;
                        farthest_index = f_idx;
                    }
                }

                // Remove the optimal page and append the new one
                if (farthest_index != -1) {
                    frames.erase(frames.begin() + farthest_index);  // Remove the farthest page
                } else {
                    frames.erase(frames.begin());  // Default: remove the first page
                }
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
