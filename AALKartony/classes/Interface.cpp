/**
nazwa projektu: "Kartony"
nazwa studenta:	 Volodymyr Ostruk, 255356
prowadzący:    Lukasz Skonieczny
Politechnika Warszawka, EiTI
*/

#include "Interface.h"
using namespace std;

Interface::Interface (int argc, char* argv[]) : mArgCount (argc) {
    configureParameters ();

    for (int i = 1; i < mArgCount; ++i) {

        string parameter (argv[i]);

        if (mapParamBools.find (parameter) != mapParamBools.end () && mapParamBools[parameter].first != true) {
            mapParamBools[parameter].first = mapParamBools[mapParamBools[parameter].second].first = true;
        }
        else if (mapParamStrings.find (parameter) != mapParamStrings.end () &&
                 i + 1 < mArgCount &&
                 mapParamStrings[parameter].first == "") {
            string filename (argv[i + 1]);
            mapParamStrings[parameter].first = mapParamStrings[mapParamStrings[parameter].second].first = filename;
            i++;
            continue;
        }
        else {
            mapParamBools["--help"].first = true;
            mapParamBools["-h"].first = true;
            break;
        }
    }
}

void Interface::configureParameters () {
    // Bool parameters: exists or not.
    mapParamBools["--stat"] = make_pair (false, "-s");
    mapParamBools["-s"] = make_pair (false, "--stat");
    mapParamBools["--help"] = make_pair (false, "-h");
    mapParamBools["-h"] = make_pair (false, "--help");

    // Parameters with extra value (necessary).
    mapParamStrings["--file"] = make_pair ("", "-f");
    mapParamStrings["-f"] = make_pair ("", "--file");
    mapParamStrings["--output"] = make_pair ("", "-o");
    mapParamStrings["-o"] = make_pair ("", "--output");
    mapParamStrings["--generate-tests"] = make_pair ("", "--generate-tests");
}

void Interface::printHelp () {
    cout << " >> Pomoc\n";
    cout << left;
    cout << "Program dla pakowania kartonow\n";
    cout << "Program umieszcza kartony wewnatrz innych dla oszczedzania miejsca.\n\n";
	cout << " >> Usage:\n";
	cout << left;
	int size = 35;
	cout << setw(size) << " -h | --help" << " : Prints this help.\n";
	cout << setw(size) << " -s | --stat" << " : Runs the time experiment mode";
	cout << setw(size) << " -f | --file[filename]" << " : Input file with information about boxes.\n";
	cout << setw(size) << " -o | --output[filename]" << " : Output file to be created with program results.\n";
	cout << setw(size) << " --generate-tests [number_of_boxes]" << " : Forces program to generate its own tests in given number.\n";
}

string Interface::getStringParam (const string key) {
    
    if (mapParamStrings.find (key) != mapParamStrings.end ())
        return mapParamStrings[key].first;
    else
        return "";
}

bool Interface::getBoolParam (const string key) {
    if (mapParamBools.find (key) != mapParamBools.end ())
        return mapParamBools[key].first;
    else {
		cout << "Warn: Requested wrong parameter: false returned";
        return false;
    }
}

