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
#include "anzeigeWeb.h"
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#include <iostream>
using namespace std;
		
		// erzeugt array ohne inhalt
		Bild::Bild(){
			this->bildPixel = new unsigned char *[(int)Bild::bildHoehe/ Bild::anzahlPanel];
			for (int idy = 0; idy<(int)(Bild::bildHoehe / Bild::anzahlPanel); idy++) {
				this->bildPixel[idy] = new unsigned char[Bild::bildBreite];
			}
			//this->setupGPIO();
		}
		Bild::Bild(unsigned char ** vorhandenesArray) {
			this->bildPixel = vorhandenesArray;
			//AnzeigeWeb::bild2html(this);
			//this->setupGPIO();
			//this->bild2SPI();
		}
		// erzeugt für 1 gelbes Bild (nur 1) und für 0 schwarzes Bild
		Bild::Bild(Farbe bildhintergrund){
			this->bildPixel = new unsigned char *[(int)Bild::bildHoehe/ Bild::anzahlPanel];
			for(int idx=0;idx<(int)(Bild::bildHoehe/ Bild::anzahlPanel); idx++){
				this->bildPixel[idx] = new unsigned char[bildBreite];
				for(int idx2=0;idx2<Bild::bildBreite;idx2++){
					this->bildPixel[idx][idx2]=0b01010101*(int)bildhintergrund;
				}
			}
			//this->setupGPIO();
			//this->bild2SPI();
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
			for (int idy = 0; idy < (int)(Bild::bildHoehe / Bild::anzahlPanel); idy++) {
				for (int idx = 0; idx < Bild::bildBreite; idx++) {
					wiringPiSPIDataRW(0, &(bildPixel[idy][idx]), 1); //int wiringPiSPIDataRW (int channel, unsigned char *data, int len) ;
				}
			}
			digitalWrite(Bild::pin_resync, HIGH); delayMicroseconds(Bild::delay_pin_resync);
			//digitalWrite(14, HIGH);
			//digitalWrite(14, LOW);
			digitalWrite(Bild::pin_resync, LOW);
			cout <<	 "Bild gesendet" << endl;
			return 1;
		}
		
		//Konfiguration der GPIO-Ausgabe
		int Bild::setupGPIO(){
			wiringPiSetup ();
			wiringPiSPISetup(0, Bild::spispeed);
			pinMode(Bild::pin_resync, OUTPUT);
			//pinMode(14, OUTPUT); //SPI_CLOCK
			digitalWrite(Bild::pin_resync, LOW);
			return 1;
		}
