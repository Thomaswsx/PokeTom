#include "gui.h"
#include "stworzenie.h"

#include <iostream>
#include <random>

static constexpr unsigned PREMIA_PLUS  = 2;
static constexpr unsigned PREMIA_MINUS = 3;


bool Stworzenie::ewolucja() {
    if( !exp )
        return false; // nie możemy jeszcze ewoluować

    drukujSeparator();
    while( exp ) {
        drukuj(); // Wyświetlenie obecnych statystyk
        char stat = odpUzytkownika(" Jaką statystykę chiałbyś powiększyć? [ (S)iła +1 (Z)ręczność +1 (W)ytrzymałość +5 życia]", "SsZzWw");
        switch( stat ) {
            case 'S':
            case 's':
                ++sila;
                break;
            case 'Z':
            case 'z':
                ++zrecznosc;
                break;
            case 'W':
            case 'w':
                max_zycie+=5;
                zycie+=5;
                break;
            default:
                std::cout << "wewnętrzy bład programu!" << std::endl;
        }
        --exp;
    }
    return true;
}

unsigned StworzeniaWodne::atak(Stworzenie* stworek) {

    // Przygotowanie generatora losowego
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 100.0);
    unsigned szansa = dist(mt);
    if( szansa < stworek->pobierzZrecznosc() )
        return 0 ; // Udało sie uniknąc ataku;

    StworzeniaWodne* wodny_stworek = dynamic_cast<StworzeniaWodne*>(stworek);
    if( wodny_stworek ) {
        wodny_stworek->przyjmijObrazenia(sila-PREMIA_MINUS);
        if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
            exp += wzrost_exp;
        return sila-PREMIA_MINUS;
    }

    StworzeniaZiemne* ziemny_stworek = dynamic_cast<StworzeniaZiemne*>(stworek);
    if( ziemny_stworek ) {
        ziemny_stworek->przyjmijObrazenia(sila+PREMIA_PLUS);
        if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
            exp += wzrost_exp;
        return sila+PREMIA_PLUS;
    }

    StworzeniaOgnia* ognisty_stworek = dynamic_cast<StworzeniaOgnia*>(stworek);
    if( ognisty_stworek ) {
        ognisty_stworek->przyjmijObrazenia(sila+PREMIA_PLUS);
        if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
            exp += wzrost_exp;
        return sila+PREMIA_PLUS;
    }

    // Pozostałe
    stworek->przyjmijObrazenia(sila);
    if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
        exp += wzrost_exp;
    return sila;
}

unsigned StworzeniaZiemne::atak(Stworzenie* stworek) {

    // Przygotowanie generatora losowego
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 100.0);
    unsigned szansa = dist(mt);
    if( szansa < stworek->pobierzZrecznosc() )
        return 0 ; // Udało sie uniknąc ataku;

    StworzeniaPowietrzne* powietrzny_stworek = dynamic_cast<StworzeniaPowietrzne*>(stworek);
    if( powietrzny_stworek ) {
        powietrzny_stworek->przyjmijObrazenia(sila-PREMIA_MINUS);
        if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
            exp += wzrost_exp;
        return sila-PREMIA_MINUS;
    }

    StworzeniaOgnia* ognisty_stworek = dynamic_cast<StworzeniaOgnia*>(stworek);
    if( ognisty_stworek ) {
        ognisty_stworek->przyjmijObrazenia(sila+PREMIA_PLUS);
        if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
            exp += wzrost_exp;
        return sila+PREMIA_PLUS;
    }

    StworzeniaLodowe* lodowy_stworek = dynamic_cast<StworzeniaLodowe*>(stworek);
    if( lodowy_stworek ) {
        lodowy_stworek->przyjmijObrazenia(sila+PREMIA_PLUS);
        if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
            exp += wzrost_exp;
        return sila+PREMIA_PLUS;
    }

    StworzeniaStalowe* stalowy_stworek = dynamic_cast<StworzeniaStalowe*>(stworek);
    if( stalowy_stworek ) {
        stalowy_stworek->przyjmijObrazenia(sila+PREMIA_PLUS);
        if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
            exp += wzrost_exp;
        return sila+PREMIA_PLUS;
    }

    // Pozostałe
    stworek->przyjmijObrazenia(sila);
    if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
        exp += wzrost_exp;
    return sila;
}

unsigned StworzeniaPowietrzne::atak(Stworzenie* stworek) {

    // Przygotowanie generatora losowego
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 100.0);
    unsigned szansa = dist(mt);
    if( szansa < stworek->pobierzZrecznosc() )
        return 0 ; // Udało sie uniknąc ataku;

    StworzeniaZiemne* ziemny_stworek = dynamic_cast<StworzeniaZiemne*>(stworek);
    if( ziemny_stworek ) {
        ziemny_stworek->przyjmijObrazenia(sila-PREMIA_MINUS);
        if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
            exp += wzrost_exp;
        return sila-PREMIA_MINUS;
    }

    StworzeniaStalowe* stalowy_stworek = dynamic_cast<StworzeniaStalowe*>(stworek);
    if( stalowy_stworek ) {
        stalowy_stworek->przyjmijObrazenia(sila-PREMIA_MINUS);
        if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
            exp += wzrost_exp;
        return sila-PREMIA_MINUS;
    }

    StworzeniaLodowe* lodowy_stworek = dynamic_cast<StworzeniaLodowe*>(stworek);
    if( lodowy_stworek ) {
        lodowy_stworek->przyjmijObrazenia(sila+PREMIA_PLUS);
        if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
            exp += wzrost_exp;
        return sila+PREMIA_PLUS;
    }

    // Pozostałe
    stworek->przyjmijObrazenia(sila);
    if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
        exp += wzrost_exp;
    return sila;
}

