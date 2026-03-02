#include "StringClass.h"
#include <iostream>
using namespace std;

int main() {
    // Создание объектов
    Stroka s1("qwert");      // Конструктор с параметром
    Stroka s3;               // Конструктор по умолчанию
    Stroka s4(s1);           // Конструктор копирования
    Stroka s5;               // Конструктор по умолчанию
    
    // Ввод строки
    cout << "Введите строку для s3: ";
    s3.vvod();
    
    // Присваивание
    s3 = "asdfg";
    cout << "s3 после присваивания = ";
    s3.vyvod();
    cout << endl;
    
    // Конкатенация
    s5 = s1 + s3 + s4;
    cout << "s5 = s1 + s3 + s4 = ";
    s5.vyvod();
    cout << endl;
    
    // Вывод длины
    cout << "Длина s5 = " << s5.dlina() << endl;
    
    // Сравнение строк
    if (s1 == s5) {
        cout << "Строки s1 и s5 равны" << endl;
    } else if (s1 == s4) {
        cout << "Строки s1 и s4 равны" << endl;
    } else {
        cout << "Строки не равны" << endl;
    }
    
    return 0;
}