#ifndef GUI_H
#define GUI_H

/**
 * Zbiur funckji wykorztywanych do prezetacji gry - pseudo GUI
 * być może powstanie z tego obiekt...
 */

#include <string>

/**
 * @brief Funkcja zwracajaca LOGO gry
 * @return Zwracaj logo grr
 */
const char* pobierzLogo();

/**
 * @brief Funkcja zwracająca odpowiedź użytkownika po
 * @param quest Pytanie które jest wyświetlane użytkownikowi
 * @param ans Zbiór dozwolonych odpowiedzi po otrzymaniu której kończone jest pytanie
 * @return Zwracany jest znak wybrany przez użytkownika - zgodny z przekazanym w parametrze asn
 */
char odpUzytkownika( const std::string& quest, const std::string& ans);

void drukujSeparator(char c = '*', unsigned length = 90);

void drukujSeparatorRuchomy(char c = '*', unsigned length = 90, unsigned milisec = 5);

void drukujNapis(const std::string& napis, unsigned milisec = 50);


const char* kolorCzerwoneTlo();

const char* kolorZieloneTlo();

const char* kolorNiebieskieTlo();

const char* kolorSzareTlo();

const char* kolorReset();

#endif // GUI_H
