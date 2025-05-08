#include <iostream>
using namespace std;

void obmen1(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    cout <<"\n в функции обмена 1:  a="<< a << " b=" << b;
}
void obmen2(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    cout <<"\n в функции обмена 2:  a="<< *a << " b=" << *b;
}
void obmen3(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
    cout <<"\n в функции обмена 3:  a="<< *a << " b=" << *b;
}

int main() {
    int a = 2;
    int b = 5;
    // void obmen2(int*, int*);
    // void obmen3(int&, int&);
    cout <<"до обмена:  a="<< a <<" b="<< b;
    obmen1(a, b);
    cout <<"\n после обмена 1:  a="<< a << " b=" << b;
    obmen2(&a, &b);
    cout <<"\n после обмена 2:  a="<< a << " b=" << b;
    obmen3(a, b);
    cout <<"\n после обмена 3:  a="<< a << " b=" << b;
    // obmen1 не изменяет оригинальные переменные, используется передача по значению.
    // obmen3 также изменяет оригинальные переменные, но используется более удобный синтаксис ссылок, что делает код проще и безопаснее.
    // obmen2 изменяет оригинальные переменные, используется передача указателей.
}