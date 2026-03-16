#include <iostream>
#include <fstream>   // для работы с файлами (ifstream, ofstream)
#include <cstring>
#include <cstdio>    // для FILE, fopen, fclose, fgetc и тд
using namespace std;

// ===========================================
// Задание 1: выводим содержимое файла на экран
// просто читаем файл посимвольно и выводим
// ===========================================
void task1_printFile(const char* filename) {
    // открываем файл для чтения
    FILE* in;
    in = fopen(filename, "r");
    if (in == NULL) {
        printf("Файл %s не открыт\n", filename);
        return;
    }
    // читаем по одному символу пока не конец файла
    char ch;
    while (!feof(in)) {
        ch = fgetc(in);
        if (!feof(in))       // проверяем ещё раз, а то последний символ дублируется
            putchar(ch);     // выводим символ на экран
    }
    fclose(in);  // закрываем файл, не забываем
    cout << endl;
}

// ===========================================
// Задание 2: считаем "пустые" и "непустые" символы
// пустые — это пробел, табуляция, перенос строки и тд
// непустые — все остальные (буквы, цифры, знаки)
// ===========================================
void task2_countChars(const char* filename) {
    FILE* in = fopen(filename, "r");
    if (in == NULL) {
        printf("Файл %s не открыт\n", filename);
        return;
    }

    int empty = 0, notempty = 0;
    char ch;
    while ((ch = fgetc(in)) != EOF) {
        // пустые символы: пробел, таб, перенос строки, возврат каретки
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
            empty++;
        else
            notempty++;
    }

    cout << "Пустых символов: " << empty << endl;
    cout << "Непустых символов: " << notempty << endl;
    fclose(in);
}

// ===========================================
// Задание 3: ищем подстроку в файле
// читаем файл построчно, в каждой строке ищем нужное слово
// результат пишем в отдельный файл
// ===========================================
void task3_findSubstring(const char* filename, const char* substr) {
    ifstream in(filename);
    if (!in.is_open()) {
        cout << "Файл " << filename << " не открыт" << endl;
        return;
    }

    ofstream out("search_result.txt");  // результат в отдельный файл
    char line[1024];
    int lineNum = 0;
    int found = 0;

    while (in.getline(line, 1024)) {
        lineNum++;
        // strstr ищет подстроку в строке, если нашла — вернёт указатель, если нет — NULL
        if (strstr(line, substr) != NULL) {
            cout << "Строка " << lineNum << ": " << line << endl;
            out << "Строка " << lineNum << ": " << line << endl;
            found++;
        }
    }

    if (found == 0)
        cout << "Подстрока \"" << substr << "\" не найдена" << endl;
    else
        cout << "Найдено совпадений: " << found << endl;

    in.close();
    out.close();
    cout << "Результат сохранён в search_result.txt" << endl;
}

// ===========================================
// Задание 4: обработка номеров страниц
// в исходном тексте номера страниц стоят в начале строки
// типа "- 34 -" а нужно перенести число в конец предыдущей строки
// и убрать дефисы. признак новой страницы — символ '\f'
//
// читаем файл построчно, если строка начинается с "- "
// значит это номер страницы — достаём число и дописываем
// к предыдущей строке
// ===========================================
void task4_pageNumbers(const char* filename) {
    ifstream in(filename);
    if (!in.is_open()) {
        cout << "Файл " << filename << " не открыт" << endl;
        return;
    }

    ofstream out("pages_result.txt");
    char line[1024];
    char prevLine[1024] = "";  // предыдущая строка
    bool hasPrev = false;

    while (in.getline(line, 1024)) {
        // проверяем: если строка начинается с "- " — это номер страницы
        if (line[0] == '-' && line[1] == ' ') {
            // достаём номер — он между дефисами: "- 34 -"
            // ищем число в строке
            int pageNum = 0;
            int i = 2; // пропускаем "- "
            while (line[i] >= '0' && line[i] <= '9') {
                pageNum = pageNum * 10 + (line[i] - '0');
                i++;
            }
            // дописываем номер к предыдущей строке
            if (hasPrev) {
                out << prevLine << " " << pageNum << endl;
                hasPrev = false;
            }
        } else {
            // обычная строка — выводим предыдущую и запоминаем текущую
            if (hasPrev)
                out << prevLine << endl;
            strcpy(prevLine, line);
            hasPrev = true;
        }
    }
    // не забываем последнюю строку
    if (hasPrev)
        out << prevLine << endl;

    in.close();
    out.close();
    cout << "Результат сохранён в pages_result.txt" << endl;
}

