#!bin/bash
g++ -fno-trapping-math -o KartonyLinuxProgram main.cpp classes/UI.cpp classes/Upakowanie.cpp classes/Karton.cpp classes/PisarzPlikow.cpp -std=c++11 | grep error

