#include <iostream>
#include <cstring>  // тут живут strlen, strcpy, strcmp, strcat
#include <cstdlib>  // тут malloc, calloc, free
using namespace std;

// ===========================================
// Задание 1: просто пробуем стандартные функции
// strlen — длина строки
// strcpy — копирует одну строку в другую
// strcmp — сравнивает две строки (0 = одинаковые)
// strcat — склеивает строки (вторую дописывает к первой)
// ===========================================

// ===========================================
// Задание 2: пишем свои версии этих функций
// ===========================================

// длина строки — способ 1: просто считаем символы в цикле
// идём по строке пока не встретим '\0' (конец строки)
int dlina1(char* s) {
    int len = 0;
    while (s[len] != '\0')
        len++;
    return len;
}

// длина строки — способ 2: через указатель
// двигаем указатель вперёд и считаем шаги
int dlina2(char* s) {
    char* p = s;  // запоминаем начало
    while (*p != '\0')
        p++;      // двигаем указатель на следующий символ
    return p - s; // разница между концом и началом = длина
}

// длина строки — способ 3: рекурсия
// если текущий символ не '\0', то длина = 1 + длина остатка
int dlina3(char* s) {
    if (*s == '\0') return 0;
    return 1 + dlina3(s + 1);
}

// копирование строки — посимвольно копируем из src в dst
// пока не встретим конец строки
void kopir(char* dst, char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';  // не забываем поставить конец строки
}

// сравнение строк — сравниваем посимвольно
// если строки одинаковые — вернём 0
// если первая "меньше" — отрицательное число, если "больше" — положительное
void sravn(char* s1, char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
        i++;  // пока символы совпадают, идём дальше
    int result = s1[i] - s2[i];
    if (result == 0)
        cout << "  Строки одинаковые" << endl;
    else if (result < 0)
        cout << "  Первая строка меньше (result=" << result << ")" << endl;
    else
        cout << "  Первая строка больше (result=" << result << ")" << endl;
}

// конкатенация — дописываем src в конец dst
// сначала находим конец dst, потом туда копируем src
void konkat(char* dst, char* src) {
    int i = 0;
    // ищем конец первой строки
    while (dst[i] != '\0') i++;
    // дописываем вторую строку
    int j = 0;
    while (src[j] != '\0') {
        dst[i] = src[j];
        i++;
        j++;
    }
    dst[i] = '\0';  // ставим конец строки
}

