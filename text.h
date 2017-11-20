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
public:
	Text2LED(char text[], int len);
	~Text2LED();
	Bild * meinBild;
	static int setupAlphabet();
};
#endif //text_h
