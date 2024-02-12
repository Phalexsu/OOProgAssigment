/**
* @file rute.cpp
* @author Aleksander Solhaug, Jan Olav Lyche Aspelund og Philip Alexander Sundt
*/
#include "rute.h"
#include "stoppesteder.h"
#include <iostream>
#include "bane.h"
#include "buss.h"
#include "funksjoner.h"
#include "const.h"
#include <iomanip>
#include "LesData3.h"

using namespace std;
extern Stoppesteder gStoppestederBase;
/**
 * @brief Constructor for Rute.
 * 
 * @param innfil  - Filobjekt som leser fra fil.
 */
Rute::Rute(ifstream& innfil) {
    int antallStopp;                            //antall stopp på ruten
    innfil >> antallStopp;
    for (int i = 0; i < antallStopp; i++) {     //For antall stopp på ruten
        Stopp* nyttStopp = new Stopp;           //Oppretter nytt stopp
        innfil >> nyttStopp->indeks >>nyttStopp->minFraForrige;//Stopp sin data
        stopp.push_back(nyttStopp);       //Legger stoppet bakertst i vektoren
    }
}

/**
* @brief Destructor, sletter ruten sin liste med stopp
*/
Rute::~Rute(){
    while (!stopp.empty()) {  //så lenge listen ikke er tom
        delete stopp.back();  //sletter siste tilpetkte stoppet
        stopp.pop_back();     //fjerner den siste pekeren
    }
    //Samme som over
    
    while (!allePerioder.empty()) {
        delete allePerioder.back();
        allePerioder.pop_back();
    }
}

/**
* @brief Skriver dataemedlemmene til ruten
* 
* @see Stoppesteder::indektsTilNavn(...)
*/
void Rute::skrivData() {

    int totMin = 0;
    cout << "\n\tRute:";
    for (const auto& val : stopp) { //val blir et stopp for hver iterasjon
                                    //går gjennom alle stoppene i stopp
        totMin += val->minFraForrige;
        cout << "\n\t\t" << gStoppestederBase.indeksTilNavn(val->indeks)
            << setw(15 - gStoppestederBase.indeksTilNavn(val->indeks).size());
        cout << "- " << val->minFraForrige;
        if (val->minFraForrige != 0) {      //Ikke første stopp på ruten
            cout << " min fra forrige" << (totMin > 9 ? " (" : " ( ") << totMin
            //Dersom tot min er minder er 10 legg til en null foran
                << " min fra rutestart)";
        }
    }
}
/**
* @bries Skriver rutens data i motsatt rekkefølge 
*        altså hvis fra endestopp til start
* 
* @see Stoppesteder::indeksTilNavn(...)
*/
void Rute::skrivDataOmvendt() {
    int totMin = 0;
    int counter = 0;
    int forrigeMin = 0;
    cout << "\n\tRute:";
    stopp.reverse();                //Reverserer rekkefølgen på lista
    for (const auto& val : stopp) { //går igjennom listen likt som over
        totMin += forrigeMin;
        cout << "\n\t\t" << gStoppestederBase.indeksTilNavn(val->indeks)
            << setw(15 - gStoppestederBase.indeksTilNavn(val->indeks).size());
        cout << "- " << forrigeMin;
        counter++;
        if (forrigeMin != 0 && counter != 1) {  //Ikke første stoppested 
            cout << " min fra forrige" << (totMin > 9 ? " (" : " ( ") << totMin
            //Dersom totMin mindre enn 10 legg til '0'
                << " min fra rutestart)";
        }
        forrigeMin = val->minFraForrige;   
        //Må ha forrige stoppestedet sin minFraforrige siden listen er reversert
    }
    stopp.reverse();               //Reverserer lista tilbake til normalen

}

