/*
Programmname: Bilderzeugung und Übertragung
Modulname: Bild
Dateiname: bild.h

Autor: Nico Herkner
Version: 0.1
Status: in Bearbeitung
Datum: 10.11.2017

Beschreibung:
Basisklasse zum speichern des Bildes in einem Array und der Übertragung
Klassenbeschreibung (Header-Datei)

Historie:
Version		Datum		Bearbeiter			Bearbeitungsgrund
0.1			20.09.2017 	Nico Herkner		Neuerstellung
0.2			20.09.2017 	Nico Herkner		Neuerstellung

*/
//Include Guard
#ifndef text_h
#define text_h

#include "bild.h"

class Text2LED {
private:
	char text[12];
	static unsigned char ** alphabet;
	static int const anfangersterBuchstabe = 5;
	static int const laengeBuchstabe = 15;
	static int const anzahlBuchstaben = 3;
	static int const alphabetLaenge = 2500;
	static int const leerzeichenPixel = 1; //anzhal der Pixel zwischen zwei Zeichen
	Bild * meinBild;
	int letter2bild(char letter); // setzt einen Buchstaben ans ende des Textes
	int pos; // ende (x-pos) des letzten Buchtabens
	public:
	Text2LED(const char text[]);
	~Text2LED();
	static int setupAlphabet();
	static int exitAlphabet();
	Bild * getBild();
};
#endif //text_h
