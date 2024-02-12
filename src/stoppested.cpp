#include <iostream>
#include "stoppested.h"
#include "funksjoner.h"
using namespace std;

/**
 * @brief Constructor for class Stoppested.
 */
Stoppested::Stoppested() {
    navn = "";
}

/**
 * @brief Leser data om stoppested fra fil.
 * 
 * @param inn  - Filobjekt som leser fra fil.
 */
void Stoppested::lesFraFil(ifstream & inn) {
    int antall;
    int stopp, min;
    inn >> navn >> antall;
    for (int i = 0; i < antall; i++) {
        inn >> stopp >> min;
        naboStopp.push_back(stopp);
        minTilNabo.push_back(min);
    }
}

/**
 * @brief Skriver data fra stoppested til fil.
 * 
 * @param ut  - Filobjekt som skriver til fil.
 */
void Stoppested::skrivTilFil(ofstream & ut) {
    ut << navn << ' ' << naboStopp.size() << ' ';
    for (int i = 0; i < naboStopp.size(); i++)
        ut << naboStopp[i] << ' ' << minTilNabo[i] << ' ';
    ut << '\n';
}

/**
 * @brief Legger til nytt nabostopp(indeks) og minutter til ny nabo.
 * 
 * @param nyNabo  - Antall minutter til ny nabo.
 */
void Stoppested::leggTilNabo(const int nyNabo, const int min) {
    naboStopp.push_back(nyNabo);
    minTilNabo.push_back(min);
}

/**
 * @brief Sjekker om stoppet eksisterer.
 * 
 * @see toUpper(...)
 * 
 * @return true/false om stoppestedet eksisterer eller ei.
 */
bool Stoppested::sjekkDuplikat(const string nyttNavn) {
    string navn1 = toUpper(navn);
    string navn2 = toUpper(nyttNavn);
    
    if (navn1 == navn2)
        return true;
    else
        return false;
}

/**
 * @brief Lagrer navn til nytt stopp.
 * 
 * @param nyttNavn  - Navnet til det nye stoppet.
 */
void Stoppested::lagreNavn(const string nyttNavn) {
    navn = nyttNavn;
}

/**
 * @brief Henter tid mellom nabostopp. Hvis ikke funnet, 
 * returnerer 0.
 * 
 * @return Tall for hvor langt det er til nabostopp.
 *         0 betyr ingen tilknytning.
 */
int Stoppested::hentNabotid(const int nabo) {
    for (int i = 0; i < naboStopp.size(); i++) {
        if (naboStopp[i] == nabo) {
            return minTilNabo[i];
        }
    }
    return 0;
}

/**
 * @brief Skriver navn og hvor langt til stoppet en er ute etter.
 */
void Stoppested::skrivNabotid(const int nabo) {
    for (int i = 0; i < naboStopp.size(); i++) {
        if (naboStopp[i] == nabo) {
            cout<<"  "<<navn<<" - Tid til stopp: "<<minTilNabo[i]<<'\n';
        }
    }
}

/**
 * @brief Henter vector av indekser for nabostopp.
 *
 * @param nabo  - vector <int> for hvilke naboer stopper har.
 * 
 * @return naboStopp - Nabostoppet
 */
vector <int> Stoppested::hentNaboer() {
    return naboStopp;
}

/**
 * @brief Henter navn fra stoppested.
 * 
 * @return Navn til stoppested.
 */
string Stoppested::hentNavn() {
    return navn;
}