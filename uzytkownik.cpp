
#include "gui.h"
#include "uzytkownik.h"
#include "przeciwnik.h"

#include <iostream>
#include <limits>

Uzytkownik::Uzytkownik() : Gracz(" TY ", 6)
{
    std::vector<Stworzenie*> wszystkie_stworzenia = pobierzDostepneStworki();

    unsigned wolne_miejsce = miejsca;
    while ( wolne_miejsce ) {
        std::cout << "Wybierz swoich czempionów (pozostało "<< wolne_miejsce << "):" << std::endl;
        for( int i = 0; i < wszystkie_stworzenia.size(); ++i ) {
            std::cout << " " << i+1 << ((i<9) ? " ": "") << " - ";
            wszystkie_stworzenia[i]->drukuj();
        }

        unsigned int wybor = 0;
        do {
            std::cout << "Twój wybór:" << std::flush;
            while( !(std::cin >> wybor) ) {
                std::cout << "Podałeś nieporawny numer. Twój wybór:" << std::flush;
                std::cin.clear(); //wyczyszczenie flag bledow
                //pomin wszystkie aktualne znaki w buforze
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } while (wybor > wszystkie_stworzenia.size() || wybor < 1 );

        druzyna.push_back(wszystkie_stworzenia[wybor-1]); // Kopiujemy wskażnik do zasobnika gracza
        wszystkie_stworzenia.erase(wszystkie_stworzenia.begin()+wybor-1); // Usunięcie przeniesionego stworzenia
        --wolne_miejsce;
    }

    // Usuwmy resztę stowrzeń
    for(auto p : wszystkie_stworzenia)
        delete p;

    drukujPelnyZasobnik("\nTwoi czempioni:");

    std::cout << "\nRuszamy podbić świat!" << std::endl;
}

void Uzytkownik::akcjaTurowa( Gracz* p ) {
    while(true) {
        char znak = odpUzytkownika("Co robimy? *(A)tak *(W)ymiana *(E)wolucja *(S)pecjalne","AaWwEeSs");
        switch( znak ) {
            case 'A':
            case 'a':
            {
                Stworzenie* s = druzyna[aktywny]; // Pobierz swojego czempinona
                if( s->pobierzStan() == Stworzenie::STAN::ZEMDLAL) {
                    std::cout << "Twój czempion '" << s->pobierzNazwe() << " jest wyczerpany, musisz dać mu odpocząć. Wubierz innego czempiona." << std::endl;
                    break;
                }
                unsigned obrazenia = s->atak(p->pobierzAktywnegoStworka());
                if( obrazenia )
                    std::cout << "* Twój czempion '" << s->pobierzNazwe() << "' atakuje stworka '" << p->pobierzAktywnegoStworka()->pobierzNazwe() << "' zadając " << obrazenia << " punktów obrażeń." << std::endl;
                else
                    std::cout << "* Twój czempion '" << s->pobierzNazwe() << "' atakuje stworka '" << p->pobierzAktywnegoStworka()->pobierzNazwe() << "' któremu udaje się uniknąć twojemu ataku." << std::endl;
            }
                return;
            case 'W':
            case 'w':
            {
                // Wypisanie dostępnej listy
                drukujPelnyZasobnik("Twoja drużyna:");
                unsigned int wybor = 0;
                do {
                    std::cout << "Twój wybór:" << std::flush;
                    while( !(std::cin >> wybor) ) {
                        std::cout << "Podałeś nieporawny numer. Twój wybór:" << std::flush;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                } while (wybor > druzyna.size() || wybor < 1 );

                if( wybor-1 == aktywny ) {
                    std::cout << "Wybrałeś tego samego czempiona - nie tracisz kolejki." << std::endl;
                    break;
                }

                aktywny = wybor-1;
            }
                return;
            case 'E':
            case 'e':
            {
                Stworzenie* s = druzyna[aktywny]; // Pobierz swojego czempinona
                bool res = s->ewolucja();
                if( !res ) {
                    std::cout << "Twój " << s->pobierzNazwe() << " nie może jeszcze ewoluować - pokonaj jakiegoś przeciwnika." << std::endl;
                    break;
                }
                return;
            }
            case 'S':
            case 's':
            {
                std::cout << "Brak specjalnych mocy - nie tracisz kolejki." << std::endl;
                break;
            }
            default:
                std::cout << "Wewnętrzny błąd..." << std::endl;
                return;
        }
    }
}

