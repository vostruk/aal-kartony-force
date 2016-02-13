/**
[AAL] projekt: "Kartony"
student:	   Volodymyr Ostruk
prowadzący:    Lukasz Skonieczny
Politechnika Warszawka, EiTI
*/

#include "Upakowanie.h"

Upakowanie::Upakowanie(){}
Upakowanie::Upakowanie (Kartony kk) :wszystkieKartony (kk){}
Upakowanie::~Upakowanie(){
	usunKartony();
}

static clock_t czasStop = 0;
static clock_t czasStart = 0;

void Upakowanie::upakuj () {
   
	czasStart = clock();
	//ETAP 1: sortowanie Kartonow wedlug objetosci. Zlozonosc nlogn
	std::sort(wszystkieKartony.begin(), wszystkieKartony.end(),
		[](const Karton * k1, const Karton * k2) -> bool {
		return k1->podajObjetosc() > k2->podajObjetosc();
	});
    
	//ETAP 2: pakowanie Kartonow jeden wewnatrz drugiego - wypelnienie stosow kartonow. Zlozonosc n*n
	if (wszystkieKartony.size() > 1) 
	for (Karton * k : wszystkieKartony) {
		bool juzWstawiony = false;
		cout << "K: " << k->podajID() << endl;
		if (stosyKartonow.size() == 0) {     //wstawianie pierwszego stosu
			Kartony kstos;
			kstos.push_back(k);
			stosyKartonow.push_back(kstos);
		}
		else{
			auto stack = stosyKartonow.end();
				for (--stack; ; stack-- ) { //dla kazdego stosu sprawdz czy mozna umiescic na gorze stosu z najmniejszym elementem
				if (stack->size() != 0 && k->czySieZmiesci((*stack)[stack->size() - 1])) { //sprawdz czy jest wiekszy
					stack->push_back(k);
					juzWstawiony = true;
					break;
				}
				if (stack == stosyKartonow.begin()) break;
			}
			if (!juzWstawiony) {  //stworz nowy stos z jednym kartonem
				Kartony stack;
				stack.push_back(k);
				stosyKartonow.push_back(stack);
			}
		}
	}
	czasStop = clock();
	czasPakowania = ((double)(czasStop - czasStart)) / (double)CLOCKS_PER_SEC;
}


std::string Upakowanie::podajWszystkieUpakowania () {
    std::string out = "";
    unsigned int stNr = 0;
    for (Kartony & s : stosyKartonow) {
        out += "                          Upakowanie " + std::to_string (stNr) + "\n";
        out += "---------------------------------------------------------------------\n";
        for (Karton * k : s) {
            std::stringstream ss;
            ss << *k;
            out += ss.str ();
        }
        ++stNr;
        out += "\n";
    }

    return out;
}


float Upakowanie::podajObjetoscPoUpakowaniu () {
    float sum = 0.f;
    for (Kartony & s : stosyKartonow)
        sum += s[0]->podajObjetosc ();

    return sum;
}

unsigned int Upakowanie::podajIloscStosow () {
    return stosyKartonow.size ();
}

double Upakowanie::podajCzasPakowania () {
    return czasPakowania;
}


void Upakowanie::trybGeneracjiLosowej(unsigned long ilosc, unsigned int max, unsigned int dokladnosc) {
	// wyczyść to co bylo
	usunKartony();
	stosyKartonow.clear();
	// generuj
	for (unsigned long i = 0; i < ilosc; ++i) {
		long randomValue = static_cast<long>( max * std::pow(10, dokladnosc));
		float l, w, h;
		l = (float)(rand() % randomValue);
		l /= (float)std::pow(10, dokladnosc);
		w = (float)(rand() % randomValue);
		w /= (float)std::pow(10, dokladnosc);
		h = (float)(rand() % randomValue);
		h /= (float)std::pow(10, dokladnosc);
		wszystkieKartony.push_back(new Karton(l, w, h));
		objetoscWszystkich += l * h * w;
	}
}

Kartony * Upakowanie::podajWszystkieKartony() {
	return &wszystkieKartony;
}


float Upakowanie::podajObjetoscWszystkich() {
	return objetoscWszystkich;
}

void Upakowanie::ustawKartony(Kartony & kk) {
	this->wszystkieKartony = kk;
	for (Karton * k : wszystkieKartony)
		objetoscWszystkich += k->podajObjetosc();
}


void Upakowanie::usunKartony() {
	// Clear container if not empty.
	if (wszystkieKartony.size() != 0) {
		for (Karton * k : wszystkieKartony)
			delete k;
		wszystkieKartony.clear();
	}
}
