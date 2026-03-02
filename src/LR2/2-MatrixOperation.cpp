#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <limits>
#include <tuple>
#include <array>
#include <vector>

#define N 5

using namespace std;

//1 Метод для нахождения минимума\максимума матрицы.
tuple<float, float> minMax(float m[][N]) {
    float min = numeric_limits<float>::infinity();
    float max = -numeric_limits<float>::infinity();
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            min = std::min(min, m[i][j]);
            max = std::max(max, m[i][j]);
        }

    return {min, max};
}

//2 Метод для нахождения максимума\минимума нижнетреугольной части матрицы.
tuple<float, float> minMaxBottomTriangle(float m[][N]) {
    float min = numeric_limits<float>::infinity();
    float max = -numeric_limits<float>::infinity();
    for (int i = 0; i < N; i++)
        for (int j = 0; j <= i; j++) {
            min = std::min(min, m[i][j]);
            max = std::max(max, m[i][j]);
        }

    return {min, max};
}

//3 Метод для нахождения максимума\минимума верхнетреугольной части матрицы.
tuple<float, float> minMaxTopTriangle(float m[][N]) {
    float min = numeric_limits<float>::infinity();
    float max = -numeric_limits<float>::infinity();
    for (int i = 0; i < N; i++)
        for (int j = 0; j <= i; j++) {
            min = std::min(min, m[j][i]);
            max = std::max(max, m[j][i]);
        }

    return {min, max};
}

//4 Метод для нахождения максимума\минимума главной диагонали матрицы.
tuple<float, float> minMaxMainDiagonal(float m[][N]) {
    float min = numeric_limits<float>::infinity();
    float max = -numeric_limits<float>::infinity();
    for (int i = 0; i < N; i++) {
        min = std::min(min, m[i][i]);
        max = std::max(max, m[i][i]);
    }

    return {min, max};
}

//5 Метод для нахождения максимума\минимума второстепенной диагонали матрицы.
tuple<float, float> minMaxSecondDiagonal(float m[][N]) {
    float min = numeric_limits<float>::infinity();
    float max = -numeric_limits<float>::infinity();
    for (int i = 0; i < N; i++) {
        int j = N - i - 1;
        min = std::min(min, m[j][i]);
        max = std::max(max, m[j][i]);
    }

    return {min, max};
}

//6 Метод для нахождения cреднеарифметического значение элементов матрицы.
float avg(float m[][N]) {
    float sum = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            sum += m[i][j];

    return sum / (N * N);
}

// Декларации функций для 7 и 8
float sumBottomTriangle(float m[][N]);
float sumTopTriangle(float m[][N]);

//7 Метод для нахождения cреднеарифметического значения элементов нижнетреугольной части матрицы.
float avgBottomTriangle(float m[][N]) {
    int count = (1 + N) * N / 2;
    return sumBottomTriangle(m) / count;
}

//8 Метод для нахождения cреднеарифметического значения элементов верхнетреугольной части матрицы.
float avgTopTriangle(float m[][N]) {
    int count = (1 + N) * N / 2;
    return sumTopTriangle(m) / count;
}

//9 Метод для нахождения cуммы строк матрицы.
float sumRow(float m[][N], int i) {
    float sum = 0;
    for (int j = 0; j < N; j++)
        sum += m[i][j];

    return sum;
}

//10 Метод для нахождения cуммы столбцов матрицы;
float sumColumn(float m[][N], int i) {
    float sum = 0;
    for (int j = 0; j < N; j++)
        sum += m[j][i];

    return sum;
}

//11 Метод для нахождения максимального/минимального значения в строке
tuple<float*, float*> minMaxRows(float m[][N]) {
    // Создаем массивы для хранения результатов
    float* minRows = new float[N];
    float* maxRows = new float[N];
    
    // Проходим по каждой строке
    for (int i = 0; i < N; i++) {
        // Инициализируем min и max для текущей строки
        float min = numeric_limits<float>::infinity();
        float max = -numeric_limits<float>::infinity();
        
        // Проходим по всем столбцам текущей строки
        for (int j = 0; j < N; j++) {
            // Обновляем min и max
            if (m[i][j] < min) min = m[i][j];
            if (m[i][j] > max) max = m[i][j];
        }
        
        // Сохраняем результаты для текущей строки
        minRows[i] = min;
        maxRows[i] = max;
    }
    
    // Возвращаем указатели на массивы
    return {minRows, maxRows};
}

