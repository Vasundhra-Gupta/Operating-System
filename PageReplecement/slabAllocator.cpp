#include <iostream>
#include <vector>
using namespace std;

class SlabAllocator {
private:
    struct Object {
        bool isFree;
        Object() : isFree(true) {}
    };

    struct Slab {
        vector<Object> objects;
        int freeCount;

        Slab(int objectCount) : freeCount(objectCount) {
            for (int i = 0; i < objectCount; ++i)
                objects.push_back(Object());
        }
    };

    vector<Slab*> slabs;
    int objectsPerSlab;

public:
    SlabAllocator(int objectsPerSlab = 8) : objectsPerSlab(objectsPerSlab) {}

    ~SlabAllocator() {
        for (auto slab : slabs) delete slab;
    }

    // Allocate an object
    Object* allocate() {
        // Find a slab with free space
        for (auto slab : slabs) {
            if (slab->freeCount > 0) {
                for (auto& obj : slab->objects) {
                    if (obj.isFree) {
                        obj.isFree = false;
                        slab->freeCount--;
                        cout << "Allocated object from existing slab.\n";
                        return &obj;
                    }
                }
            }
        }

        // No available slab, create new slab
        Slab* newSlab = new Slab(objectsPerSlab);
        slabs.push_back(newSlab);
        newSlab->objects[0].isFree = false;
        newSlab->freeCount--;
        cout << "Created new slab and allocated object.\n";
        return &newSlab->objects[0];
    }

    // Deallocate an object
    void deallocate(Object* obj) {
        obj->isFree = true;
        for (auto slab : slabs) {
            for (auto& o : slab->objects) {
                if (&o == obj) {
                    slab->freeCount++;
                    cout << "Deallocated object.\n";
                    return;
                }
            }
        }
    }

    // Print slabs status
    void printSlabs() {
        cout << "\n--- Slabs Status ---\n";
        int slabIndex = 0;
        for (auto slab : slabs) {
            cout << "Slab " << slabIndex++ << ": ";
            for (auto& obj : slab->objects) {
                cout << (obj.isFree ? "[Free] " : "[Used] ");
            }
            cout << endl;
        }
        cout << "---------------------\n";
    }
};

int main() {
    SlabAllocator allocator(4); // Each slab has 4 objects

    auto* o1 = allocator.allocate();
    auto* o2 = allocator.allocate();
    auto* o3 = allocator.allocate();
    auto* o4 = allocator.allocate();
    auto* o5 = allocator.allocate();  // Will trigger new slab

    allocator.printSlabs();

    allocator.deallocate(o2);
    allocator.deallocate(o4);

    allocator.printSlabs();

    auto* o6 = allocator.allocate();  // Reuses free object

    allocator.printSlabs();

    return 0;
}
