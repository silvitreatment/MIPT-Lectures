#include <iostream>
using namespace std;

int main() {
    int number {25};
    int *pnumber {&number};
    cout << pnumber << endl;
}