/**
* @brief Leser data for ny rute fra bruker.
*
* @see sjekkRuteDuplikat(...)
* @see Stoppesteder::entydigStoppested(...)
* @see Stoppesteder::indeksTilNavn(...)
* @see Stoppesteder::sjekkTilknyttingEllerLeggTil(...)
*/
void Rute::lesData() {
    string navn = "tmp";
    int antStopp = 0;
    int indeksForrige = 0;
    
while (!navn.empty()) {
    cout << "\n\tStoppested (entydig navn / tall / ENTER): ";
    getline(cin, navn);

    if (sjekkRuteDuplikat(navn)==true)           //Dersom navn finnes på ruten
        cout << "\n\tStoppet finnes allerede på ruten!";
    
    else if (gStoppestederBase.entydigStoppested(navn) != MAKSRUTENR + 1 ||
                                                    (isdigit(navn[0]) != 0)) {
    //Dersom funnnet det entydige navnet, eller bruker skrev inn et tall
        Stopp* nyttStopp = new Stopp;               //Oppretter et nytt stopp
        if (isdigit(navn[0]) != 0)                  //Dersom bruker skrev tall
            nyttStopp->indeks = stoi(navn)-1;         //string med tall til int 

        else                                       //Dersom navn skrevet inn
            nyttStopp->indeks = gStoppestederBase.entydigStoppested(navn);
        //sjekker om navn = entydig og returner indeks til det entydige stoppet
        
        cout << "\n\tStoppested: "             //Kviterer med funnet stoppested
             << gStoppestederBase.indeksTilNavn(nyttStopp->indeks);
        if (antStopp != 0) {                   //Dersom ikke start stopp
            nyttStopp->minFraForrige =
                                gStoppestederBase.sjekkTilknytningEllerLeggTil
                                            (indeksForrige, nyttStopp->indeks);
          //legger inn tiden fra forrige stoppested
        }
        else nyttStopp->minFraForrige = 0;    //Dersom start stopp
        indeksForrige = nyttStopp->indeks;
        stopp.push_back(nyttStopp);           
        }
    else if (!navn.empty()) {                //Ikke "Enter" og ikke entydig
        cout << "\n\t\tIkke funnet (det entydige) stoppestedet!";
        antStopp--;
    }
    antStopp++;
}
    if(stopp.size()>1)                      //Fler enn et stopp på ruten
        cout << "\n\tNy rute er lagt inn!";
}

/**
* @brief Skriver startstoppet og sluttstoppet på ruten
* 
* @see Stoppesteder::indeksTilNavn(...)
*/
void Rute::skrivStartSlutt() {
    cout << gStoppestederBase.indeksTilNavn(stopp.front()->indeks)
        << " - " << gStoppestederBase.indeksTilNavn(stopp.back()->indeks);
}

/**
* @brief Henter søtrrelsen til ruten
* 
* @return int - Størrelsen til ruten
*/
int Rute::hentStorrelse() {
    return stopp.size();
}

/**
 * @brief Skriver data om ruten til fil.
 * 
 * @param ut - filen det skrives til
 */
void Rute::skrivTilFil(ofstream & ut) {
    ut << stopp.size()<<' ';
    for (Stopp* val : stopp)           //Går gjennom alle stoppene
        ut << val->indeks<<' '<<val->minFraForrige<<' ';    
                                       //Skriver stoppets datamedlemmer til fil  
}

