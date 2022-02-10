#include <iostream>   // cout,endl
#include <string>
#include <thread>     // sleep
#include <chrono>     // 1000ms
#include <vector>
#include <memory>

#include <cstdlib> // std::atoi

#include "gui.h"
#include "stworzenie.h"
#include "uzytkownik.h"
#include "przeciwnik.h"

static const std::string HELP_TAG_LONG  = "--help";
static const std::string HELP_TAG_SHORT = "-h";

/**
 * @brief Wyświetla pomoc do gry
 */
void print_help() {
    std::cout << pobierzLogo() << std::endl;
    std::cout << R"help( Gra turowa jako projekt zaliczeniowy.
    Opcje uruchomienia:
     --help  - wyświetlenie tej pomocy
    
    Opcje rozgrywki:
      a - atak
      w - wymiana stworzenia
      e - ewolucja stworzenia po osiągnięciu wystarczającego doświadczenia
      s - umiejętność specjalna )help" << std::endl;
}

void koniec() {
    drukujSeparator();
    drukujNapis( pobierzLogo(), 15);
    drukujNapis( "  Koniec Gry\n", 15);
    drukujSeparator();
}

void drukujWstep( Uzytkownik* u, Przeciwnik* p) {
    std::cout << std::endl;
    drukujSeparator();
    std::cout << "# " << p->pobiezNazwe() << std::endl;;
    p->drukujPelnyZasobnik(" Przeciwnik posiada:");
    drukujSeparator();
    drukujNapis("Rozpoczyna się walka...");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    p->drukujZasobnik();
    u->drukujZasobnik();
    drukujSeparator(); // Odzielenie tury
}

void rozegrajRunde(Uzytkownik* u, Przeciwnik* p, unsigned runda) {
    // Walka turowa do upadłego...
    while( *u && *p ) {
        u->akcjaTurowa(p); // Zaczyna gracz

        // Stan gry
        p->drukujZasobnik();
        u->drukujZasobnik();

        std::cout << std::endl; // Separator

        p->akcjaTurowa(u); // Akcja przeciwnika

        // Stan gry
        p->drukujZasobnik();
        u->drukujZasobnik();

        drukujSeparator(); // Odzielenie tury
    }
}

/**
 * @brief Główna funkcja programu od której startuje program
 * @param argc Ilość parametrów przekazanych podczas wywołania programu
 * @param argv Tablica wskaźników na c-stringi każdego z przekazanych parametrów wywołania
 * @return Kod wyjścia programu, wartość inna niż 0 oznacza błąd
 */
int main(int argc, char** argv) {

    // Obsługa opcji wywołania, w tym '--help'
    if( argc > 1 ) {
        if( argc == 2 && (HELP_TAG_LONG == argv[1] || HELP_TAG_SHORT == argv[1]) ) {
            print_help();
        } else {
            std::cout << "Nieprawidłowe wywołanie programu. W celu uzyskania pomocy uruchom:\n " << argv[0] << " --help" << std::endl;
            return -1;
        }
    }

    // 1 Wstęp
    std::cout << pobierzLogo() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Zatrzymanie programu po wyświtleniu LOGO

    std::unique_ptr<Uzytkownik> user;

    // 2 Menu początkowe
    char znak = odpUzytkownika("Witaj, co chcesz zrobić?\n * (N)owa gra\n * (Z)aładuj grę\n * (W)yjdź z gry","NnZzWw");
    // TODO: To też można zakmnąć w jakaś funkcję..
    switch( znak ) {
        case 'W':
        case 'w':
            koniec();
            return 0;

        case 'Z':
        case 'z':
            drukujSeparatorRuchomy();
//        user.reset( new Uzytkownik() ); // Wtyczanie gracza z pliku - odpowiedni konstruktor
            std::cout << "Próba załadwowania stanu gry..." << std::endl;
            drukujSeparatorRuchomy();
            break;

        case 'N':
        case 'n': // Można to zrobić jako domyślne działanie
            drukujSeparatorRuchomy();
            user.reset( new Uzytkownik() ); // Stworzneie nowego gracza
            break;

        default:
            std::cout << "wewnętrzy bład programu!" << std::endl;
            return -2;
    }

    // Jeśli użtkonik nie utworzył sie poprawnie - koniec gry
    if( !user )
        return -3;

    /**
     *  Rozgrywka
     */

    /// Przeciwnik 1
    Przeciwnik p1("Slabeusz", 1);
    drukujWstep(user.get(), &p1);

    // Walka turowa do upadłego...
    rozegrajRunde(user.get(), &p1, 1);
    if( *user ) {
        drukujNapis("GRATULACJE WYGRAŁEŚ SWOJĄ PIERWSZĄ WALKĘ.");
    } else {
        drukujNapis("Zostałeś pokonany");
        koniec();
        return 0;
    }
    // Nagroda za wygraną - odzyskanie życia
    user->premiaTurowa(70);

    /// Przeciwnik 2
    Przeciwnik p2("Wloczega", 2);
    drukujWstep(user.get(), &p2);

    // Walka turowa do upadłego...
    rozegrajRunde(user.get(), &p2, 2);
    if( *user ) {
        drukujNapis("GRATULACJE WYGRAŁEŚ JUŻ DRUGĄ WALKĘ.");
    } else {
        drukujNapis("Zostałeś pokonany");
        koniec();
        return 0;
    }
    // Nagroda za wygraną - odzyskanie życia
    user->premiaTurowa(90);

    /// Przeciwnik 3
    Przeciwnik p3("Rzezimieszek", 3);
    drukujWstep(user.get(), &p3);

    // Walka turowa do upadłego...
    rozegrajRunde(user.get(), &p3, 3);
    if( *user ) {
        drukujNapis("JESTEŚ NAPRAWDĘ DOBRY WYGRAŁEŚ TRZECIĄ WALKĘ.");
    } else {
        drukujNapis("Zostałeś pokonany");
        koniec();
        return 0;
    }
    // Nagroda za wygraną - odzyskanie życia
    user->premiaTurowa(120);

    /// Przeciwnik 4 - Boss
    Przeciwnik p4("Boss", 4);
    drukujWstep(user.get(), &p4);

    // Walka turowa do upadłego...
    rozegrajRunde(user.get(), &p4, 4);
    if( *user ) {
        drukujNapis("JESTEŚ NAJLEPSZY!!!");
        drukujNapis( pobierzLogo(), 22);
        drukujSeparator();
        return 0;
    } else {
        drukujNapis("Zostałeś pokonany");
    }
    koniec();
    return 0;
}

