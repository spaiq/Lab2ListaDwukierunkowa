#include <iostream>

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

    void wstaw_na_poczatek(const T& dane) {
        glowa = new wezel_listy(dane, glowa); //nowa glowa
        ++dlugosc;
    }

    void wstaw_na_koniec(const T& dane) {
        ogon = new wezel_listy(dane, ogon); //nowy ogon
        ++dlugosc;
    }

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

    template<typename Comp>
    wezel_listy* znajdz_element(const T& el, Comp comp) const
    {
        for (auto p = glowa; p; p = p->nast)
            if (comp(el, p->dane))
                return p;
        return nullptr;
    }

    void podmien(unsigned index, const T& dane) {
        if (index <= dlugosc) {
            wezel_listy* temp = glowa;

            for (auto i = 0; i < index; i++) {
                temp = temp->nast;
            }

            temp.dane = dane;
        }
        else {
            throw std::domain_error("Proba wywolania nieistniejacego elementu.");
        }
    }

    template<typename Comp>
    void usun_element(const T& el, Comp comp) const
    {
        for (auto p = glowa; p; p = p->nast)
            if (comp(el, p->dane)) {
                delete p;
                p = nullptr;
                std::cout << "Element usuniety z powodzeniem\n";
            }
        std::cout << "Nie udalo sie usunac tego elementu\n"
    }
};

struct some_class {
    int some_int;
    bool operator== (const some_class& obj) const {
        return some_int == obj.some_int;
    };
};

int main()
{
    lista_dwukierunkowa<some_class> lista;
    
    lista.wstaw_na_koniec(some_class{ 123 });
    lista.wstaw_na_poczatek(some_class{ 'a ' });

    return 0;
}