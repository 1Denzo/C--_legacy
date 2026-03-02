#include <iostream>
using namespace std;

// Шаблон класса Node (узел списка)
template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
    
    Node(const T& value) : data(value), next(nullptr) {}
};

// Шаблон класса LinkedList (односвязный линейный список)
template <typename T>
class LinkedList {
private:
    Node<T>* head;  // Указатель на первый элемент
    Node<T>* tail;  // Указатель на последний элемент
    
public:
    // Конструктор по умолчанию
    LinkedList() : head(nullptr), tail(nullptr) {}
    
    // Деструктор
    ~LinkedList() {
        clear();
    }
    
    // Формирование первого элемента (аналог функции first)
    void createFirst(const T& value) {
        head = new Node<T>(value);
        tail = head;
    }
    
    // Добавление в конец списка (аналог функции add)
    void pushBack(const T& value) {
        if (!head) {
            createFirst(value);
            return;
        }
        Node<T>* newNode = new Node<T>(value);
        tail->next = newNode;
        tail = newNode;
    }
    
    // Поиск элемента по ключу (аналог функции find)
    Node<T>* find(const T& key) const {
        Node<T>* current = head;
        while (current) {
            if (current->data == key) 
                return current;
            current = current->next;
        }
        return nullptr;
    }
    
    // Удаление элемента по ключу (аналог функции remove)
    bool remove(const T& key) {
        if (!head) return false;
        
        // Если удаляем первый элемент
        if (head->data == key) {
            Node<T>* temp = head;
            head = head->next;
            if (!head) tail = nullptr;
            delete temp;
            return true;
        }
        
        // Поиск элемента для удаления
        Node<T>* current = head;
        while (current->next && current->next->data != key) {
            current = current->next;
        }
        
        if (current->next) {
            Node<T>* toDelete = current->next;
            current->next = toDelete->next;
            if (toDelete == tail) {
                tail = current;
            }
            delete toDelete;
            return true;
        }
        
        return false;
    }
    
    // Вставка элемента после указанного ключа (аналог функции insert)
    bool insertAfter(const T& key, const T& value) {
        Node<T>* pkey = find(key);
        if (!pkey) return false;
        
        Node<T>* newNode = new Node<T>(value);
        newNode->next = pkey->next;
        pkey->next = newNode;
        
        // Если вставляем после последнего элемента, обновляем tail
        if (pkey == tail) {
            tail = newNode;
        }
        
        return true;
    }
    
    // Вывод списка на экран
    void print() const {
        Node<T>* current = head;
        while (current) {
            cout << current->data;
            if (current->next) cout << " -> ";
            current = current->next;
        }
        cout << endl;
    }
    
    // Очистка списка
    void clear() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }
    
    // Проверка на пустоту
    bool isEmpty() const {
        return head == nullptr;
    }
    
    // Получение первого элемента (для совместимости с original)
    Node<T>* getHead() const {
        return head;
    }
    
    // Получение последнего элемента (для совместимости с original)
    Node<T>* getTail() const {
        return tail;
    }
};

int main() {
    cout << "Программа для работы с односвязным линейным списком\n";
    cout << "(аналог функций из двусвязного списка)\n";
    cout << "==================================================\n\n";
    
    // Формирование первого элемента списка (аналог first)
    cout << "1. Формирование первого элемента\n";
    LinkedList<int> list;
    list.createFirst(1);
    cout << "   Создан первый элемент: 1\n";
    cout << "   Список: ";
    list.print();
    
    // Добавление в конец элементов 2, 3, 4, 5 (аналог add)
    cout << "\n2. Добавление в конец элементов 2, 3, 4, 5\n";
    for (int i = 2; i <= 5; i++) {
        list.pushBack(i);
        cout << "   Добавлен элемент: " << i << endl;
    }
    cout << "   Список: ";
    list.print();
    
    // Вставка элемента 200 после элемента 2 (аналог insert)
    cout << "\n3. Вставка элемента 200 после элемента 2\n";
    if (list.insertAfter(2, 200)) {
        cout << "   Элемент 200 успешно вставлен\n";
    } else {
        cout << "   Элемент 2 не найден\n";
    }
    cout << "   Список: ";
    list.print();
    
    // Удаление элемента 5 (аналог remove)
    cout << "\n4. Удаление элемента 5\n";
    if (list.remove(5)) {
        cout << "   Элемент 5 успешно удален\n";
    } else {
        cout << "   Элемент 5 не найден\n";
    }
    cout << "   Список: ";
    list.print();
    
    // Попытка удалить несуществующий элемент
    cout << "\n5. Попытка удалить элемент 10\n";
    if (list.remove(10)) {
        cout << "   Элемент 10 удален\n";
    } else {
        cout << "   Элемент 10 не найден\n";
    }
    
    // Поиск элемента
    cout << "\n6. Поиск элемента 3\n";
    Node<int>* found = list.find(3);
    if (found) {
        cout << "   Элемент 3 найден, его значение: " << found->data << endl;
    } else {
        cout << "   Элемент 3 не найден\n";
    }
    
    // Поиск несуществующего элемента
    cout << "\n7. Поиск элемента 100\n";
    found = list.find(100);
    if (found) {
        cout << "   Элемент 100 найден\n";
    } else {
        cout << "   Элемент 100 не найден\n";
    }
    
    // Вставка в конец (проверка обновления tail)
    cout << "\n8. Вставка элемента 500 после последнего элемента (5)\n";
    if (list.insertAfter(5, 500)) {
        cout << "   Элемент 500 успешно вставлен в конец\n";
    }
    cout << "   Список: ";
    list.print();
    
    // Удаление первого элемента
    cout << "\n9. Удаление первого элемента (1)\n";
    list.remove(1);
    cout << "   Список: ";
    list.print();
    
    // Удаление последнего элемента
    cout << "\n10. Удаление последнего элемента (500)\n";
    list.remove(500);
    cout << "   Список: ";
    list.print();
    
    // Проверка на пустоту
    cout << "\n11. Проверка на пустоту\n";
    cout << "   Список пуст? " << (list.isEmpty() ? "Да" : "Нет") << endl;
    
    // Очистка списка
    cout << "\n12. Очистка списка\n";
    list.clear();
    cout << "   Список после очистки: ";
    list.print();
    cout << "   Список пуст? " << (list.isEmpty() ? "Да" : "Нет") << endl;
    
    // Демонстрация работы со строками
    cout << "\n13. Работа со строками\n";
    LinkedList<string> strList;
    strList.createFirst("Первый");
    strList.pushBack("Второй");
    strList.pushBack("Третий");
    
    cout << "   Список строк: ";
    strList.print();
    
    cout << "   Вставка 'Вставленный' после 'Второй':\n";
    strList.insertAfter("Второй", "Вставленный");
    cout << "   Список: ";
    strList.print();
    
    cout << "   Удаление 'Третий':\n";
    strList.remove("Третий");
    cout << "   Список: ";
    strList.print();
    
    return 0;
}