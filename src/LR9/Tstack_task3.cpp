#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Шаблон класса TStack
template <class T>
class TStack {
private:
    T *arr;          // Массив для хранения элементов
    int top;         // Индекс верхнего элемента
    int maxSize;     // Максимальный размер стека
    
public:
    // Конструкторы
    TStack(int size = 100) {
        maxSize = size;
        arr = new T[maxSize];
        top = -1;
    }
    
    // Деструктор
    ~TStack() {
        delete[] arr;
    }
    
    // Операции со стеком
    void Push(T value) {
        if (top < maxSize - 1) {
            arr[++top] = value;
        }
    }
    
    T Pop() {
        if (!IsEmpty()) {
            return arr[top--];
        }
        return T(); // Возвращаем значение по умолчанию если стек пуст
    }
    
    T Top() {
        if (!IsEmpty()) {
            return arr[top];
        }
        return T();
    }
    
    bool IsEmpty() {
        return top == -1;
    }
    
    bool IsFull() {
        return top == maxSize - 1;
    }
    
    int GetSize() {
        return top + 1;
    }
};

// Функция для сортировки состава с использованием тупика
void SortTrain(int *train, int n) {
    TStack<int> deadEnd(n);  // Тупик (стек)
    int *output = new int[n];  // Выходной путь
    int outputIndex = 0;
    
    int nextWanted = 1;  // Какой вагон ожидается следующим
    
    cout << "Процесс сортировки:" << endl;
    cout << "Вход\tТупик\tВыход" << endl;
    cout << "---------------------" << endl;
    
    for (int i = 0; i < n; i++) {
        int currentWagon = train[i];
        
        // Пока текущий вагон не равен ожидаемому
        if (currentWagon == nextWanted) {
            // Вагон сразу отправляется на выход
            output[outputIndex++] = currentWagon;
            cout << currentWagon << "\t";
            
            // Проверяем, может быть нужные вагоны есть в тупике
            while (!deadEnd.IsEmpty() && deadEnd.Top() == nextWanted + 1) {
                output[outputIndex++] = deadEnd.Pop();
                nextWanted++;
            }
            
            nextWanted++;
        } else {
            // Отправляем вагон в тупик
            deadEnd.Push(currentWagon);
            cout << currentWagon << "\t";
        }
        
        // Выводим содержимое тупика
        if (!deadEnd.IsEmpty()) {
            TStack<int> temp(n);
            cout << "|";
            while (!deadEnd.IsEmpty()) {
                int val = deadEnd.Pop();
                temp.Push(val);
                cout << " " << val;
            }
            cout << "\t";
            
            // Восстанавливаем стек
            while (!temp.IsEmpty()) {
                deadEnd.Push(temp.Pop());
            }
        } else {
            cout << "| \t";
        }
        
        // Выводим выход
        cout << "|";
        for (int j = 0; j < outputIndex; j++) {
            cout << " " << output[j];
        }
        cout << endl;
    }
    
    // Выталкиваем оставшиеся вагоны из тупика
    while (!deadEnd.IsEmpty()) {
        output[outputIndex++] = deadEnd.Pop();
    }
    
    // Копируем отсортированный состав обратно
    for (int i = 0; i < n; i++) {
        train[i] = output[i];
    }
    
    delete[] output;
}

