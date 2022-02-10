#ifndef GRACZ_H
#define GRACZ_H

#include <string>
#include <vector>

#include "stworzenie.h"

class Gracz
{
public:
    Gracz(const std::string& name, unsigned wielkosc_druzyny);
    ~Gracz();

    Stworzenie* pobierzAktywnegoStworka() {
        return druzyna[aktywny];
    }

    const std::string& pobiezNazwe() {
        return nazwa;
    }

    void drukujZasobnik();

    void drukujPelnyZasobnik(const std::string& opis);

    void premiaTurowa( unsigned p );

    virtual void akcjaTurowa( Gracz* p ) = 0;

protected:
    unsigned aktywny = 0; // Domyslnie aktywny pierwszy
    const std::string nazwa;
    const unsigned miejsca;
    std::vector<Stworzenie*> druzyna;
};

#endif // GRACZ_H
