#include "readBMP.h"

ReadBMP::ReadBMP(char *dateiPfad) {
	neuesBild = new Bild(bmp2Array(dateiPfad)); // ruft den Konstruktor
}
ReadBMP::~ReadBMP() {
	delete neuesBild; //Löscht das Bild
}

unsigned char ** ReadBMP::bmp2Array(char *dateiPfad){
	int const divisorRot = 128;
	int const divisorGruen = 69;
	FILE * streamIn = fopen(dateiPfad, "r"); //BMP-Datei wird geöffnet (nur Leseberechtigungen)
	if (streamIn == (FILE *)0) {
		cout << "File opening error ocurred. Exiting program.\n";
		return nullptr;
	}
	char header[70];
	for (int idx = 0; idx < 54; idx++) header[idx] = getc(streamIn);  // strip out BMP header //66775666000000540004000017600032000102400000266001951400195140000000000 18:176->22:32
	int bildHoehe = (int)header[22]; //Bildhöhe wird aus header gelesen
	int bildBreite = (int)header[18]; //Bildbreite wird aus header gelesen
	unsigned char ** rueckgabeArray = new unsigned char *[(int)(bildHoehe / Bild::anzahlPanel)]; //Erste Dimension des Arrays
	for (int idy = 0; idy < (int)(bildHoehe / Bild::anzahlPanel); idy++) {    // Reihen von unten nach oben
		rueckgabeArray[idy] = new unsigned char[bildBreite];
	}
	for(unsigned char bitwahl=128; bitwahl; bitwahl >>=2){ //wahlt das bit und damit das panel aus
		for (int idy = (int)(bildHoehe/Bild::anzahlPanel) - 1; idy >= 0; idy--) {    // Reihen von unten nach oben
			for (int idx = 0; idx<bildBreite; idx++) {    ///Spalten von links nach rechts
				getc(streamIn); //Blau wird nicht verwendet
				rueckgabeArray[idy][idx] |= (bitwahl >> 1) & (255*(int)(getc(streamIn) / divisorGruen)); //Gruen an aktuelle Bitstelle
				rueckgabeArray[idy][idx] |= bitwahl & (255*(int)(getc(streamIn) / divisorRot)); //Rot an aktuelle Bitstelle
			}
		}
	}
	fclose(streamIn); //Datei-Zugriff wird beendet
	return rueckgabeArray;
}
Bild * ReadBMP::getBild() {
	return this->neuesBild;
}

int ReadBMP::string2int(char eingabe[14], int len) {
	int rueckgabe = 0;
	int stellenwert = 1;
	for (int idx = len - 1; idx >= 0; idx--) {
		if ((int)eingabe[idx] > 48 && (int)eingabe[idx] < 58) {
			rueckgabe += (int)(eingabe[idx] - 48)*stellenwert;
			stellenwert *= 10;
		}
	}
	return rueckgabe;
}
/*
66775666000000540004000017600032000102400000266001951400195140000000000
*/