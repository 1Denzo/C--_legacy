#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
#include <cstdlib>

#define MAX_LINE_LEN 1000
#define MAX_PAGES 1000

// Структура для хранения страницы
struct Page {
    std::string lines[50];
    int lineCount;
    int pageNumber;
};

// Функция для извлечения номера из формата "-34-"
int extractPageNumber(const char* str) {
    int num = 0;
    char numStr[20];
    int j = 0;
    
    // Пропускаем первый символ '-'
    for(int i = 1; str[i] != '\0' && str[i] != '-'; i++) {
        if(isdigit(str[i])) {
            numStr[j++] = str[i];
        }
    }
    numStr[j] = '\0';
    
    if(j > 0) {
        num = atoi(numStr);
    }
    
    return num;
}

// Функция для удаления знаков переноса в конце строки
void removeHyphen(std::string& str) {
    if(!str.empty() && str.back() == '-') {
        str.pop_back();
    }
}

// Функция для обработки файла
void processFile(const char* inputFile, const char* outputFile) {
    std::ifstream fin(inputFile);
    std::ofstream fout(outputFile);
    
    if(!fin.is_open() || !fout.is_open()) {
        std::cout << "Ошибка открытия файлов!" << std::endl;
        return;
    }
    
    Page pages[MAX_PAGES];
    int pageCount = 0;
    std::string buffer;
    int currentPage = -1;
    
    std::cout << "Обработка файла " << inputFile << "..." << std::endl;
    
    // Первый проход: разбиваем на страницы и собираем номера
    while(std::getline(fin, buffer)) {
        // Проверяем, является ли строка номером страницы (начинается с '-')
        if(!buffer.empty() && buffer[0] == '-' && buffer.length() > 2 && buffer.back() == '-') {
            // Начинаем новую страницу
            currentPage++;
            pageCount++;
            pages[currentPage].pageNumber = extractPageNumber(buffer.c_str());
            pages[currentPage].lineCount = 0;
            std::cout << "  Найдена страница " << (currentPage + 1) 
                     << ", номер " << pages[currentPage].pageNumber << std::endl;
        }
        else if(currentPage >= 0) {
            // Обычная строка текущей страницы
            if(pages[currentPage].lineCount < 50) {
                removeHyphen(buffer); // Удаляем знаки переноса
                pages[currentPage].lines[pages[currentPage].lineCount] = buffer;
                pages[currentPage].lineCount++;
            }
        }
    }
    
    fin.close();
    
    // Второй проход: записываем в выходной файл с номерами в конце
    std::cout << "\nЗапись результата в " << outputFile << "..." << std::endl;
    
    for(int p = 0; p < pageCount; p++) {
        // Записываем все строки страницы
        for(int l = 0; l < pages[p].lineCount; l++) {
            fout << pages[p].lines[l] << std::endl;
        }
        // Записываем номер страницы в конце
        fout << pages[p].pageNumber << std::endl;
        
        // Добавляем разделитель страниц (табуляция)
        if(p < pageCount - 1) {
            fout << "\t" << std::endl;
        }
    }
    
    fout.close();
    
    std::cout << "\nОбработка завершена!" << std::endl;
    std::cout << "Всего обработано страниц: " << pageCount << std::endl;
}

// Функция для просмотра результата
void viewFile(const char* filename) {
    std::ifstream f(filename);
    if(!f.is_open()) {
        std::cout << "Не удалось открыть " << filename << std::endl;
        return;
    }
    
    std::string buffer;
    int lineNum = 0;
    
    std::cout << "\n--- Содержимое " << filename << " ---" << std::endl;
    while(std::getline(f, buffer)) {
        std::cout << lineNum + 1 << ": " << buffer << std::endl;
        lineNum++;
    }
    
    f.close();
    std::cout << "------------------------" << std::endl;
}

// Функция для создания тестового файла
void createTestFile(const char* filename) {
    std::ofstream f(filename);
    if(!f.is_open()) return;
    
    f << "-1-" << std::endl;
    f << "Это первая страница" << std::endl;
    f << "Продолжение первой страницы-" << std::endl;
    f << " с переносом" << std::endl;
    f << "\t" << std::endl;
    
    f << "-2-" << std::endl;
    f << "Вторая страница начинается здесь" << std::endl;
    f << "Еще текст на второй странице" << std::endl;
    f << "\t" << std::endl;
    
    f << "-3-" << std::endl;
    f << "Третья страница" << std::endl;
    f << "Последняя строка третьей страницы-" << std::endl;
    f << " с переносом" << std::endl;
    
    f.close();
    std::cout << "Создан тестовый файл " << filename << std::endl;
}

int main() {
    char inputFile[100], outputFile[100];
    int choice;
    
    std::cout << "=== ПРОГРАММА ОБРАБОТКИ НОМЕРОВ СТРАНИЦ ===" << std::endl;
    std::cout << "1. Создать тестовый файл" << std::endl;
    std::cout << "2. Обработать существующий файл" << std::endl;
    std::cout << "3. Выход" << std::endl;
    std::cout << "Выберите действие: ";
    std::cin >> choice;
    
    if(choice == 1) {
        createTestFile("test_input.txt");
        viewFile("test_input.txt");
        std::cout << "\nТеперь обработаем этот файл..." << std::endl;
        processFile("test_input.txt", "test_output.txt");
        viewFile("test_output.txt");
    }
    else if(choice == 2) {
        std::cout << "Введите имя входного файла: ";
        std::cin >> inputFile;
        std::cout << "Введите имя выходного файла: ";
        std::cin >> outputFile;
        
        processFile(inputFile, outputFile);
        viewFile(outputFile);
    }
    
    std::cout << "\nПрограмма завершена." << std::endl;
    return 0;
}