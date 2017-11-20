#include "bild.h"
#include "readBMP.h"
#include "anzeigeWeb.h"
int main(){
	Bild * bild1 = new Bild(weiss);
	//cout << (int)bild1->bildPixel[3][3];
	ReadBMP * bild2 = new ReadBMP("/var/www/html/medien/aktuell.bmp");
	AnzeigeWeb::bild2html(bild2->getBild());
	delete bild1;
	delete bild2;
	return 0;
}