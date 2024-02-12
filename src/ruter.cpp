/**
* @file ruter.cpp
* @author Aleksander Solhaug, Jan Olav Lyche Aspelund og Philip Alexander Sundt
*/
#include "ruter.h"
#include "rute.h"
#include "stoppested.h"
#include "stoppesteder.h"
#include "LesData3.h"
#include "bane.h"
#include "buss.h"
#include "iostream"
#include "iomanip"
#include "const.h"

using namespace std;
extern Stoppesteder gStoppestederBase;
/**
* @brief dekonstructor for Ruter
*/
Ruter::~Ruter()
{
    //Går gjennom alle rutene
    for (auto it = alleRuter.begin(); it != alleRuter.end(); it++) {
        delete (*it).second;            //sletter rute objektet         
    }
    alleRuter.clear();                  //fjerner alle map skuffene
}

/**
 * Lager ny rute
 * 
 * @see skjekkDuplikat(...), Rute::hentStorrelse()
 */
void Ruter::nyRute() {
    int ruteNr = 0;
    int counter = 0;                     //ruteNr spørres bare om dersom lik 0
    bool funn = false;                   //Om lignende ruteNr er registrert   
    char ruteType;
    bool duplikat = false;
   
    do {
        ruteNr = lesInt("\n\trutenr:", 1, 999);     //ønsket ruteNr
        if (skjekkDuplikat(ruteNr) != 0) {
            duplikat = true;
            cout << "\tDette ruteNummeret er allerede registrert for en"
                << "annen rute, vennligst tast inn et annet rutenummer";
        }
        else duplikat = false;
    //Dersom duplikat RuteNr, bruker må skrive inn ruteNr på nytt
    } while (duplikat == true);   
        
    do {
        ruteType = lesChar("\n\tRutetype((b)A(ne), (b)U(ss)): ");
    } while (ruteType != 'A' && ruteType != 'U');

    if (ruteType == 'A') {
        //NyRute med baneobjekt, kjører dens constructor
        Rute* nyRute = new Bane();       
        if (nyRute->hentStorrelse() >= 1) {
            //Dersom fler enn et stoppested legg inn den ny ruten
            alleRuter.insert(pair <int, Rute*>(ruteNr, nyRute));
        }
        else {
            cout << "\nRute slettet, må inneholde fler enn et stopp!";
            delete nyRute;
        }
    }
    else {                     //Samme som over bare med et bussobjekt isteden
        Rute* nyRute = new Buss();
        if (nyRute->hentStorrelse() >= 2)
            alleRuter.insert(pair <int, Rute*>(ruteNr, nyRute));
        else {
            cout << "\nRute slettet, må inneholde fler enn et stopp!";
            delete nyRute;
        }
    }
}



/**
 * Skriver enten delvis data om en rute (nr, type, og start slutt stopp)
 * Eller all data til en rute.
 * kjører også Rute::ruteEndre() hvis det ble valgt i menyen
 * 
 * @param alle  - Om delvis data om alle ruter skal skrives
 *                eller all data til en rute
 * @see skjekkDuplkat(...), Rute::skrivData(...), Rute::skrivDataOmvendt(...), 
 * Rute::ruteEndre(), Rute::SkrivType(), Bane/Buss::SkrivType(),
 * Rute::skrivStartSlutt() 
 */
void Ruter::skrivRuter(const bool alle, const bool endre,const bool omvendt) {
    int ruteNr = 0;
    int counter = 0;
    bool duplikat = true;

    if (alle == false) {               //Param alle 
        if (alleRuter.size() != 0) {   //Dersom ruter er registrert
            do {
                ruteNr = lesInt("\n\trutenr:", 1, 999); //Ønsket ruteNr
                if (skjekkDuplikat(ruteNr) == 0) {
                    duplikat = false;
                    cout << "\n\tIngen rute med innskrevet nummer!";
                }
                else {
                    alleRuter[ruteNr]->skrivData(); //Ønsket rute sin skrivData
                    cout << "\n\n\n\t";
                    if (omvendt)                    //I motsatt rekkefølge
                        alleRuter[ruteNr]->skrivDataOmvendt();
                    duplikat = true;
                }
            //Kjør på nytt Dersom det ikke fantes en rute med ønsket ruteNr
            } while (duplikat == false);
          
            if (endre)                          //dersom param endre == true
                alleRuter[ruteNr]->ruteEndre(); 
        }
        else cout << "\n\tIngen ruter er registrert";
    }
    else {
        if (alleRuter.size() != 0) {        //Dersom registrerte ruter
            cout << "\n\tFolgende ruter er registrert:";
            //Går gjennom alle rutene
            for (auto it = alleRuter.cbegin(); it != alleRuter.cend(); it++) {
                
                cout << "\n\t\t" << (*it).first << " ("; //(*it).first==ruteNr
                (*it).second->skrivType();               //'A' eller 'B'
                cout << "):\t";
                (*it).second->skrivStartSlutt();        //Start og sluttstopp
            }
        }
        else cout << "\n\tIngen registrerte ruter!";
    }
}

