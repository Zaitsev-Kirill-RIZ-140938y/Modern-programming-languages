#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

// ===========================================
// ЛР8: потоки + программы со стр. 22, 23, 24
// ===========================================

// ===========================================
// Задание 1: класс Stroka с потоковым вводом/выводом
// добавляем операторы << и >> чтобы работало через потоки
// ===========================================
class Stroka {
    char* str;
    int maxLen;
public:
    Stroka(const char* s) {
        maxLen = strlen(s) + 1;
        str = new char[maxLen];
        strcpy(str, s);
    }
    Stroka() {
        maxLen = 256;
        str = new char[maxLen];
        str[0] = '\0';
    }
    Stroka(const Stroka& s) {
        maxLen = s.maxLen;
        str = new char[maxLen];
        strcpy(str, s.str);
    }
    ~Stroka() { delete[] str; }

    Stroka& operator=(const Stroka& s) {
        if (this == &s) return *this;
        delete[] str;
        maxLen = s.maxLen;
        str = new char[maxLen];
        strcpy(str, s.str);
        return *this;
    }
    int dlina() { return strlen(str); }

    // оператор вывода — cout << s
    // friend нужен чтобы функция видела приватное поле str
    friend ostream& operator<<(ostream& os, const Stroka& s) {
        os << s.str;
        return os;
    }
    // оператор ввода — cin >> s
    friend istream& operator>>(istream& is, Stroka& s) {
        is.getline(s.str, s.maxLen);
        return is;
    }
};

// ===========================================
// Задание 2: программа со стр. 22 — класс Money
// с перегрузкой оператора > и << для потокового вывода
// + шаблон сортировки Sort, который работает с Money
// ===========================================

// шаблон сортировки пузырьком — работает с любым типом
// главное чтобы у типа был оператор >
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

// класс Money — хранит доллары и центы
class Money {
    long dollars;
    int cents;
public:
    Money() : dollars(0), cents(0) {}
    Money(long d, int c) {
        dollars = d;
        cents = c;
    }

    // оператор > нужен чтобы шаблон Sort мог сравнивать Money
    int operator>(const Money& amt) const {
        return (dollars > amt.dollars) ||
               ((dollars == amt.dollars) && (cents > amt.cents));
    }

    // оператор << для вывода в поток (cout << m)
    friend ostream& operator<<(ostream& os, Money& amt) {
        os << "$" << amt.dollars << '.' << amt.cents;
        return os;
    }
};

// ===========================================
// Задание 2: программа со стр. 23 — шаблон getmax
// находит максимум из двух значений
// работает с int, float, и тд
// ===========================================
template <class T>
T getmax(T t1, T t2) {
    // тернарный оператор: если t1 > t2 вернуть t1, иначе t2
    return t1 > t2 ? t1 : t2;
}

// перегрузка getmax для массива — ищет максимум в массиве
template <class T>
T getmax(T t[], size_t size) {
    T retval = t[0];
    for (size_t i = 1; i < size; i++)
        if (t[i] > retval) retval = t[i];
    return retval;
}

// ===========================================
// Задание 2: программа со стр. 24 — специализация для строк
// обычный getmax сравнивает через >, но для char* это сравнивает
// адреса в памяти, а не содержимое строк
// поэтому пишем отдельную версию для char*
// ===========================================
char* getmax(char* s1, char* s2) {
    return strcmp(s1, s2) > 0 ? s1 : s2;
}

// ===========================================
// Задание 3: шифратор из ЛР5 через потоки
// ===========================================
void encryptStream(const char* inputFile, const char* outputFile, const char* key) {
    ifstream in(inputFile, ios::binary);   // бинарный режим
    ofstream out(outputFile, ios::binary);
    if (!in || !out) {
        cout << "Ошибка открытия файлов!" << endl;
        return;
    }
    int keyLen = strlen(key);
    int keyIndex = 0;
    char ch;
    while (in.get(ch)) {
        out.put(ch ^ key[keyIndex]);  // XOR шифрование
        keyIndex = (keyIndex + 1) % keyLen;  // ключ циклически
    }
    in.close();
    out.close();
    cout << "  " << inputFile << " -> " << outputFile << endl;
}

// ===========================================
// Задание 4: состояние потоков
// ===========================================
void showStreamState(const char* label, ios& stream) {
    cout << label << ": ";
    cout << "good=" << stream.good();
    cout << " eof=" << stream.eof();
    cout << " fail=" << stream.fail();
    cout << " bad=" << stream.bad() << endl;
}

int main() {
    // === Задание 1: потоковый ввод/вывод Stroka ===
    cout << "=== Задание 1: операторы << и >> для Stroka ===" << endl;
    Stroka s1("hello");
    Stroka s2("world");
    cout << "s1 = " << s1 << ", длина = " << s1.dlina() << endl;
    cout << "s2 = " << s2 << ", длина = " << s2.dlina() << endl;
    cout << endl;

    // === Задание 2: стр. 22 — Money + Sort ===
    cout << "=== Стр. 22: класс Money + шаблон Sort ===" << endl;
    Money mas[] = {
        Money(19, 10),
        Money(99, 99),
        Money(99, 95),
        Money(19, 95)
    };
    int moneySize = sizeof(mas) / sizeof(mas[0]);

    Sort(mas, moneySize);
    for (int i = 0; i < moneySize; i++)
        cout << "  mas[" << i << "] = " << mas[i] << endl;
    cout << endl;

    // === Задание 2: стр. 23 — getmax ===
    cout << "=== Стр. 23: шаблон getmax ===" << endl;
    int i1 = 3, i2 = 5;
    cout << "  max int = " << getmax(i1, i2) << endl;

    int intMas[] = {3, 9, 5, 8};
    cout << "  max int массива = " << getmax(intMas, sizeof(intMas) / sizeof(intMas[0])) << endl;
    cout << endl;

    // === Задание 2: стр. 24 — специализация для строк ===
    cout << "=== Стр. 24: специализация getmax для строк ===" << endl;
    char* str1 = (char*)"строка1";
    char* str2 = (char*)"строка2";
    cout << "  max int = " << getmax(i1, i2) << endl;
    cout << "  max str = " << getmax(str1, str2) << endl;
    cout << endl;

    // === Задание 3: шифратор через потоки ===
    cout << "=== Задание 3: шифратор через потоки ===" << endl;
    // создаём тестовый файл
    ofstream testFile("original.txt");
    testFile << "Секретный текст для шифрования!" << endl;
    testFile.close();

    const char* key = "mykey";
    encryptStream("original.txt", "encrypted.bin", key);
    encryptStream("encrypted.bin", "decrypted.txt", key);

    // проверяем
    cout << "  Расшифровано: ";
    ifstream check("decrypted.txt");
    string line;
    while (getline(check, line)) cout << line;
    check.close();
    cout << endl << endl;

    // === Задание 4: состояние потоков ===
    cout << "=== Задание 4: состояние потоков ===" << endl;

    ifstream f("original.txt");
    showStreamState("  После открытия", f);

    while (getline(f, line)) {}
    showStreamState("  После чтения до конца", f);

    f.clear();  // сбрасываем флаги
    showStreamState("  После clear()", f);
    f.close();

    ifstream bad("несуществующий.txt");
    showStreamState("  Несуществующий файл", bad);
    cout << endl;

    // объяснение:
    // good() = всё нормально, можно читать/писать
    // eof()  = дочитали до конца файла
    // fail() = ошибка (неправильный формат или конец файла)
    // bad()  = серьёзная ошибка (железо сломалось)
    // clear() = сбрасывает все флаги обратно в good

    return 0;
}