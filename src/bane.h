#ifndef __BANE_H
#define __BANE_H

#include "rute.h"
#include <fstream>
#include <iostream>

class Bane : public Rute
{
  private:
    int antallVogner;    ///< Int for antall faste vogner som g�r p� banen.
    int baneLengde;      ///< Int for lengden p� banen.


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
