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
#ifndef bild_h
#define bild_h

	#include <wiringPi.h>
	#include <wiringPiSPI.h> 
	#include <stdio.h>
	#include <iostream>
using namespace std;
	//Farbdefinition
	enum Farbe {schwarz=0, gruen, rot, gelb};
class Bild {
	public:
		int const bildBreite = 176;
		static int const bildHoehe = 32;
		static int const anzahlPanel = 4;
		static int const panelReihen = (int)(Bild::bildHoehe / Bild::anzahlPanel);
	private:
		static int const spispeed = 1000000;
		static int const pin_resync = 6;
		static int const delay_pin_resync = 10;
	public:
		unsigned char ** bildPixel; //bildpixel[32/4][176]
		Bild(int bildBreite=176); // erzeugt array ohne inhalt mit variabler Länge
		Bild(unsigned char ** vorhandenesArray); // erzeugt array ohne inhalt
		Bild(Farbe bildhintergrund); // erzeugt für 3 gelbes Bild (nur 1), für 2 gruen, für 1 rot und für 0 schwarzes Bild
		~Bild(); //löscht Array
		int bild2SPI(int beginn=0); //sendet das Bild zum FPGA
		static int setupGPIO(); //konfiguration für GPIO ausgabe
};
#endif // !bild_h