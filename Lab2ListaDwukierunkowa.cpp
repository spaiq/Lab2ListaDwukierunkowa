#include <iostream>
#include <sstream>

template<typename T>
class lista_dwukierunkowa {
public:
    struct wezel_listy {
        T dane;
        wezel_listy* nast;
        wezel_listy* pop;

        wezel_listy(const T& dane, wezel_listy* nast = nullptr, wezel_listy* pop = nullptr)
            : dane(dane), nast(nast), pop(pop) {

        }

        wezel_listy(T&& dane, wezel_listy* nast = nullptr, wezel_listy* pop = nullptr)
            : dane(dane), nast(nast), pop(pop) {
        }

        ~wezel_listy() {
            if (nast) {
                delete nast;
                nast = nullptr;
            }
            
            if (pop) {
                delete pop;
                pop = nullptr;
            }
        }
    };

private:
    wezel_listy* glowa;
    wezel_listy* ogon;
    unsigned dlugosc;

public:
    lista_dwukierunkowa() noexcept
        : glowa(nullptr), ogon(nullptr), dlugosc(0) {

    }

    ~lista_dwukierunkowa() {
        if (glowa) {
            delete glowa;
            glowa = nullptr;
            dlugosc = 0;
        }
        
        if (ogon) {
            delete ogon;
            ogon = nullptr;
            dlugosc = 0;
        }
    }

    unsigned pobierz_dlugosc() const noexcept {
        return dlugosc;
    }

    //b)
    void wstaw_na_poczatek(const T& dane) {
        glowa = new wezel_listy(dane, glowa); //nowa glowa
        ++dlugosc;
    }

    // a)
    void wstaw_na_koniec(const T& dane) {

        if (glowa == nullptr) {
            wstaw_na_poczatek(dane);
            return;
        }

        ogon = new wezel_listy(dane); //nowy ogon
        wezel_listy* temp = glowa;

        while (temp->nast != nullptr) {
            temp = temp->nast;
        }
        //temp->nast->pop = temp->nast;
        temp->nast = ogon;
        ogon->pop = temp;
        ++dlugosc;
    }

    // d)
    void usun_glowe() {
        wezel_listy* usun = glowa;

        if (glowa == nullptr ) {
            throw std::domain_error("Proba usuniecia nieistniejacego elementu");
        }

        if (dlugosc == 1) {
            delete ogon;
            ogon = nullptr;
        }
        
        glowa = usun->nast;

        if (usun->nast != nullptr) {
            usun->nast->pop = usun->pop;
        }

        delete usun;
        usun = nullptr;

        dlugosc--;
    }
    // c)
    void usun_ogon() {
        wezel_listy* usun = ogon;

        if (ogon == nullptr) {
            throw std::domain_error("Proba usuniecia nieistniejacego elementu");
        }

        if (dlugosc == 1){
            delete glowa;
            glowa = nullptr;
        }

        ogon = usun->pop;

        if (usun->pop != nullptr) {
            usun->pop->nast = usun->nast;
        }

        delete usun;
        usun = nullptr;
        
        dlugosc--;
    }

    // e)
    T zwroc_wartosc(unsigned index) {
        if (index <= dlugosc) {
            wezel_listy* temp = glowa;

            for (auto i = 0; i < index; i++) {
                temp = temp->nast;
            }

            return temp->dane;
        }
        else {
            throw std::domain_error("Proba wywolania nieistniejacego elementu.");
        }
    }

    // g)
    template<typename Comp>
    wezel_listy* znajdz_element(const T& el, Comp comp) const
    {
        for (auto p = glowa; p; p = p->nast)
            if (comp(el, p->dane))
                return p;
        return nullptr;
    }

    // f)
    void podmien(unsigned index, const T& dane) {
        if (index <= dlugosc) {
            wezel_listy* temp = glowa;

            for (auto i = 0; i < index; i++) {
                temp = temp->nast;
            }

            temp->dane = dane;
        }
        else {
            throw std::domain_error("Proba wywolania nieistniejacego elementu.");
        }
    }


    // h)
    template<typename Comp>
    void usun_element(const T& el, Comp comp) const{
        bool flag = false;
        for (auto p = glowa; p; p = p->nast)
            if (comp(el, p->dane)){
                delete p;
                p = nullptr;
                flag = true;
                std::cout << "Element usuniety z powodzeniem\n";
            }
        if (flag == false)
            std::cout << "Nie udalo sie usunac tego elementu\n";
    }

    // i)
    template<typename Comp>
    void wstaw_porzadek(const T& el, Comp comp) const {
        bool flag = false;
        for (auto p = glowa; p; p = p->nast)
            if (comp(el, p->dane)){
                p = new wezel_listy(el, p);
                flag = true;
                std::cout << "Element dodany z powodzeniem\n";
                break;
            }
        if (flag == false)
            std::cout << "Nie udalo sie dodac tego elementu\n";
    }

    // k)
    std::string to_string() const
    {
        if (dlugosc == 0)
            return "[]";
        std::ostringstream str; // pamiętaj o #include <sstream>
        str << "[" << glowa->dane;
        for (auto p = glowa->nast; p; p = p->nast)
            str << ", " << p->dane;
        str << "]";
        return str.str(); // wydobycie napisu ze strumienia
    }


};


struct some_class {
    int some_int;
    bool operator== (const some_class& obj) const {
        return some_int == obj.some_int;
    };

};

std::ostream& operator<< (std::ostream& out, const some_class& obj)
{
    out << obj.some_int;
    return out;
}

int main()
{
    lista_dwukierunkowa<some_class> lista;
    
    lista.wstaw_na_koniec(some_class{123});
    lista.wstaw_na_poczatek(some_class{ 'a' });
    std::cout << lista.zwroc_wartosc(0) << "\n";
    std::cout << lista.to_string() << "\n";
    lista.podmien(1, some_class{ 1234 });
    std::cout << lista.to_string() << "\n";


    return 0;
}