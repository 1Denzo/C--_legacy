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
    
    // Деструктор
    ~Stroka();
    
    // Перегруженные операции
    Stroka& operator=(const Stroka& s);      // Присваивание
    Stroka operator+(const Stroka& s) const; // Сцепление (конкатенация)
    int operator==(const Stroka& s) const;   // Сравнение
    
    // Методы
    int dlina() const;              // Определение длины строки
    void vvod();                     // Ввод строки (традиционный)
    void vyvod() const;               // Вывод строки (традиционный)
    
    // Дружественные функции для перегрузки операторов ввода/вывода
    friend ostream& operator<<(ostream& os, const Stroka& s);
    friend istream& operator>>(istream& is, Stroka& s);
};

// Глобальные операторы ввода/вывода (объявлены как дружественные)
ostream& operator<<(ostream& os, const Stroka& s);
istream& operator>>(istream& is, Stroka& s);

// Объявления пользовательских функций (если используются)
char* vvodStroki(const char* prompt);
char* kopir_dinamic(char* src);
char* konkat_dinamic(char* str1, char* str2);
int sravn_dinamic(char* str1, char* str2);

#endif