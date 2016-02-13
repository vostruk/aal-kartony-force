*******************************   WIZYTÓWKA PROJEKTU  ********************************************
Analiza Algorytmow 15Z 

* Nazwa projektu: AAL-12-LS kartony
* program oryginalnie został napisany za pomocą środowiska Visual C++ 2013. 
  Dla uruchomienia na swoim komputerze wystarczy 
  uruchomić plik Kartony.sln w głównym katałogu.
* program został przetestowany i poprawnie działa na dwóch najbardziej 
  rozpowszechnionych systemach: Windows(10) oraz Linux(Mint).
  
*******************************   WIZYTÓWKA  STUDENTA  *********************************************
Student:    Volodymyr Ostruk, 255356

Prowadzący: Lukasz Sklonieczny

Uczelnia:   Politechnika Warszawska, EiTI

*******************************  KRÓTKA SPECYFIKACJA PROBLEMU  **************************************
***  Oryginalny tekst zadania
* Ortodoksyjny kolekcjoner tekturowych kartonów zaczyna narzekać na brak
* miejsca do przechowywania swoich cennych zdobyczy. Postanowił
* oszczędzić miejsce przez wkładanie kartonów jeden w drugi. W trosce o
* zachowanie dobrego stanu kartonów, umieszcza tylko jeden karton
* wewnątrz większego, a wolną przestrzeń wypełnia materiałem ochronnym.
* Tak zabezpieczony karton może następnie umieścić wewnątrz innego
* większego kartonu, ale nie może umieścić dwóch kartonów obok siebie w
* jednym kartonie. Dla danego zbioru kartonów należy znaleźć najlepsze
* upakowanie kartonów, tzn. takie, które zwalnia najwięcej miejsca.

*** Zwęzła analiza wymagań
*  Dany jest zbior kartonow teksturowych o wymiarach x*y*z
*  Upakowac kartony tak, zeby zajmowaly najmniej miejsca,
   czyli znalezc takie upakowanie zeby jak najwiecej kartonow byly 
   upakowane wewnatrz innych kartonow.(zmienna U - ilosc kartonow,
   znajdujacych sie wewnatrz innych kartonow)
*  Nie wolno umieszczac kilku kartonow obok siebie - tylko jeden
   wewnatrz drugiego.

   
   
************************** PRZEWODNIK PO FOLDERACH i PLIKACH PROGRAMU *******************************
dokumentacja_koncowa.pdf - plik dokumentacji koncowej

/RozwiazaniePrzenosne - miesci pliki wynikowe do uruchomienia na różnych płatformach: 
   Kartony.exe  - program wynikowy dla uruchomienia na Windows
   KartonyLinuxProgram - dla uruchomienia na Linux
   
/AALKartony - główny folder ze wszystkimi plikami rozwiązania
   compileOnLinux.sh - skrypt dla kompilacji rozwiązania na systemach Linux
   AALKartony.sln    - solution dla uruchomienia na Visual Studio C++(windows)
   every_run_results - plik ze zbiorczymi danymi z każdego uruchomienia programu
   k_.txt            - pliki wejściowe z danymi o kartonach
   main.cpp          - plik z funkcja main() programu
   wynik_data.txt    - pliki wynikowe domyslne generowane gdy nie podano opcji -o z nazwa pliku wynikowego
   /classes          - folder ze wszystkimi klasami projektu
   
   
**************************   INFORMACJA O MOZLIWYCH POLECENIACH AKTYWACJI PROGRAMU *************************
Program jest zgodny z konwencjami programow UNIX. Program musi byc aktywowany z konsoli.
Polecenia aktywacji programu:

* -h | --help					: Wypisuje menu pomocnicze.
* -s | --stat  					: Trybi eksperymentalny z wyprowadzeniem statystyki.
* -f | --file[filename] 		: Plik wejsciowy z danymi kartonow.\n";
* -o | --output[filename] 		: Plik wyjsciowy dla wypisania wynikow programu.\n";
* --gentest [number_of_boxes]	: Tryb automatycznej generacji danych o kartonach.\n";

**********************   OPIS KONWENCJI DOTYCZĄCYCH DANYCH WEJŚCIOWYCH I PREZENTACJI WYNIKÓW ****************
*** Dane wejsciowe
Podstawowo dla opcji wczytania z pliku -f przyjęta następująca konwencja:
* Kazda linijka pliku wejsciowego prezentuje jeden karton z jego trzema parametrami: dlugość, szerokość oraz wysokość odpowiednio.
* Każda wartość odzielone jest spacją
* Linije zaczynające się od  '#' uznawane są za komentarz(ignorowane)

Przykładowy plik wejśćiowy z jednym kartonem:
# jakis ignorowany tekst
1.11 2.54 3.54



*** Prezenatacja wynikow

