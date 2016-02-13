/**
[AAL] projekt: "Kartony"
student:	   Volodymyr Ostruk
prowadzący:    Lukasz Skonieczny
Politechnika Warszawka, EiTI
*/

#include "PisarzPlikow.h"

bool PisarzPlikow::zapiszWynik (Upakowanie * up, bool czyStandartowaNazwa) {
    std::fstream output;
    std::ifstream templateFile;
	std::string resultsPath = nazwaPlikWynikowy, templateContent = "", currentDateTime = "";
    std::stringstream ss;

    
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime (buffer, 80, "_%d-%m-%Y_%H-%M-%S", timeinfo);
    std::string str (buffer);
    currentDateTime = str;

	if (czyStandartowaNazwa) {
        resultsPath =  resultsPath + currentDateTime + ".txt";
        currentDateTime = currentDateTime.substr (1, (size_t)currentDateTime.size () - 2);
    }


	templateContent = "### PLIK WYNIKOWY Z UPAKOWANIAMI KARTONOW ###\n# DATA WYGENEROWANIA        				   :  $date\n# ILOSC WSZYSTKICH KARTONOW PRZED PAKOWANIEM   :  $records\n# CZAS PAKOWANIA               				   :  $time [sec]\n";
	templateContent += "# ILOSC PACZEK KARTONOW        				   :  $stacks\n# CALKOWITA ZAJETA OBJĘTOŚĆ PO UPAKOWANIU      :  $volume\n# ZAOSZCZĘDZONO MIEJSCA W POROWNANIU Z PRZED   :  $profit %\n\n";
	templateContent +="UPAKOWANIA KARTONOW\n=====================================================================\n ID          | DLUGOŚĆ    | SZEROKOŚĆ  | WYSOKOŚĆ   | OBJĘTOŚĆ      |\n";
	templateContent += "=====================================================================\n$rows\n";

    output.open (resultsPath, std::ios::out | std::ios::trunc);
    if (!output.is_open ()) {
		std::cout << "Blad: Saving results to file failed!(file: " + resultsPath + ")";
        return false;
    }

    zmienWzorzec ("$date", currentDateTime, templateContent);
    zmienWzorzec ("$records", std::to_string (up->podajWszystkieKartony ()->size ()), templateContent);
    zmienWzorzec ("$time", std::to_string (up->podajCzasPakowania ()), templateContent);
    zmienWzorzec ("$stacks", std::to_string (up->podajIloscStosow ()), templateContent);
    zmienWzorzec ("$volume", std::to_string (up->podajObjetoscPoUpakowaniu ()), templateContent);
    zmienWzorzec ("$profit", std::to_string (std::abs(100.f - up->podajObjetoscPoUpakowaniu () * 100.f / up->podajObjetoscWszystkich ())), templateContent);
    zmienWzorzec ("$rows", up->podajWszystkieUpakowania (), templateContent);

    output << templateContent;
    output.close ();

    return true;
}


void PisarzPlikow::zmienWzorzec(const std::string wzorzec, std::string naco, std::string & gdzie) {
	if (naco == "")
		naco = "default";

	size_t wzorzecPos = gdzie.find(wzorzec);
	if (wzorzecPos == std::string::npos) {
		std::cout << "Blad: wzorzec '" + wzorzec + "' nie znaleziony!";
		return;
	}

	while (wzorzecPos != std::string::npos) {
		std::string before = "", after = "";
		before = gdzie.substr(0, wzorzecPos);
		after = gdzie.substr(wzorzecPos + wzorzec.size(), gdzie.size() - (wzorzecPos + wzorzec.size()));

		gdzie = before + naco + after;
		wzorzecPos = gdzie.find(wzorzec);
	}
}

bool PisarzPlikow::zapiszWynikSumaryczny (Upakowanie * up) {
    std::fstream output;
	std::string globalStatsPath = "every_run_results.txt", currentDateTime = "";

    // wynik zboirczy
    output.open (globalStatsPath, std::ios::out | std::ios::app);
    if (!output.is_open ()) {
        std::cout<< "Blad:Saving global results to file failed!  (file: " + globalStatsPath + ")";
        return false;
    }

    // data
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime (buffer, 80, "%d-%m-%Y_%H-%M-%S", timeinfo);
    std::string str (buffer);
    currentDateTime = str;

    // wyjscie
    std::string row = "";
    std::string separator = " | ";

    // zapisz
    output << currentDateTime << " | ";
    row += sformatuj<unsigned int> (up->podajWszystkieKartony ()->size (), 10, ' ', separator);
    row += sformatuj<double> (up->podajCzasPakowania (), 9, ' ', separator);
    row += sformatuj<float> (std::abs (100.f - up->podajObjetoscPoUpakowaniu () * 100.f / up->podajObjetoscWszystkich ()), 
                               7, ' ', separator, false, true);

    output << row << "\n";
    output.close ();

    return true;
}

void PisarzPlikow::ustawNazwe (const std::string s) {
    this->nazwaPlikWynikowy = s;
}
