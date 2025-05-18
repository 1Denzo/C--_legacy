#include <iostream>

using namespace std;

int main() {
    int arr[] = {2, 5, -8, 1, -4, 6, 3, -5, -9, 13, 0, 4, 9};
    int imin, imax = 0;

    // Сортировка методом min-max
    int n = sizeof(arr) / sizeof(int);
    for (int i = 0; i < n - 1; i++) {
        imin = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[imin])
                imin = j;
        int t = arr[i];
        arr[i] = arr[imin];
        arr[imin] = t;
    }
    for (int i = 0; i < n; i++)
        cout << arr[i] << ' ';
    cout << endl;

    return 0;
}