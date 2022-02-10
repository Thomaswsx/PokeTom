#ifndef STWORZENIE_H
#define STWORZENIE_H

#include <vector>
#include <cstdio>     // fprintf

/**
 * @brief The Stworzenie class
 */
class Stworzenie {
public:

    enum class STAN {
        PRZYTOMNY,
        ZEMDLAL
    };

    Stworzenie() = default;
    virtual ~Stworzenie() {};

    /**
     * @brief Funkcja zwracajaca nazwę danego storka
     * Całkowicie firtualna przez co cała klasa Stworzenie staje się abstrakcyjna
     * @return Zwraca c-string z nazwą stworzenia
     */
    virtual const char* pobierzNazwe() const =0;

    /**
     * @brief Podstawowa implementacja ataku
     * @param stworek Stwprzenie któremu zadamy obrażenia
     */
    virtual unsigned atak(Stworzenie* stworek) {
        stworek->przyjmijObrazenia(sila);
        if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
            exp += wzrost_exp;
        return sila;
    }

    /**
     * @brief Funkcja realizująca pomniejszanie życia o określoną ilość punktów - otrzymanie obrażeń
     * @param obrazenia ilość otrzymanych obrażeń
     */
    void przyjmijObrazenia(unsigned obrazenia) {
        if( obrazenia >= zycie ) {
            zycie = 0;
            stan = STAN::ZEMDLAL;
        } else {
            zycie -= obrazenia;
        }
    }

    /**
     * @brief Funkcja realizuje regenerację życia Stworzenia
     * @param p Ilość odzyskanych punktów życia
     */
    void regeneracja(unsigned p) {
        zycie += p;
        if(zycie > max_zycie)
            zycie = max_zycie;
        stan = STAN::PRZYTOMNY;
    }

    /**
     * @brief Wyświetlenie opisu Stworzenia
     */
    void drukuj() const {
        // Formatowanie:
        printf("%-15.15s Atrybuty[ siła:%3u zręczność:%3u życie:%4u] Doświadczenie[%4u]\n", pobierzNazwe(), sila, zrecznosc, zycie, exp);
    }

    STAN pobierzStan() {
        return stan;
    }

    unsigned pobierzZycie() {
        return zycie;
    }

    unsigned pobierzZrecznosc() {
        return zrecznosc;
    }

    /**
     * @brief Obsługa ewolucji Stworzenia
     * @return true jeśli ewolucja jest możliwa, false jeśli nie możemy jeszcze ewoluować
     */
    bool ewolucja();

protected:
    // Konstruktor dla klas pochodnych
    Stworzenie(unsigned sila, unsigned zrecznosc, unsigned specjalny, unsigned zycie, unsigned exp) :
            sila(sila), zrecznosc(zrecznosc), specjalny(specjalny), zycie(zycie), max_zycie(zycie), wzrost_exp(exp) {};

    unsigned sila       = 0;
    unsigned zrecznosc  = 0;

    unsigned specjalny  = 0;


    unsigned zycie      = 0;
    unsigned max_zycie  = 0;

    unsigned exp        = 0;
    unsigned wzrost_exp = 0;

    STAN stan;
};

// Główne klasy storzeń
class StworzeniaWodne : public Stworzenie {
public:
    unsigned atak(Stworzenie* stworek);
    using Stworzenie::Stworzenie;
};

class StworzeniaZiemne : public Stworzenie {
public:
    unsigned atak(Stworzenie* stworek);
    using Stworzenie::Stworzenie;
};

class StworzeniaPowietrzne : public Stworzenie {
public:
    unsigned atak(Stworzenie* stworek);
    using Stworzenie::Stworzenie;
};

class StworzeniaOgnia : public Stworzenie {
public:
    unsigned atak(Stworzenie* stworek);
    using Stworzenie::Stworzenie;
};

class StworzeniaLodowe : public Stworzenie {
public:
    unsigned atak(Stworzenie* stworek);
    using Stworzenie::Stworzenie;
};

class StworzeniaStalowe : public Stworzenie {
public:
    unsigned atak(Stworzenie* stworek);
    using Stworzenie::Stworzenie;
};


/// Po 3 stworzenia każdego rodzaju
// Wodne
class Wodnik : public StworzeniaWodne {
public:
    Wodnik() : StworzeniaWodne(9,12,19,120,3) {};

    virtual const char* pobierzNazwe() const {
        return "Wodnik";
    }
};

