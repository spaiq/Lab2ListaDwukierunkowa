#include <iostream>
#include <sstream>
#include <time.h>

template<typename T>
class doubly_linked_list {
public:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(const T& data, Node* next = nullptr, Node* prev = nullptr)
            : data(data), next(next), prev(prev) {

        }

        Node(T&& data, Node* next = nullptr, Node* prev = nullptr)
            : data(data), next(next), prev(prev) {
        }

        ~Node() {
            next = nullptr;
            prev = nullptr;
        }
    };

private:
    Node* head = new Node();
    Node* tail = new Node();
    unsigned length;

public:
    doubly_linked_list() noexcept
        : head(nullptr), tail(nullptr), length(0) {

    }

    ~doubly_linked_list() {
        if (head) {
            delete(head);
        }
        if (tail) {
            delete(tail);
        }
        length = 0;
    }

    unsigned getLength() const noexcept {
        return length;
    }

    // b)
    void push(const T& data) {
        if (length == 0) {
            head = new Node(data, tail);
            tail = new Node(data, nullptr, head);
        }
        else if (length == 1) {
            head = new Node(data, tail);
            tail->prev = head;
        }
        
        head = new Node(data, head);
        head->next->prev = head;
        
        ++length;
    }

    // a)
    void append(const T& data) {

        if (head == nullptr) {
            push(data);
            return;
        }

        Node* temp = tail;
        if (length == 1) {
            tail = new Node(data, nullptr, head);
            head->next = tail;

            ++length;
            return;
        }
        
        tail = new Node(data, nullptr, tail);
        tail->prev->next = tail;
        
        ++length;
    }

    // d)
    void deleteHead() {
        Node* usun = head;

        if (head == nullptr) {
            throw std::domain_error("Proba usuniecia nieistniejacego elementu");
        }

        head = usun->next;

        if (usun->next != nullptr)
            usun->next->prev = usun->prev;

        length--;

        usun = nullptr;
        return;
    }
    // c)
    void deleteTail() {
        Node* usun = tail;

        if (tail == nullptr) {
            throw std::domain_error("Proba usuniecia nieistniejacego elementu");
        }

        tail = usun->prev;

        if (usun->prev != nullptr)
            usun->prev->next = usun->next;
        
        length--;

        usun = nullptr;
        return;
    }

    // e)
    T returnValue(unsigned index) {
        if (index < length) {
            Node* temp = head;

            for (unsigned i = 0; i < index; i++) {
                temp = temp->next;
            }

            return temp->data;
        }
        else {
            throw std::domain_error("Proba wywolania nieistniejacego elementu.");
        }
    }

    // g)
    template<typename Comp>
    Node* findElement(const T& el, Comp comp) const{
        for (auto p = head; p; p = p->next)
            if (comp(el, p->data))
                return p;
        return nullptr;
    }

    // f)
    void insertAtIndex(unsigned index, const T& data) {
        if (index <= length) {
            Node* temp = head;

            for (unsigned i = 0; i < index; i++) {
                temp = temp->next;
            }

            temp->data = data;
        }
        else {
            throw std::domain_error("Proba wywolania nieistniejacego elementu.");
        }
    }


    // h)
    template<typename Comp>
    void find_and_remove(const T& el, Comp comp){
        for (auto p = head; p; p = p->next)
            if (comp(el, p->data)) {
                if (p == head){
                    deleteHead();
                }
                else if (p == tail) {
                    deleteTail();
                }
                else {
                    if (p->prev) p->prev->next = p->next;
                    if (p->next) p->next->prev = p->prev;
                    p = nullptr;
                    length--;
                }
                //std::cout << "Element usuniety z powodzeniem\n";
                return;
            }
        //std::cout << "Nie udalo sie usunac tego elementu\n";
        return;
    }

    // i)
    template<typename Comp>
    void insertByComp(const T& el, Comp comp) {
        if (length == 0) {
            push(el);
            //std::cout << "Element dodany z powodzeniem\n";
        }
        for (auto p = head; p; p = p->next)
            if (comp(el, p->data)){
                if (p == head) {
                    push(el);
                }
                else {
                    Node* nowyWezel = new Node(el, p, p->prev);
                    p->prev->next = nowyWezel;
                    p->prev = nowyWezel;
                    length++;
                }
                //std::cout << "Element dodany z powodzeniem\n";
                return;
            }
        append(el);
        //std::cout << "Element dodany z powodzeniem\n";
    }

    // j)
    void clear() {
        Node* temp;

        while (head != nullptr) {
            temp = head;
            head = head->next;
            temp = nullptr;
        }
        length = 0;
        return;
    }

    // k)
    std::string to_string() const{
        if (length == 0)
            return "[]";
        std::ostringstream str; // pamiętaj o #include <sstream>
        str << "[" << head->data;
        for (auto p = head->next; p; p = p->next)
            str << ", " << p->data;
        str << "]";
        return str.str(); // wydobycie napisu ze strumienia
    }

    std::string border_to_string() const {
        if (length == 0)
            return "[]";
        std::ostringstream str; // pamiętaj o #include <sstream>
        str << "[" << head->data;
        if (length <= 12)
            for (auto p = head->next; p; p = p->next)
                str << ", " << p->data;
        else {
            auto p = head->next;
            for (int i = 0; i <= 5; i++) {
                str << ", " << p->data;
                p = p->next;
            }
            str << ", ...";
            p = tail;
            for (int i = 0; i <= 5; i++) {
                p = p->prev;
            }

            for (int i = 0; i <= 5; i++) {
                str << ", " << p->data;
                p = p->next;
            }
        }
        str << "] dlugosc: " << length;
        return str.str(); // wydobycie napisu ze strumienia
    }


};

