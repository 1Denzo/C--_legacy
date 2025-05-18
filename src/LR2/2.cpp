#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <limits>
#include <tuple>

#define N 5

using namespace std;

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

tuple<float, float> minMaxMainDiagonal(float m[][N]) {
    float min = numeric_limits<float>::infinity();
    float max = -numeric_limits<float>::infinity();
    for (int i = 0; i < N; i++) {
        min = std::min(min, m[i][i]);
        max = std::max(max, m[i][i]);
    }

    return {min, max};
}

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

float avg(float m[][N]) {
    float sum = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            sum += m[i][j];

    return sum / (N * N);
}

float sumBottomTriangle(float m[][N]) {
    float sum = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j <= i; j++) {
            sum += m[i][j];
        }

    return sum;
}

float avgBottomTriangle(float m[][N]) {
    int count = (1 + N) / 2 * N;
    return sumBottomTriangle(m) / count;
}

float sumTopTriangle(float m[][N]) {
    float sum = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j <= i; j++) {
            sum += m[j][i];
        }

    return sum;
}

float avgTopTriangle(float m[][N]) {
    int count = (1 + N) / 2 * N;
    return sumTopTriangle(m) / count;
}

float sumRow(float m[][N], int i) {
    float sum = 0;
    for (int j = 0; j < N; j++)
        sum += m[i][j];

    return sum;
}

float sumColumn(float m[][N], int i) {
    float sum = 0;
    for (int j = 0; j < N; j++)
        sum += m[j][i];

    return sum;
}

float minRow(float m[][N], int i) {
    float sum = 0;
    for (int j = 0; j < N; j++)
        sum += m[i][j];

    return sum;
}

float minColumn(float m[][N], int i) {
    float min = numeric_limits<float>::infinity();
    for (int j = 0; j < N; j++)
        min = std::min(min, m[j][i]);

    return min;
}

float maxRow(float m[][N], int i) {
    float max = -numeric_limits<float>::infinity();
    for (int j = 0; j < N; j++)
        max = std::max(max, m[i][j]);

    return max;
}

float maxColumn(float m[][N], int i) {
    float max = -numeric_limits<float>::infinity();
    for (int j = 0; j < N; j++)
        max = std::max(max, m[j][i]);

    return max;
}

float avgRow(float m[][N], int i) {
    return sumRow(m, i) / N;
}

float avgColumn(float m[][N], int i) {
    return sumColumn(m, i) / N;
}

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

int main() {
    float m[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            m[i][j] = rand() / 10.;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << setw(8) << setprecision(5) << m[i][j];
        cout << endl;
    }

    auto min_max = minMax(m);
    cout << "min: " << get<0>(min_max) << endl;
    cout << "max: " << get<1>(min_max) << endl;
    auto min_max_bottom_triangle = minMaxBottomTriangle(m);
    cout << "min bottom triangle: " << get<0>(min_max_bottom_triangle) << endl;
    cout << "max bottom triangle: " << get<1>(min_max_bottom_triangle) << endl;
    auto min_max_top_triangle = minMaxTopTriangle(m);
    cout << "min top triangle: " << get<0>(min_max_top_triangle) << endl;
    cout << "max top triangle: " << get<1>(min_max_top_triangle) << endl;
    auto min_max_main_diagonal = minMaxMainDiagonal(m);
    cout << "min main diagonal: " << get<0>(min_max_main_diagonal) << endl;
    cout << "max main diagonal: " << get<1>(min_max_main_diagonal) << endl;
    auto min_max_second_diagonal = minMaxSecondDiagonal(m);
    cout << "min second diagonal: " << get<0>(min_max_second_diagonal) << endl;
    cout << "max second diagonal: " << get<1>(min_max_second_diagonal) << endl;

    float avg_val = avg(m);
    cout << "average: " << avg_val << endl;
    cout << "near avg value: " << nearAvgValue(m, avg_val) << endl;
    cout << "sum bottom triangle: " << sumBottomTriangle(m) << endl;
    cout << "average bottom triangle: " << avgBottomTriangle(m) << endl;
    cout << "sum top triangle: " << sumTopTriangle(m) << endl;
    cout << "average top triangle: " << avgTopTriangle(m) << endl;

    cout << endl;

    for (int i = 0; i < N; i++) {
        cout << "sum row " << i << ": " << sumRow(m, i) << endl;
        cout << "min row " << i << ": " << minRow(m, i) << endl;
        cout << "max row " << i << ": " << maxRow(m, i) << endl;
        cout << "avg row " << i << ": " << avgRow(m, i) << endl;
        cout << endl;
    }
    for (int i = 0; i < N; i++) {
        cout << "sum column " << i << ": " << sumColumn(m, i) << endl;
        cout << "min column " << i << ": " << minColumn(m, i) << endl;
        cout << "max column " << i << ": " << maxColumn(m, i) << endl;
        cout << "avg column " << i << ": " << avgColumn(m, i) << endl;
        cout << endl;
    }
    return 0;
}