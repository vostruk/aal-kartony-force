/**
[AAL] projekt: "Kartony"
student:	   Volodymyr Ostruk
prowadzący:    Lukasz Skonieczny
Politechnika Warszawka, EiTI
*/
#include "UI.h"
#include <cmath>

using namespace std;
UI::UI(int argc, char* argv[]){
	
	//inicjalizacja mozliwych argumentow programu
	argWartLog["--stat"] = make_pair(false, "-s");
	argWartLog["-s"] = make_pair(false, "--stat");
	argWartLog["--help"] = make_pair(false, "-h");
	argWartLog["-h"] = make_pair(false, "--help");
	argWartTekst["--file"] = make_pair("", "-f");
	argWartTekst["-f"] = make_pair("", "--file");
	argWartTekst["--output"] = make_pair("", "-o");
	argWartTekst["-o"] = make_pair("", "--output");
	argWartTekst["--gentest"] = make_pair("", "--gentest");

	for (int i = 1; i < argc; ++i) {

		string parameter(argv[i]);

		if (argWartLog.find(parameter) != argWartLog.end() && argWartLog[parameter].first != true) {
			argWartLog[parameter].first = argWartLog[argWartLog[parameter].second].first = true;
		}
		else if (argWartTekst.find(parameter) != argWartTekst.end() &&
			i + 1 < argc &&
			argWartTekst[parameter].first == "") {
			string filename(argv[i + 1]);
			argWartTekst[parameter].first = argWartTekst[argWartTekst[parameter].second].first = filename;
			i++;
			continue;
		}
		else {
			argWartLog["--help"].first = true;
			argWartLog["-h"].first = true;
			break;
		}
	}
}

UI::~UI() {
};

void UI::tryb_statystyki(ostream& out){

	int iter;
	int recMax, recMin;
	std::stringstream ss;
	string s;
	cout << "Wybralesz tryb eksperymentow z pomiarami czasu!" << endl;
	cout << "Podaj maksymalny rozmiar problemu(max. 10000000) :";
	cin >> s;
	if (s.size() > 9 || s[0] <49 || s[0]>57){
		cout << "\nNiespelnione ograniczenia programu!"; return;
    }
	ss.str(s);
	ss >> recMax;
	if (recMax < 12000) recMax = 12000;
	cout << "\nPodaj ilosc instancji problemu(np. 12): ";
	ss.clear();
	cin >> s;
	if (s.size()>5 || s[0] <49 || s[0]>57){
		cout << "\nNiespelnione ograniczenia programu!!"; return;
	}
	ss.str(s);
	ss >>iter;
	recMin = 8000;
	vector<int> n;
	int k = 0;
	int val = (recMax-recMin) / iter;
	while(iter-->0) n.push_back(recMin+ ++k*val);

	vector<double> tn;
	vector<long double> qn;
	cout << "Prosze czekac, program opracowuje wynik .";
	for (auto i = n.begin(); i < n.end(); i++){
		upakowania.trybGeneracjiLosowej(*i, recMax/100, 3);
		cout << ".";
		upakowania.upakuj();
		tn.push_back(upakowania.podajCzasPakowania());
	}

	//przeliczenie oszacowania(ilosc akcji) na czas
	int mediana = n[(int) n.size() / 2];
	double tmed = (double) 10 * (tn[(int)n.size() / 2]);
	double Tmed = (((double)mediana/CLOCKS_PER_SEC)*mediana/ (double) 5000);
	long double c = tmed / Tmed;

	out << "\n\nAlgorytm z asymptota O(n^2) "<<"T: "<<Tmed<<" t: "<<tmed  << endl;
	out << "\n|========|================|=============|" << endl;
	  out << "|   N    |     t(n) [s]   |     q(n)    |" << endl;
	  out << "|========|================|=============|" << endl;
	
	auto i = n.begin();
	auto i2 = tn.begin();
	for (; i != n.end() && i2!=tn.end(); i++, i2++)
	{
		long double l = (long double)(*i2 * 10);
		long double m = ((long double)c*((*i /(double) CLOCKS_PER_SEC)*(*i)/ (double)5000));
		qn.push_back( l/m );
		out <<"| " <<setw(5) << *i << "  |  "<<setw(10) << *i2 << "    |  "<<setw(9) << qn.back()<<"  |" << endl;
	}
	out << "|========|================|=============|" << endl;
	out << "Uwaga: tabela moze byc malejaca dla wiekszych instancji problemu. Dla wyjasnienia prosze patrzec dokumentacje, rozdzial testowanie." << endl;
}


