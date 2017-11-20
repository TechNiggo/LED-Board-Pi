#ifndef readBMP_h
#define readBMP_h

#include "bild.h"
#include "text.h"
class ReadBMP {
private:
	Bild * neuesBild;
public:
	ReadBMP(char *dateiPfad);
	~ReadBMP();
	static unsigned char ** bmp2Array(char *dateiPfad);
	Bild * getBild();
};
#endif //readBMP_h
