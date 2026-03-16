#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define N 5

using namespace std;

// Вывод матрицы на экран
void printMatrix(float m[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << setw(10) << setprecision(4) << m[i][j];
        cout << endl;
    }
    cout << endl;
}

// 1. Минимум матрицы
float minMatrix(float m[N][N]) {
    float mn = m[0][0];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (m[i][j] < mn) mn = m[i][j];
    return mn;
}

// 2. Максимум матрицы
float maxMatrix(float m[N][N]) {
    float mx = m[0][0];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (m[i][j] > mx) mx = m[i][j];
    return mx;
}

// 3. Максимум нижнетреугольной части (i >= j)
float maxLowerTriangle(float m[N][N]) {
    float mx = m[0][0];
    for (int i = 0; i < N; i++)
        for (int j = 0; j <= i; j++)
            if (m[i][j] > mx) mx = m[i][j];
    return mx;
}

// 4. Максимум верхнетреугольной части (i <= j)
float maxUpperTriangle(float m[N][N]) {
    float mx = m[0][0];
    for (int i = 0; i < N; i++)
        for (int j = i; j < N; j++)
            if (m[i][j] > mx) mx = m[i][j];
    return mx;
}

// 5. Минимум нижнетреугольной части
float minLowerTriangle(float m[N][N]) {
    float mn = m[0][0];
    for (int i = 0; i < N; i++)
        for (int j = 0; j <= i; j++)
            if (m[i][j] < mn) mn = m[i][j];
    return mn;
}

// 6. Минимум верхнетреугольной части
float minUpperTriangle(float m[N][N]) {
    float mn = m[0][0];
    for (int i = 0; i < N; i++)
        for (int j = i; j < N; j++)
            if (m[i][j] < mn) mn = m[i][j];
    return mn;
}

// 7. Минимум главной диагонали
float minMainDiag(float m[N][N]) {
    float mn = m[0][0];
    for (int i = 1; i < N; i++)
        if (m[i][i] < mn) mn = m[i][i];
    return mn;
}

// 8. Максимум главной диагонали
float maxMainDiag(float m[N][N]) {
    float mx = m[0][0];
    for (int i = 1; i < N; i++)
        if (m[i][i] > mx) mx = m[i][i];
    return mx;
}

// 9. Минимум побочной диагонали
float minSecondDiag(float m[N][N]) {
    float mn = m[0][N - 1];
    for (int i = 1; i < N; i++)
        if (m[i][N - 1 - i] < mn) mn = m[i][N - 1 - i];
    return mn;
}

// 10. Максимум побочной диагонали
float maxSecondDiag(float m[N][N]) {
    float mx = m[0][N - 1];
    for (int i = 1; i < N; i++)
        if (m[i][N - 1 - i] > mx) mx = m[i][N - 1 - i];
    return mx;
}

// 11. Среднеарифметическое всей матрицы
float avgMatrix(float m[N][N]) {
    float sum = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            sum += m[i][j];
    return sum / (N * N);
}

// 12. Среднеарифметическое нижнетреугольной части
float avgLowerTriangle(float m[N][N]) {
    float sum = 0;
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j <= i; j++) {
            sum += m[i][j];
            count++;
        }
    return sum / count;
}

// 13. Среднеарифметическое верхнетреугольной части
float avgUpperTriangle(float m[N][N]) {
    float sum = 0;
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = i; j < N; j++) {
            sum += m[i][j];
            count++;
        }
    return sum / count;
}

// 14. Суммы строк
void sumRows(float m[N][N], float result[N]) {
    for (int i = 0; i < N; i++) {
        result[i] = 0;
        for (int j = 0; j < N; j++)
            result[i] += m[i][j];
    }
}

// 15. Суммы столбцов
void sumCols(float m[N][N], float result[N]) {
    for (int j = 0; j < N; j++) {
        result[j] = 0;
        for (int i = 0; i < N; i++)
            result[j] += m[i][j];
    }
}

// 16. Минимальные значения строк
void minRows(float m[N][N], float result[N]) {
    for (int i = 0; i < N; i++) {
        result[i] = m[i][0];
        for (int j = 1; j < N; j++)
            if (m[i][j] < result[i]) result[i] = m[i][j];
    }
}

// 17. Минимальные значения столбцов
void minCols(float m[N][N], float result[N]) {
    for (int j = 0; j < N; j++) {
        result[j] = m[0][j];
        for (int i = 1; i < N; i++)
            if (m[i][j] < result[j]) result[j] = m[i][j];
    }
}

