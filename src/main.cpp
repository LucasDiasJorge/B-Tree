#include <iostream>
#include <vector>
using namespace std;

class BTreeNode {
public:
    vector<int> keys;
    vector<BreeNode*> Children;
    bool lead;
    int t;

    BTreeNode(int _t, bool _leadt);

    void traverse();
    BTreeNode* search(int key);

	void insertNonFull(int key);
    void splitChild(int i, BTreeNode* y);

    friend class BTree;
};

class BTree {
    BTreeNode* root;
    int t;

    BTree(int _t) {
		root = nullptr;
        t = _t;
    }

    void traverse() {
        if (root != nullptr) {
            root->traverse();
		}
    }

    BTreeNode* search(int key) {
        return (root == nullptr) ? nullptr : root->search(key);
    }

    void insert(int key);
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}