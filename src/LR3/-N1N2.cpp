// Программа, которая для массива сненерированных целых значений выполняет сортировку по убыванию на интервале индексов от N1 до N2
// задаваемых пользователем после вывода сгенерированного массива:

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
    
    // Генерация
    cout << "Массив: ";
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 199 - 99;
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // Ввод
    int N1, N2;
    cout << "N1 N2: ";
    cin >> N1 >> N2;
    
    // Сортировка
    sort(arr.begin() + N1, arr.begin() + N2 + 1, greater<int>());
    
    // Вывод
    cout << "Результат: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    return 0;
}