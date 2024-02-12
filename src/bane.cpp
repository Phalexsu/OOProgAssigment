/**
* @file bane.cpp
* @author Aleksander Solhaug, Jan Olav Lyche Aspelund og Philip Alexander Sundt
*/
#include "bane.h"
#include "const.h"
#include "lesData3.h"
#include "fstream"
using namespace std;

/**
* @brief default constructor til bane
* @see Rute::lesData()
*/
Bane::Bane(){
    lesData();
    Rute::lesData();
}
/**
* @brief constructor for lesing fra fil
* @param inn - referanseoverført fil for å lese fra
*/
Bane::Bane(ifstream & inn): Rute(inn) {
    inn >> antallVogner;
    baneLengde = antallVogner * VOGNLENGDE;
}

/**
* @brief leser inn dat til banen fra brukeren
*/
void Bane::lesData() {
    antallVogner = lesInt("antall vogner paa T-banen", MINVOGNER, MAKSVOGNER);
}

/**
* @brief skriver ut dataen til banen
* @see Rute::skrivData()
*/
void Bane::skrivData() {
    cout << "\n\tT-banen har " << antallVogner << " vogner";
    cout << "\n\tBanen er " << baneLengde << "m lang";
    Rute::skrivData();
}

/**
* @brief skriver banedataen til fil
* @param ut - referanseoverført fil for å skrive til
* @see Rute::skrivTilFil(...)
*/
void Bane::skrivTilFil(ofstream& ut) {
    ut << "A ";
    Rute::skrivTilFil(ut);
    ut << antallVogner << ' ';
}

