/**
    [AAL] projekt: "Kartony"
    student:	   Volodymyr Ostruk
	prowadzący:    Lukasz Skonieczny
	Politechnika Warszawka, EiTI
    */

#include "Karton.h"

unsigned long Karton::STATIC_ID = 0;

bool Karton::czySieZmiesci (Karton * wiekszyKarton) {
    if (this->wysokosc < wiekszyKarton->wysokosc &&
        this->szerokosc < wiekszyKarton->szerokosc &&
        this->dlugosc < wiekszyKarton->dlugosc)
        return true;
    else
        return false;
}

Karton::Karton (const float d, const float sz, const float w)
    : szerokosc (sz), wysokosc (w), dlugosc (d),
    objetosc (sz * d * w), staleID (STATIC_ID++) {

    uporzadkuj_boki ();
}

Karton::~Karton() 
{
};
float Karton::podajSzerokosc () {
    return szerokosc;
}

float Karton::podajWysokosc () {
    return wysokosc;
}

float Karton::podajDlugosc () {
    return dlugosc;
}

float Karton::podajObjetosc () const {
    return objetosc;
}


unsigned long Karton::podajID () {
    return staleID;
}

void Karton::uporzadkuj_boki () {
    float sizes[3] = {dlugosc, szerokosc, wysokosc};
    std::sort (sizes, sizes + 3);
    wysokosc = sizes[0];
    szerokosc = sizes[1];
    dlugosc = sizes[2];
}

