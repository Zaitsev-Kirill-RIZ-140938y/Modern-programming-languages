#include "stroka.h"
#include <iostream>
using namespace std;

// === свои функции вместо библиотечных (задание 3) ===

// своя strlen
int myStrlen(const char* s) {
    int len = 0;
    while (s[len] != '\0') len++;
    return len;
}

// своя strcpy
void myStrcpy(char* dst, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
}

// своя strcmp
int myStrcmp(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
        i++;
    return s1[i] - s2[i];
}

// своя strcat
void myStrcat(char* dst, const char* src) {
    int i = 0;
    while (dst[i] != '\0') i++;
    int j = 0;
    while (src[j] != '\0') {
        dst[i] = src[j];
        i++;
        j++;
    }
    dst[i] = '\0';
}

// === конструкторы ===

// из строки
stroka::stroka(const char* string) {
    maxLen = myStrlen(string) + 1;
    str = new char[maxLen];
    myStrcpy(str, string);
}

// пустой
stroka::stroka() {
    maxLen = 256;
    str = new char[maxLen];
    str[0] = '\0';
}

// копирования
stroka::stroka(const stroka& s) {
    maxLen = s.maxLen;
    str = new char[maxLen];
    myStrcpy(str, s.str);
}

// с заданным размером (задание 4)
stroka::stroka(int size) {
    maxLen = size;
    str = new char[maxLen];
    str[0] = '\0';
}

// деструктор — освобождаем память
stroka::~stroka() {
    delete[] str;
}

// === операторы ===

// присваивание
stroka& stroka::operator=(const stroka& s) {
    if (this == &s) return *this;
    delete[] str;
    maxLen = s.maxLen;
    str = new char[maxLen];
    myStrcpy(str, s.str);
    return *this;
}

// сцепление
stroka& stroka::operator+(const stroka& s) {
    int newLen = myStrlen(str) + myStrlen(s.str) + 1;
    if (newLen > maxLen) {
        char* temp = new char[newLen];
        myStrcpy(temp, str);
        delete[] str;
        str = temp;
        maxLen = newLen;
    }
    myStrcat(str, s.str);
    return *this;
}

// сравнение
int stroka::operator==(const stroka& s) {
    if (myStrcmp(str, s.str) == 0)
        return 1;
    else
        return 0;
}

// === методы ===

int stroka::dlina() {
    return myStrlen(str);
}

void stroka::vvod() {
    cout << "Введите строку: ";
    cin.getline(str, maxLen);
}

void stroka::vyvod() {
    cout << str;
}