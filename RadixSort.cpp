#include <bits/stdc++.h>
using namespace std;

mt19937 rng(random_device{}());

int getRandomNumber(int low, int high) {
    uniform_int_distribution<int> dist(low, high);
    return dist(rng);
}

int getDigit(int number, int exp) {
    return (number / exp) % 10;
}
bool checkSort(vector<int>&arr) {
    bool flag = true;
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}
void countingSort(vector<int>& arr, int exp){
    int n = arr.size();
    vector<int> output(n);
    vector<int> count(10, 0);
    
    for (int i = 0; i < n; i++) {
        int digit = getDigit(arr[i], exp);
        count[digit]++;
    }
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    
    for (int i = n - 1; i >= 0; i--) {
        int digit = getDigit(arr[i], exp);
        output[--count[digit]] = arr[i];
    }
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void radixSort(vector<int>&arr) {
    int maxNumber = *max_element(arr.begin(), arr.end());
    for (int exp = 1; maxNumber / exp > 0; exp *= 10) {
        countingSort(arr, exp);
    }
}

int main() {
    const int n = 1000;
    vector<int> arr(n);
    for (int i{}; i < n; i++) {
        arr[i] = getRandomNumber(0, 1000);
    }
    radixSort(arr);
    cout << checkSort(arr) << endl;
    return 0;
}