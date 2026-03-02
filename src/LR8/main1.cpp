#include "Stroka.h"
#include <iostream>
#include <fstream>  // для файловых потоков
using namespace std;

int main() {
    cout << "=== Работа с файловыми потоками ===\n\n";
    
    // Запись в файл с помощью оператора <<
    ofstream outFile("test.txt");
    if (outFile.is_open()) {
        Stroka s1("Первая строка");
        Stroka s2("Вторая строка");
        
        outFile << s1 << endl;
        outFile << s2 << endl;
        outFile << "Обычная строка" << endl;
        
        outFile.close();
        cout << "Данные записаны в файл test.txt\n";
    }
    
    // Чтение из файла с помощью оператора >>
    ifstream inFile("test.txt");
    if (inFile.is_open()) {
        Stroka s1, s2, s3;
        
        inFile >> s1 >> s2 >> s3;
        
        cout << "\nПрочитано из файла:\n";
        cout << "s1 = " << s1 << endl;
        cout << "s2 = " << s2 << endl;
        cout << "s3 = " << s3 << endl;
        
        inFile.close();
    }
    
    // Демонстрация работы с потоками разных типов
    cout << "\n=== Работа со строковыми потоками ===\n";
    #include <sstream>
    
    stringstream ss;
    Stroka s4("Тестовая строка");
    Stroka s5;
    
    // Запись в строковый поток
    ss << "Число: " << 42 << ", строка: " << s4;
    cout << "Содержимое stringstream: " << ss.str() << endl;
    
    // Очистка и чтение из строкового потока
    ss.clear();
    ss.str("Новые данные для s5");
    ss >> s5;
    cout << "s5 после чтения из stringstream = " << s5 << endl;
    
    return 0;
}