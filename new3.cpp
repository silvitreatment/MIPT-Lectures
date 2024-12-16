#include <bits/stdc++.h>
using namespace std;

vector<long long> generateArray(size_t n) {
    vector<long long> array(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<long long> dist(0, static_cast<long long>(n) * n * n - 1);

    for (size_t i = 0; i < n; ++i) {
        array[i] = dist(gen);
    }

    return array;
}

void radixSort(vector<long long>& array) {
    long long maxValue = *max_element(array.begin(), array.end());
    long long exp = 1;
    vector<long long> output(array.size());

    while (maxValue / exp > 0) {
        vector<int> count(10, 0); 

        for (long long num : array) {
            ++count[(num / exp) % 10];
        }

        for (int i = 1; i < 10; ++i) {
            count[i] += count[i - 1];
        }

        for (int i = array.size() - 1; i >= 0; --i) {
            int digit = (array[i] / exp) % 10;
            output[--count[digit]] = array[i];
        }

        array = output;
        exp *= 10;
    }
}

int main() {

    size_t n = 1e5; 

    vector<long long> array = generateArray(n);
    vector<long long> arrayCopy = array;

    auto startRadix = chrono::high_resolution_clock::now();
    radixSort(array);
    auto endRadix = chrono::high_resolution_clock::now();
    chrono::duration<double> durationRadix = endRadix - startRadix;

    auto startStd = chrono::high_resolution_clock::now();
    sort(arrayCopy.begin(), arrayCopy.end());
    auto endStd = chrono::high_resolution_clock::now();
    chrono::duration<double> durationStd = endStd - startStd;

    bool isCorrect = (array == arrayCopy);

    cout << "совпадают ли сортировки: " << (isCorrect ? "да" : "нет") << endl;
    cout << "порязрядная сортировка (время): " << durationRadix.count() << " секунд" << endl;
    cout << "стандартная сортировка (время): " << durationStd.count() << " секунд" << endl;

    return 0;
}
