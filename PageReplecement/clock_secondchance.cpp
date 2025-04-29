#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

struct Page {
    int pageNumber;
    bool referenceBit;
    bool active; // true=active, false=inactive
};

class LRU_Approx {
    vector<Page> frames;
    int hand; // Clock hand position
    int maxFrames;
    bool useActiveInactive;
    // bool useSwappiness;
    // int swappinessThreshold; // After how many scans force replacement
    // int scansDone;

public:
    LRU_Approx(int frameCount, bool activeInactive = false, bool swappiness = false, int threshold = 3)
        : maxFrames(frameCount), useActiveInactive(activeInactive)
        // , useSwappiness(swappiness), swappinessThreshold(threshold) 
        {
        hand = 0;
        // scansDone = 0;
    }

    void accessPage(int pageNum) {
        // Check if already loaded
        for (auto &p : frames) {
            if (p.pageNumber == pageNum) {
                p.referenceBit = 1;
                if (useActiveInactive)
                    p.active = true;
                cout << "Page " << pageNum << " accessed: Already in memory. Setting Reference Bit = 1.\n";
                return;
            }
        }

        // Page Fault
        cout << "Page Fault: " << pageNum << " needs to be loaded.\n";
        if (frames.size() < maxFrames) {
            frames.push_back({pageNum, 1, true});
        } else {
            replacePage(pageNum);
        }
    }

    void replacePage(int pageNum) {
        int attempts = 0;
        while (true) {
            if (frames[hand].referenceBit == 0) {
                cout << "Replacing page " << frames[hand].pageNumber << " with " << pageNum << ".\n";
                frames[hand] = {pageNum, 1, true};
                hand = (hand + 1) % maxFrames;
                // scansDone = 0;
                break;
            } else {
                cout << "Second chance to page " << frames[hand].pageNumber << ". Setting Reference Bit = 0.\n";
                frames[hand].referenceBit = 0;
                if (useActiveInactive)
                    frames[hand].active = false; // Demote to inactive
                hand = (hand + 1) % maxFrames;
                attempts++;
                // scansDone++;
                
                // if (useSwappiness && scansDone >= swappinessThreshold) {
                //     cout << "Swappiness Triggered! Forcing replacement at page " << frames[hand].pageNumber << ".\n";
                //     frames[hand] = {pageNum, 1, true};
                //     hand = (hand + 1) % maxFrames;
                //     scansDone = 0;
                //     break;
                // }
            }
        }
    }

    void displayFrames() {
        cout << "Current Frames: \n";
        for (auto &p : frames) {
            cout << "Page: " << p.pageNumber << " | Ref: " << p.referenceBit;
            if (useActiveInactive)
                cout << " | " << (p.active ? "Active" : "Inactive");
            cout << endl;
        }
        cout << "-----------\n";
    }
};

int main() {
    int frameCount;
    cout << "Enter number of frames: ";
    cin >> frameCount;

    bool activeInactive, swappiness;
    cout << "Use Active/Inactive List? (1-Yes/0-No): ";
    cin >> activeInactive;
    // cout << "Use Swappiness Feature? (1-Yes/0-No): ";
    // cin >> swappiness;

    // int threshold = 3; // Default threshold
    // if (swappiness) {
    //     cout << "Enter Swappiness Threshold (e.g., 3): ";
    //     cin >> threshold;
    // }

    LRU_Approx cache(frameCount, activeInactive, swappiness);

    int n;
    cout << "Enter number of page accesses: ";
    cin >> n;

    cout << "Enter page numbers: \n";
    for (int i = 0; i < n; i++) {
        int page;
        cin >> page;
        cache.accessPage(page);
        cache.displayFrames();
    }

    return 0;
}
