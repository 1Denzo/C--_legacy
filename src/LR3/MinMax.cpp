#include <iostream>
using namespace std;

int main() {
    int arr[] = {2, 5, -8, 1, -4, 6, 3, -5, -9, 13, 0, 4, 9};
    int n = sizeof(arr) / sizeof(int);
    
    cout << "Исходный массив: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << ' ';
    cout << endl;
    
    // Min-Max сортировка (двусторонняя сортировка выбором)
    for (int left = 0, right = n - 1; left < right; left++, right--) {
        int min_idx = left;
        int max_idx = left;
        
        // Ищем минимум и максимум в текущем диапазоне
        for (int j = left + 1; j <= right; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
            if (arr[j] > arr[max_idx])
                max_idx = j;
        }
        
        // Обмен минимума с левым элементом
        int temp = arr[left];
        arr[left] = arr[min_idx];
        arr[min_idx] = temp;
        
        // Важная коррекция: если максимум был на месте left, он теперь на месте min_idx
        if (max_idx == left)
            max_idx = min_idx;
        
        // Обмен максимума с правым элементом
        temp = arr[right];
        arr[right] = arr[max_idx];
        arr[max_idx] = temp;
    }
    
    cout << "Отсортированный массив: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << ' ';
    cout << endl;
    
    return 0;
}