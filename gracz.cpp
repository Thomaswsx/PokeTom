#include "gui.h"
#include "gracz.h"

#include <iostream>

Gracz::Gracz(const std::string& name, unsigned wielkosc_druzyny)
        : nazwa(name), miejsca(wielkosc_druzyny) {
}

Gracz::~Gracz() {
    for(auto p : druzyna)
        delete p;
}

void Gracz::premiaTurowa( unsigned plus ) {
//    for( auto i = 0; i < druzyna.size(); ++i ) {
//        druzyna[i]->regeneracja(p);
//    }
    for(auto p : druzyna)
        p->regeneracja(plus);
}

void Gracz::drukujPelnyZasobnik(const std::string& opis) {
    std::cout << opis << std::endl;
    for( int i = 0; i < druzyna.size(); ++i ) {
        std::cout << " " << i+1 << (i == aktywny ? " A " : (druzyna[i]->pobierzStan() == Stworzenie::STAN::ZEMDLAL ? " Z " :  " - "));
        druzyna[i]->drukuj();
    }
}

void Gracz::drukujZasobnik() {
    printf("%-15.15s", nazwa.c_str());
    for(auto i = 1; i < druzyna.size()+1; ++i ) {
        Stworzenie* s = druzyna[i-1];
        std::cout << " (" <<i<<")"
                  << ((i-1 == aktywny) ? kolorNiebieskieTlo() : "" ) << ((s->pobierzStan() == Stworzenie::STAN::ZEMDLAL) ? kolorSzareTlo() : "")
                  << s->pobierzNazwe() << ((i-1 == aktywny) ? "[A]" : "")  << ((s->pobierzStan() == Stworzenie::STAN::ZEMDLAL) ? "[Z] " : " ")
                  << ((i-1 == aktywny) ? kolorReset() : "" ) << ((s->pobierzStan() == Stworzenie::STAN::ZEMDLAL) ? kolorReset() : "")
                  << " {" << kolorCzerwoneTlo() << s->pobierzZycie() << kolorReset() << "}"
                  << std::flush;
    }
    std::cout << " ]" << std::endl;
}
