#include "stroka.h"
#include <iostream>
using namespace std;

int main() {
    stroka s1("qwert");
    stroka s4(s1);
    stroka s3, s5;

    cout << "=== Ввод строки s3 ===" << endl;
    s3.vvod();

    cout << "s3 = ";
    s3.vyvod();
    cout << endl;

    s5 = s1 + s3 + s4;

    cout << "длина s5 = " << s5.dlina() << endl;
    cout << "s5 = ";
    s5.vyvod();
    cout << endl;

    if (s1 == s5)
        cout << "строки s1 и s5 равны" << endl;
    else
        cout << "строки s1 и s5 не равны" << endl;

    if (s1 == s4)
        cout << "строки s1 и s4 равны" << endl;
    else
        cout << "строки s1 и s4 не равны" << endl;

    cout << endl;
    cout << "=== Задание 4: конструктор с размером ===" << endl;
    stroka s6(500);
    s6 = stroka("test dynamic");
    cout << "s6 = ";
    s6.vyvod();
    cout << ", длина = " << s6.dlina() << endl;

    return 0;
}