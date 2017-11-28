#include <wiringPi.h>
#include <wiringPiSPI.h> 
#include <stdio.h>
#include <iostream>
using namespace std;
int main(int argc, char* argv[]) {
	wiringPiSetup();
	wiringPiSPISetup(0, 1);
	pinMode(6, OUTPUT);
	digitalWrite(6, LOW);
	unsigned char einByte = 255;
	if (argc > 0) {
		einByte = argv[1][0];
	}
	for (;true;) {
		wiringPiSPIDataRW(0, &einByte, 1); //int wiringPiSPIDataRW (int channel, unsigned char *data, int len) ;
		delayMicroseconds(10);
		cout << (int)einByte << endl;
	}
	return 1;
}