// ===========================================
// Задание 5: шифратор XOR
// берём каждый символ из файла и XOR-им его с символом ключа
// формула: зашифрованный = символ ^ ключ[i]
// XOR классная штука — если зашифровать два раза тем же ключом,
// получишь обратно исходный текст
// ===========================================
void task5_encrypt(const char* inputFile, const char* outputFile, const char* key) {
    FILE* in = fopen(inputFile, "rb");   // rb — читаем как бинарный файл
    if (in == NULL) {
        printf("Файл %s не открыт\n", inputFile);
        return;
    }

    FILE* out = fopen(outputFile, "wb");  // wb — пишем как бинарный
    if (out == NULL) {
        printf("Не могу создать файл %s\n", outputFile);
        fclose(in);
        return;
    }

    int keyLen = strlen(key);
    int keyIndex = 0;  // текущая позиция в ключе
    int ch;

    // читаем по символу, XOR-им с ключом, пишем в выходной файл
    while ((ch = fgetc(in)) != EOF) {
        char encrypted = ch ^ key[keyIndex];  // вот сам XOR
        fputc(encrypted, out);
        keyIndex++;
        // если ключ кончился — начинаем сначала (циклически)
        if (keyIndex >= keyLen) keyIndex = 0;
    }

    fclose(in);
    fclose(out);
    cout << "Файл зашифрован: " << inputFile << " -> " << outputFile << endl;
}

// ===========================================
// Задание 6: имя файла и ключ из командной строки
// по сути то же самое что задание 5, но имя файла
// и ключ не захардкожены, а берутся из аргументов main
// (argc, argv) — см. main ниже
// ===========================================

int main(int argc, char* argv[]) {
    // === Создаём тестовый файл чтобы было на чём проверять ===
    ofstream testFile("test.txt");
    testFile << "Hello World!" << endl;
    testFile << "This is a test file." << endl;
    testFile << "It has multiple lines." << endl;
    testFile << "Hello again!" << endl;
    testFile << "The end." << endl;
    testFile.close();

    // --- Задание 1 ---
    cout << "=== Задание 1: вывод файла ===" << endl;
    task1_printFile("test.txt");
    cout << endl;

    // --- Задание 2 ---
    cout << "=== Задание 2: подсчёт символов ===" << endl;
    task2_countChars("test.txt");
    cout << endl;

    // --- Задание 3 ---
    cout << "=== Задание 3: поиск подстроки ===" << endl;
    task3_findSubstring("test.txt", "Hello");
    cout << endl;

    // --- Задание 4 ---
    // создаём тестовый файл с номерами страниц
    ofstream pageFile("pages_test.txt");
    pageFile << "Первая строка текста" << endl;
    pageFile << "- 34 -" << endl;
    pageFile << "Вторая строка текста" << endl;
    pageFile << "Третья строка" << endl;
    pageFile << "- 35 -" << endl;
    pageFile << "Четвёртая строка" << endl;
    pageFile.close();

    cout << "=== Задание 4: номера страниц ===" << endl;
    task4_pageNumbers("pages_test.txt");
    cout << endl;

    // --- Задание 5 ---
    cout << "=== Задание 5: шифратор XOR ===" << endl;
    const char* key = "secretkey";

    // шифруем
    task5_encrypt("test.txt", "encrypted.txt", key);

    // расшифровываем (тот же XOR с тем же ключом)
    task5_encrypt("encrypted.txt", "decrypted.txt", key);

    // проверяем что расшифрованный файл совпадает с исходным
    cout << "Расшифрованный файл:" << endl;
    task1_printFile("decrypted.txt");
    cout << endl;

    // --- Задание 6 ---
    // если запустить программу с аргументами из командной строки:
    //   ./lr5 test.txt mykey
    // то argc=3, argv[0]="./lr5", argv[1]="test.txt", argv[2]="mykey"
    cout << "=== Задание 6: аргументы командной строки ===" << endl;
    if (argc >= 3) {
        // argv[1] — имя файла, argv[2] — ключ
        cout << "Файл: " << argv[1] << ", ключ: " << argv[2] << endl;
        task5_encrypt(argv[1], "cmd_encrypted.txt", argv[2]);
        task5_encrypt("cmd_encrypted.txt", "cmd_decrypted.txt", argv[2]);
        cout << "Проверка:" << endl;
        task1_printFile("cmd_decrypted.txt");
    } else {
        cout << "Для задания 6 запустите с аргументами:" << endl;
        cout << "  ./lr5 имя_файла ключ" << endl;
        cout << "Например: ./lr5 test.txt secretkey" << endl;
    }

    return 0;
}