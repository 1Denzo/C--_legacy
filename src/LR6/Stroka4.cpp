#include "Stroka4.h"
#include <iostream>
#include <cstdlib>  // для calloc, free
using namespace std;

// Реализация пользовательских функций
// (vvodStroki, kopir_dinamic, konkat_dinamic, sravn_dinamic - без изменений)

// Реализация методов класса Stroka

// Конструктор по умолчанию
Stroka::Stroka() {
    str = (char*)calloc(1, sizeof(char));
    if(str != NULL) {
        str[0] = '\0';
    }
    cout << "Вызван конструктор по умолчанию" << endl;
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
    cout << "Вызван конструктор из C-строки: " << str << endl;
}

// Конструктор копирования
Stroka::Stroka(const Stroka& s) {
    str = kopir_dinamic(s.str);
    cout << "Вызван конструктор копирования: " << str << endl;
}

// НОВЫЙ КОНСТРУКТОР: с заданным размером динамической памяти
Stroka::Stroka(int size) {
    if (size > 0) {
        // Выделяем память указанного размера
        str = (char*)calloc(size + 1, sizeof(char)); // +1 для нуль-терминатора
        if(str != NULL) {
            str[0] = '\0';  // Инициализируем пустой строкой
        }
        cout << "Вызван конструктор с размером " << size << ": память выделена" << endl;
    } else {
        // Если размер некорректный, создаем пустую строку
        str = (char*)calloc(1, sizeof(char));
        if(str != NULL) {
            str[0] = '\0';
        }
        cout << "Вызван конструктор с некорректным размером, создана пустая строка" << endl;
    }
}

// Деструктор
Stroka::~Stroka() {
    if(str != NULL) {
        cout << "Вызван деструктор для строки: " << str << " (освобождение памяти)" << endl;
        free(str);
        str = NULL;
    }
}

// Остальные методы (operator=, operator+, operator==, dlina, vvod, vyvod) - без изменений
// ...