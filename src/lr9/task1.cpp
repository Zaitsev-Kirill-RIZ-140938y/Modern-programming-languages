#include <iostream>
#include <cstring>
using namespace std;

// ===========================================
// ЛР9: шаблоны функций и классов
// ===========================================

// ===========================================
// Шаблон сортировки пузырьком из учебника (стр. 20-21)
// template <class T> — T может быть любым типом
// главное чтобы для этого типа работал оператор >
// ===========================================
template <class T>
void Sort(T array[], size_t size) {
    for (size_t i = 0; i < size - 1; i++)
        for (size_t j = size - 1; i < j; j--)
            if (array[i] > array[j]) {
                T tmp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = tmp;
            }
}

// ===========================================
// Задание 1: шаблон Sort с классом Money (стр. 22)
// чтобы Sort мог сортировать Money, нужен оператор >
// ===========================================
class Money {
    long dollars;
    int cents;
public:
    Money() : dollars(0), cents(0) {}
    Money(long d, int c) : dollars(d), cents(c) {}

    // оператор > — без него Sort не сможет сравнивать Money
    int operator>(const Money& amt) const {
        return (dollars > amt.dollars) ||
               ((dollars == amt.dollars) && (cents > amt.cents));
    }

    // оператор << для красивого вывода
    friend ostream& operator<<(ostream& os, const Money& amt) {
        os << "$" << amt.dollars << '.' << amt.cents;
        return os;
    }
};

// ===========================================
// Задание 2: примеры из п. 9.1.2 — перегрузка шаблона getmax
// ===========================================

// getmax для двух значений любого типа
template <class T>
T getmax(T t1, T t2) {
    return t1 > t2 ? t1 : t2;
}

// getmax для массива любого типа
template <class T>
T getmax(T t[], size_t size) {
    T retval = t[0];
    for (size_t i = 1; i < size; i++)
        if (t[i] > retval) retval = t[i];
    return retval;
}

// ===========================================
// Задание 2: пример из п. 9.1.3 — специализация для char*
// обычный getmax сравнивает через >, но для char* это
// сравнивает адреса, а не содержимое строк
// поэтому пишем отдельную версию
// ===========================================
char* getmax(char* s1, char* s2) {
    return strcmp(s1, s2) > 0 ? s1 : s2;
}

// ===========================================
// Шаблон класса Tstack — стек (стр. 25-26)
// стек — как стопка тарелок: кладёшь сверху, берёшь сверху
// LIFO — Last In First Out (последний вошёл — первый вышел)
// ===========================================
template <class T>
class Tstack {
protected:
    int numItem;   // сколько элементов сейчас
    int maxSize;   // максимальный размер
    T* item;       // массив элементов
public:
    Tstack(int size = 10) {
        numItem = 0;
        maxSize = size;
        item = new T[size];
    }
    ~Tstack() { delete[] item; }

    void push(T t) {
        if (numItem < maxSize) {
            item[numItem++] = t;
        } else {
            cout << "Стек полон!" << endl;
        }
    }

    T pop() {
        if (numItem > 0) {
            return item[--numItem];
        }
        cout << "Стек пуст!" << endl;
        return T();
    }

    bool isEmpty() { return numItem == 0; }

    // подсмотреть верхний элемент без удаления
    T top() {
        if (numItem > 0) return item[numItem - 1];
        return T();
    }

    int count() { return numItem; }
};

