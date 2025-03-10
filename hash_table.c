#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// Структура для элемента хеш-таблицы
typedef struct Node {
    char *key;
    int value;
    struct Node *next;
} Node;

// Хеш-таблица (массив указателей на узлы)
Node *hashTable[TABLE_SIZE];

// Функция хеширования
unsigned int hash(const char *key) {
    unsigned int hashValue = 0;
    while (*key) {
        hashValue = (hashValue * 31) + *key;
        key++;
    }
    return hashValue % TABLE_SIZE;
}

// Функция вставки элемента в хеш-таблицу
void insert(const char *key, int value) {
    unsigned int index = hash(key);
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->value = value;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

// Функция поиска элемента в хеш-таблице
int search(const char *key) {
    unsigned int index = hash(key);
    Node *current = hashTable[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return -1; // Если ключ не найден
}

// Функция удаления элемента из хеш-таблицы
void delete(const char *key) {
    unsigned int index = hash(key);
    Node *current = hashTable[index];
    Node *prev = NULL;

    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                hashTable[index] = current->next;
            }
            free(current->key);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Функция вывода хеш-таблицы
void printTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d]: ", i);
        Node *current = hashTable[i];
        while (current) {
            printf("(%s, %d) -> ", current->key, current->value);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// Очистка памяти
void freeTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = hashTable[i];
        while (current) {
            Node *temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

int main() {
    insert("Alice", 25);
    insert("Bob", 30);
    insert("Charlie", 35);
    insert("David", 40);
    insert("Eve", 45);
    
    printTable();
    
    printf("\nSearch for Bob: %d\n", search("Bob"));
    printf("Search for Eve: %d\n", search("Eve"));
    
    delete("Alice");
    printf("\nAfter deleting Alice:\n");
    printTable();
    
    freeTable();
    return 0;
}
