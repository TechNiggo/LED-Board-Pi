g++ -c text.cpp
g++ -c bild.cpp
g++ -c siemens.cpp
g++ -c readBMP.cpp
g++ -c anzeigeWeb.cpp
g++ -o siemens text.o bild.o siemens.o readBMP.o anzeigeWeb.o -lwiringPi
