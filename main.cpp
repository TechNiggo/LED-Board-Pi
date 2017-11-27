#include "bild.h"
#include "readBMP.h"
#include "anzeigeWeb.h"
int main(){
	//Bild * bild1 = new Bild(schwarz);
	Bild * bild3 = new Bild(gruen);
	//Bild * bild4 = new Bild(schwarz);
	Bild::setupGPIO();
	ReadBMP * bild2 = new ReadBMP("/var/www/html/medien/upload/aktuell.bmp");
	//AnzeigeWeb::bild2html(bild1);
	//AnzeigeWeb::bild2html(bild3);
	//AnzeigeWeb::bild2html(bild4);
	//bild2->getBild()->bild2SPI();
	//AnzeigeWeb::bild2html(bild2->getBild());
	//for (int idx = 0; idx < 459; idx++)
		//bild3->bild2SPI();
		bild2->getBild()->bild2SPI();
	//delete bild1;
	AnzeigeWeb::bild2html(bild2->getBild());
	cout << millis() << endl;
	delete bild2;
	delete bild3;
	//delete bild4;
	return 0;
}