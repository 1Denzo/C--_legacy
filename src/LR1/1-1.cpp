// Програма возводит в степень от 0 до 10 число 2


#include <iostream>
using namespace std;

int power(int n, int x) {
    int p = 1;
    for (int i = 1; i < x; i++) {
        p *= n;
    }

    return p;
}

int main() {

    std::string numInput;
    std::string pwInput;
int num;
int pw;

std::cout << "Введите число, которое я возведу в степень: ";
std::cin >> numInput;
std::cout << "Введите стпень числа возводимого в степень: ";
std::cin >> pwInput;

//В круглых скобках функции указывается значение, которое нужно конвертировать
num = stoi(numInput);
pw = stoi(pwInput);
        int k = power(num, pw);
        cout << "Число " << num << " После возвозведения в степень " << k << endl;


    return 0;
}
