#include <iostream>
#include <cstring>
using namespace std;

// ===========================================
// ЛР10: связные списки
// ===========================================

// ===========================================
// Задание 1: односвязный список
// В отличие от двусвязного — у каждого узла только next,
// нет prev. Проще, но назад ходить нельзя.
// ===========================================

struct Node {
    int d;          // данные (число)
    Node* next;     // указатель на следующий элемент
};

// создание первого элемента списка
Node* first(int d) {
    Node* pv = new Node;
    pv->d = d;
    pv->next = 0;   // следующего нет — это единственный элемент
    return pv;
}

// добавление элемента в конец списка
// pend — указатель на последний элемент (передаём по ссылке)
void add(Node** pend, int d) {
    Node* pv = new Node;
    pv->d = d;
    pv->next = 0;          // новый элемент — последний
    (*pend)->next = pv;     // старый последний теперь указывает на новый
    *pend = pv;             // обновляем указатель на конец
}

// поиск элемента по ключу
Node* find(Node* const pbeg, int d) {
    Node* pv = pbeg;
    while (pv) {
        if (pv->d == d) return pv;  // нашли!
        pv = pv->next;
    }
    return 0;  // не нашли
}

// удаление элемента по ключу (для односвязного списка)
// нужен предыдущий элемент, поэтому ищем его
int remove(Node** pbeg, Node** pend, int key) {
    // ищем элемент и его предшественника
    Node* prev = 0;
    Node* curr = *pbeg;
    while (curr) {
        if (curr->d == key) break;
        prev = curr;
        curr = curr->next;
    }
    if (!curr) return 0;  // не нашли

    if (curr == *pbeg) {
        // удаляем первый элемент
        *pbeg = curr->next;
    } else if (curr == *pend) {
        // удаляем последний
        *pend = prev;
        prev->next = 0;
    } else {
        // удаляем из середины
        prev->next = curr->next;
    }
    delete curr;
    return 1;
}

// вставка элемента после элемента с ключом key
void insert(Node* const pbeg, Node** pend, int key, int d) {
    Node* pkey = find(pbeg, key);
    if (!pkey) return;

    Node* pv = new Node;
    pv->d = d;
    pv->next = pkey->next;  // новый указывает на следующий за key
    pkey->next = pv;         // key теперь указывает на новый

    // если вставили после последнего — обновляем pend
    if (pkey == *pend)
        *pend = pv;
}

// вывод списка
void printList(Node* pbeg) {
    Node* pv = pbeg;
    while (pv) {
        cout << pv->d << " ";
        pv = pv->next;
    }
    cout << endl;
}

// очистка списка (освобождаем память)
void clearList(Node** pbeg) {
    while (*pbeg) {
        Node* tmp = *pbeg;
        *pbeg = (*pbeg)->next;
        delete tmp;
    }
}

// ===========================================
// Задание 2: шаблон класса «односвязный список»
// теперь то же самое но через шаблон — работает с любым типом
// ===========================================
template <class T>
class LinkedList {
    struct ListNode {
        T data;
        ListNode* next;
    };
    ListNode* head;  // начало списка
    ListNode* tail;  // конец списка

public:
    LinkedList() : head(0), tail(0) {}

