#ifndef __RUTE_H
#define __RUTE_H
#include "stoppested.h" 
#include <list>
#include <vector>
#include <fstream>
#include <string>


class Rute
{
  private:
    struct Stopp {
        int indeks;                      ///< Indeks for hvert stoppested
        int minFraForrige;               ///< Minutter fra forrige stopp
    };
    struct Periode {
        int startTime, startMin,      ///< Starttid for hver periode
            sluttTime, sluttMin;      ///< Sluttid for hver periode
        int minPerAvgang;             ///< Hvor mange minutter mellom avganger
    };
    std::list <Stopp*> stopp;             ///< Alle stoppestedene på ruta
    std::vector <Periode*> allePerioder;      ///< Alle perioder med avgangstider

  public:
    Rute(){};
    Rute(std::ifstream& innfil);
    ~Rute();
    virtual void skrivTilFil(std::ofstream & ut);
    virtual void lesData();
    virtual void skrivData();
    virtual void skrivType() {};
    void skrivDataOmvendt();
    void skrivStartSlutt();
    int hentStorrelse();
    bool sjekkRuteDuplikat(std::string s1);
    void ruteEndre();
    void ruteSmettInn(int forste, int andre);
    void slettStopp(int forste, int andre);
    void leggTilAvganger();
    void skrivAvganger(const int stoppIndeks);
};

#endif // __RUTE_H
