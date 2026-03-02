#include <iostream>
#include <string>
#include <limits>
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
    
    // Формирование первого элемента
    void first(const T& value) {
        head = new Node<T>(value);
        tail = head;
    }
    
    // Добавление в конец списка
    void add(const T& value) {
        if (!head) {
            first(value);
            return;
        }
        Node<T>* newNode = new Node<T>(value);
        tail->next = newNode;
        tail = newNode;
    }
    
    // Поиск элемента по ключу (по номеру автобуса)
    Node<T>* find(int busNumber) const {
        Node<T>* current = head;
        while (current) {
            if (current->data.getBusNumber() == busNumber) 
                return current;
            current = current->next;
        }
        return nullptr;
    }
    
    // Удаление элемента по ключу (по номеру автобуса)
    bool remove(int busNumber) {
        if (!head) return false;
        
        // Если удаляем первый элемент
        if (head->data.getBusNumber() == busNumber) {
            Node<T>* temp = head;
            head = head->next;
            if (!head) tail = nullptr;
            delete temp;
            return true;
        }
        
        // Поиск элемента для удаления
        Node<T>* current = head;
        while (current->next && current->next->data.getBusNumber() != busNumber) {
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
    
    // Вставка элемента после указанного ключа (не используется в этой задаче)
    Node<T>* insert(int key, const T& value) {
        return nullptr;
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
    
    // Получение первого элемента
    Node<T>* getHead() const {
        return head;
    }
    
    // Проверка на пустоту
    bool isEmpty() const {
        return head == nullptr;
    }
    
    // Получение количества элементов
    int size() const {
        int count = 0;
        Node<T>* current = head;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }
};

// Класс, представляющий информацию об автобусе
class Bus {
private:
    int busNumber;      // Номер автобуса
    string driverName;  // Фамилия и инициалы водителя
    int routeNumber;    // Номер маршрута
    
public:
    // Конструктор по умолчанию
    Bus() : busNumber(0), driverName(""), routeNumber(0) {}
    
    // Конструктор с параметрами
    Bus(int busNum, const string& driver, int route) 
        : busNumber(busNum), driverName(driver), routeNumber(route) {}
    
    // Геттеры
    int getBusNumber() const { return busNumber; }
    string getDriverName() const { return driverName; }
    int getRouteNumber() const { return routeNumber; }
    
    // Сеттеры
    void setBusNumber(int num) { busNumber = num; }
    void setDriverName(const string& name) { driverName = name; }
    void setRouteNumber(int route) { routeNumber = route; }
    
    // Перегрузка оператора вывода для удобного отображения
    friend ostream& operator<<(ostream& os, const Bus& bus) {
        os << "Автобус №" << bus.busNumber 
           << ", Водитель: " << bus.driverName 
           << ", Маршрут №" << bus.routeNumber;
        return os;
    }
};

// Класс для управления автобусным парком
class BusPark {
private:
    LinkedList<Bus> parkBuses;      // Автобусы в парке
    LinkedList<Bus> routeBuses;     // Автобусы на маршруте
    
public:
    // Начальное формирование данных обо всех автобусах в парке
    void initializePark() {
        cout << "=== Начальное формирование данных об автобусах ===\n";
        
        int count;
        cout << "Введите количество автобусов в парке: ";
        cin >> count;
        
        for (int i = 0; i < count; i++) {
            cout << "\nАвтобус #" << (i + 1) << ":\n";
            
            int busNum, routeNum;
            string driverName;
            
            cout << "  Номер автобуса: ";
            cin >> busNum;
            
            cout << "  Фамилия и инициалы водителя: ";
            cin.ignore();
            getline(cin, driverName);
            
            cout << "  Номер маршрута: ";
            cin >> routeNum;
            
            Bus newBus(busNum, driverName, routeNum);
            parkBuses.add(newBus);
        }
        
        cout << "\nДанные успешно загружены. В парке " << parkBuses.size() << " автобусов.\n";
    }
    
    // Выезд автобуса из парка на маршрут
    void departBus() {
        if (parkBuses.isEmpty()) {
            cout << "\nОшибка: В парке нет автобусов!\n";
            return;
        }
        
        cout << "\n=== Выезд автобуса из парка ===\n";
        cout << "Введите номер автобуса: ";
        int busNumber;
        cin >> busNumber;
        
        // Ищем автобус в парке
        Node<Bus>* found = parkBuses.find(busNumber);
        
        if (found) {
            // Получаем данные об автобусе
            Bus bus = found->data;
            
            // Удаляем из парка и добавляем на маршрут
            parkBuses.remove(busNumber);
            routeBuses.add(bus);
            
            cout << "Автобус №" << busNumber << " выехал на маршрут.\n";
        } else {
            cout << "Ошибка: Автобус с номером " << busNumber << " не найден в парке.\n";
        }
    }
    
    // Въезд автобуса в парк с маршрута
    void arriveBus() {
        if (routeBuses.isEmpty()) {
            cout << "\nОшибка: На маршруте нет автобусов!\n";
            return;
        }
        
        cout << "\n=== Въезд автобуса в парк ===\n";
        cout << "Введите номер автобуса: ";
        int busNumber;
        cin >> busNumber;
        
        // Ищем автобус на маршруте
        Node<Bus>* found = routeBuses.find(busNumber);
        
        if (found) {
            // Получаем данные об автобусе
            Bus bus = found->data;
            
            // Удаляем с маршрута и добавляем в парк
            routeBuses.remove(busNumber);
            parkBuses.add(bus);
            
            cout << "Автобус №" << busNumber << " вернулся в парк.\n";
        } else {
            cout << "Ошибка: Автобус с номером " << busNumber << " не найден на маршруте.\n";
        }
    }
    
    // Вывод списка автобусов в парке
    void showParkBuses() const {
        cout << "\n=== Автобусы в парке ===\n";
        if (parkBuses.isEmpty()) {
            cout << "В парке нет автобусов.\n";
            return;
        }
        
        Node<Bus>* current = parkBuses.getHead();
        int count = 1;
        while (current) {
            cout << count++ << ". " << current->data << endl;
            current = current->next;
        }
        cout << "Всего в парке: " << parkBuses.size() << " автобусов.\n";
    }
    
    // Вывод списка автобусов на маршруте
    void showRouteBuses() const {
        cout << "\n=== Автобусы на маршруте ===\n";
        if (routeBuses.isEmpty()) {
            cout << "На маршруте нет автобусов.\n";
            return;
        }
        
        Node<Bus>* current = routeBuses.getHead();
        int count = 1;
        while (current) {
            cout << count++ << ". " << current->data << endl;
            current = current->next;
        }
        cout << "Всего на маршруте: " << routeBuses.size() << " автобусов.\n";
    }
    
    // Проверка наличия автобуса в парке
    bool isInPark(int busNumber) const {
        return parkBuses.find(busNumber) != nullptr;
    }
    
    // Проверка наличия автобуса на маршруте
    bool isOnRoute(int busNumber) const {
        return routeBuses.find(busNumber) != nullptr;
    }
};

// Функция для отображения меню
void showMenu() {
    cout << "\n========================================\n";
    cout << "АВТОБУСНЫЙ ПАРК - МЕНЮ УПРАВЛЕНИЯ\n";
    cout << "========================================\n";
    cout << "1. Начальное формирование данных\n";
    cout << "2. Выезд автобуса на маршрут\n";
    cout << "3. Въезд автобуса в парк\n";
    cout << "4. Показать автобусы в парке\n";
    cout << "5. Показать автобусы на маршруте\n";
    cout << "0. Выход\n";
    cout << "========================================\n";
    cout << "Выберите действие: ";
}

int main() {
    BusPark park;
    int choice;
    bool initialized = false;
    
    cout << "Программа управления автобусным парком\n";
    cout << "========================================\n";
    
    do {
        showMenu();
        cin >> choice;
        
        // Обработка некорректного ввода
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка: Введите число от 0 до 5.\n";
            continue;
        }
        
        switch (choice) {
            case 1:
                park.initializePark();
                initialized = true;
                break;
                
            case 2:
                if (!initialized) {
                    cout << "\nСначала выполните начальное формирование данных (пункт 1).\n";
                } else {
                    park.departBus();
                }
                break;
                
            case 3:
                if (!initialized) {
                    cout << "\nСначала выполните начальное формирование данных (пункт 1).\n";
                } else {
                    park.arriveBus();
                }
                break;
                
            case 4:
                if (!initialized) {
                    cout << "\nСначала выполните начальное формирование данных (пункт 1).\n";
                } else {
                    park.showParkBuses();
                }
                break;
                
            case 5:
                if (!initialized) {
                    cout << "\nСначала выполните начальное формирование данных (пункт 1).\n";
                } else {
                    park.showRouteBuses();
                }
                break;
                
            case 0:
                cout << "\nПрограмма завершена. До свидания!\n";
                break;
                
            default:
                cout << "\nОшибка: Неверный выбор. Введите число от 0 до 5.\n";
        }
        
    } while (choice != 0);
    
    return 0;
}