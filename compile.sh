g++ -c text.cpp
g++ -c bild.cpp
g++ -c main.cpp
g++ -c readBMP.cpp
g++ -o main text.o bild.o main.o readBMP.o -lwiringPi
