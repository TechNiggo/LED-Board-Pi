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

	for (int idx = 0; idx<54; idx++) getc(streamIn);  // strip out BMP header
	unsigned char ** rueckgabeArray = new unsigned char *[(int)(Bild::bildHoehe / Bild::anzahlPanel)]; //Erste Dimension des Arrays
	for (int idy = (int)(Bild::bildHoehe / Bild::anzahlPanel) - 1; idy >= 0; idy--) {    // Reihen von unten nach oben
		rueckgabeArray[idy] = new unsigned char[Bild::bildBreite];
	}
	for(unsigned char bitwahl=128; bitwahl; bitwahl >>=2){ //wahlt das bit und damit das panel aus
		for (int idy = (int)(Bild::bildHoehe/Bild::anzahlPanel) - 1; idy >= 0; idy--) {    // Reihen von unten nach oben
			for (int idx = 0; idx<Bild::bildBreite; idx++) {    ///Spalten von links nach rechts
				getc(streamIn); //Blau wird nicht verwendet
				rueckgabeArray[idy][idx] |= bitwahl & (255*(int)(getc(streamIn) / divisorGruen)); //Gruen
				rueckgabeArray[idy][idx] |= (bitwahl >> 1) & (255*(int)(getc(streamIn) / divisorRot)); //Rot
				//cout << (int)bitwahl << "\t" << idy << "\t" << idx << "\t" << (getc(streamIn) / divisorGruen) << endl;
			}
		}
	}
	fclose(streamIn);
	return rueckgabeArray;
}
Bild * ReadBMP::getBild() {
	return this->neuesBild;
}