struct some_class {
    int some_int;
    bool operator== (const some_class& obj) const {
        return some_int == obj.some_int;
    };
};

std::ostream& operator<< (std::ostream& out, const some_class& obj){
    out << obj.some_int;
    return out;
}

int main()
{
    auto kompLess = [](const some_class& a, const some_class& b) {
        return a.some_int < b.some_int;
    };

    auto kompEq = [](const some_class& a, const some_class& b) {
        return a.some_int == b.some_int;
    };

    doubly_linked_list<some_class>* list = new doubly_linked_list<some_class>;
    list->append(some_class{123});
    list->push(some_class{'a'});

    std::cout << list->returnValue(0) << "\n";

    std::cout << list->to_string() << "\n";

    list->insertAtIndex(1, some_class{ 1234 });
    std::cout << list->to_string() << "\n";

    list->insertByComp(some_class{ 100 }, kompLess); // wstawienie z zachowaniem porządku
    std::cout << list->to_string() << "\n";

    list->find_and_remove(some_class{ 1234 }, kompEq);
    std::cout << list->to_string() << "\n";

    std::cout << list->findElement(some_class{ 100 }, kompEq) << "\n";
    std::cout << list->to_string() << "\n";

    for (int i = 101; i <= 110; i++)
        list->append(some_class{ i });
    std::cout << list->to_string() << "\n";

    list->clear();
    std::cout << list->to_string() << "\n";

    //const int MAX_ORDER = 6;
    //doubly_linked_list<some_class>* ll = new doubly_linked_list<some_class>();
    //for (int o = 1; o <= MAX_ORDER; o++) {
    //    const int n = pow(10, o); // rozmiar danych
    //    srand(time(NULL));

    //    clock_t t1 = clock();
    //    for (int i = 0; i < n; i++) {
    //        int random = rand() % 10001;
    //        some_class so = some_class{ random };
    //        ll->append(so);
    //    }
    //    clock_t t2 = clock();
    //    
    //    double mstimediff = 1000 * (t2 - t1) / (double)CLOCKS_PER_SEC;
    //    std::cout << ll->border_to_string() << "\nPomiar 1, rzedu " << o << "\nCzas calkowity: " << mstimediff << "ms\nCzas w przeliczeniu na jedna operacje: " << mstimediff/n << "ms\n\n";

    //    const int m = pow(10, 4);
    //    
    //    t1 = clock();
    //    for (int i = 0; i < m; i++) {
    //        int random = rand() % 10001;
    //        some_class so = some_class{ random };
    //        ll->find_and_remove(so, kompEq);
    //        so = some_class{NULL};
    //    }

    //    t2 = clock();
    //    mstimediff = 1000 * (t2 - t1) / (double)CLOCKS_PER_SEC;
    //    std::cout << ll->border_to_string() << "\nPomiar 2, rzedu " << o << "\nCzas calkowity: " << mstimediff << "ms\nCzas w przeliczeniu na jedna operacje: " << mstimediff / n << "ms\n\n";

    //    ll->clear();
    //}

    //delete ll;
    return 0;
}
