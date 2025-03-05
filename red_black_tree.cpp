#include <iostream>
using namespace std;

// Определяем два возможных цвета для узлов
enum Color { RED, BLACK };

// Структура узла красно-чёрного дерева
struct Node {
    int data;          // Значение узла
    Color color;       // Цвет узла (RED или BLACK)
    Node *left, *right, *parent; // Указатели на левое, правое поддерево и родителя

    // Конструктор: по умолчанию новый узел имеет красный цвет
    Node(int data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

// Класс красно-чёрного дерева
class RBTree {
private:
    Node* root; // Корень дерева

    // Функция для левого вращения вокруг узла x
    void leftRotate(Node* x) {
        Node* y = x->right;      // y – правый сын x
        x->right = y->left;      // переносим поддерево y->left в x->right
        if (y->left != nullptr)
            y->left->parent = x;
        y->parent = x->parent;   // устанавливаем родителя y равным родителю x
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else 
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    // Функция для правого вращения вокруг узла x
    void rightRotate(Node* x) {
        Node* y = x->left;       // y – левый сын x
        x->left = y->right;      // переносим поддерево y->right в x->left
        if (y->right != nullptr)
            y->right->parent = x;
        y->parent = x->parent;   // устанавливаем родителя y равным родителю x
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else 
            x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    // Функция для балансировки дерева после вставки нового узла
    void insertFixUp(Node* z) {
        while (z != root && z->parent->color == RED) {
            // Если родитель z – левый сын своего родителя
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right; // Дядя z
                // Если дядя существует и красный, делаем перекрашивание
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    // Если z – правый сын, выполняем левое вращение
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    // Выполняем правое вращение и перекрашивание
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else { // Аналогичный случай, когда родитель z – правый сын
                Node* y = z->parent->parent->left; // Дядя z
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        // Корень всегда черный
        root->color = BLACK;
    }

    // Рекурсивный обход дерева (inorder)
    void inorderHelper(Node* node) {
        if (node == nullptr)
            return;
        inorderHelper(node->left);
        cout << node->data << " (" << (node->color == RED ? "R" : "B") << ") ";
        inorderHelper(node->right);
    }

public:
    // Конструктор
    RBTree() : root(nullptr) {}

    // Функция вставки нового значения в дерево
    void insert(int data) {
        Node* z = new Node(data);
        Node* y = nullptr;
        Node* x = root;

        // Находим правильное место для вставки нового узла
        while (x != nullptr) {
            y = x;
            if (z->data < x->data)
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;
        if (y == nullptr) {
            // Если дерево пустое, новый узел становится корнем
            root = z;
        } else if (z->data < y->data) {
            y->left = z;
        } else {
            y->right = z;
        }

        // Новый узел всегда вставляется красным.
        z->color = RED;

        // Вызываем балансировку дерева, если нарушены свойства красно-чёрного дерева.
        insertFixUp(z);
    }

    // Функция для вывода inorder-прохождения дерева
    void inorder() {
        inorderHelper(root);
        cout << endl;
    }
};

// Пример использования красно-чёрного дерева
int main() {
    RBTree tree;
    // Вставляем значения
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);
    tree.insert(5);
    tree.insert(1);

    cout << "Inorder обход дерева: " << endl;
    tree.inorder();

    return 0;
}
