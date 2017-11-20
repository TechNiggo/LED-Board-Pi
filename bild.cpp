	/*
	Programmname: Bilderzeugung und Übertragung
	Modulname: Bild
	Dateiname: bild.cpp
	
	Autor: Nico Herkner
	Version: 0.1
	Status: in Bearbeitung
	Datum: 10.11.2017 
	
	Beschreibung:
	Basisklasse zum speichern des Bildes in einem Array und der Übertragung
	
	Historie:
	Version		Datum		Bearbeiter			Bearbeitungsgrund
	0.1		20.09.2017 	Nico Herkner			Neuerstellung
	
	*/
#include "bild.h"
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#include <iostream>
using namespace std;
		
		// erzeugt array ohne inhalt
		Bild::Bild(){
			this->bildPixel = new unsigned char *[(int)Bild::bildHoehe/ Bild::anzahlPanel];
			for (int idx = 0; idx<(int)(Bild::bildHoehe / Bild::anzahlPanel); idx++) {
				this->bildPixel[idx] = new unsigned char[Bild::bildBreite];
			}
			this->setupGPIO();
		}
		Bild::Bild(unsigned char ** vorhandenesArray) {
			this->bildPixel = vorhandenesArray;
			this->setupGPIO();
			this->bild2SPI();
		}
		// erzeugt für 1 gelbes Bild (nur 1) und für 0 schwarzes Bild
		Bild::Bild(Farbe schwarzweiss){
			this->bildPixel = new unsigned char *[(int)Bild::bildHoehe/ Bild::anzahlPanel];
			for(int idx=0;idx<(int)(Bild::bildHoehe/ Bild::anzahlPanel); idx++){
				this->bildPixel[idx] = new unsigned char[bildBreite];
				for(int idx2=0;idx2<Bild::bildBreite;idx2++){
					this->bildPixel[idx][idx2]=0xFF*(int)schwarzweiss;
				}
			}
			this->setupGPIO();
			this->bild2SPI();
		}

		//löscht Array
		Bild::~Bild(){
			for (int idx = 0; idx<(int)(Bild::bildHoehe / Bild::anzahlPanel); idx++) {
				delete bildPixel[idx];
				
			}
			delete bildPixel;
		}
		
		
		//sendet das Bild zum FPGA
		int Bild::bild2SPI(){
			for (int idx = 0; idx<(int)(Bild::bildHoehe / Bild::anzahlPanel); idx++) {
				for (int idx2 = 0; idx2<Bild::bildBreite; idx2++) {
					cout << wiringPiSPIDataRW(0, &(bildPixel[idx][idx2]), 1) << endl; //int wiringPiSPIDataRW (int channel, unsigned char *data, int len) ;
					//delay(500);
				}
			}
			return 1;
		}
		
		//Konfiguration der GPIO-Ausgabe
		int Bild::setupGPIO(){
			wiringPiSetup ();
			wiringPiSPISetup(0, Bild::spispeed);
			return 1;
		}