/**
* Leser ruter sin data til fil
* 
*/
void Ruter::lesFraFil() {

    int antallRuter = 0;
    int ruteNr = 0;
    int indeks = 0;
    char ruteType;

    ifstream innfil("RUTER.DTA");                   //Åpner filen som innfil

    if (innfil) {
        cout << "\nLeser fra RUTER.DTA...";
        innfil >> antallRuter;                     
        for (int i = 0; i < antallRuter; i++) {    //Antall ruter på filen
            innfil >> ruteNr;                      
            innfil >> ruteType;
          
            switch (ruteType) {                     
            case 'A': {                           //Dersom bane
                //Ny rute med Baneobjekt og kjører dens constructor
                Rute* nyBane = new Bane(innfil);
                //Legger inn ruten og dens nr i map
                alleRuter.insert(pair <int, Rute*>(ruteNr, nyBane));
                break;
            }
            //Samme som over men med buss objekt isteden
            case 'B': {
                Rute* nyBuss = new Buss(innfil);
                alleRuter.insert(pair <int, Rute*>(ruteNr, nyBuss));
                break;
            }
            }
            innfil.ignore();
        }
    }
    else cout << "\nKunne ikke lese fra RUTER.DTA";
}

/**
* Skriver alle rutenes datamedlemmer til fil 
* Altså nøkkelen som er rutenummeret og alle stoppestedene på denne ruten
* 
* @see Rute::skrivTilFil(...)
*/
void Ruter::skrivTilFil() {
    ofstream utfil("RUTER.DTA");                //Åpner filen som utfil

    if (utfil) {                                //Fikk åpnet filen
        cout << "\nSkriver til fil...";
        utfil << alleRuter.size()<<"\n";        //Antall ruter
                                                //Går gjennom alle rutene
        for (auto it = alleRuter.cbegin(); it != alleRuter.cend(); it++) {
            utfil << (*it).first << ' ';        //Rutens nummer
            (*it->second).skrivTilFil(utfil);   //Rute sin skrivTilFil
            cout<<"\n";
        }
    }
    else cout << "Kunne ikke skrive til fil RUTER.DTA!";
}

/**
* Starter prosessen med å skrive ut rutetabell for ruten bruker velger.
* 
* @see  lesInt(...)
*       skjekkDuplikat(...), Rute::skrivData(),
*       Stoppesteder::entydigStoppested(...), Rute::skrivAvganger(...)
*/
void Ruter::ruteTabell() {
    string stoppNavn;
    int ruteNr = lesInt("\n\trutenr:", 1, 999); //Ønsket ruteNr
    if (skjekkDuplikat(ruteNr) != 0) {
        alleRuter[ruteNr]->skrivData();  //Ønsket rute sin skrivData
        cout << "\n\n\t";
        cout << "Rutetabell for stoppestedet (navn): ";
        getline(cin, stoppNavn);
        int stoppIndeks = gStoppestederBase.entydigStoppested(stoppNavn);
        alleRuter[ruteNr]->skrivAvganger(stoppIndeks);
    }
    else {
        cout << "\nFinner ikke ruten.";
    }
}

/**
* Handlingene som er mulig for ruter sine funksjoner
* 
* @see NyRute(), skrivRuter(...), endreRute(), ruteTabell();
* @param valg - Bokstaven som bestemmer hvilken funksjon som kjøres
*/
void Ruter::handling(char valg) {           //kjører funksjon basert på param
    switch (valg) {
    case 'N':  nyRute();                        break;
    case 'A':  skrivRuter(true, false,false);   break;
    case 'E':  skrivRuter(false, true, false);  break;
    case 'B':  skrivRuter(false, false,true);   break;
    case 'T':  ruteTabell();                    break;
    default:   cout << "\nNoe gikk galt";       break;
    }
}

/**
* Sjekker om medsendt rute nr finnes i tilknytting til en annen rute fra før
* 
* @param ruteNR - det medsendte rute nummeret
* @return rute nummeret dersom det har tilknytting til en annen rute
*/
int Ruter::skjekkDuplikat(int ruteNR) {
    for (auto rute : alleRuter) {       //Går gjennom alle rutene
        if (rute.first == ruteNR) {     //Dersom ruteNR allerede er registrert
            return ruteNR;              
        }   
    }
    return 0;                          //Rute nummeret fantes ikke
}