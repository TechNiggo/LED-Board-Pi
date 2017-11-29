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
		Bild::Bild(int bildBreite)
			: bildBreite{ bildBreite } {
			this->bildPixel = new unsigned char *[(int)Bild::bildHoehe/ Bild::anzahlPanel];
			for (int idy = 0; idy<(int)(Bild::bildHoehe / Bild::anzahlPanel); idy++) {
				this->bildPixel[idy] = new unsigned char[Bild::bildBreite];
			}
		}
		//erzeugt neues Bild aus schon vorhandenem Bildarray
		Bild::Bild(unsigned char ** vorhandenesArray) {
			this->bildPixel = vorhandenesArray;
		}
		// erzeugt für 1 gelbes Bild (nur 1) und für 0 schwarzes Bild
		Bild::Bild(Farbe bildhintergrund){
			this->bildPixel = new unsigned char *[Bild::panelReihen];
			for(int idx=0;idx<Bild::panelReihen; idx++){
				this->bildPixel[idx] = new unsigned char[bildBreite];
				for(int idx2=0;idx2<Bild::bildBreite;idx2++){
					this->bildPixel[idx][idx2]=0b01010101*(int)bildhintergrund;
				}
			}
		}

		//löscht Array
		Bild::~Bild(){
			for (int idy = 0; idy<Bild::panelReihen; idy++) {
				delete bildPixel[idy];
			}
			delete bildPixel;
		}
		
		//sendet das Bild zum FPGA
		int Bild::bild2SPI(int beginn){
			for (int idy = 0; idy < (int)(Bild::bildHoehe / Bild::anzahlPanel); idy++) {
				for (int idx = 0; idx < Bild::bildBreite; idx++) {
					wiringPiSPIDataRW(0, &(bildPixel[idy][idx]), 1); //int wiringPiSPIDataRW (int channel, unsigned char *data, int len) ;
				}
			}
			//cout <<	 "Bild gesendet" << endl;
			digitalWrite(Bild::pin_resync, HIGH); delay(20); digitalWrite(Bild::pin_resync, LOW); //Toggelt SRAM Baustein, nachdem ein Bild fertig gesendet wurde
			return 1;
		}
		
		//Konfiguration der GPIO-Ausgabe
		int Bild::setupGPIO(){
			wiringPiSetup ();
			wiringPiSPISetup(0, Bild::spispeed);
			pinMode(Bild::pin_resync, OUTPUT);
			digitalWrite(Bild::pin_resync, LOW);
			return 1;
		}