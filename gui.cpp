#include "gui.h"

#include <iostream>
#include <thread>


const char* pobierzLogo() {
    static const char* LOGO = R"logo(
  ____       _       _____
 |  _ \ ___ | | ____|_   _|__  _ __ ___
 | |_) / _ \| |/ / _ \| |/ _ \| '_ ` _ \
 |  __/ (_) |   <  __/| | (_) | | | | | |
 |_|   \___/|_|\_\___||_|\___/|_| |_| |_|


  Autor: Tomasz Wytrykus
)logo";
    return LOGO;
}

/**
 * @brief Funkcja zwracająca odpowiedź użytkownika po
 * @param quest Pytanie które jest wyświetlane użytkownikowi
 * @param ans Zbiór dozwolonych odpowiedzi po otrzymaniu której kończone jest pytanie
 * @return Zwracany jest znak wybrany przez użytkownika - zgodny z przekazanym w parametrze asn
 */
char odpUzytkownika( const std::string& quest, const std::string& ans) {
    std::cout << quest << std::endl;
    char znak;
    while( 1 ) {
        std::cin >> znak; // Pobranie tego co wcisnął gracz
        if( ans.find(znak) != std::string::npos)
            break;
    }
    return znak;
}

void drukujSeparator(char c , unsigned length) {
    static std::string separator(length, c);
    std::cout << separator << std::endl;
}

void drukujSeparatorRuchomy(char c, unsigned length, unsigned milisec) {
    while(length--) {
        std::this_thread::sleep_for(std::chrono::milliseconds(milisec));
        std::cout << c << std::flush;
    }
    std::cout << std::endl;
}


void drukujNapis(const std::string& napis, unsigned milisec) {
    for( const auto& c : napis ) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(milisec));
    }
    std::cout << std::endl;
}

const char* kolorCzerwoneTlo(){
#if defined(__linux__)
    return "\033[41m";
#elif defined(__APPLE__)
    return "\033[41m";
#else
    return  "";
#endif
}

const char* kolorZieloneTlo(){
#if defined(__linux__)
    return "\033[42m";
#elif defined(__APPLE__)
    return "\033[42m";
#else
    return  "";
#endif
}

const char* kolorNiebieskieTlo(){
#if defined(__linux__)
    return "\033[44m";
#elif defined(__APPLE__)
    return "\033[44m";
#else
    return  "";
#endif
}

const char* kolorSzareTlo(){
#if defined(__linux__)
    return "\033[47m";
#elif defined(__APPLE__)
    return "\033[47m";
#else
    return  "";
#endif
}

const char* kolorReset(){
#if defined(__linux__)
    return "\033[0m";
#elif defined(__APPLE__)
    return "\033[0m";
#else
    return  "";
#endif
}
