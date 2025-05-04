#define PR(x) printf("x=%u, *x=%d, &x=%u\n", x, *x, &x)
#include <stdio.h>

using namespace std;

int main() {
    int mas[] = {100, 200, 300};
    int *ptr1, *ptr2;
    ptr1 = mas;
    // Сохраняем адрес памяти элемента mas[2] в ptr2. * - обратная операция - получает объект по адресу памяти
    ptr2=&mas[2];
    PR(ptr1);
    ptr1++;
    PR(ptr1);
    PR(ptr2);
    ++ptr2;
    printf("ptr2-ptr1=%lld\n", ptr2-ptr1);

    return 0;
}
