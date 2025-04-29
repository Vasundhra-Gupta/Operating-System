#include <iostream>
#include <cmath>

using namespace std;

class BuddyAllocator {
private:
    struct Node {
        int size;         // Size of block
        bool isFree;      // Is this block free
        Node* left;       // Left buddy
        Node* right;      // Right buddy
        Node* parent;     // Parent block
        int id;           // For identification

        Node(int s, Node* p = nullptr, int identifier = 0)
            : size(s), isFree(true), left(nullptr), right(nullptr), parent(p), id(identifier) {}
    };

    Node* root;
    int totalSize;
    int blockCounter = 1;  // Unique ID for allocations

public:
    BuddyAllocator(int totalMemory) {
        totalSize = nextPowerOfTwo(totalMemory);
        root = new Node(totalSize);
        cout << "Buddy Allocator initialized with size: " << totalSize << " bytes.\n";
    }

    // Find next power of 2 >= size
    int nextPowerOfTwo(int size) {
        int power = 1;
        while (power < size) power *= 2;
        return power;
    }

    Node* allocate(Node* node, int reqSize) {
        if (!node) return nullptr;

        // If block is not free or too small
        if (!node->isFree || node->size < reqSize)
            return nullptr;

        // Perfect match
        if (node->size == reqSize && node->left == nullptr && node->right == nullptr) {
            node->isFree = false;
            node->id = blockCounter++;
            return node;
        }

        // If node is bigger, split if not already split
        if (node->left == nullptr && node->right == nullptr) {
            node->left = new Node(node->size / 2, node);
            node->right = new Node(node->size / 2, node);
        }

        // Try allocating on left first
        Node* allocated = allocate(node->left, reqSize);
        if (!allocated) {
            allocated = allocate(node->right, reqSize);
        }
        return allocated;
    }

    void* allocate(int reqSize) {
        int allocSize = nextPowerOfTwo(reqSize);
        Node* node = allocate(root, allocSize);
        if (node) {
            cout << "Allocated " << reqSize << " bytes (actual " << allocSize << " bytes) in block ID: " << node->id << endl;
            return node;
        } else {
            cout << "Allocation failed for " << reqSize << " bytes.\n";
            return nullptr;
        }
    }

    void deallocate(Node* node) {
        if (!node) return;
        node->isFree = true;
        cout << "Deallocated block ID: " << node->id << " of size " << node->size << " bytes\n";
        node->id = 0;

        // Try to merge upward
        merge(node->parent);
    }

    void deallocate(void* ptr) {
        Node* node = (Node*)ptr;
        deallocate(node);
    }

    void merge(Node* node) {
        if (!node || !node->left || !node->right) return;

        if (node->left->isFree && node->right->isFree) {
            // Merge buddies
            delete node->left;
            delete node->right;
            node->left = nullptr;
            node->right = nullptr;
            node->isFree = true;
            cout << "Merged block of size " << node->size << " bytes\n";

            // Continue merging upward
            merge(node->parent);
        }
    }

    void printTree(Node* node, int level = 0) {
        if (!node) return;

        for (int i = 0; i < level; ++i) cout << "  ";
        cout << "|- [" << (node->isFree ? "Free" : "Used") << "] Size: " << node->size;
        if (!node->isFree) cout << " (ID: " << node->id << ")";
        cout << endl;

        printTree(node->left, level + 1);
        printTree(node->right, level + 1);
    }

    void printMemoryTree() {
        cout << "\n--- Memory Tree ---\n";
        printTree(root);
        cout << "--------------------\n";
    }
};

int main() {
    BuddyAllocator allocator(1024);  // 1KB memory

    void* a = allocator.allocate(200);  // Allocate ~256 bytes
    void* b = allocator.allocate(100);  // Allocate ~128 bytes
    void* c = allocator.allocate(300);  // Allocate ~512 bytes

    allocator.printMemoryTree();

    allocator.deallocate(a);
    allocator.deallocate(b);
    allocator.deallocate(c);

    allocator.printMemoryTree();

    return 0;
}
