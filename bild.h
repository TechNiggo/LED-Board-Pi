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
		static int const bildBreite = 176;
		static int const bildHoehe = 32;
		static int const anzahlPanel = 4;
	private:
		static int const spispeed = 1;
		static int const pin_resync = 6;
		static int const delay_pin_resync = 1;
	public:
		unsigned char ** bildPixel; //bildpixel[32/4][176]
		Bild(); // erzeugt array ohne inhalt
		Bild(unsigned char ** vorhandenesArray); // erzeugt array ohne inhalt
		Bild(Farbe bildhintergrund); // erzeugt für 1 gelbes Bild (nur 1) und für 0 schwarzes Bild
		~Bild(); //löscht Array
		int bild2SPI(); //sendet das Bild zum FPGA
		static int setupGPIO(); //konfiguration für GPIO ausgabe
};
#endif // !bild_h