class Rusalka : public StworzeniaWodne {
public:
    Rusalka() : StworzeniaWodne(8,14,18,110,3) {};

    virtual const char* pobierzNazwe() const {
        return "Rusalka";
    }
};

class Hipokamp : public StworzeniaWodne {  // Koń wodny
public:
    Hipokamp() : StworzeniaWodne(7,13,21,100,3) {};

    virtual const char* pobierzNazwe() const {
        return "Hipokamp";
    }
};

// Ziemne
class Golem : public StworzeniaZiemne {
public:
    Golem() : StworzeniaZiemne(13,5,18,140,4) {};

    virtual const char* pobierzNazwe() const {
        return "Golem";
    }
};

class Steelix : public StworzeniaZiemne {
public:
    Steelix() : StworzeniaZiemne(11,10,17,125,3) {};

    virtual const char* pobierzNazwe() const {
        return "Steelix";
    }
};

class WielkiRobak : public StworzeniaZiemne {
public:
    WielkiRobak() : StworzeniaZiemne(11,11,17,125,4) {};

    virtual const char* pobierzNazwe() const {
        return "Robak";
    }
};

//Powietrze
class Orzel : public StworzeniaPowietrzne {
public:
    Orzel() : StworzeniaPowietrzne(9,11,20,120,3) {};

    virtual const char* pobierzNazwe() const {
        return "Orzel";
    }
};

class Harpia : public StworzeniaPowietrzne {
public:
    Harpia() : StworzeniaPowietrzne(11,9,20,120,3) {};

    virtual const char* pobierzNazwe() const {
        return "Harpia";
    }
};

class Feniks : public StworzeniaPowietrzne {
public:
    Feniks() : StworzeniaPowietrzne(11,11,20,120,5) {};

    virtual const char* pobierzNazwe() const {
        return "Feniks";
    }
};

// Ogień
class Charmeleon : public StworzeniaOgnia {
public:
    Charmeleon() : StworzeniaOgnia(7,10,17,110,3) {};

    virtual const char* pobierzNazwe() const {
        return "Charmeleon";
    }
};

class Magmar : public StworzeniaOgnia {
public:
    Magmar() : StworzeniaOgnia(9,13,20,130,3) {};

    virtual const char* pobierzNazwe() const {
        return "Magmar";
    }
};

class Entei : public StworzeniaOgnia {
public:
    Entei() : StworzeniaOgnia(11,10,19,125,4) {};

    virtual const char* pobierzNazwe() const {
        return "Entei";
    }
};

// Lód
class Vulpix : public StworzeniaLodowe {
public:
    Vulpix() : StworzeniaLodowe(10,13,19,110,3) {};

    virtual const char* pobierzNazwe() const {
        return "Vulpix";
    }
};

class Snorut : public StworzeniaLodowe {
public:
    Snorut() : StworzeniaLodowe(12,10,18,110,3) {};

    virtual const char* pobierzNazwe() const {
        return "Snorut";
    }
};

class Silvally : public StworzeniaLodowe {
public:
    Silvally() : StworzeniaLodowe(12,15,20,120,4) {};

    virtual const char* pobierzNazwe() const {
        return "Silvally";
    }
};

// Stal
class Klink : public StworzeniaStalowe {
public:
    Klink() : StworzeniaStalowe(10,12,19,115,3) {};

    virtual const char* pobierzNazwe() const {
        return "Klink";
    }
};

class Registeel : public StworzeniaStalowe {
public:
    Registeel() : StworzeniaStalowe(9,10,17,110,3) {};

    virtual const char* pobierzNazwe() const {
        return "Registeel";
    }
};

class Lucario : public StworzeniaStalowe {
public:
    Lucario() : StworzeniaStalowe(12,10,17,100,4) {};

    virtual const char* pobierzNazwe() const {
        return "Lucario";
    }
};

// Pobranie listy wszystkich storzeń
static inline std::vector<Stworzenie*> pobierzDostepneStworki() {
    std::vector<Stworzenie*> stworki = {
            // Wodne
            new Wodnik(), new Rusalka(), new Hipokamp(),
            // Ziemne
            new Golem(), new Steelix(), new WielkiRobak(),
            //Powietrze
            new Orzel(), new Harpia(), new Feniks(),
            //Ogień
            new Charmeleon(), new Magmar(), new Entei(),
            //Lód
            new Vulpix(), new Snorut(), new Silvally(),
            //Stal
            new Klink(), new Registeel(), new Lucario()
    };
    return stworki;
}

#endif // STWORZENIE_H
