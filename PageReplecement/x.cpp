#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

struct Page
{
    int pageNumber;
    bool referenceBit;
    bool active; // true=active, false=inactive
};

class LRU_Approx
{
    vector<Page> frames;
    int hand;
    int maxFrames;

public:
    LRU_Approx(int frameCount)
        : maxFrames(frameCount)
    {
        hand = 0;
    }

    void accessPage(int pageNum)
    {
        // Check if already loaded
        for (auto &p : frames)
        {
            if (p.pageNumber == pageNum)
            {
                p.referenceBit = 1;
                cout << "Page " << pageNum << " accessed: Already in memory. Setting Reference Bit = 1.\n";
                return;
            }
        }

        // Page Fault
        cout << "Page Fault: " << pageNum << " needs to be loaded.\n";
        if (frames.size() < maxFrames)
        {
            frames.push_back({pageNum, 1, true});
        }
        else
        {
            replacePage(pageNum);
        }
    }

    void replacePage(int pageNum)
    {
        int attempts = 0;
        while (true)
        {
            if (frames[hand].referenceBit == 0)
            {
                cout << "Replacing page " << frames[hand].pageNumber << " with " << pageNum << ".\n";
                frames[hand] = {pageNum, 1, true};
                hand = (hand + 1) % maxFrames;
                break;
            }
            else
            {
                cout << "Second chance to page " << frames[hand].pageNumber << ". Setting Reference Bit = 0.\n";
                frames[hand].referenceBit = 0;
                hand = (hand + 1) % maxFrames;
                attempts++;
            }
        }
    }

    void displayFrames()
    {
        cout << "Current Frames: \n";
        for (auto &p : frames)
        {
            cout << "Page: " << p.pageNumber << " | Ref: " << p.referenceBit;
            cout << endl;
        }
        cout << "-----------\n";
    }
};

int main()
{
    int frameCount;
    cout << "Enter number of frames: ";
    cin >> frameCount;

    LRU_Approx cache(frameCount);

    int n;
    cout << "Enter number of page accesses: ";
    cin >> n;

    cout << "Enter page numbers: \n";
    for (int i = 0; i < n; i++)
    {
        int page;
        cin >> page;
        cache.accessPage(page);
        cache.displayFrames();
    }

    return 0;
}