void UI::start () {

	if (argWartLog["--help"].first) {
        wypiszPomoc ();
        return;
    }
	if (argWartLog["--stat"].first){
		tryb_statystyki();
		return;
	}

    // Tryb 1
    if (wartosc_argumentu ("--file") != "") {
		if (wartosc_argumentu("--gentest") != "")
			cout << "Podalesz plik wejsciowy i zadasz generacji danych jednoczesnie! Generacja zostaje zignorowana!"<<endl;

		cout << "Wczytywanie danych o kartonach z pliku...\n";
		if (!this->wczytaj_dane()) return;
	
	}// Tryb 2
	else if (wartosc_argumentu ("--gentest") != "") {
		unsigned int tests = 0;
		std::stringstream ss;
		ss.str(wartosc_argumentu("--gentest"));
		ss >> tests;
        cout << "Generowanie danych o kartonach ...\n";
        if (tests > 0) this->upakowania.trybGeneracjiLosowej (tests, 100, 4);
        else {
			cout << "Blad: Ilosc testow nie moze byc mniejsza od 1!" << endl;
            return;
        }
	}
	else{
		wypiszPomoc();
		return;
	}

	cout << "Pakowanie danych..." << endl;
    upakowania.upakuj ();
	cout << "Zapisanie wynikow do pliku..." << endl;
    // Saving results
    std::string filename = wartosc_argumentu ("--output");
    if (filename != "") {
        mPisarzPlikow.ustawNazwe (filename);
        mPisarzPlikow.zapiszWynik (&upakowania,  false);
    }
    else
        mPisarzPlikow.zapiszWynik (&upakowania);

    // Saving global results
    mPisarzPlikow.zapiszWynikSumaryczny (&upakowania);
   
}

bool UI::wczytaj_dane () {
    std::string filename = wartosc_argumentu ("--file");
    if (filename != "") {
        Kartony newBoxes;
		if (!parsuj_dane(newBoxes, filename)) return false;
        upakowania.ustawKartony (newBoxes);
    }
    else {
		cout << "Blad: Nie podano nazwy pliku z danymi";
        return false;
    }

    return true;
}


bool UI::parsuj_dane(Kartony & kk, const string nazwaPlik) {
	std::ifstream inputFile;
	std::string content = "";
	std::stringstream ss;

	// Try to open file and read from it.

	inputFile.open(nazwaPlik, std::ios::in);
	if (!inputFile.is_open()) {
		std::cout << "Plik " + nazwaPlik + " nie istnieje lub nie moze byc otwarty!!\n";
		return false;
	}

	// kopijuje plik do zmiennej
	while (std::getline(inputFile, content)) {
		if (content[0] != '#' && content.find_first_not_of("\t\n ") != content.npos) {
			Karton * newBox = parsuj_wiersz(content);
			if (newBox != nullptr)
				kk.push_back(newBox);
			else {
				std::cout << "Blad:parsowanie pliku sie nie powiodlo! Nieprawidlowa struktura pliku!\n";
				return false;
			}
		}
	}


	inputFile.close();

	return true;
}

Karton * UI::parsuj_wiersz(const std::string & wiersz) {
	std::stringstream ss;
	ss.str(wiersz);
	float w, l, h;
	Karton * newBox = nullptr;

	try {
		ss >> l >> w >> h;
		newBox = new Karton(l, w, h);
		return newBox;
	}
	catch (...) {
		if (newBox != nullptr)
			delete newBox;
		return nullptr;
	}

	return nullptr;
}


void UI::wypiszPomoc() {
	cout << " >> Pomoc\n";
	cout << left;
	cout << "Program dla pakowania kartonow\n";
	cout << "Program umieszcza kartony wewnatrz innych dla oszczedzania miejsca.\n\n";
	cout << " >> Sposoby uruchamiania:\n";
	cout << left;
	int size = 35;
	cout << setw(size) << " -h | --help" << " : Wypisuje ten help.\n";
	cout << setw(size) << " -s | --stat" << " : Trybi eksperymentalny z wyprowadzeniem statystyki.\n";
	cout << setw(size) << " -f | --file[filename]" << " : Plik wejsciowy z danymi kartonow.\n";
	cout << setw(size) << " -o | --output[filename]" << " : Plik wyjsciowy dla wypisania wynikow programu.\n";
	cout << setw(size) << " --gentest [number_of_boxes]" << " : Tryb automatycznej generacji danych o kartonach.\n";
	cout << "\n >> Dla bardziej szczegolowych informacji prosze czytac plik 'readme.txt'\n";
}

string UI::wartosc_argumentu(const string k) {

	if (argWartTekst.find(k) != argWartTekst.end())
		return argWartTekst[k].first;
	else
		return "";
}
