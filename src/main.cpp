/**
* Program til å lage å se ruter til buss og bane
* Programmet skal:
*   - lese og skrive stoppesteder fra fil
*   - lese og skrive ruter fra fil
*   - legge til stoppesteder
*   - skrive ut alle stoppestedene
*   - skrive alt om et stoppested
*   - lage ny rute
*   - skrive ut alle rutene
*   - legge til nye stopp i midten av en rute
*   - slette stopp mellom to valgte stopp i en rute
*   - skrive beskrivelse av en rute
*   - skrive ut rutetabell av stopp på en rute
*
* @file main.cpp
* @author Aleksander Solhaug, Jan Olav Lyche Aspelund og Philip Alexander Sundt 
*/
#include <iostream>
#include <fstream>
#include "stoppesteder.h"
#include "ruter.h"
#include "funksjoner.h"
#include "LesData3.h"
using namespace std;
Stoppesteder gStoppestederBase;     ///<  Datastrukturen med ALLE Stoppestedene
Ruter gRuterBase;                   ///<  Datastrukturen med ALLE Rutene

    
/**
* Hovedprogrammet:
*/
int main()  {
  string input;
  vector <char> valg;
  gStoppestederBase.lesFraFil();
  gRuterBase.lesFraFil();
  skrivMeny();
  cout << "\nKommando: ";
  getline(cin, input);
  valg = splitToChars(input);

  while (valg[0] != 'Q') {
    switch(valg[0]) {
      case 'S':  gStoppestederBase.handling(valg[1]);   break;
      case 'R':  gRuterBase.handling(valg[1]);          break;
      default:   skrivMeny();                           break;
    }
    cout << "\nKommando: ";
    getline(cin, input);
    valg = splitToChars(input);
  }
  
  gStoppestederBase.skrivTilFil();
  gRuterBase.skrivTilFil();

  cout << "\n\n";
  return 0;
}
