#include <iostream>
#include <vector>

using namespace std;

int partition(vector<int>& arr, int low, int high) {

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {

        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);

        }
    }

    swap(arr[i+1], arr[high]);
    return i+1;
}

void quickSort(vector<int>& arr, int low, int high) {

    if (low < high) {
        int pi = partition(arr, low, high);

        // Recurive sorting of elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    
    vector<int> arr = {10, 7, 8, 9, 1, 5};
    int n = arr.size();

    cout << "original array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    quickSort(arr, 0, n - 1);

    cout << "sorted array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}