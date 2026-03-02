#include <iostream.h>
#include <alloc.h>
#include <string.h>

// Функций с динамическим выделением памяти
char* vvodStroki(const char* prompt);           // Ввод строки с динамическим выделением
char* kopir_dinamic(char* src);                  // Копирование строки в новую память
char* konkat_dinamic(char* str1, char* str2);    // Конкатенация с созданием новой строки
int sravn_dinamic(char* str1, char* str2);       // Сравнение строк (возвращает результат)
void test_dinamic_functions();                    // Тестовая функция


// Ввод строки с динамическим выделением памяти
char* vvodStroki(const char* prompt)
{
    char buffer[256];  // Временный буфер для ввода
    cout << prompt;
    cin >> buffer;
    
    // Выделяем память точно под размер введенной строки (+1 для '\0')
    char* str = (char*)malloc(strlen(buffer) + 1);
    
    if(str != NULL)
    {
        strcpy(str, buffer);  // Копируем из временного буфера
    }
    
    return str;
}

// Копирование строки с выделением новой памяти
char* kopir_dinamic(char* src)
{
    if(src == NULL) return NULL;
    
    // Выделяем память под копию
    int len = dlina1(src);
    char* dest = (char*)malloc(len + 1);
    
    if(dest != NULL)
    {
        // Копируем символы
        for(int i = 0; i <= len; i++)
        {
            dest[i] = src[i];
        }
    }
    
    return dest;
}

// Конкатенация с созданием новой строки
char* konkat_dinamic(char* str1, char* str2)
{
    if(str1 == NULL || str2 == NULL) return NULL;
    
    // Вычисляем общую длину
    int len1 = dlina1(str1);
    int len2 = dlina1(str2);
    
    // Выделяем память под результат
    char* result = (char*)malloc(len1 + len2 + 1);
    
    if(result != NULL)
    {
        // Копируем первую строку
        for(int i = 0; i < len1; i++)
        {
            result[i] = str1[i];
        }
        
        // Добавляем вторую строку
        for(int i = 0; i < len2; i++)
        {
            result[len1 + i] = str2[i];
        }
        
        // Добавляем завершающий нуль
        result[len1 + len2] = '\0';
    }
    
    return result;
}

// Сравнение строк (возвращает результат)
int sravn_dinamic(char* str1, char* str2)
{
    if(str1 == NULL || str2 == NULL) return 0;
    
    int i = 0;
    
    // Сравниваем символы
    while(str1[i] != '\0' && str2[i] != '\0')
    {
        if(str1[i] < str2[i]) return -1;
        if(str1[i] > str2[i]) return 1;
        i++;
    }
    
    // Проверяем длину строк
    if(str1[i] == '\0' && str2[i] == '\0') return 0;
    if(str1[i] == '\0') return -1;
    return 1;
}

// Тестовая функция для демонстрации работы
void test_dinamic_functions()
{
    cout << "\n=== ТЕСТИРОВАНИЕ ДИНАМИЧЕСКИХ ФУНКЦИЙ ===\n" << endl;
    
    // 1. Ввод строк с динамическим выделением
    cout << "--- Тест 1: Ввод строк ---" << endl;
    char* str1 = vvodStroki("Введите первую строку: ");
    char* str2 = vvodStroki("Введите вторую строку: ");
    
    if(str1 == NULL || str2 == NULL)
    {
        cout << "Ошибка выделения памяти!" << endl;
        if(str1) free(str1);
        if(str2) free(str2);
        return;
    }
    
    cout << "Введенные строки: \"" << str1 << "\" и \"" << str2 << "\"" << endl;
    
    
    // 3. Сравнение строк
    cout << "\n--- Тест 3: Сравнение строк ---" << endl;
    int cmp_result = sravn_dinamic(str1, str2);
    cout << "Результат сравнения: ";
    if(cmp_result == 0) cout << "строки идентичны";
    else if(cmp_result < 0) cout << "первая строка меньше второй";
    else cout << "первая строка больше второй";
    cout << endl;
    
    // 4. Копирование строки
    cout << "\n--- Тест 4: Копирование строки ---" << endl;
    char* str1_copy = kopir_dinamic(str1);
    if(str1_copy != NULL)
    {
        cout << "Оригинал:     \"" << str1 << "\"" << endl;
        cout << "Копия:        \"" << str1_copy << "\"" << endl;
        cout << "Сравнение:    ";
        if(sravn_dinamic(str1, str1_copy) == 0)
            cout << "копирование успешно";
        else
            cout << "ошибка копирования";
        cout << endl;
    }
    
    // 5. Конкатенация строк
    cout << "\n--- Тест 5: Конкатенация строк ---" << endl;
    char* concat_result = konkat_dinamic(str1, str2);
    if(concat_result != NULL)
    {
        cout << "Строка 1:     \"" << str1 << "\"" << endl;
        cout << "Строка 2:     \"" << str2 << "\"" << endl;
        cout << "Результат:    \"" << concat_result << "\"" << endl;
    }
    
    // 6. Дополнительный тест: конкатенация с пустой строкой
    cout << "\n--- Тест 6: Конкатенация с пустой строкой ---" << endl;
    char* empty = kopir_dinamic("");
    char* test_concat = konkat_dinamic(str1, empty);
    if(test_concat != NULL)
    {
        cout << "Строка + пустая: \"" << test_concat << "\"" << endl;
        free(test_concat);
    }
    
    // 7. Освобождение всей выделенной памяти
    cout << "\n--- Очистка памяти ---" << endl;
    free(str1);
    free(str2);
    free(str1_copy);
    free(concat_result);
    free(empty);
    cout << "Вся динамическая память освобождена!" << endl;
    
    cout << "\n=== ТЕСТИРОВАНИЕ ЗАВЕРШЕНО ===\n" << endl;
}

// Главная функция
void main(void)
{
    cout << "ПРОГРАММА РАБОТЫ С ДИНАМИЧЕСКИМИ СТРОКАМИ" << endl;
    cout << "==========================================" << endl;
    
    // Запуск тестирования
    test_dinamic_functions();
}