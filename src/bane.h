#ifndef __BANE_H
#define __BANE_H

#include "rute.h"
#include <fstream>
#include <iostream>

class Bane : public Rute
{
  private:
    int antallVogner;    ///< Int for antall faste vogner som går på banen.
    int baneLengde;      ///< Int for lengden på banen.


  public:
    Bane();
    Bane(std::ifstream& inn);
    ~Bane();
    virtual void lesData();
    void skrivData();
    void skrivType() { std::cout << "Bane"; }
    virtual void skrivTilFil(std::ofstream& ut);
};

#endif // __BANE_H