/**
* @brief Sjekker om medsendt stoppenavn finnes på ruten fra før
* 
* @param s1 - medsendt navn på stoppet
* 
* @see Stoppesteder::entydigStoppested(...)
* @see Stoppesteder::indeksTilNavn(...)
* @see toUpper(...)
* @return bool - om stoppet fantes på ruten eller ikke
*/
bool Rute::sjekkRuteDuplikat(string s1) {
    int ruteNrS1 = 0;
    if (gStoppestederBase.entydigStoppested(s1) != MAKSRUTENR + 1)
        ruteNrS1 = gStoppestederBase.entydigStoppested(s1);
    else return false;
    string s2 = " ";
    for (Stopp* val : stopp) {
        s2 = gStoppestederBase.indeksTilNavn(val->indeks);
        s1 = gStoppestederBase.indeksTilNavn(ruteNrS1);
        toUpper(s2); toUpper(s1);
        if (s2 == s1)
            return true;
    }
    return false;
}
/**
* @brief velger hvilke stopp du skal endre på og om du skal slette eller legge
*         til stopp
* @see  skjekkeDuplikat(...)
* @see  Stoppesteder::entydigStoppested(...)
* @see  Stoppesteder::indeksTilNavn(...)
* @see  ruteSmettInn(...)
* @see  skrivData()
* @see  slettStopp(...)
*/
void Rute::ruteEndre(){
    char valg;
    string forste;
    string andre;
    int indeksForste;
    int indeksAndre;
    int i;
    int counter;
    do {                //looper til 'S' eller 'L' er valgt
        valg = lesChar("\nVil du slette eller legge inn stoppesteder?(S,L)");
    } while (valg != 'S' && valg != 'L');
    cout << "\nMellom hvilke stopp skal du gjøre det? ";
    do {                //looper hvis andre stopp kommer etter første
        do {            //looper hvis stoppet ikke finnes
            cout << "\nFørste:";
            getline(cin, forste);
        } while (!sjekkRuteDuplikat(forste));
        indeksForste = gStoppestederBase.entydigStoppested(forste);
        cout << "\n\tStoppested: " << "\n\t"   //Kviterer med funnet stoppested
            << gStoppestederBase.indeksTilNavn(indeksForste);
        i = 0;
        counter = 0;
        //endrer indeksen fra å være indeks i alleStoppesteder til indeks i stopp
        for (Stopp* stp : stopp) {  
            if (indeksForste == stp->indeks && counter == 0) {
                indeksForste = i;
                counter++;
            }
            i++;
        }
        do {            //looper hvis stoppet ikke finnes
            cout << "\nAndre:";
            getline(cin, andre);
        } while (!sjekkRuteDuplikat(andre));
        indeksAndre = gStoppestederBase.entydigStoppested(andre);
        if (indeksAndre <= indeksForste) {
            cout << "\nSkjekk om du har skrevet samme stopp to ganger,"
                 <<"hvis ikke så må stoppene reverseres for å gå videre.";
        }
    } while (indeksAndre <= indeksForste);
    cout << "\n\tStoppested: " << "\n\t"   //Kviterer med funnet stoppested
        << gStoppestederBase.indeksTilNavn(indeksAndre);
    i = 0;
    counter = 0;
    //endrer indeksen fra å være indeks i alleStoppesteder til indeks i stopp
    for (Stopp* stp : stopp) {
        if (indeksAndre == stp->indeks && counter == 0) {
            indeksAndre = i;
            counter++;
        }           
        i++;
    }

    switch (valg) {
    case 'L': {
        //får bare lov til å kjøre hvis det ikke er stopp imellom
        if (indeksAndre == indeksForste + 1) {  
            ruteSmettInn(indeksForste, indeksAndre);
        }
        else {
            cout << "\nStoppene er ikke ved siden av hverandre";
        }
        skrivData();
        break; 
    }
    case 'S': slettStopp(indeksForste, indeksAndre); skrivData();   break;
    default: cout << "\nNoe gikk galt";                             break;
    }

}
/**
* @brief legger til stopp mellom to valgte stopp
* @param forste - forste stoppested sin indeks i stopp listen
*        andre  - andre stoppested sin indeks i stopp listen
* @see  skjekkDuplikat(...)
* @see  Stoppesteder::entydigStoppested(...)
* @see  Stoppesteder::indeksTilNavn(...)
* @see  Stoppesteder::sjekkTilknytningEllerLeggTil(...)
*/
void Rute::ruteSmettInn(int forste,int andre) {
    cout << "\nNavn på stopp som skal smettes inn";
    string navn = "tmp";
    int stoppsize = stopp.size();
    int antStopp = stopp.size();
    int indeksForrige = forste;
    list<Stopp*>::iterator it = stopp.begin();
    advance(it, forste+1);

    while (!navn.empty()) {
        cout << "\n\tStoppested (entydig navn / tall / ENTER): ";
        getline(cin, navn);

        if (sjekkRuteDuplikat(navn) == true)           //Dersom navn finnes på ruten
            cout << "\n\tStoppet finnes allerede på ruten!";

        else if (gStoppestederBase.entydigStoppested(navn) != MAKSRUTENR + 1 ||
            (isdigit(navn[0]) != 0)) {
            //Dersom funnnet det entydige navnet, eller bruker skrev inn et tall
            Stopp* nyttStopp = new Stopp;               //Oppretter et nytt stopp
            if (isdigit(navn[0]) != 0) {                //Dersom bruker skrev tall
                nyttStopp->indeks = stoi(navn);         //string med tall til int    
            }
            else {                                     //Dersom navn skrevet inn
                //sjekker om navn = entydig og returner indeks til det entydige stoppet
                nyttStopp->indeks = gStoppestederBase.entydigStoppested(navn);

            }
            cout << "\n\tStoppested: " << "\n\t"   //Kviterer med funnet stoppested
                << gStoppestederBase.indeksTilNavn(nyttStopp->indeks);
            if (antStopp != 0) {                   //Dersom ikke start stopp
                //legger inn tiden fra forrige stoppested
                nyttStopp->minFraForrige =
                    gStoppestederBase.sjekkTilknytningEllerLeggTil
                    (indeksForrige, nyttStopp->indeks);
                
            }
            else nyttStopp->minFraForrige = 0;    //Dersom start stopp
            indeksForrige = nyttStopp->indeks;
            
            stopp.insert(it, nyttStopp);
        }
        else if (!navn.empty()) {                //Ikke "Enter" og ikke entydig
            cout << "\n\t\tIkke funnet (det entydige) stoppestedet!";
            antStopp--;
        }
        antStopp++;
    }
    cout << "\nSluttstopp i endringen: "
        <<gStoppestederBase.indeksTilNavn((*it)->indeks);
    //oppdaterer tid mellom siste lagt inn stopp og andre stopp som ble valgt
    (*it)->minFraForrige =
        gStoppestederBase.sjekkTilknytningEllerLeggTil
        (indeksForrige, (*it)->indeks);
}
/**
* @brief sletter alle stopp mellom de to valgte stoppene
* @param forste - forste stoppested sin indeks i stopp listen
*        andre  - andre stoppested sin indeks i stopp listen
* @see   Stoppesteder::indeksTilNavn(...)
* @see   Stoppesteder::sjekkTilknytningEllerLeggTil(...)
*/
void Rute::slettStopp(int forste, int andre) {
    list<Stopp*>::iterator it1 = stopp.begin();
    list<Stopp*>::iterator it2 = stopp.begin();
    advance(it1, forste+1);
    advance(it2, andre);
    if (it1 != it2) {
        stopp.erase(it1, it2);
        it2 = stopp.begin();
        advance(it2, forste+1);
        it1 = stopp.begin();
        advance(it1, forste);
        cout << "\nSluttstopp i endringen: "
            << gStoppestederBase.indeksTilNavn((*it2)->indeks);
        //oppdaterer tid mellom siste lagt inn stopp og andre stopp som ble valgt
        (*it2)->minFraForrige =
            gStoppestederBase.sjekkTilknytningEllerLeggTil
            ((*it1)->indeks, (*it2)->indeks);
    }  
}

