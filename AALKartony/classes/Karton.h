/**
[AAL] projekt: "Kartony"
student:	   Volodymyr Ostruk
prowadzący:    Lukasz Skonieczny
Politechnika Warszawka, EiTI
*/

#ifndef _KARTON_
#define _KARTON_

#include <iostream>
#include <iomanip>
#include <algorithm>


class Karton {

    float dlugosc = 0.f;
    float szerokosc = 0.f;
    float wysokosc = 0.f;
    float objetosc = 0.f;

	// zrob dlugosc>=szerokosc>=wysokosc
	void uporzadkuj_boki();

	unsigned long staleID;
    // wyprowadzenie informacji o kartonie
    friend std::ostream & operator<< (std::ostream & output, Karton & k) {
        output << std::right << std::setw (6) << k.podajID() << "       | ";
        output << std::left << std::setw (10) << k.podajDlugosc () << " | ";
        output << std::left << std::setw (10) << k.podajSzerokosc () << " | ";        
        output << std::left << std::setw (10) << k.podajWysokosc () << " | ";
        output << std::left << std::setw (14) << k.podajObjetosc () << "|\n";

        return output;
    }

public:
	// zeby nadac ID wszystkim kartonom trzeba miec zmienna static
	static unsigned long STATIC_ID;

	~Karton();

	Karton(const float dlugosc, const float szerokosc, const float wysokosc);
	bool czySieZmiesci(Karton * wiekszyKarton);


	float podajSzerokosc();
	float podajWysokosc();
	float podajDlugosc();
	float podajObjetosc() const;
	unsigned long podajID();

};

#endif 

