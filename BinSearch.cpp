#include <iostream>

using namespace std;

int const notFound = -1;

int binSearch(int arr[], int target, int size) {
    int right = size - 1;
    int left = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;

        }

    }
    return notFound;
}

int main() {
    int arr[] = {1,3,5,7,8,209};
    int target = 7;
    int size = sizeof(arr) / sizeof(arr[0]);

    int result = binSearch(arr, target, size);
    if (result != notFound) {
        cout << "The element was found on the index " << result << endl;
    } else {
        cout << "The element wasn't found" << endl;
    }
    
    target = 208;

    result = binSearch(arr, target, size);
    if (result != notFound) {
        cout << "The element was found on the index " << result << endl;
    } else {
        cout << "The element wasn't found" << endl;
    }
    return 0;
}