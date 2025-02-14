#include <iostream>
using namespace std;

class BTreeNode {
public:
    int *keys;
    int t;
    BTreeNode **children;
    int n;
    bool leaf;

    BTreeNode(int t, bool leaf);
    void traverse();
    BTreeNode *search(int k);
    void insertNonFull(int k);
    void splitChild(int i, BTreeNode *y);
    friend class BTree;
};

class BTree {
public:
    BTreeNode *root;
    int t;

    BTree(int t) { root = nullptr; this->t = t; }
    void traverse() { if (root) root->traverse(); }
    BTreeNode *search(int k) { return (root == nullptr) ? nullptr : root->search(k); }
    void insert(int k);
};

BTreeNode::BTreeNode(int t, bool leaf) {
    this->t = t;
    this->leaf = leaf;
    keys = new int[2*t - 1];
    children = new BTreeNode *[2*t];
    n = 0;
}

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (!leaf) children[i]->traverse();
        cout << " " << keys[i];
    }
    if (!leaf) children[i]->traverse();
}

BTreeNode *BTreeNode::search(int k) {
    int i = 0;
    while (i < n && k > keys[i])
        i++;
    if (keys[i] == k)
        return this;
    if (leaf)
        return nullptr;
    return children[i]->search(k);
}

void BTree::insert(int k) {
    if (!root) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    } else {
        if (root->n == 2*t - 1) {
            BTreeNode *s = new BTreeNode(t, false);
            s->children[0] = root;
            s->splitChild(0, root);
            int i = (s->keys[0] < k) ? 1 : 0;
            s->children[i]->insertNonFull(k);
            root = s;
        } else {
            root->insertNonFull(k);
        }
    }
}

void BTreeNode::insertNonFull(int k) {
    int i = n - 1;
    if (leaf) {
        while (i >= 0 && keys[i] > k) {
            keys[i+1] = keys[i];
            i--;
        }
        keys[i+1] = k;
        n++;
    } else {
        while (i >= 0 && keys[i] > k)
            i--;
        if (children[i+1]->n == 2*t - 1) {
            splitChild(i+1, children[i+1]);
            if (keys[i+1] < k)
                i++;
        }
        children[i+1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode *y) {
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j+t];
    if (!y->leaf)
        for (int j = 0; j < t; j++)
            z->children[j] = y->children[j+t];
    y->n = t - 1;
    for (int j = n; j >= i+1; j--)
        children[j+1] = children[j];
    children[i+1] = z;
    for (int j = n-1; j >= i; j--)
        keys[j+1] = keys[j];
    keys[i] = y->keys[t-1];
    n++;
}

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
    
    cout << "Traversal of the constructed tree: ";
    t.traverse();
    cout << endl;
    return 0;
}
