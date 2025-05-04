#include <iostream>
using namespace std;

int main() {
    int power(int, int);
    for (int i = 0; i < 10; i++) {
        int k = power(2, i);
        cout << "i = " << i << " k = " << k << endl;
    }

    return 0;
}

int power(int n, int x) {
    int p = 1;
    for (int i = 1; i < x; i++) {
        p *= n;
    }

    return p;
}