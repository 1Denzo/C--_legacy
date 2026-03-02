#ifndef STROKA_H
#define STROKA_H

#include <iostream>
using namespace std;

class Stroka {
private:
    char* str;  // Указатель на динамически выделенную память

public:
    // Конструкторы
    Stroka();                      // Конструктор по умолчанию
    Stroka(const char* s);         // Конструктор из C-строки
    Stroka(const Stroka& s);       // Конструктор копирования
    Stroka(int size);              // Конструктор с заданным размером памяти
    
    // Деструктор
    ~Stroka();
    
    // Перегруженные операции
    Stroka& operator=(const Stroka& s);      // Присваивание
    Stroka operator+(const Stroka& s) const; // Сцепление (конкатенация)
    int operator==(const Stroka& s) const;   // Сравнение
    
    // Методы
    int dlina() const;              // Определение длины строки
    void vvod();                     // Ввод строки
    void vyvod() const;               // Вывод строки
};

// Объявления пользовательских функций
char* vvodStroki(const char* prompt);
char* kopir_dinamic(char* src);
char* konkat_dinamic(char* str1, char* str2);
int sravn_dinamic(char* str1, char* str2);

#endif