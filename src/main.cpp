#include <iostream>
#include <vector>
using namespace std;

class BTreeNode {
public:
    vector<int> keys;
    vector<BTreeNode*> Children;
    bool leaf;
    int t;

    BTreeNode(int _t, bool _leaf) {
		t = _t;
        leaf = _leaf;
    }

    void traverse() {
        int i;
        for (i = 0; i < keys.size(); i++) {
            if (!leaf) {
				Children[i]->traverse();
            }
            cout << keys[i] << " ";
        }
    }


    BTreeNode* search(int key) {
        int i = 0;

        while (i < keys.size() && key > keys[i]) {
            i++;
        }

        if (i < keys.size() && keys[i] == key) {
			return this; // Key found
        }

        if (leaf) {
			return nullptr; // Key not found in leaf node
        }
		return Children[i]->search(key); // Recur on the child
    }

    void splitChild(int i, BTreeNode* y) {
        BTreeNode* z = new BTreeNode(y->t, y->leaf);

        for (int j = 0; j < t - 1; j++) {
            z->keys.push_back(y->keys[j + t]);
        }

        if (!y->leaf) {
            for (int j = 0; j < t; j++) {
                z->Children.push_back(y->Children[j + t]);
            }
        }

        y->keys.resize(t - 1);
        if (!y->leaf) {
            y->Children.resize(t);
        }

        Children.insert(Children.begin() + i + 1, z);
        keys.insert(keys.begin() + i, y->keys[t - 1]);
    }


    void insertNonFull(int key) {

        int i = keys.size() - 1;
        if (leaf) {
            keys.push_back(0);
            while (i >= 0 && keys[i] > key) {
                keys[i + 1] = keys[i];
                i--;
            }
            keys[i + 1] = key;
        }
        else {
            while (i >= 0 && keys[i] > key)
                i--;
            i++;
            if (Children[i]->keys.size() == 2 * t - 1) {
                splitChild(i, Children[i]);
                if (keys[i] < key)
                    i++;
            }
            Children[i]->insertNonFull(key);
        }
    }



    friend class BTree;
};

class BTree {
public:
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

    void insert(int key) {
        if (root == nullptr) {
            root = new BTreeNode(t, true);
            root->keys.push_back(key);
        }
        else {
            if (root->keys.size() == 2 * t -1) {
                BTreeNode* s = new BTreeNode(t, false);
                s->Children.push_back(root);
                s->splitChild(0, root);

                int i = 0;

                if (s->keys[0] < key) {
                    i++;
                }
                s->Children[i]->insertNonFull(key);
                root = s;
            }
            else {
                root->insertNonFull(key);
            }
        }
    }
};

int main() {

    BTree t(3);

	t.insert(10);
	t.insert(20);
	t.insert(5);
	t.insert(6);
	t.insert(12);
	t.insert(30);
	t.insert(7);
	t.insert(17);

	cout << "Traversal of the B-tree is: ";
	t.traverse();
	cout << endl;

	int key = 6;
    (t.search(key) != nullptr) ? cout << "\nPresent" << endl : cout << "\nNot Present" << endl;

    return 0;
}