int main() {
    // ===========================================
    // Задание 1: проверяем стандартные функции
    // ===========================================
    cout << "=== Задание 1: стандартные функции ===" << endl;
    char test1[] = "hello";
    char test2[] = "world";
    char buf[100];

    cout << "strlen(\"hello\") = " << strlen(test1) << endl;
    cout << "strlen(\"world\") = " << strlen(test2) << endl;

    strcpy(buf, test1);  // скопировали "hello" в buf
    cout << "strcpy: buf = " << buf << endl;

    cout << "strcmp(\"hello\", \"world\") = " << strcmp(test1, test2) << endl;

    strcat(buf, test2);  // склеили, теперь buf = "helloworld"
    cout << "strcat: buf = " << buf << endl;
    cout << endl;

    // ===========================================
    // Задание 2: свои функции
    // ===========================================
    cout << "=== Задание 2: свои функции ===" << endl;

    char str1[] = "qwerty";
    char str2[] = "1234567890";
    char result[200];  // буфер для результатов

    // три способа посчитать длину
    cout << "длина str1=\"" << str1 << "\": ";
    cout << "dlina1=" << dlina1(str1);
    cout << ", dlina2=" << dlina2(str1);
    cout << ", dlina3=" << dlina3(str1) << endl;

    cout << "длина str2=\"" << str2 << "\": ";
    cout << "dlina1=" << dlina1(str2);
    cout << ", dlina2=" << dlina2(str2);
    cout << ", dlina3=" << dlina3(str2) << endl;

    // копирование
    kopir(result, str1);
    cout << "kopir: result = " << result << endl;

    // сравнение
    cout << "sravn(str1, str2): ";
    sravn(str1, str2);

    // конкатенация — сначала копируем str1 в result, потом приклеиваем str2
    kopir(result, str1);
    konkat(result, str2);
    cout << "konkat: result = " << result << endl;
    cout << endl;

    // ===========================================
    // Задание 3: динамическая память через malloc
    // malloc выделяет кусок памяти нужного размера
    // (char*) — приводим тип, потому что malloc возвращает void*
    // free — освобождаем память когда она больше не нужна
    // ===========================================
    cout << "=== Задание 3: malloc ===" << endl;

    char* dyn1 = (char*)malloc(100);  // выделили 100 байт
    char* dyn2 = (char*)malloc(100);

    kopir(dyn1, "privet");
    kopir(dyn2, "mir");

    cout << "dyn1 = " << dyn1 << ", длина = " << dlina1(dyn1) << endl;
    cout << "dyn2 = " << dyn2 << ", длина = " << dlina1(dyn2) << endl;

    konkat(dyn1, dyn2);
    cout << "после konkat: dyn1 = " << dyn1 << endl;

    free(dyn1);  // освобождаем
    free(dyn2);
    cout << endl;

    // ===========================================
    // Задание 4: calloc вместо malloc
    // calloc делает то же самое что malloc, но ещё
    // заполняет всю выделенную память нулями
    // malloc(100) -> calloc(100, 1) — 100 элементов по 1 байту
    // ===========================================
    cout << "=== Задание 4: calloc ===" << endl;

    char* cal1 = (char*)calloc(100, sizeof(char));  // 100 символов, заполнены нулями
    char* cal2 = (char*)calloc(100, sizeof(char));

    kopir(cal1, "calloc_test");
    kopir(cal2, "_works!");

    cout << "cal1 = " << cal1 << endl;
    cout << "cal2 = " << cal2 << endl;

    konkat(cal1, cal2);
    cout << "после konkat: cal1 = " << cal1 << endl;

    // разница: malloc может содержать мусор, calloc — всегда нули
    // поэтому calloc безопаснее, но чуть медленнее
    cout << "Разница: malloc не обнуляет память, calloc — обнуляет" << endl;

    free(cal1);
    free(cal2);
    cout << endl;

    // ===========================================
    // Задание 5: массив строк
    // создаём массив из нескольких строк и применяем
    // наши функции ко всем строкам
    // ===========================================
    cout << "=== Задание 5: массив строк ===" << endl;

    // массив указателей на строки
    const char* words[] = {"banana", "apple", "cherry", "date", "elderberry"};
    int count = 5;

    // копируем в динамический массив чтобы можно было менять
    char* arr[5];
    for (int i = 0; i < count; i++) {
        arr[i] = (char*)malloc(100);
        kopir(arr[i], (char*)words[i]);
    }

    // выводим все строки и их длины
    cout << "Все строки:" << endl;
    for (int i = 0; i < count; i++)
        cout << "  arr[" << i << "] = \"" << arr[i] << "\", длина = " << dlina1(arr[i]) << endl;

    // сравниваем первую со второй
    cout << "Сравнение arr[0] и arr[1]: ";
    sravn(arr[0], arr[1]);

    // склеиваем первую и вторую
    konkat(arr[0], arr[1]);
    cout << "После konkat arr[0]+arr[1]: arr[0] = \"" << arr[0] << "\"" << endl;

    // копируем третью в четвёртую
    kopir(arr[3], arr[2]);
    cout << "После kopir arr[2] -> arr[3]: arr[3] = \"" << arr[3] << "\"" << endl;

    // не забываем освободить память
    for (int i = 0; i < count; i++)
        free(arr[i]);

    return 0;
}