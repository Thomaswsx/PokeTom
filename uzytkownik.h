#ifndef UZYTKOWNIK_H
#define UZYTKOWNIK_H

#include <vector>

#include "gracz.h"

/**
 * @brief The Uzytkownik class Przechowuje stan uzytkownika
 */
class Uzytkownik : public Gracz
{
public:
    Uzytkownik();

    // służy do sprawdzenia czy gracz może jeszcze czym grać
    operator bool() const {
        bool wynik = false;
        for(auto s : druzyna)
            if( s->pobierzStan() == Stworzenie::STAN::PRZYTOMNY) // Jeśli choć jedno stworzenie jest przytomne, to można walczyć do upadłego
                wynik = true;
        return wynik;
    }

    virtual void akcjaTurowa( Gracz* p );

};

#endif // UZYTKOWNIK_H
