#include <iostream>
#include "StringM.h"
#include "../lab4/4-func.h"

using namespace std;

StringM::StringM() {
}

StringM::StringM(char *other) {
    copystr(str, other);
}

StringM::StringM(const StringM &other) {
    copystr(str, (char*) other.str);
}

StringM::StringM(int size) {
    str = (char*) malloc(size);
}

StringM::~StringM() {
    free(str);
}

StringM &StringM::operator=(const StringM &other) {
    copystr(str, (char*) other.str);
    return *this;
}

StringM &StringM::operator+(const StringM &other) {
    concat(str, (char*) other.str);
    return *this;
}

int StringM::operator==(const StringM &other) {
    if (sravn(str, (char*) other.str) == 0)
        return 1;
    return 0;
}

int StringM::length() {
    return dlina1(str);
}

void StringM::input() {
    cin >> str;
}

void StringM::output() {
    cout << str << endl;
}


//ЛР 8
istream &operator>>(istream &is, StringM &s) {
    char buff[1024];
    cin >> buff;
    s.str = new char[dlina1(buff)];
    copystr(s.str, buff);
    return is;
}

ostream &operator<< (ostream &os, StringM &s) {
    cout << s.str;
    return os;
}
