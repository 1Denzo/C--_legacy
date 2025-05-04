#include <iostream>

using namespace std;

int main() {
    int a = 2, b = 5;
    void obmen1(int, int);
    void obmen2(int *, int *);
    void obmen3(int &, int &);

    cout << "     до обмена: a = " << a << " b = " << b << endl;
    obmen1(a, b);
    cout << "после обмена 1: a = " << a << " b = " << b << endl;
    obmen2(&a, &b);
    cout << "после обмена 2: a = " << a << " b = " << b << endl;
    obmen3(a, b);
    cout << "после обмена 3: a = " << a << " b = " << b << endl;
    return 0;
}

// Невозможно обменять, т.к. аргументы передаются по значению (=копируются)
void obmen1(int a, int b) {
}

// Обмен по указателям
void obmen2(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Обмен по ссылке на указатель (обмен ссылок)
void obmen3(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}