#include "readBMP.h"

ReadBMP::ReadBMP(char *dateiPfad) {
	neuesBild = new Bild(bmp2Array(dateiPfad));
}
ReadBMP::~ReadBMP() {
	delete neuesBild;
}

unsigned char ** ReadBMP::bmp2Array(char *dateiPfad){
	int const divisorRot = 128;
	int const divisorGruen = 128;
	FILE *streamIn;
	streamIn = fopen(dateiPfad, "r");
	if (streamIn == (FILE *)0) {
		printf("File opening error ocurred. Exiting program.\n");
		exit(0);
	}

	for (int idx = 0; idx<54; idx++) std::cout << getc(streamIn);  // strip out BMP header
	unsigned char ** rueckgabeArray = new unsigned char *[(int)(Bild::bildHoehe / Bild::anzahlPanel)];
	for (int idy = (int)(Bild::bildHoehe/Bild::anzahlPanel) - 1; idy >= 0; idy--) {    // Reihen von unten nach oben
		rueckgabeArray[idy] = new unsigned char[Bild::bildBreite];
		for (int idx = 0; idx<Bild::bildBreite; idx++) {    ///Spalten von links nach rechts
			rueckgabeArray[idy][idx] = 0;
			for (int panelwahl = 1; panelwahl < 16; panelwahl *=2) { //Schleife wird 4mal durchlaufen 2^4=2^Bild::anzahlPanel ->16
				getc(streamIn); //Blau wird nicht verwendet
				rueckgabeArray[idy][idx] += (unsigned char)(panelwahl*(bool)(getc(streamIn) / divisorGruen)); //Gruen
				rueckgabeArray[idy][idx] += (unsigned char)(panelwahl*(bool)(getc(streamIn) / divisorRot) * 2); //Rot
			}
			
			}
	}
	fclose(streamIn);
	return rueckgabeArray;
}
