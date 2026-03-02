#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>  // Добавлено для atan2 и M_PI
#include <unistd.h>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <termios.h>
#include <fcntl.h>
#include <sys/select.h>
#endif

using namespace std;

// Простые консольные цвета
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_RESET   "\033[0m"
#define COLOR_WHITE   "\033[37m"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Массив цветов для циклической смены
const int COLOR_ARRAY[] = {31, 32, 33, 34, 35, 36, 37};
const int COLOR_COUNT = 7;

// Консольные символы для графики
#define EMPTY ' '
#define FILLED '#'

class Point {
protected:
    int X, Y;
    int Color;
    char Symbol;

public:
    Point() : X(0), Y(0), Color(37), Symbol(FILLED) {}
    
    virtual ~Point() {}
    
    void Init(int XN, int YN, int color = 37, char symbol = FILLED) {
        X = XN;
        Y = YN;
        Color = color;
        Symbol = symbol;
    }
    
    virtual void Show() {
        gotoxy(X, Y);
        setColor(Color);
        cout << Symbol;
        setColor(37);
        cout.flush();
    }
    
    virtual void Hide() {
        gotoxy(X, Y);
        cout << EMPTY;
        cout.flush();
    }
    
    void GetLocation(int &XL, int &YL) {
        XL = X;
        YL = Y;
    }
    
    void Fly(int Cost);
    
    // Новый метод: смена цвета
    void ChangeColor() {
        static int colorIndex = 0;
        colorIndex = (colorIndex + 1) % COLOR_COUNT;
        Color = COLOR_ARRAY[colorIndex];
    }
    
    // Вспомогательные функции для работы с консолью
    static void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }
    
    static void gotoxy(int x, int y) {
#ifdef _WIN32
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
        printf("\033[%d;%dH", y, x);
#endif
    }
    
    static void setColor(int color) {
        cout << "\033[" << color << "m";
    }
    
    static void hideCursor() {
        cout << "\033[?25l";
        cout.flush();
    }
    
    static void showCursor() {
        cout << "\033[?25h";
        cout.flush();
    }
    
    static bool kbhit() {
#ifdef _WIN32
        return _kbhit() != 0;
#else
        struct timeval tv = { 0L, 0L };
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(0, &fds);
        return select(1, &fds, NULL, NULL, &tv) > 0;
#endif
    }
    
    static int getch() {
#ifdef _WIN32
        return _getch();
#else
        struct termios oldt, newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
#endif
    }
};

class Circle : public Point {
protected:
    int Radius;
    int StartAngle;
    int EndAngle;

public:
    Circle() : Point(), Radius(1), StartAngle(0), EndAngle(360) {}
    
    void Init(int XN, int YN, int R, int color = 37, char symbol = FILLED) {
        Point::Init(XN, YN, color, symbol);
        Radius = (R > 0) ? R : 1;
        StartAngle = 0;
        EndAngle = 360;
    }
    
    virtual void Show() override {
        drawSector(true);
    }
    
    virtual void Hide() override {
        drawSector(false);
    }
    
    // Методы для работы с сектором
    void SetSector(int start, int end) {
        if (start >= 0 && start <= 360 && end >= 0 && end <= 360) {
            StartAngle = start;
            EndAngle = end;
        }
    }
    
    void ExpandSector(int delta) {
        Hide();
        StartAngle = max(0, StartAngle - delta);
        EndAngle = min(360, EndAngle + delta);
        Show();
    }
    
    void NarrowSector(int delta) {
        Hide();
        StartAngle = min(360, StartAngle + delta);
        EndAngle = max(0, EndAngle - delta);
        if (StartAngle >= EndAngle) {
            StartAngle = 0;
            EndAngle = 360;
        }
        Show();
    }
    
    // Метод для полета с сужением/расширением и сменой цвета
    void FlyWithEffects(int Cost, bool changeColor = true, bool changeSector = true);
    
    int GetStartAngle() const { return StartAngle; }
    int GetEndAngle() const { return EndAngle; }

protected:
    virtual void drawSector(bool show) {
        char ch = show ? Symbol : EMPTY;
        int col = show ? Color : 37;
        
        setColor(col);
        
        for (int dy = -Radius; dy <= Radius; dy++) {
            for (int dx = -Radius; dx <= Radius; dx++) {
                int distance = dx*dx + dy*dy;
                if (distance <= Radius*Radius) {
                    if (isPointInSector(dx, dy)) {
                        gotoxy(X + dx, Y + dy);
                        cout << ch;
                    }
                }
            }
        }
        
        setColor(37);
        cout.flush();
    }
    
    bool isPointInSector(int dx, int dy) {
        if (dx == 0 && dy == 0) return true;
        
        double angle = atan2(-dy, dx) * 180 / M_PI;
        if (angle < 0) angle += 360;
        
        if (StartAngle == 0 && EndAngle == 360) return true;
        
        if (StartAngle > EndAngle) {
            return (angle >= StartAngle || angle <= EndAngle);
        } else {
            return (angle >= StartAngle && angle <= EndAngle);
        }
    }
};

class Ring : public Circle {
private:
    int Width;
    int InnerStartAngle;
    int InnerEndAngle;

public:
    Ring() : Circle(), Width(1), InnerStartAngle(0), InnerEndAngle(360) {}
    
    void Init(int XN, int YN, int R, int W, int color = 37, char symbol = FILLED) {
        Circle::Init(XN, YN, R, color, symbol);
        Width = (W > 0 && W < R) ? W : 1;
        InnerStartAngle = StartAngle;
        InnerEndAngle = EndAngle;
    }
    
    virtual void Show() override {
        drawSector(true);
        
        setColor(37);
        for (int dy = -Radius + Width; dy <= Radius - Width; dy++) {
            for (int dx = -Radius + Width; dx <= Radius - Width; dx++) {
                int distance = dx*dx + dy*dy;
                if (distance <= (Radius - Width)*(Radius - Width)) {
                    if (isPointInInnerSector(dx, dy)) {
                        gotoxy(X + dx, Y + dy);
                        cout << EMPTY;
                    }
                }
            }
        }
        cout.flush();
    }
    
    // Методы для работы с сектором кольца
    void SetRingSector(int start, int end) {
        Circle::SetSector(start, end);
        InnerStartAngle = start;
        InnerEndAngle = end;
    }
    
    void ExpandRingSector(int delta) {
        Circle::ExpandSector(delta);
        InnerStartAngle = StartAngle;
        InnerEndAngle = EndAngle;
    }
    
    void NarrowRingSector(int delta) {
        Circle::NarrowSector(delta);
        InnerStartAngle = StartAngle;
        InnerEndAngle = EndAngle;
    }
    
    // Специфичные для кольца методы
    void ExpandRing(int delta) {
        Hide();
        Width = max(1, Width - delta);
        Show();
    }
    
    void NarrowRing(int delta) {
        Hide();
        Width = min(Radius - 1, Width + delta);
        Show();
    }
    
    // Метод для полета с эффектами для кольца
    void FlyWithEffects(int Cost, bool changeColor = true, bool changeSector = true, bool changeRing = true);
    
    int GetWidth() const { return Width; }

private:
    bool isPointInInnerSector(int dx, int dy) {
        if (dx == 0 && dy == 0) return true;
        
        double angle = atan2(-dy, dx) * 180 / M_PI;
        if (angle < 0) angle += 360;
        
        if (InnerStartAngle > InnerEndAngle) {
            return (angle >= InnerStartAngle || angle <= InnerEndAngle);
        } else {
            return (angle >= InnerStartAngle && angle <= InnerEndAngle);
        }
    }
};

#endif