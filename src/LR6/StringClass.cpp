#include "StringClass.h"
#include <cstring>
#include <iostream>
#include <cstdlib>  // для calloc, free
using namespace std;

// Реализация пользовательских функций

// Ввод строки с динамическим выделением памяти через calloc
char* vvodStroki(const char* prompt)
{
    char buffer[256];
    cout << prompt;
    cin >> buffer;
    
    char* str = (char*)calloc(strlen(buffer) + 1, sizeof(char));
    
    if(str != NULL)
    {
        for(int i = 0; i <= strlen(buffer); i++)
        {
            str[i] = buffer[i];
        }
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
        // Копируем первую строку
        for(int i = 0; i < strlen(str1); i++)
        {
            result[i] = str1[i];
        }
        
        // Копируем вторую строку
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

// Реализация методов класса Stroka

// Конструктор по умолчанию
Stroka::Stroka() {
    str = (char*)calloc(1, sizeof(char));
    if(str != NULL) {
        str[0] = '\0';
    }
}

// Конструктор из C-строки
Stroka::Stroka(const char* s) {
    if(s != NULL) {
        str = (char*)calloc(strlen(s) + 1, sizeof(char));
        if(str != NULL) {
            for(int i = 0; i <= strlen(s); i++) {
                str[i] = s[i];
            }
        }
    } else {
        str = (char*)calloc(1, sizeof(char));
        if(str != NULL) {
            str[0] = '\0';
        }
    }
}

// Конструктор копирования
Stroka::Stroka(const Stroka& s) {
    str = kopir_dinamic(s.str);
}

// Деструктор
Stroka::~Stroka() {
    if(str != NULL) {
        free(str);
        str = NULL;
    }
}

// Оператор присваивания
Stroka& Stroka::operator=(const Stroka& s) {
    if (this != &s) {  // Защита от самоприсваивания
        // Освобождаем старую память
        if(str != NULL) {
            free(str);
        }
        
        // Копируем новую строку
        str = kopir_dinamic(s.str);
    }
    
    return *this;
}

// Оператор сцепления (конкатенация)
Stroka Stroka::operator+(const Stroka& s) const {
    Stroka result;
    
    // Освобождаем память, выделенную конструктором по умолчанию
    if(result.str != NULL) {
        free(result.str);
    }
    
    // Создаем новую строку через конкатенацию
    result.str = konkat_dinamic(this->str, s.str);
    
    return result;
}

// Оператор сравнения
int Stroka::operator==(const Stroka& s) const {
    return (sravn_dinamic(this->str, s.str) == 0) ? 1 : 0;
}

// Метод определения длины строки
int Stroka::dlina() const {
    if(str == NULL) return 0;
    
    int len = 0;
    while(str[len] != '\0') {
        len++;
    }
    return len;
}

// Метод ввода строки
void Stroka::vvod() {
    char* newStr = vvodStroki("");
    
    if(newStr != NULL) {
        // Освобождаем старую память
        if(str != NULL) {
            free(str);
        }
        
        // Присваиваем новый указатель
        str = newStr;
    }
}

// Метод вывода строки
void Stroka::vyvod() const {
    if(str != NULL) {
        cout << str;
    }
}