//12 Метод для нахождения максимального/минимального значения в столбце
tuple<float*, float*> minMaxColumnsExplicit(float m[][N]) {
    float* minCols = new float[N];
    float* maxCols = new float[N];
    
    for (int j = 0; j < N; j++) {
        float minVal = numeric_limits<float>::infinity();
        float maxVal = -numeric_limits<float>::infinity();
        
        for (int i = 0; i < N; i++) {
            minVal = min(minVal, m[i][j]);
            maxVal = max(maxVal, m[i][j]);
        }
        
        minCols[j] = minVal;
        maxCols[j] = maxVal;
    }
    
    // Явное создание tuple
    return make_tuple(minCols, maxCols);
}

//13 Метод для нахождения cреднеарифметического значений строк.
tuple<array<float, N>> avgRowsStatic(float m[][N]) {
    array<float, N> averages;
    
    for (int i = 0; i < N; i++) {
        float sum = 0;
        for (int j = 0; j < N; j++) {
            sum += m[i][j];
        }
        averages[i] = sum / N;
    }
    
    return make_tuple(averages);
}

//14 Метод для нахождения cреднеарифметического значений столбцов.
tuple<vector<float>> avgColumnsRect(const vector<vector<float>>& matrix) {
    if (matrix.empty()) return make_tuple(vector<float>());
    
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    vector<float> averages(cols, 0.0);
    
    for (int j = 0; j < cols; j++) {
        float sum = 0;
        for (int i = 0; i < rows; i++) {
            sum += matrix[i][j];
        }
        averages[j] = sum / rows;
    }
    
    return make_tuple(averages);
}

//15 Метод для нахождения суммы нижне- и верхнегреугольных частей матрицы
tuple<float, float> sumBottomAndTopTriangles(float m[][N]) {
    float sumBottom = 0; // сумма нижнетреугольной части (включая диагональ)
    float sumTop = 0;    // сумма верхнетреугольной части (включая диагональ)
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i >= j) {
                // Элемент на или ниже главной диагонали
                sumBottom += m[i][j];
            }
            if (i <= j) {
                // Элемент на или выше главной диагонали
                sumTop += m[i][j];
            }
        }
    }
    
    return make_tuple(sumBottom, sumTop);
}

//16 Метод для нахождения элемента, наиболее близкого по значению к среднеарифметическому.
float nearAvgValue(float m[][N], float avg_val) {
    float diff = numeric_limits<float>::infinity();
    float last_val = m[0][0];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            float diff_local = abs(m[i][j] - avg_val);
            if (diff_local < diff) {
                diff = diff_local;
                last_val = m[i][j];
            }
        }

    return last_val;
}

// Вспомогательные функции для сумм треугольников
float sumBottomTriangle(float m[][N]) {
    float sum = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j <= i; j++)
            sum += m[i][j];
    return sum;
}

float sumTopTriangle(float m[][N]) {
    float sum = 0;
    for (int i = 0; i < N; i++)
        for (int j = i; j < N; j++)
            sum += m[i][j];
    return sum;
}