unsigned StworzeniaOgnia::atak(Stworzenie* stworek) {

    // Przygotowanie generatora losowego
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 100.0);
    unsigned szansa = dist(mt);
    if( szansa < stworek->pobierzZrecznosc() )
        return 0 ; // Udało sie uniknąc ataku;

    StworzeniaWodne* wodny_stworek = dynamic_cast<StworzeniaWodne*>(stworek);
    if( wodny_stworek ) {
        wodny_stworek->przyjmijObrazenia(sila-PREMIA_MINUS);
        if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
            exp += wzrost_exp;
        return sila-PREMIA_MINUS;
    }

    StworzeniaZiemne* ziemny_stworek = dynamic_cast<StworzeniaZiemne*>(stworek);
    if( ziemny_stworek ) {
        ziemny_stworek->przyjmijObrazenia(sila-PREMIA_MINUS);
        if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
            exp += wzrost_exp;
        return sila-PREMIA_MINUS;
    }

    StworzeniaLodowe* lodowy_stworek = dynamic_cast<StworzeniaLodowe*>(stworek);
    if( lodowy_stworek ) {
        lodowy_stworek->przyjmijObrazenia(sila+PREMIA_PLUS);
        if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
            exp += wzrost_exp;
        return sila+PREMIA_PLUS;
    }

    StworzeniaStalowe* stalowy_stworek = dynamic_cast<StworzeniaStalowe*>(stworek);
    if( stalowy_stworek ) {
        stalowy_stworek->przyjmijObrazenia(sila+PREMIA_PLUS);
        if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
            exp += wzrost_exp;
        return sila+PREMIA_PLUS;
    }

    // Pozostałe
    stworek->przyjmijObrazenia(sila);
    if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
        exp += wzrost_exp;
    return sila;
}

unsigned StworzeniaLodowe::atak(Stworzenie* stworek) {

    // Przygotowanie generatora losowego
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 100.0);
    unsigned szansa = dist(mt);
    if( szansa < stworek->pobierzZrecznosc() )
        return 0 ; // Udało sie uniknąc ataku;

    StworzeniaWodne* wodny_stworek = dynamic_cast<StworzeniaWodne*>(stworek);
    if( wodny_stworek ) {
        wodny_stworek->przyjmijObrazenia(sila-PREMIA_MINUS);
        if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
            exp += wzrost_exp;
        return sila-PREMIA_MINUS;
    }

    StworzeniaOgnia* ognisty_stworek = dynamic_cast<StworzeniaOgnia*>(stworek);
    if( ognisty_stworek ) {
        ognisty_stworek->przyjmijObrazenia(sila-PREMIA_MINUS);
        if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
            exp += wzrost_exp;
        return sila-PREMIA_MINUS;
    }

    StworzeniaLodowe* lodowy_stworek = dynamic_cast<StworzeniaLodowe*>(stworek);
    if( lodowy_stworek ) {
        lodowy_stworek->przyjmijObrazenia(sila-PREMIA_MINUS);
        if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
            exp += wzrost_exp;
        return sila-PREMIA_MINUS;
    }

    StworzeniaZiemne* ziemny_stworek = dynamic_cast<StworzeniaZiemne*>(stworek);
    if( ziemny_stworek ) {
        ziemny_stworek->przyjmijObrazenia(sila+PREMIA_PLUS);
        if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
            exp += wzrost_exp;
        return sila+PREMIA_PLUS;
    }

    // Pozostałe
    stworek->przyjmijObrazenia(sila);
    if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
        exp += wzrost_exp;
    return sila;
}

unsigned StworzeniaStalowe::atak(Stworzenie* stworek) {

    // Przygotowanie generatora losowego
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 100.0);
    unsigned szansa = dist(mt);
    if( szansa < stworek->pobierzZrecznosc() )
        return 0 ; // Udało sie uniknąc ataku;

    StworzeniaOgnia* ognisty_stworek = dynamic_cast<StworzeniaOgnia*>(stworek);
    if( ognisty_stworek ) {
        ognisty_stworek->przyjmijObrazenia(sila-PREMIA_MINUS);
        if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
            exp += wzrost_exp;
        return sila-PREMIA_MINUS;
    }

    StworzeniaStalowe* stalowy_stworek = dynamic_cast<StworzeniaStalowe*>(stworek);
    if( stalowy_stworek ) {
        stalowy_stworek->przyjmijObrazenia(sila-PREMIA_MINUS);
        if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
            exp += wzrost_exp;
        return sila-PREMIA_MINUS;
    }

    StworzeniaWodne* wodny_stworek = dynamic_cast<StworzeniaWodne*>(stworek);
    if( wodny_stworek ) {
        wodny_stworek->przyjmijObrazenia(sila+PREMIA_PLUS);
        if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
            exp += wzrost_exp;
        return sila+PREMIA_PLUS;
    }

    StworzeniaPowietrzne* powietrzny_stworek = dynamic_cast<StworzeniaPowietrzne*>(stworek);
    if( powietrzny_stworek ) {
        powietrzny_stworek->przyjmijObrazenia(sila+PREMIA_PLUS);
        if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
            exp += wzrost_exp;
        return sila+PREMIA_PLUS;
    }

    // Pozostałe
    stworek->przyjmijObrazenia(sila);
    if(stworek->pobierzStan() == STAN::ZEMDLAL) // Skoro udało się ogłuszyć przeciwnika to możemy zystać doświadczenie
        exp += wzrost_exp;
    return sila;
}
