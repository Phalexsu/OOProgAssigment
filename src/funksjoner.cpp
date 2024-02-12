/**
* @file funskjoner.cpp
* 
* @author Aleksander Solhaug, Jan Olav Lyche Aspelund og Philip Alexander Sundt
*/
#include "funksjoner.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;
 /**
 * @brief Skriver valgalternativene til brukeren
 * 
 */
void skrivMeny() {
    cout << "\nDisse kommandoene kan brukes:\n"
        << "\tS  N - Lag nytt stoppested.\n"
        << "\tS  A - Skriv alle stoppesteder.\n"
        << "\tS  E - Skriv alt om ett stoppested.\n"
        << "\tR  N - Lag ny rute.\n"
        << "\tR  A - Skriv alle ruter.\n"
        << "\tR  E - Endre rute.\n"
        << "\tR  B - Vis rutebeskrivelse.\n"
        << "\tR  T - Rutetabell for ett stoppested.\n"
        << "\tQ - Quit / avslutt\n";
}

/**
 * @brief Splitter string opp i chars.
 * 
 * @param str  - String som skal splittes.
 * @return Vector med alle separerte bokstavene.
 */
vector <char> splitToChars(const string str) {
    vector <char> split;
    // Leser opp en og en char og legger dem i en vector. Mellomrom ignorert.
    for (const auto& val : str) {
        if (val != ' ') {
            split.push_back(val);
        }
    }
    // Gjør alle chars til uppercase.
    for (int i = 0; i < split.size(); i++)
        split[i] = toupper(split[i]);
    split.push_back(' ');
    split.push_back(' ');
    return split;
}

/**
 * Splitter string ut fra mellomrom eller ':'.
 *
 * @param str - Stringen som skal splittes.
 * @return vector <string> - Vector array med de splittede stringene.
 */
vector <string> splitString(const string str) {
    vector<string> split;
    string tmp = "";
    for (const char& val : str) {
        // Legger "opplest" del av string i vector om ' ' eller ':' er funnet.
        if (val == ':' || val == ' ') {
            split.push_back(tmp);
            tmp = "";
        }
        else
            // Legger en og en bokstav fra str til tmp via val.
            tmp += val;
    }
    split.push_back(tmp);
    return split;
}
/*
/**
 * Leser tid fra bruker (f.eks 10 30)
 * 
 * @param t - Tekst som blir skrevet for bruker.
 * @param minTime - Minste timen som kan skrives inn.
 * @param minMin - Minste minuttet som kan skrives inn.
 * @param maxTime - Høyeste time som kan leses inn.
 * @param maxMin - Høyeste minutt som kan leses inn.
 * @return vector <int> - Vector med tiden skrevet inn.
 *                        Time ligger i [0] og minutt ligger i [1].
 */

vector <int> lesTid(const string t, const int minTime, const int minMin,
                                    const int maxTime, const int maxMin) {
    string tmp; // Midlertidig lagring for brukerinput.
    vector <string> deltTmp; // Delt opp tekst fra bruker (mellomrom og :)
    vector <int>  tall; // Delt opp tall fra bruker.
    int handler; // Håndterer tall ett og ett.
    bool feil = false; // Om det er en feil i brukerinput.
    bool erTall = false; // Om brukerinput er tall.
    do {
        tall.clear();
        deltTmp.clear();
        erTall = true;
        feil = false;
        cout <<"\n" << t << "( " <<(minTime<10 ? "0" : "")<< minTime << ":"
             <<(minMin < 10 ? "0" : "")<<minMin<< " - " << maxTime << ":"
             << maxMin << " ): ";
           
        // Leser inn tid fra bruker før splitting.
        do {
            getline(cin, tmp);
        } while (tmp == "");
        deltTmp = splitString(tmp);
        // Splitter innlest tid og gjør dem til tall.
        for (auto val : deltTmp) {
            for (int i = 0; i < val.length(); i++)
            {
                // Sjekker om brukerinput er tall.
                if (!isdigit(val[i])) {
                    erTall = false;
                }
            }
            // Gjør om tekst (om det er rene tall) til tall.
            if (erTall) {
                handler = stoi(val);
                tall.push_back(handler);
            }
            else {
                feil = true;
                cout << "\nEn feil skjedde.";
            }
            
        }
        if (tall.size() < 2) {
            tall.push_back(0);
        }
        if (!feil) {
            // Sjekker om tiden er innenfor riktige grenser.
            if ((tall[0] < minTime || tall[0] > maxTime
                || (tall[0]==minTime && tall[1] < minMin) || tall[1] > maxMin)
                && (tall[0] != 0 || tall[1] != 0)) {
                feil = true;
                cout << "\nfeil";
            }

        }
    } while (feil);

    return tall;
}

/**
* @brief Gjør alle bokstaver i den medsendte stringen til stor bokstav
* 
* @param s - Den medsendte stringen
* 
* @return s - Medsendte stringen gjort om til store bokstaver
*/
string toUpper(string s) {
    for (int i = 0; i < s.size(); i++)  //for lengden til stringen
        s[i] = toupper(s[i]);           //gjør char til upper
    return s;
}

