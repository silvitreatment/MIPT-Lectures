#include <iostream>
#include <random>

std::mt19937 rng(std::random_device{}());

struct Node {
    int key, priority;
    Node *left, *right;
    
    Node(int k) : key(k), priority(rng()), left(nullptr), right(nullptr) {}
};

void split(Node* root, int key, Node*& left, Node*& right) {
    if (!root) {
        left = right = nullptr;
    } else if (key < root->key) {
        split(root->left, key, left, root->left);
        right = root;
    } else {
        split(root->right, key, root->right, right);
        left = root;
    }
}

Node* merge(Node* left, Node* right) {
    if (!left || !right) return left ? left : right;
    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    } else {
        right->left = merge(left, right->left);
        return right;
    }
}

void insert(Node*& root, int key) {
    Node* newNode = new Node(key);
    Node *left, *right;
    split(root, key, left, right);
    root = merge(merge(left, newNode), right);
}

void erase(Node*& root, int key) {
    if (!root) return;
    if (root->key == key) {
        Node* temp = merge(root->left, root->right);
        delete root;
        root = temp;
    } else if (key < root->key) {
        erase(root->left, key);
    } else {
        erase(root->right, key);
    }
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    std::cout << root->key << " ";
    inorder(root->right);
}

int main() {
    Node* root = nullptr;
    
    insert(root, 5);
    insert(root, 2);
    insert(root, 8);
    insert(root, 1);
    insert(root, 3);
    
    std::cout << "Inorder traversal: ";
    inorder(root);
    std::cout << std::endl;
    
    erase(root, 2);
    std::cout << "After deleting 2: ";
    inorder(root);
    std::cout << std::endl;
    
    return 0;
}
