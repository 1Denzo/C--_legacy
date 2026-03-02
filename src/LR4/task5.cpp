#include <iostream.h>
#include <alloc.h>
#include <string.h>
#include <stdlib.h>

// Функции с динамическим выделением памяти (используя calloc)
char* vvodStroki(const char* prompt);           // Ввод строки с динамическим выделением
char* kopir_dinamic(char* src);                  // Копирование строки в новую память
char* konkat_dinamic(char* str1, char* str2);    // Конкатенация с созданием новой строки
int sravn_dinamic(char* str1, char* str2);       // Сравнение строк (возвращает результат)

// Новые функции для работы с массивом строк
char** generirovatMassiv(int& size);             // Генерация массива строк
void vyvestiMassiv(char** massiv, int size);     // Вывод массива строк
void primenitFunkciiKMassivu(char** massiv, int size); // Применение функций к массиву
void osvoboditMassiv(char** massiv, int size);   // Освобождение памяти массива

// Ввод строки с динамическим выделением памяти через calloc
char* vvodStroki(const char* prompt)
{
    char buffer[256];
    cout << prompt;
    cin >> buffer;
    
    char* str = (char*)calloc(strlen(buffer) + 1, sizeof(char));
    
    if(str != NULL)
    {
        strcpy(str, buffer);
    }
    
    return str;
}

// Копирование строки с выделением новой памяти через calloc
char* kopir_dinamic(char* src)
{
    if(src == NULL) return NULL;
    
    char* dest = (char*)calloc(strlen(src) + 1, sizeof(char));
    
    if(dest != NULL)
    {
        for(int i = 0; i <= strlen(src); i++)
        {
            dest[i] = src[i];
        }
    }
    
    return dest;
}

// Конкатенация с созданием новой строки через calloc
char* konkat_dinamic(char* str1, char* str2)
{
    if(str1 == NULL || str2 == NULL) return NULL;
    
    char* result = (char*)calloc(strlen(str1) + strlen(str2) + 1, sizeof(char));
    
    if(result != NULL)
    {
        for(int i = 0; i < strlen(str1); i++)
        {
            result[i] = str1[i];
        }
        
        for(int i = 0; i < strlen(str2); i++)
        {
            result[strlen(str1) + i] = str2[i];
        }
    }
    
    return result;
}

// Сравнение строк (возвращает результат)
int sravn_dinamic(char* str1, char* str2)
{
    if(str1 == NULL || str2 == NULL) return 0;
    
    int i = 0;
    
    while(str1[i] != '\0' && str2[i] != '\0')
    {
        if(str1[i] < str2[i]) return -1;
        if(str1[i] > str2[i]) return 1;
        i++;
    }
    
    if(str1[i] == '\0' && str2[i] == '\0') return 0;
    if(str1[i] == '\0') return -1;
    return 1;
}

// Генерация массива строк
char** generirovatMassiv(int& size)
{
    cout << "Введите количество строк в массиве: ";
    cin >> size;
    
    // Выделяем память под массив указателей
    char** massiv = (char**)calloc(size, sizeof(char*));
    
    if(massiv == NULL)
    {
        cout << "Ошибка выделения памяти для массива!" << endl;
        return NULL;
    }
    
    cout << "\n--- Ввод элементов массива ---" << endl;
    for(int i = 0; i < size; i++)
    {
        cout << "Строка " << i + 1 << ": ";
        char buffer[256];
        cin >> buffer;
        
        massiv[i] = (char*)calloc(strlen(buffer) + 1, sizeof(char));
        if(massiv[i] != NULL)
        {
            strcpy(massiv[i], buffer);
        }
    }
    
    return massiv;
}

// Вывод массива строк
void vyvestiMassiv(char** massiv, int size)
{
    cout << "\n--- Содержимое массива ---" << endl;
    for(int i = 0; i < size; i++)
    {
        cout << "massiv[" << i << "] = \"" << massiv[i] << "\" (длина: " << strlen(massiv[i]) << ")" << endl;
    }
}

// Применение функций к массиву строк
void primenitFunkciiKMassivu(char** massiv, int size)
{
    if(size < 2)
    {
        cout << "\nДля сравнения нужно минимум 2 строки!" << endl;
        return;
    }
    
    cout << "\n=== ПРИМЕНЕНИЕ ФУНКЦИЙ К МАССИВУ СТРОК ===\n" << endl;
    
    // 1. Длина каждой строки (используем strlen)
    cout << "--- Длины строк ---" << endl;
    for(int i = 0; i < size; i++)
    {
        cout << "Строка " << i << ": " << strlen(massiv[i]) << " символов" << endl;
    }
    
    // 2. Сравнение первой строки с остальными
    cout << "\n--- Сравнение первой строки с остальными ---" << endl;
    for(int i = 1; i < size; i++)
    {
        int result = sravn_dinamic(massiv[0], massiv[i]);
        cout << "Сравнение massiv[0] с massiv[" << i << "]: ";
        if(result == 0) cout << "строки идентичны";
        else if(result < 0) cout << "первая меньше";
        else cout << "первая больше";
        cout << endl;
    }
    
    // 3. Копирование строк
    cout << "\n--- Копирование строк ---" << endl;
    for(int i = 0; i < size && i < 3; i++) // Копируем первые 3 строки (для примера)
    {
        char* copy = kopir_dinamic(massiv[i]);
        if(copy != NULL)
        {
            cout << "Оригинал massiv[" << i << "]: \"" << massiv[i] << "\"" << endl;
            cout << "Копия:                 \"" << copy << "\"" << endl;
            cout << "Сравнение: " << (sravn_dinamic(massiv[i], copy) == 0 ? "успешно" : "ошибка") << endl;
            cout << endl;
            free(copy);
        }
    }
    
    // 4. Конкатенация строк
    cout << "--- Конкатенация соседних строк ---" << endl;
    for(int i = 0; i < size - 1; i++)
    {
        char* concat = konkat_dinamic(massiv[i], massiv[i + 1]);
        if(concat != NULL)
        {
            cout << "massiv[" << i << "] + massiv[" << i + 1 << "] = \"" << concat << "\"" << endl;
            free(concat);
        }
    }
}

// Освобождение памяти массива
void osvoboditMassiv(char** massiv, int size)
{
    for(int i = 0; i < size; i++)
    {
        if(massiv[i] != NULL)
        {
            free(massiv[i]);
        }
    }
    free(massiv);
    cout << "\nПамять массива освобождена!" << endl;
}

// Главная функция
void main(void)
{
    cout << "РАБОТА С МАССИВОМ СТРОК" << endl;
    cout << "=======================" << endl;
    
    int size = 0;
    char** massiv = generirovatMassiv(size);
    
    if(massiv != NULL && size > 0)
    {
        vyvestiMassiv(massiv, size);
        primenitFunkciiKMassivu(massiv, size);
        osvoboditMassiv(massiv, size);
    }
    
    cout << "\nРабота программы завершена!" << endl;
}