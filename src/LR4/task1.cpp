#include <iostream>
#include <string.h>  // Для работы с C-строками

using namespace std;

int main() {
    // Демонстрация функции strlen() - определение длины строки
    cout << "=== Демонстрация strlen() ===" << endl;
    char str1[] = "Привет, мир!";
    char str2[] = "C++ programming";
    
    cout << "Строка 1: \"" << str1 << "\"" << endl;
    cout << "Длина строки 1: " << strlen(str1) << " символов" << endl;
    cout << "Строка 2: \"" << str2 << "\"" << endl;
    cout << "Длина строки 2: " << strlen(str2) << " символов" << endl;
    cout << endl;

    // Демонстрация функции strcat() - конкатенация (объединение) строк
    cout << "=== Демонстрация strcat() ===" << endl;
    char buffer1[100] = "Hello";
    char buffer2[100] = "Привет";
    char append1[] = " World!";
    char append2[] = ", мир!";
    
    cout << "Исходный buffer1: \"" << buffer1 << "\"" << endl;
    cout << "Добавляем: \"" << append1 << "\"" << endl;
    strcat(buffer1, append1);
    cout << "Результат: \"" << buffer1 << "\"" << endl;
    
    cout << "\nИсходный buffer2: \"" << buffer2 << "\"" << endl;
    cout << "Добавляем: \"" << append2 << "\"" << endl;
    strcat(buffer2, append2);
    cout << "Результат: \"" << buffer2 << "\"" << endl;
    cout << endl;

    // Демонстрация функции strcpy() - копирование строк
    cout << "=== Демонстрация strcpy() ===" << endl;
    char source[] = "Исходная строка для копирования";
    char destination[50];
    
    cout << "Исходная строка: \"" << source << "\"" << endl;
    strcpy(destination, source);
    cout << "Скопированная строка: \"" << destination << "\"" << endl;
    
    // Копирование с перезаписью
    char another_source[] = "Новая строка";
    cout << "\nКопируем другую строку: \"" << another_source << "\"" << endl;
    strcpy(destination, another_source);
    cout << "Результат в destination: \"" << destination << "\"" << endl;
    cout << endl;

    // Демонстрация функции strcmp() - сравнение строк
    cout << "=== Демонстрация strcmp() ===" << endl;
    
    // Функция strcmp() возвращает:
    // 0 - если строки идентичны
    // <0 - если первая строка меньше второй (по алфавиту)
    // >0 - если первая строка больше второй
    
    char s1[] = "apple";
    char s2[] = "apple";
    char s3[] = "apricot";
    char s4[] = "Apple";  // Заглавная буква
    char s5[] = "banana";
    
    cout << "Сравнение \"" << s1 << "\" и \"" << s2 << "\": ";
    int result1 = strcmp(s1, s2);
    if (result1 == 0) {
        cout << "строки идентичны" << endl;
    } else if (result1 < 0) {
        cout << "первая строка меньше" << endl;
    } else {
        cout << "первая строка больше" << endl;
    }
    
    cout << "Сравнение \"" << s1 << "\" и \"" << s3 << "\": ";
    int result2 = strcmp(s1, s3);
    if (result2 == 0) {
        cout << "строки идентичны" << endl;
    } else if (result2 < 0) {
        cout << "\"" << s1 << "\" меньше \"" << s3 << "\" (apple < apricot)" << endl;
    } else {
        cout << "\"" << s1 << "\" больше \"" << s3 << "\"" << endl;
    }
    
    cout << "Сравнение \"" << s1 << "\" и \"" << s4 << "\": ";
    int result3 = strcmp(s1, s4);
    if (result3 == 0) {
        cout << "строки идентичны" << endl;
    } else if (result3 < 0) {
        cout << "\"" << s1 << "\" меньше \"" << s4 << "\" (apple < Apple?)" << endl;
        cout << "   Примечание: strcmp учитывает регистр!" << endl;
    } else {
        cout << "\"" << s1 << "\" больше \"" << s4 << "\"" << endl;
    }
    
    cout << "\nСравнение \"" << s1 << "\" и \"" << s5 << "\": ";
    int result4 = strcmp(s1, s5);
    if (result4 == 0) {
        cout << "строки идентичны" << endl;
    } else if (result4 < 0) {
        cout << "\"" << s1 << "\" меньше \"" << s5 << "\" (apple < banana)" << endl;
    } else {
        cout << "\"" << s1 << "\" больше \"" << s5 << "\"" << endl;
    }
    cout << endl;

    // Практический пример: использование всех функций вместе
    cout << "=== Практический пример ===" << endl;
    
    char firstName[50], lastName[50], fullName[100], copyName[100];
    
    cout << "Введите имя: ";
    cin.getline(firstName, 50);
    
    cout << "Введите фамилию: ";
    cin.getline(lastName, 50);
    
    // Используем strlen() для проверки ввода
    if (strlen(firstName) == 0 || strlen(lastName) == 0) {
        cout << "Ошибка: имя или фамилия не могут быть пустыми!" << endl;
        return 1;
    }
    
    // Используем strcpy() для инициализации
    strcpy(fullName, firstName);
    
    // Используем strcat() для объединения
    strcat(fullName, " ");
    strcat(fullName, lastName);
    
    // Используем strcpy() для копирования
    strcpy(copyName, fullName);
    
    cout << "Полное имя: \"" << fullName << "\"" << endl;
    cout << "Копия имени: \"" << copyName << "\"" << endl;
    
    // Используем strcmp() для сравнения
    if (strcmp(fullName, copyName) == 0) {
        cout << "Копирование выполнено успешно!" << endl;
    } else {
        cout << "Ошибка при копировании!" << endl;
    }
    
    cout << "\nДлина полного имени: " << strlen(fullName) << " символов" << endl;
    
    return 0;
}