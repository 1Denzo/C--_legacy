#include <iostream.h>

// Прототипы функций для определения длины строки (3 способа)
int dlina1(char* str);  // С использованием индексации
int dlina2(char* str);  // С использованием указателей
int dlina3(char* str);  // Рекурсивный метод

// Прототипы остальных функций
void kopir(char* dest, char* src);     // Копирование строк
void sravn(char* str1, char* str2);    // Сравнение строк
void konkat(char* dest, char* src);    // Конкатенация строк

// Способ 1: Определение длины строки с использованием индексации
int dlina1(char* str)
{
    int length = 0;
    for(int i = 0; str[i] != '\0'; i++)
    {
        length++;
    }
    return length;
}

// Способ 2: Определение длины строки с использованием указателей
int dlina2(char* str)
{
    char* ptr = str;
    while(*ptr != '\0')
    {
        ptr++;
    }
    return ptr - str;  // Разница указателей дает длину
}

// Способ 3: Рекурсивное определение длины строки
int dlina3(char* str)
{
    if(*str == '\0')
        return 0;
    return 1 + dlina3(str + 1);
}

// Функция копирования строк
void kopir(char* dest, char* src)
{
    int i = 0;
    // Копируем каждый символ до конца строки
    while(src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';  // Добавляем завершающий нуль
}

// Функция сравнения строк
void sravn(char* str1, char* str2)
{
    int i = 0;
    
    // Сравниваем символы до конца хотя бы одной строки
    while(str1[i] != '\0' && str2[i] != '\0')
    {
        if(str1[i] < str2[i])
        {
            cout << "Первая строка меньше второй" << endl;
            return;
        }
        else if(str1[i] > str2[i])
        {
            cout << "Первая строка больше второй" << endl;
            return;
        }
        i++;
    }
    
    // Проверяем, достигли ли конца обеих строк
    if(str1[i] == '\0' && str2[i] == '\0')
    {
        cout << "Строки идентичны" << endl;
    }
    else if(str1[i] == '\0')
    {
        cout << "Первая строка меньше второй (короче)" << endl;
    }
    else
    {
        cout << "Первая строка больше второй (длиннее)" << endl;
    }
}

// Функция конкатенации строк
void konkat(char* dest, char* src)
{
    // Сначала находим конец строки dest
    int dest_len = 0;
    while(dest[dest_len] != '\0')
    {
        dest_len++;
    }
    
    // Затем добавляем символы из src в конец dest
    int i = 0;
    while(src[i] != '\0')
    {
        dest[dest_len + i] = src[i];
        i++;
    }
    
    // Добавляем завершающий нуль
    dest[dest_len + i] = '\0';
}

void main(void)
{
    // Объявление и инициализация строк
    char str1[] = "qwerty";
    char str2[] = "1234567890";
    char str1_copy[50];  // Дополнительный буфер для копирования
    char str1_concat[100]; // Дополнительный буфер для конкатенации
    
    cout << "=== Демонстрация функций определения длины строки ===" << endl;
    cout << "Исходные строки: str1 = \"" << str1 << "\", str2 = \"" << str2 << "\"" << endl;
    
    // Использование функций длины строки
    cout << "длина str1 (способ 1) = " << dlina1(str1) << ", str2 = " << dlina1(str2) << endl;
    cout << "длина str1 (способ 2) = " << dlina2(str1) << ", str2 = " << dlina2(str2) << endl;
    cout << "длина str1 (способ 3) = " << dlina3(str1) << ", str2 = " << dlina3(str2) << endl;
    cout << endl;
    
    // Демонстрация копирования строк
    cout << "=== Демонстрация копирования строк ===" << endl;
    // Сохраняем оригинал для демонстрации
    char original_str1[] = "qwerty";
    char original_str2[] = "1234567890";
    
    cout << "До копирования: str1 = \"" << original_str1 << "\", str2 = \"" << original_str2 << "\"" << endl;
    
    // Копируем str2 в str1_copy
    kopir(str1_copy, original_str2);
    cout << "После копирования str2 в str1_copy: str1_copy = \"" << str1_copy << "\"" << endl;
    cout << endl;
    
    // Демонстрация сравнения строк
    cout << "=== Демонстрация сравнения строк ===" << endl;
    cout << "Сравниваем str1 и str2: ";
    sravn(original_str1, original_str2);
    
    char str3[] = "qwerty";
    cout << "Сравниваем str1 и str3 (одинаковые строки): ";
    sravn(original_str1, str3);
    cout << endl;
    
    // Демонстрация конкатенации строк
    cout << "=== Демонстрация конкатенации строк ===" << endl;
    // Инициализируем буфер для конкатенации
    char dest[100] = "qwerty";
    cout << "До конкатенации: dest = \"" << dest << "\", src = \"" << str2 << "\"" << endl;
    
    konkat(dest, str2);
    cout << "После конкатенации: dest = \"" << dest << "\"" << endl;
}