/**
 * @brief Leser avgangstider fra bruker.
 * @see Stoppesteder::indeksTilNavn(...)
 */
void Rute::leggTilAvganger() {
    int minTime = 00, minMin = 01,
        maxTime = 23, maxMin = 59;
    vector <int> tider;
    cout << "\nRuteavganger fra: " 
         << gStoppestederBase.indeksTilNavn(stopp.front()->indeks)
         <<"\nSkriv '0' for å slutte å legge inn perioder";
    do {
        // Leser starttiden for periode.
        tider = lesTid("Fra kl. ", minTime, minMin, maxTime, maxMin);
        if (tider[0] != 0 || tider[1] != 0) {
            Periode* periode = new Periode;
            periode->startTime = tider[0]; // Lagrer starttid.
            periode->startMin = tider[1];
            minTime = tider[0]; // Øker minimumstid for innlesing.
            minMin = tider[1];
            // Leser og lagrer avganger pr min.
            tider[0] = lesInt("Tid mellom avganger", 6, 120);
            periode->minPerAvgang = tider[0];  
            // Leser sluttid for periode.
            tider = lesTid("Til kl.", minTime, minMin, maxTime, maxMin);
            if (tider[0] != 0 || tider[1] != 0) {
                // Lagrer sluttid for periode.
                periode->sluttTime = tider[0];
                periode->sluttMin = tider[1];
                minTime = tider[0]; // Øker minimumstid for innlesing.
                minMin = tider[1];
                
                allePerioder.push_back(periode);
            }
        }
    } while ((tider[0] != 0 || tider[1] != 0)
          && (tider[0] != 23 || tider[1] != 59));
}

