#include <iostream>
#include <vector>
using namespace std;

class MinHeap {
private:
    vector<int> heap;
    
    // Вспомогательные функции для получения индексов
    int parent(int i) const { return (i - 1) / 2; }
    int left(int i) const { return (i * 2) + 1; }
    int right(int i) const { return (i * 2) + 2; }

    // Просеивание элемента вверх
    void siftUp(int i) {
        while (i != 0 && heap[i] < heap[parent(i)]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    // Просеивание элемента вниз
    void siftDown(int i) {
        int smallest = i;
        int r = right(i);
        int l = left(i);

        if (l < heap.size() && heap[l] < heap[smallest]) 
            smallest = l;
        if (r < heap.size() && heap[r] < heap[smallest])
            smallest = r;

        if (smallest != i) {
            swap(heap[smallest], heap[i]);
            siftDown(smallest);
        }
    }

public:
    // Вставка элемента
    void insert(int value) {
        heap.push_back(value);
        siftUp(heap.size() - 1);
    }

    // Извлечение минимального элемента
    int extractMin() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }
        int result = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) {
            siftDown(0);
        }
        return result;
    }

    // Получение минимального элемента
    int getMin() const {
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }
        return heap[0];
    }

    // Размер кучи
    int size() const {
        return heap.size();
    }

    // Проверка на пустоту
    bool isEmpty() const {
        return heap.empty();
    }
}; 

int main() {
    MinHeap h;

    h.insert(3);
    h.insert(10);
    h.insert(5);
    h.insert(1);
    h.insert(12);

    cout << "Min: " << h.getMin() << endl;  // Ожидается: 1
    cout << "Extracting Min: " << h.extractMin() << endl;  // Ожидается: 1
    cout << "Min after extracting: " << h.getMin() << endl;  // Ожидается: 3

    return 0;
}
