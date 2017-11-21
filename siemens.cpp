#include "bild.h"
#include "readBMP.h"
#include "anzeigeWeb.h"
int main() {
	ReadBMP * bild2 = new ReadBMP("/var/www/html/medien/aktuell.bmp");
	for (int idx = 0; idx < 800;idx++) {
		bild2->getBild()->bild2SPI();
	}
	AnzeigeWeb::bild2html(bild2->getBild());
	delete bild2;
	return 0;
}