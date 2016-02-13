/**
[AAL] projekt: "Kartony"
student:	   Volodymyr Ostruk
prowadzący:    Lukasz Skonieczny
Politechnika Warszawka, EiTI
*/
#ifndef _UI_
#define _UI_

#include <iostream>
#include <map>
#include "PisarzPlikow.h"
#include "Upakowanie.h"


//Klasa glownego programu(interfejsu)
class UI {
 

    PisarzPlikow mPisarzPlikow;
	Upakowanie upakowania;


	std::map <std::string, std::pair<bool, std::string>> argWartLog; //-h lub -s
	std::map <std::string, std::pair<std::string, std::string>> argWartTekst; //cmd argumenty

	bool wczytaj_dane();
	bool parsuj_dane(Kartony &, const string filename);
	Karton * parsuj_wiersz(const std::string & row);
	void tryb_statystyki(std::ostream& out = std::cout);

public:
	UI(int argc, char* argv[]);
	~UI();
	
	void start();   //zaczyna funkcje glowna

	void wypiszPomoc();
	std::string wartosc_argumentu(const std::string key);
};

#endif

