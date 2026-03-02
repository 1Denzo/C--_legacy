#include "Shapes.h"
#include <iostream>
#include <vector>
using namespace std;

void showMenu() {
    Point::clearScreen();
    cout << "========================================\n";
    cout << "   ДЕМОНСТРАЦИЯ ЭФФЕКТОВ ФИГУР\n";
    cout << "========================================\n\n";
    cout << "1 - Обычный полет круга\n";
    cout << "2 - Полет круга с изменением цвета\n";
    cout << "3 - Полет круга с сужением/расширением сектора\n";
    cout << "4 - Полет круга со всеми эффектами\n";
    cout << "5 - Обычный полет кольца\n";
    cout << "6 - Полет кольца с изменением цвета\n";
    cout << "7 - Полет кольца с изменением сектора\n";
    cout << "8 - Полет кольца с изменением ширины\n";
    cout << "9 - Полет кольца со всеми эффектами\n";
    cout << "0 - Выход\n\n";
    cout << "Выберите режим: ";
}

void waitForKey() {
    cout << "\nНажмите любую клавишу для продолжения...\n";
    Point::getch();
}

int main() {
    Point::hideCursor();
    
    int choice;
    Circle circle;
    Ring ring;
    
    do {
        showMenu();
        cin >> choice;
        
        Point::clearScreen();
        
        switch (choice) {
            case 1:
                cout << "Обычный полет круга\n";
                circle.Init(20, 12, 5, 31, 'O');
                circle.Fly(3);
                circle.Hide();
                break;
                
            case 2:
                cout << "Полет круга с изменением цвета\n";
                circle.Init(20, 12, 5, 31, 'O');
                circle.FlyWithEffects(3, true, false);
                circle.Hide();
                break;
                
            case 3:
                cout << "Полет круга с сужением/расширением сектора\n";
                circle.Init(20, 12, 5, 31, 'O');
                circle.SetSector(0, 180);  // Начинаем с полукруга
                circle.FlyWithEffects(3, false, true);
                circle.Hide();
                break;
                
            case 4:
                cout << "Полет круга со всеми эффектами\n";
                circle.Init(20, 12, 5, 31, 'O');
                circle.FlyWithEffects(3, true, true);
                circle.Hide();
                break;
                
            case 5:
                cout << "Обычный полет кольца\n";
                ring.Init(40, 12, 8, 3, 33, '#');
                ring.Fly(2);
                ring.Hide();
                break;
                
            case 6:
                cout << "Полет кольца с изменением цвета\n";
                ring.Init(40, 12, 8, 3, 33, '#');
                ring.FlyWithEffects(2, true, false, false);
                ring.Hide();
                break;
                
            case 7:
                cout << "Полет кольца с изменением сектора\n";
                ring.Init(40, 12, 8, 3, 33, '#');
                ring.SetSector(0, 270);  // Начинаем с 3/4 круга
                ring.FlyWithEffects(2, false, true, false);
                ring.Hide();
                break;
                
            case 8:
                cout << "Полет кольца с изменением ширины\n";
                ring.Init(40, 12, 8, 3, 33, '#');
                ring.FlyWithEffects(2, false, false, true);
                ring.Hide();
                break;
                
            case 9:
                cout << "Полет кольца со всеми эффектами\n";
                ring.Init(40, 12, 8, 3, 33, '#');
                ring.FlyWithEffects(2, true, true, true);
                ring.Hide();
                break;
                
            case 0:
                cout << "Выход из программы...\n";
                break;
                
            default:
                cout << "Неверный выбор!\n";
        }
        
        if (choice != 0) {
            waitForKey();
        }
        
    } while (choice != 0);
    
    Point::showCursor();
    Point::clearScreen();
    cout << "Программа завершена.\n";
    
    return 0;
}