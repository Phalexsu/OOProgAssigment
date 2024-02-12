#ifndef __FUNKSJONER_H
#define __FUNKSJONER_H
#include <fstream>
#include <string>
#include <vector>

/**
 * For diverse universelle funksjoner.
 */

void skrivMeny();
std::vector <char> splitToChars(const std::string str);
std::vector <std::string> splitString(const std::string str);
std::vector <int> lesTid(const std::string t, const int minTime, const int minMin,
                                              const int maxTime, const int maxMin);
std::string toUpper(std::string s);


#endif // __FUNKSJONER_H
