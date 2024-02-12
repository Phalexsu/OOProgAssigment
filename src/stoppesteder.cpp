#include "iostream"
#include "iomanip"
#include <fstream>
#include <string>
#include "stoppested.h"
#include "stoppesteder.h"
#include "LesData3.h"
#include "funksjoner.h"
#include "const.h"
using namespace std;

/**
 * @brief Deconstructor for class Stoppesteder.
 */
Stoppesteder::~Stoppesteder() {
    while (!alleStoppesteder.empty()) {
        delete alleStoppesteder.back();
        alleStoppesteder.pop_back();
    }
}

/**
 * @brief Leser data om stoppesteder fra fil
 * 
 * @see Stoppested::lesFraFil(...)
 */
void Stoppesteder::lesFraFil() {
    int stopp;
    ifstream inn("STOPPESTEDER.DTA");
    if (inn) {
        cout << "\nLeser fra STOPPESTEDER.DTA...";
        inn >> stopp;
        for (int i = 0; i < stopp; i++) {
            Stoppested* tempStopp;
            tempStopp = new Stoppested;
            tempStopp->lesFraFil(inn);
            alleStoppesteder.push_back(tempStopp);
        }
    }
    else cout << "\nKunne ikke lese STOPPESTEDER.DTA...";
}

/**
 * @brief Skriver all lagret info til fil.
 * 
 * @see Stoppested::skrivTilFil(...)
 */
void Stoppesteder::skrivTilFil() {
    ofstream ut("STOPPESTEDER.DTA");
    ut << alleStoppesteder.size() << '\n';
    for (Stoppested* & stopp : alleStoppesteder)
        stopp->skrivTilFil(ut);
}

/**
 * @brief Legger til nytt stopp i liste.
 * 
 * @see Stoppested::sjekkDuplikat(...)
 * @see Stoppested::lagreNavn(...)
 */
void Stoppesteder::leggTilStopp() {
    string nyttNavn = " ";
    int valg = 0;
    // Leser navn for nytt stopp.
    while (nyttNavn == " ") {
        cout << "Skriv nytt navn på stopp: ";
        getline(cin, nyttNavn);
        for (auto & val : alleStoppesteder) {
            if (val->sjekkDuplikat(nyttNavn) == 1) {
                nyttNavn = " ";
                cout << "Navn eksisterer allerede!\n";
            }
        }
    }
    // Lager og lagrer nytt stopp.
    Stoppested* tempStopp;
    tempStopp = new Stoppested;
    tempStopp->lagreNavn(nyttNavn);
    alleStoppesteder.push_back(tempStopp);
    cout << "Stopp lagt til";
}

/**
 * @brief Skriver ut alle navn for lagrede stoppesteder.
 * 
 * @see Stoppested::hentNavn()
 */
void Stoppesteder::skrivAlleStoppesteder() {
    cout << "\n\tAlle Stoppesteder:\n\t\t";
    for (int i = 0; i < alleStoppesteder.size(); i++) {
        cout << i + 1 << ": " << alleStoppesteder[i]->hentNavn();
        cout << setw(23 - alleStoppesteder[i]->hentNavn().size());
        if ((i+1) % 3 == 0)
            cout << "\n\t\t";
    }
}

/**
 * @brief Skriver alle data om spesifisert stoppested.
 *        Tar navn fra bruker, finner stopp med samme navn,
 *        henter naboenes indekser og skriver naboenes navn og reisetid.
 * 
 * @see Stoppesteder::entydigStoppested(...)
 * @see Stoppested::hentNavn();
 * @see Stoppested::hentNaboer();
 * @see Stoppested::skrivNabotid();
 */
void Stoppesteder::skrivAltOmStoppested() {
    string stopp;
    int stoppIndex;
    vector <int> naboStopp;
    cout << "Alt om stoppested :";
    getline(cin, stopp);
    stoppIndex = entydigStoppested(stopp);
    // Går gjennom alle stopp for å finne spesifisert stopp.
    if (stoppIndex < 1000) {
        cout << alleStoppesteder[stoppIndex]->hentNavn() << '\n';
        naboStopp = alleStoppesteder[stoppIndex]->hentNaboer();
            
        // Skriver ut alle tider for tilknyttede stopp.
        for (int i = 0; i < naboStopp.size(); i++) {
            alleStoppesteder[naboStopp[i]]->skrivNabotid(stoppIndex);
        }
    }
    else {
        cout << "Stoppested finnes ikke.\n";
    }
}

/**
 * @brief Ser hva brukeren vil gjøre.
 * 
 * @param valg  - Bokstav som sier hva bruker vil gjøre.
 * @see Stoppesteder::leggTilStopp()
 * @see Stoppesteder::skrivAlleStoppesteder()
 * @see Stoppesteder::SkrivAltOmStoppested()
 */
void Stoppesteder::handling(char valg) {
    switch (valg) {
    case 'N':  leggTilStopp();              break;
    case 'A':  skrivAlleStoppesteder();     break;
    case 'E':  skrivAltOmStoppested();      break;
    default:   cout<<"\nNoe gikk galt";     break;
    }
}
/**
* Sjekker om medsendt navn er en substring av et allerede registrert navn
* Hos et stoppested 
* 
* @param str1 - navnet som skal sjekkes om er en substring av et eksisterende
* @return Indeksen til stoppestedet med navnet som hadde en substring lik param
*/
int Stoppesteder::entydigStoppested(string str1) {
    string navn;
    string navn2 = toUpper(str1);
    int tmp = 0;
    int counter = 1;
    for (int i = 0; i < alleStoppesteder.size(); i++) {
        navn = toUpper(alleStoppesteder[i]->hentNavn());
        if (navn.find(navn2) != -1) { //find returnerer npos dersom ikke funnet
            counter++;                // substring og npos har verdi -1
            tmp = i;
        }            
    }
    if (counter == 2)
        return tmp;
    else return MAKSRUTENR+1;
}

/**
 * @brief Sjekker tilknytning til nabo. Hvis tilknytning ikke er funnet
 *        blir ny tilkobling registrert.
 * 
 * @see Stoppested::hentNabotid(...)
 * @see Stoppested::leggTilNabo(...)
 * @see lesInt(...)
 * @return Int som sier hvor langt det er til stoppested.
 */
int Stoppesteder::sjekkTilknytningEllerLeggTil(const int stopp1, 
                                                        const int stopp2) {
    
    int nabotid = alleStoppesteder[stopp1]->hentNabotid(stopp2);
    if (nabotid > 0) {
        cout << "\n\tTid mellom stopp allerede registrert som: " << nabotid
            << " minutter";
        return nabotid;
    }
    else {
        nabotid = lesInt("\n\tTid fra forrige stopp", 1, 10);
        alleStoppesteder[stopp1]->leggTilNabo(stopp2, nabotid);
        alleStoppesteder[stopp2]->leggTilNabo(stopp1, nabotid);
        return nabotid;
    }
}

/**
 * @brief Henter navn til indeks.
 *
 * @see Stoppested::hentNavn()
 * @return String med navnet til stoppestedet.
 */
string Stoppesteder::indeksTilNavn(const int indeks) {
    return alleStoppesteder[indeks]->hentNavn();
}
