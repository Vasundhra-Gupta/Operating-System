#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <list>

using namespace std;

//-----------------------------------
// Buddy Allocator
//-----------------------------------
class BuddyAllocator {
public:
    BuddyAllocator(int totalSize) : totalSize(totalSize) {
        memory = vector<bool>(totalSize / pageSize, true);  // true = free
    }

    int allocate() {
        for (int i = 0; i < memory.size(); ++i) {
            if (memory[i]) {
                memory[i] = false;
                cout << "[Buddy] Allocated 4KB block at page " << i << endl;
                return i;
            }
        }
        cout << "[Buddy] No free 4KB blocks!" << endl;
        return -1;
    }

    void deallocate(int index) {
        if (index >= 0 && index < memory.size()) {
            memory[index] = true;
            cout << "[Buddy] Deallocated 4KB block at page " << index << endl;
        }
    }

private:
    const int pageSize = 4 * 1024; // 4KB
    int totalSize;
    vector<bool> memory; // track free pages
};

//-----------------------------------
// Slab Allocator
//-----------------------------------
class SlabAllocator {
public:
    SlabAllocator(BuddyAllocator& buddy, int objSize) : buddy(buddy), objSize(objSize) {
        objectsPerSlab = (4 * 1024) / objSize;
    }

    void* allocate() {
        for (auto& slab : slabs) {
            if (!slab.freeList.empty()) {
                void* obj = slab.freeList.back();
                slab.freeList.pop_back();
                cout << "[Slab] Allocated object from existing slab" << endl;
                return obj;
            }
        }

        // No free space, request a new slab from buddy
        int pageIndex = buddy.allocate();
        if (pageIndex == -1) return nullptr;

        Slab newSlab;
        newSlab.pageIndex = pageIndex;

        for (int i = 0; i < objectsPerSlab; ++i) {
            newSlab.freeList.push_back(reinterpret_cast<void*>(i));
        }

        slabs.push_back(newSlab);
        cout << "[Slab] Created new slab from buddy page: " << pageIndex << endl;

        void* obj = newSlab.freeList.back();
        newSlab.freeList.pop_back();
        return obj;
    }

    void deallocate(void* obj) {
        for (auto& slab : slabs) {
            // For simplicity we treat obj as index here
            slab.freeList.push_back(obj);

            if (slab.freeList.size() == objectsPerSlab) {
                buddy.deallocate(slab.pageIndex);
                slab.markedForDeletion = true;
                cout << "[Slab] Released slab back to buddy allocator" << endl;
            }
            return;
        }
    }

private:
    struct Slab {
        int pageIndex;
        list<void*> freeList;
        bool markedForDeletion = false;
    };

    BuddyAllocator& buddy;
    int objSize;
    int objectsPerSlab;
    vector<Slab> slabs;
};

//-----------------------------------
// Example Usage
//-----------------------------------
int main() {
    BuddyAllocator buddy(64 * 1024); // 64KB total memory
    SlabAllocator slab(buddy, 256); // slab for 256B objects

    void* obj1 = slab.allocate();
    void* obj2 = slab.allocate();

    slab.deallocate(obj1);
    slab.deallocate(obj2);

    return 0;
}