// ===========================================
// Задание 3: сортировка ж/д состава с тупиком (стеком)
//
// Идея из рис. 1 (стр. 29):
// Вагоны приходят по одному (вход). Есть тупик (стек).
// Нужно выпустить вагоны в отсортированном порядке (выход).
//
// Алгоритм:
// - берём вагон со входа
// - если он больше верхнего в тупике — сначала выпускаем
//   из тупика всё что меньше него на выход
// - потом кладём вагон в тупик
// - в конце выпускаем всё из тупика на выход
//
// По сути это сортировка с помощью стека
// ===========================================
void sortTrain(int wagons[], int n) {
    Tstack<int> tupik(n);  // тупик — стек для int
    int* result = new int[n]; // выходной путь
    int resultIdx = 0;

    cout << "  Исходный состав: ";
    for (int i = 0; i < n; i++) cout << wagons[i] << " ";
    cout << endl;

    for (int i = 0; i < n; i++) {
        // пока в тупике есть вагоны и верхний меньше текущего —
        // выпускаем их на выход (они уже на своём месте)
        while (!tupik.isEmpty() && tupik.top() <= wagons[i]) {
            result[resultIdx++] = tupik.pop();
            cout << "  Из тупика на выход: " << result[resultIdx - 1] << endl;
        }
        // текущий вагон — в тупик
        tupik.push(wagons[i]);
        cout << "  Вагон " << wagons[i] << " -> в тупик" << endl;
    }

    // выпускаем оставшиеся из тупика
    while (!tupik.isEmpty()) {
        result[resultIdx++] = tupik.pop();
        cout << "  Из тупика на выход: " << result[resultIdx - 1] << endl;
    }

    cout << "  Отсортированный состав: ";
    for (int i = 0; i < n; i++) cout << result[i] << " ";
    cout << endl;

    delete[] result;
}

int main() {
    // === Задание 1: Sort с Money (стр. 22) ===
    cout << "=== Задание 1: шаблон Sort с классом Money ===" << endl;
    Money mas[] = {
        Money(19, 10),
        Money(99, 99),
        Money(99, 95),
        Money(19, 95)
    };
    int moneySize = sizeof(mas) / sizeof(mas[0]);

    cout << "  До сортировки:" << endl;
    for (int i = 0; i < moneySize; i++)
        cout << "    mas[" << i << "] = " << mas[i] << endl;

    Sort(mas, moneySize);

    cout << "  После сортировки:" << endl;
    for (int i = 0; i < moneySize; i++)
        cout << "    mas[" << i << "] = " << mas[i] << endl;
    cout << endl;

    // Sort работает и с обычными int — тот же шаблон
    cout << "  Sort с int:" << endl;
    int intMas[] = {10, 20, 30, 11, 25, 32, 0};
    int intSize = sizeof(intMas) / sizeof(intMas[0]);
    Sort(intMas, intSize);
    for (int i = 0; i < intSize; i++)
        cout << "    mas[" << i << "] = " << intMas[i] << endl;
    cout << endl;

    // === Задание 2: getmax (п. 9.1.2, стр. 23) ===
    cout << "=== Задание 2: шаблон getmax ===" << endl;
    int i1 = 3, i2 = 5;
    cout << "  max(3, 5) = " << getmax(i1, i2) << endl;

    double d1 = 3.14, d2 = 2.71;
    cout << "  max(3.14, 2.71) = " << getmax(d1, d2) << endl;

    int arr[] = {3, 9, 5, 8};
    cout << "  max массива {3,9,5,8} = " << getmax(arr, (size_t)4) << endl;
    cout << endl;

    // === Задание 2: специализация для строк (п. 9.1.3, стр. 24) ===
    cout << "=== Задание 2: специализация getmax для строк ===" << endl;
    char* s1 = (char*)"строка1";
    char* s2 = (char*)"строка2";
    cout << "  max int = " << getmax(i1, i2) << endl;
    cout << "  max str = " << getmax(s1, s2) << endl;
    // без специализации сравнивались бы адреса, а не содержимое
    cout << endl;

    // === Задание 2: Tstack (стр. 25-27) ===
    cout << "=== Tstack — шаблон стека ===" << endl;
    Tstack<int> st(10);
    st.push(33);
    st.push(45);
    cout << "  Значения в стеке: ";
    cout << st.pop() << ", " << st.pop() << endl;
    // выведет 45, 33 — последний вошёл, первый вышел
    cout << endl;

    // === Задание 3: ж/д сортировка через тупик-стек ===
    cout << "=== Задание 3: сортировка ж/д состава ===" << endl;
    // вагоны как на рисунке: входят 1, 5, 3
    // нужно получить на выходе: 1, 3, 5 (по возрастанию)
    int wagons1[] = {1, 5, 3};
    sortTrain(wagons1, 3);
    cout << endl;

    // ещё пример посложнее
    int wagons2[] = {3, 1, 4, 2, 5};
    sortTrain(wagons2, 5);

    return 0;
}