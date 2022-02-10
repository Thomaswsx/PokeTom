#ifndef PRZECIWNIK_H
#define PRZECIWNIK_H

#include <vector>
#include <string>

#include "gracz.h"

/**
 * @brief The Przeciwnik class Przechowuje infromacje o przeciwniku
 */
class Przeciwnik : public Gracz
{
public:
    Przeciwnik(const std::string& name, unsigned level);

    operator bool() const {
        bool wynik = false;
        for(auto& s : druzyna)
            if( s->pobierzStan() == Stworzenie::STAN::PRZYTOMNY) // Jeśli choć jedno stworzenie jest przytomne, to możne walczyć do upadłego
                wynik = true;
        return wynik;
    }

    void akcjaTurowa( Gracz* p );
};

#endif // PRZECIWNIK_H
