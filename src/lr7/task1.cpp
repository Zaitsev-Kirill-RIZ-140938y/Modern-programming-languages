#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

// ===========================================
// ЛР7: наследование и виртуальные функции
// Переводим программу с Паскаля на C++
// Вместо графики BGI используем консольный вывод,
// потому что графические библиотеки Паскаля в CLion не работают
// ===========================================

// ===========================================
// Базовый класс Point (точка)
// от него потом наследуются Krug и Ring
// ===========================================
class Point {
protected:           // protected — доступно в наследниках (а private — нет)
    int x, y;        // координаты точки
    int cvet;        // цвет (просто число)

public:
    // конструктор — задаём координаты и цвет
    Point(int xn, int yn, int color) {
        x = xn;
        y = yn;
        cvet = color;
    }

    // пустой конструктор
    Point() : x(0), y(0), cvet(0) {}

    // виртуальные функции — ключевое слово virtual означает что
    // наследники могут их переопределить, и вызовется ПРАВИЛЬНАЯ версия
    // даже через указатель на базовый класс
    virtual void show() {
        cout << "  [Point] показываем точку (" << x << ", " << y
             << "), цвет=" << cvet << endl;
    }

    virtual void hide() {
        cout << "  [Point] прячем точку (" << x << ", " << y << ")" << endl;
    }

    // возвращает текущие координаты
    void locat(int &xl, int &yl) {
        xl = x;
        yl = y;
    }

    // перемещение — двигаем точку в случайном направлении
    void fly(int cost) {
        int xx, yy;

        // генерируем новую координату X
        // формула из учебника: XX = X + Round((Random-0.5)*Cost)
        do {
            xx = x + (int)((((double)rand() / RAND_MAX) - 0.5) * cost);
        } while (xx <= 0 || xx >= 800);  // чтобы не вылететь за экран

        // генерируем новую координату Y
        do {
            yy = y + (int)((((double)rand() / RAND_MAX) - 0.5) * cost);
        } while (yy <= 0 || yy >= 600);

        hide();      // прячем на старом месте
        x = xx;
        y = yy;
        show();      // показываем на новом
    }
};

// ===========================================
// Класс Krug (круг) — наследник Point
// круг это точка + радиус
// ===========================================
class Krug : public Point {
protected:
    int radius;      // радиус круга

public:
    // конструктор — вызываем конструктор родителя Point и добавляем радиус
    Krug(int xn, int yn, int r, int color) : Point(xn, yn, color) {
        radius = r;
    }

    Krug() : Point(), radius(0) {}

    // переопределяем show — рисуем круг (в консоли просто пишем)
    void show() override {
        cout << "  [Krug] рисуем круг в (" << x << ", " << y
             << "), радиус=" << radius << ", цвет=" << cvet << endl;
    }

    // переопределяем hide — стираем круг
    void hide() override {
        cout << "  [Krug] стираем круг в (" << x << ", " << y
             << "), радиус=" << radius << endl;
    }
};

// ===========================================
// Класс Ring (кольцо) — наследник Krug
// кольцо это круг + ширина кольца
// ===========================================
class Ring : public Krug {
    int width;       // ширина кольца

public:
    // конструктор
    Ring(int xn, int yn, int r, int color, int wid)
        : Krug(xn, yn, r, color) {
        width = wid;
    }

    Ring() : Krug(), width(0) {}

    // переопределяем show — рисуем кольцо
    void show() override {
        cout << "  [Ring] рисуем кольцо в (" << x << ", " << y
             << "), радиус=" << radius << ", ширина=" << width
             << ", цвет=" << cvet << endl;
    }

    // hide не переопределяем — используется от Krug
};

// ===========================================
// Задание 2: дополнительные функции
// сужение-расширение и смена цвета
// ===========================================
class KrugExtended : public Krug {
public:
    KrugExtended(int xn, int yn, int r, int color)
        : Krug(xn, yn, r, color) {}

    // сужение — уменьшаем радиус
    void shrink(int amount) {
        hide();
        if (radius - amount > 0)
            radius -= amount;
        cout << "  [Сужение] новый радиус=" << radius << endl;
        show();
    }

    // расширение — увеличиваем радиус
    void expand(int amount) {
        hide();
        radius += amount;
        cout << "  [Расширение] новый радиус=" << radius << endl;
        show();
    }

    // смена цвета
    void changeColor(int newColor) {
        hide();
        cvet = newColor;
        cout << "  [Смена цвета] новый цвет=" << cvet << endl;
        show();
    }
};

int main() {
    srand(time(nullptr));  // для случайных чисел

    // === Задание 1: основная программа из учебника ===
    cout << "=== Задание 1: наследование и виртуальные функции ===" << endl;
    cout << endl;

    // создаём круг и кольцо (как в Паскале: TestKrug и TestRing)
    Krug testKrug(150, 40, 50, 1);
    Ring testRing(450, 80, 90, 50, 10);

    cout << "--- Показываем объекты ---" << endl;
    testKrug.show();
    testRing.show();
    cout << endl;

    // fly — перемещаем объекты (как в Паскале)
    cout << "--- Перемещаем Krug (fly 100) ---" << endl;
    testKrug.fly(100);
    cout << endl;

    cout << "--- Перемещаем Ring (fly 60) ---" << endl;
    testRing.fly(60);
    cout << endl;

    cout << "--- Ещё раз перемещаем Krug (fly 60) ---" << endl;
    testKrug.fly(60);
    cout << endl;

    // прячем объекты
    cout << "--- Прячем объекты ---" << endl;
    testKrug.hide();
    testRing.hide();
    cout << endl;

    // === Демонстрация виртуальных функций ===
    // главная фишка: через указатель на базовый класс Point
    // вызывается правильная версия show() для каждого объекта
    cout << "=== Демонстрация виртуальных функций ===" << endl;
    Point* objects[3];
    objects[0] = new Point(10, 20, 5);
    objects[1] = new Krug(100, 200, 30, 7);
    objects[2] = new Ring(300, 400, 50, 3, 15);

    // вызываем show() через указатель на Point
    // благодаря virtual вызовется правильная версия для каждого типа
    for (int i = 0; i < 3; i++) {
        objects[i]->show();
    }
    cout << endl;

    // без virtual вызвался бы Point::show() для всех трёх
    // это и есть полиморфизм — один интерфейс, разное поведение

    // освобождаем память
    for (int i = 0; i < 3; i++)
        delete objects[i];

    // === Задание 2: сужение, расширение, смена цвета ===
    cout << "=== Задание 2: сужение/расширение/смена цвета ===" << endl;
    KrugExtended fancy(200, 150, 80, 2);
    fancy.show();
    cout << endl;

    fancy.shrink(20);
    cout << endl;

    fancy.expand(50);
    cout << endl;

    fancy.changeColor(9);
    cout << endl;

    // перемещение с одновременной сменой
    cout << "--- Fly + изменения ---" << endl;
    fancy.fly(80);
    fancy.expand(10);
    fancy.changeColor(4);

    return 0;
}