### PLIK WYNIKOWY Z UPAKOWANIAMI KARTONOW ###
# DATA WYGENEROWANIA        				   :  _20-01-2016_22-44-08
# ILOSC WSZYSTKICH KARTONOW PRZED PAKOWANIEM   :  9
# CZAS PAKOWANIA               				   :  0.000000 [sec]
# ILOSC PACZEK KARTONOW        				   :  3
# CALKOWITA ZAJETA OBJĘTOŚĆ PO UPAKOWANIU      :  955.000000
# ZAOSZCZĘDZONO MIEJSCA W POROWNANIU Z PRZED   :  24.235054 %

UPAKOWANIA KARTONOW
=====================================================================
 ID          | DLUGOŚĆ    | SZEROKOŚĆ  | WYSOKOŚĆ   | OBJĘTOŚĆ      |
=====================================================================
                          Upakowanie 0
---------------------------------------------------------------------
     8       | 10         | 9          | 9          | 810           |
     0       | 5          | 5          | 5          | 125           |
     1       | 4.999      | 4.999      | 4.999      | 124.925       |
     2       | 4.99       | 2.01       | 2.01       | 20.1601       |
     5       | 4          | 2          | 2          | 16            |

                          Upakowanie 1
---------------------------------------------------------------------
     7       | 10         | 5          | 2          | 100           |
     4       | 5          | 1.999      | 1.54       | 15.3923       |
     6       | 4          | 1          | 1          | 4             |

                          Upakowanie 2
---------------------------------------------------------------------
     3       | 5          | 3          | 3          | 45            |



******************** Opis metody rozwiazania zastosowanych algorytmow i struktur danych *************************
*Można uznać, że rozwiązanie problemu składa się z trzech etapów.
*Etap 1: Wczytywanie.
Podczas wczytywania danych o kartonie długości jego boków są uporząkowywane według reguły: dlugosc>=szerokosc>=wysokosc
Złożoność: N.
*Etap 2: Sortowanie
Sortowanie zbioru kartonów według objętości(malejąco). W wyniku otrzymujemy uporządkowany zbiór kartonów od największego do najmniejszego.
Złożoność: NlogN
*Etap 3: Pakowanie
*Algorytm:
-Utworz pierwszy stos i umiesc tam największy karton.
-Dla każdego kartonu:
------ Dla każdego stosu:
      ----sprawdz czy karton sie zmiesci na w kartonie umieszczonym na gorze stosu stos.
            jesli tak to umiesc na gore stosu. Karton się mieści w innym kartonie gdy 
            każdy  jego bok się mieszci w odpowiednim boku większego kartona.
-----Jeśli karton nie został umieszczony na żaden stos, utwórz nowy stos i umieść tam krton.

Dla każdego kartonu sprawdzamy czy się zmieści tyle razy ile jest stosów. Czyli w najgorszym przypadku, gdy zadny karton sie nie miesci złożoność: N*N/2
Złożoność dokladna  algorytmu:             N*(N/2 + logN + 1)
Złożoność asymptotyczna algorytmu:         O(N*N)

Uzyte struktury danych to wektor dla przechowywania Kartonow i wektor wektorow dla przechowywania upakowań. 
Te struktury trzymane są w klasie Upakowanie. Także opisana jest klasa Karton, przechowująca dane o kartonie.

********************* FUNKCJONALNA DEKOMPOZYCJA PROGRAMU NA MODUŁY ŻRÓDŁOWE ****************************
* Pliki nagłówkowe programu
- Karton.h       - klasa opisujaca karton
- Upakowanie.h   - klasa opisujaca zbior kartonow i ich upakowanie
- UI.h           - klasa opisujaca interfejs uzytkownika i metody
- PisarzPlikow.h - klasa opisujaca menedzera wypisujacego wyniki

* Pliki implementacyjne programu
- main.cpp
- Karton.cpp
- Upakowanie.cpp
- UI.cpp
- PisarzPlikow.cpp

*************************************************
* Decyzje projektowe
ograniczenia: 
rozmiaru  problemu - problem nie ma ograniczeń, oprócz tych wynikających z ograniczeń rozsądnego czasu oraz
                     ograniczeń precyzji numerycznych typu long double.
					 Program może policzyć w rozsądnym czasie problemy o rozmiarach do 10000000 kartonow.
charakterystyki  generatorow  danych  testowych - generator danych testowych jest prostym generatorem z użyciem funkcji rand()
specjalne  konwencje  w alokacji  pamięci  dynamicznej: program nie wnosi specjalnych konwencji z alokacji pamięci
wymagania  dotyczące  typow  parametryzujących szablony: brak 
konwencje związane z obsługą sytuacji wyjątkowych: program obluguje sytuacje wyjątkowe i wyprowadza komunikat użytkowniku
