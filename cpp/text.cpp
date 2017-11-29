#include "text.h"
#include "readBMP.h"
#include "anzeigeWeb.h"
//#include <stdio.h>
//#include <stdlib.h>
#include <string.h>

#define MAXROWS 256-33
#define MAXCOLS 2
unsigned char ** Text2LED::alphabet;

	Text2LED::Text2LED(const char text[]) {
		meinBild = new Bild(schwarz);
		pos = 1;// (int)(meinBild->bildBreite / 2);
		int idx = 0;
		while (text[idx] != '\0') {
			pos += this->letter2bild(text[idx]) + Text2LED::leerzeichenPixel;
			idx++;
		}
	}
	int Text2LED::letter2bild(char letter) {
		int unwichtigeZeichen = 33;
		if ((int)letter < unwichtigeZeichen) {
			return 0;
		}
		for (int idx = 0; idx < Text2LED::laengeBuchstabe; idx++){
			for (int idy = 0; idy < Bild::panelReihen; idy++){
				this->meinBild->bildPixel[idy][this->pos + idx] = Text2LED::alphabet[idy][Text2LED::anfangersterBuchstabe+((int)letter - unwichtigeZeichen)*Text2LED::laengeBuchstabe + idx];
			}
		}
		return Text2LED::laengeBuchstabe;
	}
	Text2LED::~Text2LED() {
		delete meinBild;
	}
	int Text2LED::setupAlphabet() {
		char * pfad = (char*)"/var/www/html/medien/alphabet.bmp";
		Text2LED::alphabet = ReadBMP::bmp2Array(pfad, Text2LED::alphabetLaenge);

		return 1;
	}
	int Text2LED::exitAlphabet() {
		delete Text2LED::alphabet;

	}
	Bild * Text2LED::getBild() {
		return this->meinBild;
	}