    ~LinkedList() {
        while (head) {
            ListNode* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    // добавить в конец
    void add(T data) {
        ListNode* pv = new ListNode;
        pv->data = data;
        pv->next = 0;
        if (!head) {
            head = tail = pv;  // первый элемент
        } else {
            tail->next = pv;
            tail = pv;
        }
    }

    // найти по значению
    ListNode* find(T data) {
        ListNode* pv = head;
        while (pv) {
            if (pv->data == data) return pv;
            pv = pv->next;
        }
        return 0;
    }

    // удалить по значению
    bool remove(T data) {
        ListNode* prev = 0;
        ListNode* curr = head;
        while (curr) {
            if (curr->data == data) {
                if (curr == head) head = curr->next;
                else prev->next = curr->next;
                if (curr == tail) tail = prev;
                delete curr;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        return false;
    }

    // вывести все элементы
    void print() {
        ListNode* pv = head;
        while (pv) {
            cout << pv->data << " ";
            pv = pv->next;
        }
        cout << endl;
    }

    bool isEmpty() { return head == 0; }
};

// ===========================================
// Задание 3: Автобусный парк
// Два списка: парк (автобусы стоят) и маршрут (на линии)
// Можно выезжать из парка на маршрут и возвращаться обратно
// ===========================================

struct Bus {
    int number;          // номер автобуса
    char driver[50];     // фамилия водителя
    int route;           // номер маршрута

    // оператор == нужен для поиска и удаления в шаблоне списка
    bool operator==(const Bus& other) const {
        return number == other.number;
    }

    // оператор << для вывода
    friend ostream& operator<<(ostream& os, const Bus& b) {
        os << "[#" << b.number << " " << b.driver << " марш." << b.route << "]";
        return os;
    }
};

// создаём автобус
Bus makeBus(int num, const char* driver, int route) {
    Bus b;
    b.number = num;
    strcpy(b.driver, driver);
    b.route = route;
    return b;
}

int main() {
    // === Задание 1: односвязный список (как в учебнике) ===
    cout << "=== Задание 1: односвязный список ===" << endl;

    // формируем список: 1, 2, 3, 4, 5
    Node* pbeg = first(1);
    Node* pend = pbeg;
    for (int i = 2; i <= 5; i++) add(&pend, i);

    cout << "  Список: ";
    printList(pbeg);

    // вставка 200 после элемента 2
    insert(pbeg, &pend, 2, 200);
    cout << "  После вставки 200 после 2: ";
    printList(pbeg);

    // удаление элемента 5
    remove(&pbeg, &pend, 5);
    cout << "  После удаления 5: ";
    printList(pbeg);

    clearList(&pbeg);
    cout << endl;

    // === Задание 2: шаблон списка ===
    cout << "=== Задание 2: шаблон LinkedList ===" << endl;

    // список int
    LinkedList<int> intList;
    intList.add(10);
    intList.add(20);
    intList.add(30);
    cout << "  int список: ";
    intList.print();

    intList.remove(20);
    cout << "  После удаления 20: ";
    intList.print();

    // список double — тот же шаблон, другой тип
    LinkedList<double> dblList;
    dblList.add(3.14);
    dblList.add(2.71);
    cout << "  double список: ";
    dblList.print();
    cout << endl;

    // === Задание 3: Автобусный парк ===
    cout << "=== Задание 3: Автобусный парк ===" << endl;

    LinkedList<Bus> park;     // автобусы в парке
    LinkedList<Bus> route;    // автобусы на маршруте

    // заполняем парк
    park.add(makeBus(101, "Иванов", 5));
    park.add(makeBus(102, "Петров", 7));
    park.add(makeBus(103, "Сидоров", 5));
    park.add(makeBus(104, "Козлов", 3));

    cout << "  В парке: ";
    park.print();

    // автобус 101 выезжает на маршрут
    Bus bus101 = makeBus(101, "Иванов", 5);
    park.remove(bus101);
    route.add(bus101);
    cout << "  Автобус 101 выехал на маршрут" << endl;

    // автобус 103 тоже выезжает
    Bus bus103 = makeBus(103, "Сидоров", 5);
    park.remove(bus103);
    route.add(bus103);
    cout << "  Автобус 103 выехал на маршрут" << endl;

    cout << "  В парке: ";
    park.print();
    cout << "  На маршруте: ";
    route.print();

    // автобус 101 возвращается в парк
    route.remove(bus101);
    park.add(bus101);
    cout << "  Автобус 101 вернулся в парк" << endl;

    cout << "  В парке: ";
    park.print();
    cout << "  На маршруте: ";
    route.print();

    return 0;
}