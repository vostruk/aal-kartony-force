/**
[AAL] projekt: "Kartony"
student:	   Volodymyr Ostruk
prowadzący:    Lukasz Skonieczny
Politechnika Warszawka, EiTI
*/

#ifndef _UPAKOWANIE_
#define _UPAKOWANIE_

#include <algorithm>
#include <vector>
#include <iostream>
#include <sstream>
#include "Karton.h"

using namespace std;
typedef vector<Karton*> Kartony;  //uporzadkowany zbior kartonow

//klasa do utrzymywania struktur kartonów
class Upakowanie {

	Kartony wszystkieKartony;
	vector<Kartony> stosyKartonow; //kartony rozmieszczone w poszczegolne stosy

	double czasPakowania = 0.f;				//dla uznania ile czasu zajelo pakowanie kartonów
	float objetoscWszystkich = 0.f;

	void usunKartony();					//usuwa wszystkie kartony

public:
	Upakowanie();
	Upakowanie(Kartony);

	~Upakowanie();
    
    void upakuj ();

    string podajWszystkieUpakowania ();

    float podajObjetoscPoUpakowaniu ();
    unsigned int podajIloscStosow ();           //ilosc upakowan(stosow)
    double podajCzasPakowania ();		         //zuzyty czas na stosyKartonow


	void trybGeneracjiLosowej(unsigned long ilosc, unsigned int maxRozmiar = 1, unsigned int dokladnoscPoPrzecinku = 2);
	Kartony * podajWszystkieKartony(); 
	float podajObjetoscWszystkich();  //bez pakowania

	void ustawKartony(Kartony &); 
};

#endif

