#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(nullptr));
    
    const int SIZE = 20;
    vector<int> arr(SIZE);
    
    // Генерация и вывод
    cout << "Исходный: ";
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 101 - 50;
        cout << arr[i] << " ";
    }
    
    // Сортировка кастомным компаратором
    sort(arr.begin(), arr.end(), [](int a, int b) {
        bool aEven = a % 2 == 0;
        bool bEven = b % 2 == 0;
        if (aEven != bEven) return aEven;        // чётные первыми
        if (aEven) return a < b;                  // чётные по возрастанию
        return a > b;                              // нечётные по убыванию
    });
    
    // Вывод результата
    cout << "\nРезультат: ";
    for (int num : arr) cout << num << " ";
    cout << endl;
    
    return 0;
}