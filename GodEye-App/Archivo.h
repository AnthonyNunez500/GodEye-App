#pragma once
#include "Dispositivo.h"
using namespace std;
using namespace System;
class Archivo
{
private:
	fstream arch;
	Dispositivo auxD;
	vector<Dispositivo> listAuxD;
	FILE* archFile;
public:
	Archivo() {}
	~Archivo() {}
	void LeerAtributo() {
		//Crea el archivo si no existe
		arch.open("Atributos.txt", ios::in);
		if (arch.fail()) {
			arch.open("Atributos.txt", ios::out);
			arch << "0 13:00 10/10/23 0" << endl;
			arch << "0 14:00 10/10/23 0" << endl;
			arch << "0 15:00 10/10/23 0" << endl;
			arch << "0 13:00 10/08/23 1" << endl;
			arch << "1 14:00 10/08/23 1" << endl;
			arch << "1 15:00 10/08/23 1" << endl;
		}
		arch.close();
		//De todas formas, lee el archivo
		int movimiento; char hora[5]; char fecha[5]; int dispositivoID;
		archFile = fopen("Atributos.txt", "r");
		while (fscanf(archFile, "%d%s%s%d", &movimiento, hora, fecha, &dispositivoID) != EOF) {
			listAuxD.at(dispositivoID).addAtributo(movimiento, hora, fecha);
		}
		fclose(archFile);
	}
	void LeerDispositivo() {
		//Crea el archivo si no existe
		arch.open("Dispositivo.txt", ios::in);
		if (arch.fail()) {
			arch.open("Dispositivo.txt", ios::out);
			arch << "cs-12345 1 camara salaEstar" << endl;
			arch << "ss-29156 0 sensor patio" << endl;
		}
		arch.close();
		//De todas formas, lee el archivo
		char name[20];
		bool encendido;
		char tipo[20];
		char ubicacion[10];
		archFile = fopen("Atributos.txt", "r");
		while (fscanf(archFile, "%s,%d,%s,%s", name, &encendido, tipo, ubicacion) != EOF) {
			auxD = Dispositivo(name, encendido, tipo, ubicacion);
			listAuxD.push_back(auxD);
		}
		fclose(archFile);
		LeerAtributo();
	}
	vector<Dispositivo> GetDispositivos() {
		LeerDispositivo();
		return this->listAuxD;
	}
};
