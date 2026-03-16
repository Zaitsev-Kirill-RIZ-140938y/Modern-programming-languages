#ifndef STROKA_H
#define STROKA_H

#include <iostream>
using namespace std;

class stroka {
    char* str;
    int maxLen;

public:
    stroka(const char*);
    stroka();
    stroka(const stroka&);
    stroka(int size);
    ~stroka();

    stroka& operator=(const stroka&);
    stroka& operator+(const stroka&);
    int operator==(const stroka&);

    int dlina();
    void vvod();
    void vyvod();
};

#endif