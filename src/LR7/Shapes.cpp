#include "Shapes.h"
#include <iostream>
#include <cmath>
using namespace std;

void Point::Fly(int Cost) {
    int XX, YY;
    int maxX = 80;
    int maxY = 24;
    
    Show();
    srand(time(NULL));
    
    do {
        GetLocation(XX, YY);
        
        do {
            XX = XX + (int)(((double)rand() / RAND_MAX - 0.5) * Cost);
        } while (XX <= 1 || XX >= maxX - 1);
        
        do {
            YY = YY + (int)(((double)rand() / RAND_MAX - 0.5) * Cost);
        } while (YY <= 1 || YY >= maxY - 1);
        
        Hide();
        X = XX;
        Y = YY;
        Show();
        
#ifdef _WIN32
        Sleep(300);
#else
        usleep(300000);
#endif
        
    } while (!kbhit());
    
    getch();
}

void Circle::FlyWithEffects(int Cost, bool changeColor, bool changeSector) {
    int XX, YY;
    int maxX = 80;
    int maxY = 24;
    int step = 0;
    
    Show();
    srand(time(NULL));
    
    do {
        GetLocation(XX, YY);
        
        do {
            XX = XX + (int)(((double)rand() / RAND_MAX - 0.5) * Cost);
        } while (XX <= Radius + 1 || XX >= maxX - Radius - 1);
        
        do {
            YY = YY + (int)(((double)rand() / RAND_MAX - 0.5) * Cost);
        } while (YY <= Radius + 1 || YY >= maxY - Radius - 1);
        
        Hide();
        X = XX;
        Y = YY;
        
        if (changeColor) {
            ChangeColor();
        }
        
        if (changeSector) {
            step++;
            if (step % 3 == 0) {
                ExpandSector(10);
            } else if (step % 3 == 1) {
                NarrowSector(10);
            }
        }
        
        Show();
        
#ifdef _WIN32
        Sleep(200);
#else
        usleep(200000);
#endif
        
    } while (!kbhit());
    
    getch();
}

void Ring::FlyWithEffects(int Cost, bool changeColor, bool changeSector, bool changeRing) {
    int XX, YY;
    int maxX = 80;
    int maxY = 24;
    int step = 0;
    
    Show();
    srand(time(NULL));
    
    do {
        GetLocation(XX, YY);
        
        do {
            XX = XX + (int)(((double)rand() / RAND_MAX - 0.5) * Cost);
        } while (XX <= Radius + 1 || XX >= maxX - Radius - 1);
        
        do {
            YY = YY + (int)(((double)rand() / RAND_MAX - 0.5) * Cost);
        } while (YY <= Radius + 1 || YY >= maxY - Radius - 1);
        
        Hide();
        X = XX;
        Y = YY;
        
        step++;
        
        if (changeColor) {
            ChangeColor();
        }
        
        if (changeSector) {
            switch (step % 4) {
                case 0:
                    ExpandRingSector(15);
                    break;
                case 1:
                    NarrowRingSector(15);
                    break;
                case 2:
                    if (changeRing) {
                        ExpandRing(1);
                    }
                    break;
                case 3:
                    if (changeRing) {
                        NarrowRing(1);
                    }
                    break;
            }
        } else if (changeRing) {
            if (step % 2 == 0) {
                ExpandRing(1);
            } else {
                NarrowRing(1);
            }
        }
        
        Show();
        
#ifdef _WIN32
        Sleep(250);
#else
        usleep(250000);
#endif
        
    } while (!kbhit());
    
    getch();
}