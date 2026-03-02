#include "4-func.h"

using namespace std;

int dlina1(char* str) {
    int count = 0;
    // Разыменовываем указатель, сравниваем символ и перемещаем указатель
    while (*str++ != '\0')
        count++;

    return count;
}

int dlina2(char* str) {
    int i = 0;
    // Используем индекс массива
    while (str[i] != '\0')
        i++;

    return i;
}

// Разность указателя на первый и последний символ
int dlina3(char* str) {
    char *startPtr = str;
    while (*str != '\0')
        str++;

    return str - startPtr;
}

void copystr(char* dest, char* source) {
    int i = 0;
    while (source[i] != '\0') {
        dest[i] = source[i];
        i++;
    }
    dest[i] = '\0';
}

// Сравниваем строки посимвольно до первого отличного
int sravn(char* s1, char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] < s2[i])
            return -1;
        if (s1[i] > s2[i])
            return 1;
        i++;
    }

    if (s1[i] < s2[i])
        return -1;

    if (s1[i] > s2[i])
        return 1;

    return 0;
}

char* concat(char* str1, char* str2) {
    char* res = new char[dlina1(str1) + dlina1(str2)];

    int str1len = dlina1(str1);
    for (int i = 0; i < str1len; i++)
        res[i] = str1[i];

    for (int i = 0; i < dlina1(str2); i++) {
        res[i + str1len] = str2[i];
    }

    return res;
}