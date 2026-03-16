#include <iostream>
using namespace std;

// просто выводим массив через пробел чтобы посмотреть что там
void printArray(int mas[], int n) {
    for (int i = 0; i < n; i++)
        cout << mas[i] << ' ';
    cout << endl;
}

// ===========================================
// Задание 1: сортировка "мини-макс"
// это по сути сортировка выбором — ищем минимум
// и ставим его на своё место, потом следующий и тд
// ===========================================
void sortMinMax(int mas[], int n) {
    int imin;
    // проходим по всем элементам кроме последнего
    for (int i = 0; i < n - 1; i++) {
        imin = i; // считаем что текущий элемент — минимальный
        // ищем настоящий минимум среди оставшихся
        for (int j = i + 1; j < n; j++)
            if (mas[j] < mas[imin]) imin = j;
        // меняем местами текущий и найденный минимум
        int t = mas[i];
        mas[i] = mas[imin];
        mas[imin] = t;
    }
}

// ===========================================
// Задание 2а: пузырьковая сортировка
// идея простая — сравниваем соседние элементы
// если левый больше правого — меняем их местами
// и так много раз, пока всё не отсортируется
// ===========================================
void bubbleSort(int mas[], int n) {
    for (int i = 0; i < n - 1; i++)
        // каждый проход самый большой "всплывает" наверх
        for (int j = 0; j < n - 1 - i; j++)
            if (mas[j] > mas[j + 1]) {
                // меняем соседей местами
                int t = mas[j];
                mas[j] = mas[j + 1];
                mas[j + 1] = t;
            }
}

// ===========================================
// Задание 2б: быстрая сортировка (quicksort)
// берём средний элемент как "опорный", потом
// всё что меньше него — налево, что больше — направо
// и рекурсивно делаем то же самое для левой и правой части
// ===========================================
void quickSort(int mas[], int left, int right) {
    int i = left, j = right;
    int pivot = mas[(left + right) / 2]; // опорный — берём средний

    // двигаем i вправо пока не найдём элемент >= pivot
    // двигаем j влево пока не найдём элемент <= pivot
    // потом меняем их местами
    while (i <= j) {
        while (mas[i] < pivot) i++;
        while (mas[j] > pivot) j--;
        if (i <= j) {
            int t = mas[i];
            mas[i] = mas[j];
            mas[j] = t;
            i++;
            j--;
        }
    }

    // рекурсивно сортируем левую и правую части
    if (left < j)  quickSort(mas, left, j);
    if (i < right) quickSort(mas, i, right);
}

// ===========================================
// Задание 3: чётные по возрастанию, нечётные по убыванию
// тут я сначала раскидываю числа на два массива,
// потом каждый сортирую отдельно и вывожу
// ===========================================
void sortEvenOdd(int mas[], int n) {
    // сначала считаем сколько чётных и нечётных
    int evenCount = 0, oddCount = 0;
    for (int i = 0; i < n; i++) {
        if (mas[i] % 2 == 0) evenCount++;  // делится на 2 без остатка — чётное
        else oddCount++;
    }

    // создаём два отдельных массива
    int* evens = new int[evenCount];
    int* odds  = new int[oddCount];
    int ei = 0, oi = 0;

    // раскидываем числа
    for (int i = 0; i < n; i++) {
        if (mas[i] % 2 == 0) evens[ei++] = mas[i];
        else odds[oi++] = mas[i];
    }

    // сортируем чётные по возрастанию (пузырьком)
    for (int i = 0; i < evenCount - 1; i++)
        for (int j = 0; j < evenCount - 1 - i; j++)
            if (evens[j] > evens[j + 1]) {
                int t = evens[j];
                evens[j] = evens[j + 1];
                evens[j + 1] = t;
            }

    // сортируем нечётные по убыванию (тоже пузырёк, но знак наоборот)
    for (int i = 0; i < oddCount - 1; i++)
        for (int j = 0; j < oddCount - 1 - i; j++)
            if (odds[j] < odds[j + 1]) {  // тут < а не >, потому что убывание
                int t = odds[j];
                odds[j] = odds[j + 1];
                odds[j + 1] = t;
            }

    cout << "  Чётные (по возрастанию):  ";
    for (int i = 0; i < evenCount; i++) cout << evens[i] << ' ';
    cout << endl;

    cout << "  Нечётные (по убыванию):   ";
    for (int i = 0; i < oddCount; i++) cout << odds[i] << ' ';
    cout << endl;

    // не забываем освободить память (new -> delete)
    delete[] evens;
    delete[] odds;
}

// ===========================================
// Задания 4-5: сортировка по убыванию но не всего массива,
// а только куска от индекса n1 до n2
// остальные элементы остаются на месте
// ===========================================
void sortDescRange(int mas[], int n, int n1, int n2) {
    // на всякий случай проверяем что границы нормальные
    if (n1 < 0) n1 = 0;
    if (n2 >= n) n2 = n - 1;
    if (n1 > n2) return;

    // обычный пузырёк но только на отрезке [n1, n2]
    for (int i = n1; i < n2; i++)
        for (int j = n1; j < n2 - (i - n1); j++)
            if (mas[j] < mas[j + 1]) {  // < потому что сортируем по убыванию
                int t = mas[j];
                mas[j] = mas[j + 1];
                mas[j + 1] = t;
            }
}

// копирование массива — нужно чтобы каждый раз
// начинать с исходного, а не с уже отсортированного
void copyArray(int src[], int dst[], int n) {
    for (int i = 0; i < n; i++) dst[i] = src[i];
}

int main() {
    // массив из учебника
    int original[] = {2, 5, -8, 1, -4, 6, 3, -5, -9, 13, 0, 4, 9};
    int n = sizeof(original) / sizeof(int); // считаем кол-во элементов
    int mas[20]; // рабочая копия

    cout << "Исходный массив: ";
    printArray(original, n);
    cout << endl;

    // --- задание 1 ---
    cout << "=== 1. Сортировка мини-макс ===" << endl;
    copyArray(original, mas, n);
    sortMinMax(mas, n);
    cout << "  Результат: ";
    printArray(mas, n);
    cout << endl;

    // --- задание 2а ---
    cout << "=== 2а. Пузырёк ===" << endl;
    copyArray(original, mas, n);
    bubbleSort(mas, n);
    cout << "  Результат: ";
    printArray(mas, n);
    cout << endl;

    // --- задание 2б ---
    cout << "=== 2б. Быстрая сортировка ===" << endl;
    copyArray(original, mas, n);
    quickSort(mas, 0, n - 1);
    cout << "  Результат: ";
    printArray(mas, n);
    cout << endl;

    // --- задание 3 ---
    cout << "=== 3. Чётные/нечётные ===" << endl;
    sortEvenOdd(original, n);
    cout << endl;

    // --- задание 4 ---
    int N1 = 3, N2 = 8;
    cout << "=== 4. По убыванию на отрезке [" << N1 << ", " << N2 << "] ===" << endl;
    copyArray(original, mas, n);
    cout << "  До:    ";
    printArray(mas, n);
    sortDescRange(mas, n, N1, N2);
    cout << "  После: ";
    printArray(mas, n);
    cout << endl;

    // --- задание 5 ---
    N1 = 0;
    N2 = 5;
    cout << "=== 5. По убыванию на отрезке [" << N1 << ", " << N2 << "] ===" << endl;
    copyArray(original, mas, n);
    cout << "  До:    ";
    printArray(mas, n);
    sortDescRange(mas, n, N1, N2);
    cout << "  После: ";
    printArray(mas, n);

    return 0;
}