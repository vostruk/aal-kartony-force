/**
[AAL] projekt: "Kartony"
student:	   Volodymyr Ostruk
prowadzący:    Lukasz Skonieczny
Politechnika Warszawka, EiTI
*/

#include <iostream>
#include "classes/UI.h"

int main (int argc, char *argv[]) {
    srand ((unsigned)time (NULL));

    UI konsola (argc, argv);
    konsola.start();

	std::cout << "\nProgram zakonczyl dzialanie.\nNacisnij ENTER zeby wyjsc...\n";
	std::cin.clear();
	fflush(stdin);
    std::cin.get ();

    return 0;
}
