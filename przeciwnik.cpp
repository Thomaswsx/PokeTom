#include "przeciwnik.h"
#include "uzytkownik.h"

#include <iostream>
#include <random>

Przeciwnik::Przeciwnik(const std::string& name, unsigned level) : Gracz(name, 4 + level/2)
{
    // Tworzenie i losowanie stworzeń dla preciwnika
    std::vector<Stworzenie*> dostepne_stworzenia = pobierzDostepneStworki();

    // Przygotowanie generatora losowego
    std::random_device rd;
    std::mt19937 mt(rd());

    unsigned wolne_miejsce = miejsca;
    while ( wolne_miejsce ) {
        // Losowanie storzeń z dostępnych
        std::uniform_real_distribution<double> dist(0.0, dostepne_stworzenia.size());
        unsigned wybor = dist(mt) ;
        druzyna.push_back(dostepne_stworzenia[wybor]); // Kopiujemy wskażnik do zasobnika gracza
        dostepne_stworzenia.erase(dostepne_stworzenia.begin()+wybor); // Usunięcie przeniesionego stworzenia
        --wolne_miejsce;
    }

    // Usuwmy resztę stowrzeń
    for(auto p : dostepne_stworzenia)
        delete p;
}

// "AI" przciwnika...
// Na razie bardzo trywialne....
void Przeciwnik::akcjaTurowa( Gracz* p ) {

    // Stworzenie przeciwnika
    Stworzenie* sp = p->pobierzAktywnegoStworka();

    // Wymienia stworka bez utraty tury... AI może oszukiwać - zasady gdy są dla gracza
    if( druzyna[aktywny]->pobierzStan() == Stworzenie::STAN::ZEMDLAL ) { // Wymień omdlałego stwork
        if(++aktywny >= druzyna.size())
            aktywny = 0;
    }

    Stworzenie* s = druzyna[aktywny];
    if( s->pobierzStan() == Stworzenie::STAN::ZEMDLAL ) {
        std::cout << "# WRÓG: Nie mogę dalej walczyć!" << std::endl;
        return;
    }

    unsigned obrazenia = s->atak(sp);
    if( obrazenia )
        std::cout << "# Wrogi stworek '" << s->pobierzNazwe() << "' zatakwował naszego czempiona '" << p->pobierzAktywnegoStworka()->pobierzNazwe() << "' zadając nam " << obrazenia << " punktów obrażeń." << std::endl;
    else
        std::cout << "# Wrogi stworek '" << s->pobierzNazwe() << "' zatakwował naszego czempiona '" << p->pobierzAktywnegoStworka()->pobierzNazwe() << "' ten unikną jednak wrogiego ataku." << std::endl;
}
