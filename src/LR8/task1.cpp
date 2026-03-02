#include "Stroka.h"
#include <iostream>
#include <cstdlib>  // для calloc, free
#include <cstring>  // для strlen
using namespace std;

// Реализация пользовательских функций (как в предыдущих версиях)
// ... (vvodStroki, kopir_dinamic, konkat_dinamic, sravn_dinamic)

// Реализация методов класса Stroka
// ... (конструкторы, деструктор, операторы, методы)

// ПЕРЕГРУЖЕННЫЕ ОПЕРАТОРЫ ВВОДА/ВЫВОДА

// Оператор вывода (<<)
ostream& operator<<(ostream& os, const Stroka& s) {
    if (s.str != NULL) {
        os << s.str;  // Выводим строку в поток
    }
    return os;  // Возвращаем поток для цепочек вызова
}

// Оператор ввода (>>)
istream& operator>>(istream& is, Stroka& s) {
    char buffer[256];  // Временный буфер для ввода
    
    // Очищаем буфер
    buffer[0] = '\0';
    
    // Вводим строку (до пробела или до конца строки)
    is >> buffer;  // Ввод до пробела
    
    // Или можно использовать getline для ввода с пробелами:
    // is.getline(buffer, 256);
    
    // Освобождаем старую память
    if (s.str != NULL) {
        free(s.str);
    }
    
    // Выделяем новую память и копируем строку
    s.str = (char*)calloc(strlen(buffer) + 1, sizeof(char));
    if (s.str != NULL) {
        for (int i = 0; i <= strlen(buffer); i++) {
            s.str[i] = buffer[i];
        }
    }
    
    return is;  // Возвращаем поток для цепочек вызова
}