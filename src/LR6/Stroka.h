#ifndef STROKA_H
#define STROKA_H

#include <iostream>
using namespace std;

class Stroka {
private:
    char str[80];  // Элемент-данных для хранения строки

public:
    // Конструкторы
    Stroka();                       // Конструктор по умолчанию
    Stroka(const char* s);          // Конструктор из C-строки
    Stroka(const Stroka& s);        // Конструктор копирования
    
    // Деструктор (виртуальный для корректного наследования)
    virtual ~Stroka() {}
    
    // Перегруженные операции
    Stroka& operator=(const Stroka& s);      // Присваивание
    Stroka operator+(const Stroka& s) const; // Сцепление (конкатенация)
    int operator==(const Stroka& s) const;   // Сравнение
    
    // Методы
    int dlina() const;               // Определение длины строки
    void vvod();                      // Ввод строки
    void vyvod() const;                // Вывод строки
};

#endif