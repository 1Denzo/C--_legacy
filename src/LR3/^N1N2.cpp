// Программа, которая для массива сненерированных целых значений выполняет сортировку по возрастанию на интервале индексов от N1 до N2
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
    
    // Генерация и вывод
    cout << "Сгенерированный массив:\n";
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 201 - 100;
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // Ввод индексов
    int N1, N2;
    cout << "\nВведите начальный индекс N1: ";
    cin >> N1;
    cout << "Введите конечный индекс N2: ";
    cin >> N2;
    
    // Проверка
    if (N1 < 0 || N2 >= SIZE || N1 > N2) {
        cout << "Ошибка: неверный диапазон!" << endl;
        return 1;
    }
    
    // Сортировка интервала
    cout << "\nСортируем интервал [" << N1 << ", " << N2 << "]..." << endl;
    sort(arr.begin() + N1, arr.begin() + N2 + 1);
    
    // Вывод результата
    cout << "\nРезультат:\n";
    for (int i = 0; i < SIZE; i++) {
        if (i >= N1 && i <= N2)
            cout << "[" << arr[i] << "] "; // выделяем скобками
        else
            cout << arr[i] << " ";
    }
    cout << endl;
    
    return 0;
}