/**
 * @brief Skriver ut alle avgangstider i en tabell.
 * @see leggTilAvganger()
 */
void Rute::skrivAvganger(const int stoppIndeks) {
    int teller = 0;  // Teller opp minuttene;
    int klokkeslett = 0;  // Teller opp timene
    int stoppDiffMin = 0;  // Differansen mellom rute start og når stoppet er nådd.
    int stoppDiffTime = 0; // Differanse i timer mellom start og spesifisert stopp.
    bool stoppFor = false; // Sier når stoppDiffMin skal slutte å telles.
    bool nyttKlokkeslett = true; // Sier om nytt klokkeslett skal skrives.
    Periode* forrigePeriode = new Periode;
    forrigePeriode->sluttTime = 24;

    if (allePerioder.size() == 0) {
        leggTilAvganger();
    }
    // Teller opp stoppdifferansen i min.
    for (Stopp* stp : stopp) {
        if (!stoppFor)
            stoppDiffMin += stp->minFraForrige;
        if (stoppIndeks == stp->indeks)
            stoppFor = true;
    }
    for (Periode*& val : allePerioder) {
        // Teller opp differansen.       
        teller = val->startMin + stoppDiffMin;
        while (teller > 60) {
            teller -= 60;
            stoppDiffTime++;
        }
        klokkeslett = val->startTime + stoppDiffTime;
        // Sjekker om tabellen skal fortsette på samme klokkeslett.
        if (val->startTime == forrigePeriode->sluttTime) {
            nyttKlokkeslett = false;
        }
        // Skriver ut avgangs/ankommelsestider for en 'periode' (se struct).
        while ((klokkeslett < (val->sluttTime + stoppDiffTime + 1)
            && (teller < 60 && teller >= 00)) && klokkeslett < 24) {
            if ((klokkeslett < (val->sluttTime + stoppDiffTime)
                || teller <= (val->sluttMin+stoppDiffMin)) && nyttKlokkeslett){
                cout << "\n" << (klokkeslett < 10 ? "0" : "")
                    << klokkeslett << ":";
                nyttKlokkeslett = false;
            }
            while (teller < 60) { // Skriver ut avganger for hver time.
                if (klokkeslett != (val->sluttTime + stoppDiffTime)
                    || teller <= (val->sluttMin + stoppDiffMin)) {
                    cout << setw(4) << teller;
                }
                teller += val->minPerAvgang;
            }
            teller -= 60;
            klokkeslett++;
            nyttKlokkeslett = true;
        }
        forrigePeriode = val;
    }
}
