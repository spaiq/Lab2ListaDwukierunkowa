/******************************
* @author Bartłomiej Juszczyk
*
******************************/

#include <iostream>
#include <sstream>
#include <time.h>

/*******************************
* Class representing a doubly linked list 
*
********************************/
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
    Node* head;
    Node* tail;
    unsigned length;

public:
    doubly_linked_list() noexcept
        : head(nullptr), tail(nullptr), length(0) {

    }

    ~doubly_linked_list() {
        clear();
    }

    unsigned getLength() const noexcept {
        return length;
    }

    void push(const T& data) {
        if (length == 0) {
            head = new Node(data, tail);
            tail = head;
        }
        else {
            head = new Node(data, head);
            head->next->prev = head;
        }
        
        ++length;
        return;
    }

    void append(const T& data) {

        if (head == nullptr) {
            push(data);
            return;
        }
        
        tail = new Node(data, nullptr, tail);
        tail->prev->next = tail;
        
        ++length;
    }

    void deleteHead() {
        Node* usun = head;

        if (head == nullptr) {
            throw std::domain_error("Cannot delete a non-existing element");
        }

        head = usun->next;

        if (head != nullptr)
            head->prev = nullptr;

        length--;

        delete usun;
        return;
    }

    void deleteTail() {
        Node* usun = tail;

        if (tail == nullptr) {
            throw std::domain_error("Cannot delete a non-existing element");
        }

        tail = usun->prev;

        if (tail != nullptr)
            tail->next = nullptr;
        
        length--;

        delete usun;
        return;
    }


    T& returnValue(unsigned index) {
        if (index < length) {
            Node* temp = head;

            for (unsigned i = 0; i < index; i++) {
                temp = temp->next;
            }

            return temp->data;
        }
        else {
            throw std::domain_error("Cannot return a non-existing element.");
        }
    }


    template<typename Comp>
    Node* findElement(const T& el, Comp comp) const{
        for (auto p = head; p; p = p->next)
            if (comp(el, p->data))
                return p;
        return nullptr;
    }

    void insertAtIndex(unsigned index, const T& data) {
        if (index < length) {
            Node* temp = head;

            for (unsigned i = 0; i < index; i++) {
                temp = temp->next;
            }

            temp->data = data;
        }
        else {
            throw std::domain_error("Cannot insert at a non-existing index.");
        }
    }


    template<typename Comp>
    bool find_and_remove(const T& el, Comp comp){
        Node* p = findElement(el, comp);
        if (p) {
            if (p == head) {
                deleteHead();
            }
            else if (p == tail) {
                deleteTail();
            }
            else {
                if (p->prev) p->prev->next = p->next;
                if (p->next) p->next->prev = p->prev;
                delete p;
                length--;
            }
            // The element was removed successfully
            return true;
        }
        // The element was not removed successfully
        return false;
    }
    
    template<typename Comp>
    void insertByComp(const T& el, Comp comp) {
        if (length == 0 || comp(el, head->data)) {
            push(el);
        }
        else if (comp(tail->data, el)) {
            append(el);
        }
        else {
            for (auto p = head->next; p; p = p->next)
                if (comp(el, p->data)) {
                    Node* newNode = new Node(el, p, p->prev);
                    p->prev->next = newNode;
                    p->prev = newNode;
                    length++;
                    return;
                }
        }
    }

    void clear() {
        Node* temp;

        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
        length = 0;
        return;
    }

    // Function that prints the whole list in a string
    std::string to_string() const{
        if (length == 0)
            return "[]";
        std::ostringstream str;
        str << "[" << head->data;
        for (auto p = head->next; p; p = p->next)
            str << ", " << p->data;
        str << "]";
        return str.str();
    }

    // Function that prints only first and last elements
    // if the list is longer than 12 elements
    std::string border_to_string() const {
        if (length == 0)
            return "[]";
        std::ostringstream str;
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
        return str.str();
    }


};

struct some_class {
    int some_int;
    char some_char;
    bool operator== (const some_class& obj) const {
        return some_int == obj.some_int && some_char == obj.some_char;
    };
};

std::ostream& operator<< (std::ostream& out, const some_class& obj){
    out << obj.some_int;
    out << " " << obj.some_char;
    return out;
}


// Example of usage
int main()
{
    auto compLess = [](const some_class& a, const some_class& b) {
        return a.some_int < b.some_int;
    };

    auto compEq = [](const some_class& a, const some_class& b) {
        return a.some_int == b.some_int;
    };

    //doubly_linked_list<some_class>* list = new doubly_linked_list<some_class>;
    //list->append(some_class{NULL, 'a' });
    //list->push(some_class{ 1 });

    //std::cout << list->returnValue(0) << "\n";

    //std::cout << list->to_string() << "\n";

    //list->insertAtIndex(1, some_class{ NULL , 'c' });
    //std::cout << list->to_string() << "\n";

    //list->insertByComp(some_class{ 100}, compLess); // wstawienie z zachowaniem porządku
    //std::cout << list->to_string() << "\n";

    //list->find_and_remove(some_class{NULL, 'c' }, compEq);
    //std::cout << list->to_string() << "\n";

    //std::cout << list->findElement(some_class{ 100 }, compEq) << "\n";
    //std::cout << list->to_string() << "\n";

    //for (int i = 101; i <= 110; i++)
    //    list->append(some_class{ i });
    //std::cout << list->to_string() << "\n";

    //list->clear();
    //std::cout << list->to_string() << "\n";

    const int MAX_ORDER = 6;
    doubly_linked_list<some_class>* ll = new doubly_linked_list<some_class>();
    srand(time(NULL));
    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = pow(10, o); // rozmiar danych
        int random;
        char randomChar;
        clock_t t1 = clock();
        for (int i = 0; i < n; i++) {
            random = rand() % 10001;
            randomChar = 'a' + rand() % 26;
            some_class so = some_class{ random , randomChar};
            ll->append(so);
        }
        clock_t t2 = clock();
        
        double mstimediff = 1000 * (t2 - t1) / (double)CLOCKS_PER_SEC;
        std::cout << ll->border_to_string() << "\nPomiar 1, rzedu " << o << "\nCzas calkowity: " << mstimediff << "ms\nCzas w przeliczeniu na jedna operacje: " << mstimediff/n << "ms\n\n";

        const int m = pow(10, 4);
        t1 = clock();
        for (int i = 0; i < m; i++) {
            random = rand() % 10001;
            randomChar = 'a' + rand() % 26;
            some_class so = some_class{ random , randomChar};
            ll->find_and_remove(so, compEq);
            so = some_class{NULL};
        }

        t2 = clock();
        mstimediff = 1000 * (t2 - t1) / (double)CLOCKS_PER_SEC;
        std::cout << ll->border_to_string() << "\nPomiar 2, rzedu " << o << "\nCzas calkowity: " << mstimediff << "ms\nCzas w przeliczeniu na jedna operacje: " << mstimediff / n << "ms\n\n";

        ll->clear();
    }

    delete ll;
    return 0;
}
