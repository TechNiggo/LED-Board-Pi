#include "bild.h"
#include "readBMP.h"
#include "anzeigeWeb.h"
int main(){
	Bild * bild1 = new Bild(schwarz);
	Bild * bild3 = new Bild(gelb);
	Bild * bild4 = new Bild(schwarz);
	ReadBMP * bild2 = new ReadBMP("/var/www/html/medien/aktuell.bmp");
	AnzeigeWeb::bild2html(bild1);
	AnzeigeWeb::bild2html(bild3);
	AnzeigeWeb::bild2html(bild4);
	AnzeigeWeb::bild2html(bild2->getBild());
	for (int idx = 0; idx < 800; idx++) {
		bild1->bild2SPI();
	}
	delete bild1;
	delete bild2;
	delete bild3;
	delete bild4;
	return 0;
}