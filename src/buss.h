#ifndef __BUSS_H
#define __BUSS_H

#include "rute.h"
#include <fstream>
#include <iostream>

class Buss : public Rute
{
  private:
    int sittePlasser;     ///< Antall sitteplasser p� buss.
    int staPlasser;       ///< Antall st�plasser p� buss.
    bool alleLed;         ///< Er alle bussene p� denne ruten leddbuss?

  public:
    Buss();
    Buss(std::ifstream& inn);
    ~Buss();
    virtual void lesData();
    void skrivData();
    void skrivType() { std::cout << "Buss"; }
    virtual void skrivTilFil(std::ofstream& ut);
};

#endif // __BUSS_H
