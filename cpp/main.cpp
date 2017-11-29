#include "bild.h"
#include "readBMP.h"
#include "anzeigeWeb.h"
#include "text.h"
int main(int argc, char* argv[]){
	Text2LED::setupAlphabet();
	Bild::setupGPIO();
	cout << argc << endl;
	if (argc == 2) {
		char* text = &(argv[2][0]);
		Text2LED * textBild = new Text2LED("Siemens");
		AnzeigeWeb::bild2html(textBild->getBild());
		textBild->getBild()->bild2SPI();
		AnzeigeWeb::bild2html(textBild->getBild());
		delete textBild;
	}
	else {
		Bild * bild3 = new Bild(gruen);
		ReadBMP * bild2 = new ReadBMP((char*)"/var/www/html/medien/upload/aktuell.bmp");

		delete bild2;
		delete bild3;
	}
	cout << millis() << endl;
	Text2LED::exitAlphabet();
	return 0;
}