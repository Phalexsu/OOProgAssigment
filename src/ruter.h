#ifndef __RUTER_H
#define __RUTER_H

#include <map>
#include "rute.h"
#include <string>


class Ruter {
  private:
    std::map <int, Rute*> alleRuter; ///< map med alle *unike nummererte* ruter.

  public:
    Ruter(){};
    ~Ruter();
    void nyRute();
    void endreRute();
    void skrivRuter(const bool alle, const bool endre, const bool omvendt);
    void lesFraFil();
    void skrivTilFil();
    void ruteTabell();
    void handling(char valg);
    int skjekkDuplikat(int ruteNR);
};

#endif // __RUTER_H
