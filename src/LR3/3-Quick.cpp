#include <iostream>

using namespace std;

void quickSort(int arr[], int start, int end) {
    if (end == start)
        return;
    // Выбираем опорный элемент
    int pivot = arr[end];
    int storeIndex = start;
    // По всем элементам в границах pbeg..pend
    for (int i = start; i <= end - 1; i++)
        // если элемент <= опорного, перемещаем в левую часть от опорного
        if (arr[i] <= pivot) {
            int t = arr[i];
            arr[i] = arr[storeIndex];
            arr[storeIndex] = t;
            storeIndex++;
        }

    int n = arr[storeIndex];
    arr[storeIndex] = arr[end];
    arr[end] = n;
    // Повторяем на правой и левой части массива
    if (storeIndex > start)
        quickSort(arr, start, storeIndex - 1);
    if (storeIndex < end)
        quickSort(arr, storeIndex + 1, end);
}

void quickSort(int arr[], int n) {
    quickSort(arr, 0, n - 1);
}

int main() {
    int arr[] = {2, 5, -8, 1, -4, 6, 3, -5, -9, 13, 0, 4, 9};
    int n = sizeof(arr) / sizeof(int);

    quickSort(arr, n);

    for (int i = 0; i < n; i++)
        cout << arr[i] << ' ';
    cout << endl;

    return 0;
}