// 18. Максимальные значения строк
void maxRows(float m[N][N], float result[N]) {
    for (int i = 0; i < N; i++) {
        result[i] = m[i][0];
        for (int j = 1; j < N; j++)
            if (m[i][j] > result[i]) result[i] = m[i][j];
    }
}

// 19. Максимальные значения столбцов
void maxCols(float m[N][N], float result[N]) {
    for (int j = 0; j < N; j++) {
        result[j] = m[0][j];
        for (int i = 1; i < N; i++)
            if (m[i][j] > result[j]) result[j] = m[i][j];
    }
}

// 20. Среднеарифметические значения строк
void avgRows(float m[N][N], float result[N]) {
    for (int i = 0; i < N; i++) {
        result[i] = 0;
        for (int j = 0; j < N; j++)
            result[i] += m[i][j];
        result[i] /= N;
    }
}

// 21. Среднеарифметические значения столбцов
void avgCols(float m[N][N], float result[N]) {
    for (int j = 0; j < N; j++) {
        result[j] = 0;
        for (int i = 0; i < N; i++)
            result[j] += m[i][j];
        result[j] /= N;
    }
}

// 22. Суммы нижне- и верхнетреугольных частей
void sumTriangles(float m[N][N], float &lower, float &upper) {
    lower = 0;
    upper = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            if (i >= j) lower += m[i][j];
            if (i <= j) upper += m[i][j];
        }
}

// 23. Элемент, ближайший к среднеарифметическому
float closestToAvg(float m[N][N]) {
    float avg = avgMatrix(m);
    float closest = m[0][0];
    float minDiff = fabs(m[0][0] - avg);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            float diff = fabs(m[i][j] - avg);
            if (diff < minDiff) {
                minDiff = diff;
                closest = m[i][j];
            }
        }
    return closest;
}

// Вспомогательная: вывод массива
void printArray(const char* label, float arr[N]) {
    cout << label;
    for (int i = 0; i < N; i++)
        cout << setw(10) << setprecision(4) << arr[i];
    cout << endl;
}

int main() {
    float m[N][N];
    float result[N];

    srand(time(nullptr));

    // Заполнение матрицы
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            m[i][j] = rand() / 10.0;

    cout << "=== Матрица ===" << endl;
    printMatrix(m);

    cout << "--- Скалярные значения ---" << endl;
    cout << "Минимум матрицы:            " << minMatrix(m) << endl;
    cout << "Максимум матрицы:           " << maxMatrix(m) << endl;
    cout << "Макс. нижней треуг.:        " << maxLowerTriangle(m) << endl;
    cout << "Макс. верхней треуг.:       " << maxUpperTriangle(m) << endl;
    cout << "Мин. нижней треуг.:         " << minLowerTriangle(m) << endl;
    cout << "Мин. верхней треуг.:        " << minUpperTriangle(m) << endl;
    cout << "Мин. главной диаг.:         " << minMainDiag(m) << endl;
    cout << "Макс. главной диаг.:        " << maxMainDiag(m) << endl;
    cout << "Мин. побочной диаг.:        " << minSecondDiag(m) << endl;
    cout << "Макс. побочной диаг.:       " << maxSecondDiag(m) << endl;
    cout << "Среднее матрицы:            " << avgMatrix(m) << endl;
    cout << "Среднее нижней треуг.:      " << avgLowerTriangle(m) << endl;
    cout << "Среднее верхней треуг.:     " << avgUpperTriangle(m) << endl;

    float lower, upper;
    sumTriangles(m, lower, upper);
    cout << "Сумма нижней треуг.:        " << lower << endl;
    cout << "Сумма верхней треуг.:       " << upper << endl;
    cout << "Ближайший к среднему:       " << closestToAvg(m) << endl;

    cout << endl << "--- Построчные/постолбцовые ---" << endl;

    sumRows(m, result);
    printArray("Суммы строк:       ", result);

    sumCols(m, result);
    printArray("Суммы столбцов:    ", result);

    minRows(m, result);
    printArray("Мин. строк:        ", result);

    minCols(m, result);
    printArray("Мин. столбцов:     ", result);

    maxRows(m, result);
    printArray("Макс. строк:       ", result);

    maxCols(m, result);
    printArray("Макс. столбцов:    ", result);

    avgRows(m, result);
    printArray("Средние строк:     ", result);

    avgCols(m, result);
    printArray("Средние столбцов:  ", result);

    return 0;
}