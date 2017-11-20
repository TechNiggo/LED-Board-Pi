#include "bild.h"
#include "readBMP.h"
int main(){
	//Bild * bild1 = new Bild(weiss);
	ReadBMP * bild2 = new ReadBMP("/var/www/html/medien/aktuell.bmp");
	return 0;
}