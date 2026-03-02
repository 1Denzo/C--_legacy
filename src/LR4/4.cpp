#include <iostream>
#include <cstring>
#include "4-func.h"

using namespace std;

void printInfo(char* str1, char* str2) {
    cout << endl << endl << "str1 = " << str1 << ", str2 = " << str2 << endl;
    cout << "длина str1 = " << dlina1(str1) << ", str2 = " << dlina1(str2) << endl;
    cout << "длина str1 = " << dlina2(str1) << ", str2 = " << dlina2(str2) << endl;
    cout << "длина str1 = " << dlina3(str1) << ", str2 = " << dlina3(str2) << endl;

    copystr(str1, str2);
    cout << "результат копирования: str1 = " << str1 << ", str2 = " << str2 << endl;

    int scmp = strcmp(str1, str2);
    int cmp = sravn(str1, str2);
    cout << "результат сравнения: strcmp = " << scmp << ", cmp = " << cmp << endl;

    char* scon = strcat(str1, str2);
    cout << "результат сцепления: scon = " << scon << endl;
    char* con = concat(str1, str2);
    cout << "результат сцепления: con = " << con << endl;
}

void withArray() {
    char str1[] = "abc";
    char str2[] = "defghi";
    char str3[] = "defghi";
    char* strs1[] = {str1, str2, str3};

    for (int i = 0; i < 2; i++) {
        printInfo(strs1[i], strs1[i+1]);
    }
}

int main() {
//    char str1[] = "qwerty", str2[] = "1234567890";

    // Выделяет память размером 100 байт
//    char *str1, *str2;
//    str1 = (char*) malloc(100);
//    str2 = (char*) malloc(100);

    // Выделяет память под 6 элементов по 8 байт
    char *str1, *str2;
    str1 = (char*) calloc(6, 8);
    str1[0] = 'q', str1[1] = 'w', str1[2] = 'e', str1[3] = 'r', str1[4] = 't', str1[5] = '\0';
    str2 = (char*) calloc(6, 8);
    str2[0] = '1', str2[1] = '2', str2[2] = '3', str2[3] = '4', str2[4] = '5', str2[5] = '\0';

    printInfo(str1, str2);

    free(str1);
    free(str2);

    withArray();
    return 0;
}