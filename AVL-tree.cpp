#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

int height(Node* n) {
    return n ? n->height : 0;
}

int getBalanceFactor(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

Node* createNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->height = 1;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T = x->right;
    
    x->right = y;
    y->left = T;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T = y->left;
    
    y->left = x;
    x->right = T;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node* insert(Node* node, int key) {
    if (!node) return createNode(key); // если дерево пусто, создаем новый узел

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalanceFactor(node);

    if (balance > 1 && key < node->left->key) {
        return rotateRight(node);
    } 

    if (balance < -1 && key > node->right->key) {
        return rotateLeft(node);
    }

    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

Node* findMin(Node* node) { // спускаемся в левую часть рекурсивно - гарантированно min элемент  
    while (node->left) {
        node = node->left;
    }
    return node;
}

Node* erase(Node* root, int key) {
    if (!root) return root; // если дерево пусто, возвращаем nullptr

    if (key < root->key) {
        root->left = erase(root->left, key); // рекурсивно спускаемся в левую сторону
    } else if (key > root->key) {
        root->right = erase(root->right, key);
    } else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            Node* temp = findMin(root->right);
            root->key = temp->key;
            root->right = erase(root->right, temp->key);
        }
    }

    if (!root) return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalanceFactor(root); // проверяем дельту 

    if (balance > 1 && getBalanceFactor(root->left) >= 0) { // восстанавливаем инвариант
        return rotateRight(root);
    } 

    if (balance < -1 && getBalanceFactor(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance <  -1 && getBalanceFactor(root->right) <= 0) {
        return rotateLeft(root);
    }

    if (balance < -1 && getBalanceFactor(root->right)) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

bool find(Node* root, int key) {
    if (!root) return false; //если дерево пусто 

    if (key < root->key) {
        return find(root->left, key);
    } else if (key > root->key) {
        return find(root->right, key);
    } else {
        return true;
    }
}

void print(Node* root, int level) {
    if (root) {
        cout << " lvl: (" << level << ") " << root->key << " ";
        print(root->left, ++level);
        print(root->right,++level);
    }
}

int main() {
    Node* tree = nullptr;

    for (int i = 10; i <= 100; i+=10) {
        tree = insert(tree, i);
    }
    print(tree, 1);
    cout << endl;
    tree = erase(tree, 30);
    cout << "Дерево после удаления 20: ";
    print(tree, 1);
    cout << endl;

    cout << "Find 30 in tree: " << (find(tree, 30) ? "Yes" : "No") << endl;
    cout << "Find 100 in tree: " << (find(tree, 100) ? "Yes" : "No") << endl;

    return 0;
}