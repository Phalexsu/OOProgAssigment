/**
* @file buss.cpp
* @author Aleksander Solhaug, Jan Olav Lyche Aspelund og Philip Alexander Sundt
*/
#include "buss.h"
#include "lesData3.h"
#include "const.h"
#include "fstream"
using namespace std;

/**
* @brief default constructor til buss
* @see Rute::lesData()
*/
Buss::Buss()
{
    lesData();
    Rute::lesData();
}
/**
* @brief constructor for lesing fra fil
* @param inn - referanseoverført fil for å lese fra
*/
Buss::Buss(ifstream& inn): Rute(inn) {
    inn >> sittePlasser >> staPlasser >> alleLed;
}

/**
* @brief leser inn data om bussen fra brukeren
*/
void Buss::lesData() {
    char jaNei;
    sittePlasser = lesInt("Bussrutens faste antall sitteplasser", MINSITTE,
                                                                  MAKSSITTE);
    staPlasser = lesInt("Bussrutens faste antall staaplasser",    MINSTAA,
                                                                  MAKSSTAA);

    jaNei = lesChar("Leddbuss(J/n)");
    if (jaNei == 'N')
        alleLed = false;
    else
        alleLed = true;
    
}

/**
* @brief skriver ut bussens data
* @see Rute::skrivData()
*/
void Buss::skrivData() {
    cout << "\n\tBussrutens faste antall sitteplasser: " << sittePlasser;
    cout << "\n\tBussrutens faste antall staaplasser: " << staPlasser;
    cout << "\n\tBussen er " << (!alleLed ? "ikke " : "" )<< "leddbuss";
    Rute::skrivData();
}
/**
* @brief skriver bussdataen til fil
* @param ut - referanseoverført fil for å skrive til
* @see Rute::skrivTilFil(...)
*/
void Buss::skrivTilFil(ofstream& ut) {
    ut << "U ";
    Rute::skrivTilFil(ut);
    ut << sittePlasser << ' ' << staPlasser << ' ' << alleLed << ' ';
}
