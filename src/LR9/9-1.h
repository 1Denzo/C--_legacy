#ifndef CPP_LABS_9_1_H
#define CPP_LABS_9_1_H

#include <cstdio>
#include <cstring>

using namespace std;

template<class T>
void sort(T array[], size_t size) {
    for (int i = 0; i < size - 1; i++)
        for (int j = size - 1; i < j; j--)
            if (array[i] > array[j]) {
                T tmp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = tmp;
            }
}

template<class T>
T getmax(T t1, T t2) {
    return t1 > t2 ? t1 : t2;
}

char *getmax(char *s1, char *s2) {
    return strcmp(s1, s2) > 0 ? s1 : s2;
}

template<class T>
T getmax(T t[], size_t size) {
    T retval = t[0];
    for (int i = 0; i < size; i++)
        if (t[i] > retval)
            retval = t[i];

    return retval;
}

template<class T>
class Tstack {
protected:
    int numItem;
    T *item;
public:
    Tstack(size_t size = 10) {
        numItem = 0;
        item = new T[size];
    }

    ~Tstack() {
        delete[] item;
    }

    void push(T t);

    T pop();
};

template<class T>
void Tstack<T>::push(T t) {
    item[numItem ++] = t;
}

template<class T>
T Tstack<T>::pop() {
    return item[--numItem];
}

#endif //CPP_LABS_9_1_H