int main() {
    // Инициализация матрицы случайными числами
    float m[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            m[i][j] = rand() / 10.0f;

    // Вывод исходной матрицы
    cout << "\n======================================================\n";
    cout << "ИСХОДНАЯ МАТРИЦА " << N << "x" << N << ":\n";
    cout << "======================================================\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << setw(10) << fixed << setprecision(2) << m[i][j];
        cout << endl;
    }
    cout << "======================================================\n\n";

    // 1. Минимум и максимум всей матрицы
    auto [globalMin, globalMax] = minMax(m);
    cout << "1. МИНИМУМ И МАКСИМУМ ВСЕЙ МАТРИЦЫ:\n";
    cout << "   - Минимальный элемент: " << fixed << setprecision(2) << globalMin << endl;
    cout << "   - Максимальный элемент: " << fixed << setprecision(2) << globalMax << endl;
    cout << endl;

    // 2. Минимум и максимум нижнетреугольной части
    auto [bottomMin, bottomMax] = minMaxBottomTriangle(m);
    cout << "2. МИНИМУМ И МАКСИМУМ НИЖНЕТРЕУГОЛЬНОЙ ЧАСТИ (включая диагональ):\n";
    cout << "   - Минимальный элемент: " << fixed << setprecision(2) << bottomMin << endl;
    cout << "   - Максимальный элемент: " << fixed << setprecision(2) << bottomMax << endl;
    cout << endl;

    // 3. Минимум и максимум верхнетреугольной части
    auto [topMin, topMax] = minMaxTopTriangle(m);
    cout << "3. МИНИМУМ И МАКСИМУМ ВЕРХНЕТРЕУГОЛЬНОЙ ЧАСТИ (включая диагональ):\n";
    cout << "   - Минимальный элемент: " << fixed << setprecision(2) << topMin << endl;
    cout << "   - Максимальный элемент: " << fixed << setprecision(2) << topMax << endl;
    cout << endl;

    // 4. Минимум и максимум главной диагонали
    auto [diagMin, diagMax] = minMaxMainDiagonal(m);
    cout << "4. МИНИМУМ И МАКСИМУМ ГЛАВНОЙ ДИАГОНАЛИ:\n";
    cout << "   - Минимальный элемент: " << fixed << setprecision(2) << diagMin << endl;
    cout << "   - Максимальный элемент: " << fixed << setprecision(2) << diagMax << endl;
    cout << endl;

    // 5. Минимум и максимум второстепенной диагонали
    auto [secondMin, secondMax] = minMaxSecondDiagonal(m);
    cout << "5. МИНИМУМ И МАКСИМУМ ВТОРОСТЕПЕННОЙ ДИАГОНАЛИ:\n";
    cout << "   - Минимальный элемент: " << fixed << setprecision(2) << secondMin << endl;
    cout << "   - Максимальный элемент: " << fixed << setprecision(2) << secondMax << endl;
    cout << endl;

    // 6. Среднее арифметическое всей матрицы
    float average = avg(m);
    cout << "6. СРЕДНЕЕ АРИФМЕТИЧЕСКОЕ ВСЕЙ МАТРИЦЫ:\n";
    cout << "   - Среднее значение: " << fixed << setprecision(2) << average << endl;
    cout << endl;

    // 7. Среднее арифметическое нижнетреугольной части
    float avgBottom = avgBottomTriangle(m);
    cout << "7. СРЕДНЕЕ АРИФМЕТИЧЕСКОЕ НИЖНЕТРЕУГОЛЬНОЙ ЧАСТИ:\n";
    cout << "   - Среднее значение: " << fixed << setprecision(2) << avgBottom << endl;
    cout << endl;

    // 8. Среднее арифметическое верхнетреугольной части
    float avgTop = avgTopTriangle(m);
    cout << "8. СРЕДНЕЕ АРИФМЕТИЧЕСКОЕ ВЕРХНЕТРЕУГОЛЬНОЙ ЧАСТИ:\n";
    cout << "   - Среднее значение: " << fixed << setprecision(2) << avgTop << endl;
    cout << endl;

    // 9. Суммы строк
    cout << "9. СУММЫ ЭЛЕМЕНТОВ ПО СТРОКАМ:\n";
    for (int i = 0; i < N; i++) {
        float rowSum = sumRow(m, i);
        cout << "   - Строка " << i << ": " << fixed << setprecision(2) << rowSum << endl;
    }
    cout << endl;

    // 10. Суммы столбцов
    cout << "10. СУММЫ ЭЛЕМЕНТОВ ПО СТОЛБЦАМ:\n";
    for (int i = 0; i < N; i++) {
        float colSum = sumColumn(m, i);
        cout << "   - Столбец " << i << ": " << fixed << setprecision(2) << colSum << endl;
    }
    cout << endl;

    // 11. Минимумы и максимумы по строкам
    auto [minRows, maxRows] = minMaxRows(m);
    cout << "11. МИНИМУМЫ И МАКСИМУМЫ ПО СТРОКАМ:\n";
    for (int i = 0; i < N; i++) {
        cout << "   - Строка " << i << ": min = " << fixed << setprecision(2) << minRows[i] 
             << ", max = " << fixed << setprecision(2) << maxRows[i] << endl;
    }
    delete[] minRows;
    delete[] maxRows;
    cout << endl;

    // 12. Минимумы и максимумы по столбцам
    auto [minCols, maxCols] = minMaxColumnsExplicit(m);
    cout << "12. МИНИМУМЫ И МАКСИМУМЫ ПО СТОЛБЦАМ:\n";
    for (int i = 0; i < N; i++) {
        cout << "   - Столбец " << i << ": min = " << fixed << setprecision(2) << minCols[i] 
             << ", max = " << fixed << setprecision(2) << maxCols[i] << endl;
    }
    delete[] minCols;
    delete[] maxCols;
    cout << endl;

    // 13. Средние арифметические по строкам
    auto [rowAverages] = avgRowsStatic(m);
    cout << "13. СРЕДНИЕ АРИФМЕТИЧЕСКИЕ ПО СТРОКАМ:\n";
    for (int i = 0; i < N; i++) {
        cout << "   - Строка " << i << ": " << fixed << setprecision(2) << rowAverages[i] << endl;
    }
    cout << endl;

    // 14. Средние арифметические по столбцам (с использованием vector)
    vector<vector<float>> vecMatrix(N, vector<float>(N));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            vecMatrix[i][j] = m[i][j];
    
    auto [colAverages] = avgColumnsRect(vecMatrix);
    cout << "14. СРЕДНИЕ АРИФМЕТИЧЕСКИЕ ПО СТОЛБЦАМ:\n";
    for (int i = 0; i < N; i++) {
        cout << "   - Столбец " << i << ": " << fixed << setprecision(2) << colAverages[i] << endl;
    }
    cout << endl;

    // 15. Суммы нижне- и верхнетреугольных частей
    auto [sumBottom, sumTop] = sumBottomAndTopTriangles(m);
    cout << "15. СУММЫ НИЖНЕ- И ВЕРХНЕТРЕУГОЛЬНЫХ ЧАСТЕЙ:\n";
    cout << "   - Сумма нижнетреугольной части (с диагональю): " << fixed << setprecision(2) << sumBottom << endl;
    cout << "   - Сумма верхнетреугольной части (с диагональю): " << fixed << setprecision(2) << sumTop << endl;
    
    float diagonalSum = 0;
    for (int i = 0; i < N; i++) diagonalSum += m[i][i];
    cout << "   - Сумма диагонали: " << fixed << setprecision(2) << diagonalSum << endl;
    cout << "   - Сумма нижнего треугольника (без диагонали): " << fixed << setprecision(2) << (sumBottom - diagonalSum) << endl;
    cout << "   - Сумма верхнего треугольника (без диагонали): " << fixed << setprecision(2) << (sumTop - diagonalSum) << endl;
    cout << endl;

    // 16. Элемент, наиболее близкий к среднему арифметическому
    float nearValue = nearAvgValue(m, average);
    cout << "16. ЭЛЕМЕНТ, НАИБОЛЕЕ БЛИЗКИЙ К СРЕДНЕМУ АРИФМЕТИЧЕСКОМУ:\n";
    cout << "   - Среднее арифметическое матрицы: " << fixed << setprecision(2) << average << endl;
    cout << "   - Ближайший элемент: " << fixed << setprecision(2) << nearValue << endl;
    cout << "   - Разница: " << fixed << setprecision(2) << abs(nearValue - average) << endl;
    cout << endl;

    cout << "======================================================\n";
    cout << "ЗАВЕРШЕНИЕ РАБОТЫ ПРОГРАММЫ\n";
    cout << "======================================================\n";

    return 0;
}