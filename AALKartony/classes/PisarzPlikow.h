/**
[AAL] projekt: "Kartony"
student:	   Volodymyr Ostruk
prowadzący:    Lukasz Skonieczny
Politechnika Warszawka, EiTI
*/

#ifndef _PISARZPLIKOW_
#define _PISARZPLIKOW_

#include <iomanip>
#include <fstream>
#include <sstream>
#include <ctime>
#include "Upakowanie.h"


//   Klasa zapisuje dane wynikowe Upakowania

class PisarzPlikow {

	std::string nazwaPlikWynikowy = "wynik";

	template <typename Type>
	std::string sformatuj(const Type wartosc, const unsigned int szerokosc,
		const char fill = '0', const std::string separator = " | ",
		bool showPos = false, bool addPercentage = false);

public:
    PisarzPlikow () {
    };
    ~PisarzPlikow () {
    };

    //zapisuje upakowanie do pliku
    bool zapiszWynik (Upakowanie *,  bool standartowaNazwaPliku = true);

    //dla nadzoru wszystkich iteracji
    bool zapiszWynikSumaryczny (Upakowanie *);

    void ustawNazwe (const std::string);
	void zmienWzorzec(const std::string wzorzec, std::string wartosc, std::string & gdzie);
};

#endif

template <typename Type>
inline std::string PisarzPlikow::sformatuj (const Type wartosc, const unsigned int szerokosc, 
                                               const char czym, const std::string separator, 
                                               bool pokazPozycje, bool addPercentage) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision (3) << std::left << std::setw (szerokosc)
        << std::setfill (czym) << (pokazPozycje ? std::showpos : std::noshowpos)
        << wartosc << (addPercentage ? " %  " : "") << separator;

    return ss.str ();
}