// Функция для сортировки в порядке убывания
void SortTrainDesc(int *train, int n) {
    TStack<int> deadEnd(n);
    int *output = new int[n];
    int outputIndex = 0;
    
    int nextWanted = n;  // Ожидаем самый большой вагон
    
    cout << "\nСортировка в порядке убывания:" << endl;
    cout << "Вход\tТупик\tВыход" << endl;
    cout << "---------------------" << endl;
    
    for (int i = 0; i < n; i++) {
        int currentWagon = train[i];
        
        if (currentWagon == nextWanted) {
            output[outputIndex++] = currentWagon;
            cout << currentWagon << "\t";
            
            while (!deadEnd.IsEmpty() && deadEnd.Top() == nextWanted - 1) {
                output[outputIndex++] = deadEnd.Pop();
                nextWanted--;
            }
            
            nextWanted--;
        } else {
            deadEnd.Push(currentWagon);
            cout << currentWagon << "\t";
        }
        
        // Вывод состояния (аналогично предыдущей функции)
        if (!deadEnd.IsEmpty()) {
            TStack<int> temp(n);
            cout << "|";
            while (!deadEnd.IsEmpty()) {
                int val = deadEnd.Pop();
                temp.Push(val);
                cout << " " << val;
            }
            cout << "\t";
            
            while (!temp.IsEmpty()) {
                deadEnd.Push(temp.Pop());
            }
        } else {
            cout << "| \t";
        }
        
        cout << "|";
        for (int j = 0; j < outputIndex; j++) {
            cout << " " << output[j];
        }
        cout << endl;
    }
    
    while (!deadEnd.IsEmpty()) {
        output[outputIndex++] = deadEnd.Pop();
    }
    
    for (int i = 0; i < n; i++) {
        train[i] = output[i];
    }
    
    delete[] output;
}

int main() {
    // Демонстрация различных способов создания стеков
    TStack<int> st_int1;           // стек значений int, размер по умолчанию
    TStack<int> st_int(40);        // Стек на 40 элементов
    TStack<long> *ptr;              // Указатель на стек для long
    TStack<double> dbl[10];         // Массив стеков для double
    TStack<char*> cSt;              // Стек указателей на char
    TStack<char*> *ptrcSt;          // Указатель на стек для указателей на char
    
    // Выделение памяти для ptr
    ptr = new TStack<long>(30);
    
    // Функция Init() из задания
    void Init() {
        ptrcSt = new TStack<char*>(20);
    }
    
    // Вызываем Init для инициализации ptrcSt
    Init();
    
    cout << "Программа сортировки железнодорожного состава с использованием тупика" << endl;
    cout << "=====================================================================" << endl;
    
    // Пример 1: Исходный состав из задания (1 5 3)
    cout << "\nПример 1: Состав [1, 5, 3]" << endl;
    int train1[] = {1, 5, 3};
    int n1 = sizeof(train1) / sizeof(train1[0]);
    
    cout << "Исходный состав: ";
    for (int i = 0; i < n1; i++) cout << train1[i] << " ";
    cout << endl;
    
    SortTrain(train1, n1);
    
    cout << "Отсортированный состав: ";
    for (int i = 0; i < n1; i++) cout << train1[i] << " ";
    cout << endl;
    
    // Пример 2: Случайный состав
    cout << "\nПример 2: Случайный состав" << endl;
    const int N = 6;
    int train2[N];
    srand(time(NULL));
    
    cout << "Исходный состав: ";
    for (int i = 0; i < N; i++) {
        train2[i] = rand() % 9 + 1;  // Случайные числа от 1 до 9
        cout << train2[i] << " ";
    }
    cout << endl;
    
    SortTrain(train2, N);
    
    cout << "Отсортированный состав: ";
    for (int i = 0; i < N; i++) cout << train2[i] << " ";
    cout << endl;
    
    // Пример 3: Сортировка в обратном порядке
    cout << "\nПример 3: Сортировка в порядке убывания" << endl;
    int train3[] = {3, 1, 4, 2, 5};
    int n3 = sizeof(train3) / sizeof(train3[0]);
    
    cout << "Исходный состав: ";
    for (int i = 0; i < n3; i++) cout << train3[i] << " ";
    cout << endl;
    
    SortTrainDesc(train3, n3);
    
    cout << "Отсортированный состав (убывание): ";
    for (int i = 0; i < n3; i++) cout << train3[i] << " ";
    cout << endl;
    
    // Освобождение памяти
    delete ptr;
    delete ptrcSt;
    
    return 0;
}