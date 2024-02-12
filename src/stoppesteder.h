#ifndef __STOPPESTEDER_H
#define __STOPPESTEDER_H

#include "stoppested.h"
#include <vector>
#include "string"

class Stoppesteder
{
  private:
    std::vector <Stoppested*> alleStoppesteder;

  public:
    Stoppesteder(){};
    ~Stoppesteder();
    void lesFraFil();
    void skrivTilFil();
    void leggTilStopp();
    void skrivAlleStoppesteder();
    void skrivAltOmStoppested();
    void handling(char valg);
    int entydigStoppested(std::string str1);
    int sjekkTilknytningEllerLeggTil(const int stopp1, const int stopp2);
    std::string indeksTilNavn(const int indeks);
};

#endif // __STOPPESTEDER_H
