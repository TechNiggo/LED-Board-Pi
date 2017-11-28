#include "text.h"
#include "readBMP.h"

	Text2LED::Text2LED(char text[], int len) {
		meinBild = new Bild(schwarz);
		for (int idx = 0; idx < len; idx++) {
			
		}

	}
	Text2LED::~Text2LED() {
		delete meinBild;
	}
	int Text2LED::setupAlphabet() {
		char * pfad = (char*)"../alphabet.bmp";
		unsigned char ** alphabet = ReadBMP::bmp2Array(pfad);
		return 1;
	}