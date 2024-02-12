#ifndef __STOPPESTED_H
#define __STOPPESTED_H

#include <fstream>
#include <string>
#include <vector>

class Stoppested
{
  private:
    std::string navn;
    std::vector <int> naboStopp;    ///< Indeks/nummer for "alle" nabostopp.
    std::vector <int> minTilNabo;   ///< Antall minutter til hvert nabostopp.

  public:
    Stoppested();
    Stoppested(std::string navn2) { navn = navn2; }
    ~Stoppested(){};
    void lesFraFil(std::ifstream & inn);
    void skrivTilFil(std::ofstream & ut);
    void leggTilNabo(const int nyNabo, const int min);
    bool sjekkDuplikat(const std::string nyttNavn);
    void lagreNavn(const std::string nyttNavn);
    int hentNabotid(const int nabo);
    void skrivNabotid(const int nabo);
    std::vector <int> hentNaboer();
    std::string hentNavn();
    
};

#endif // __STOPPESTED_H
