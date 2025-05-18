#include <iostream>

using namespace std;

int main() {
    int arr[] = {2, 5, -8, 1, -4, 6, 3, -5, -9, 13, 0, 4, 9};
    int n = sizeof(arr) / sizeof(int);

    // Сортировка пузырьком
    for (int i = 1; i < n; i++)
        for (int j = 0; j < n-i; j++) {
            if (arr[j] > arr[j + 1]) {
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }

    for (int i = 0; i < n; i++)
        cout << arr[i] << ' ';
    cout << endl;

    return 0;
}