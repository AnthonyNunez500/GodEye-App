#pragma once
#include "Dispositivo.h"
using namespace std;
using namespace System;
class Archivo
{
private:
	fstream arch;
	Dispositivo auxD;
	Atributo auxA;
	FILE* archFile;
public:
	Archivo() {
		this->auxD = Dispositivo();
	}
	~Archivo() {}
	void LeerAtributo(vector<Dispositivo>* listAuxD) {
		//Crea el archivo si no existe
		arch.open("Atributos.txt", ios::in);
		if (arch.fail()) {
			arch.open("Atributos.txt", ios::out);
			arch << "0 13:00 10/10/23 0" << endl;
			arch << "0 14:00 10/10/23 0" << endl;
			arch << "0 15:00 10/10/23 0" << endl;
			arch << "0 13:00 10/08/23 1" << endl;
			arch << "1 14:00 10/08/23 1" << endl;
			arch << "1 15:00 10/08/23 1";
		}
		arch.close();
		//De todas formas, lee el archivo
		int movimiento; char hora[5]; char fecha[8]; int dispositivoID;
		archFile = fopen("Atributos.txt", "r");
		while (fscanf(archFile, "%d%s%s%d", &movimiento, hora, fecha, &dispositivoID) != EOF) {
			auxA = Atributo(movimiento, hora, fecha);
			listAuxD->at(dispositivoID).addAtributo(auxA);
		}
		fclose(archFile);
	}
	void LeerDispositivo(vector<Dispositivo>* listAuxD) {
		//Crea el archivo si no existe
		arch.open("Dispositivos.txt", ios::in);
		if (arch.fail()) {
			arch.open("Dispositivos.txt", ios::out);
			arch << "Cs12345 1 Camara SalaEstar" << endl;
			arch << "Ss29156 0 Sensor Patio";
		}
		arch.close();
		//De todas formas, lee el archivo
		char name[7];
		int encendido;
		char tipo[20];
		char ubicacion[20];
		archFile = fopen("Dispositivos.txt", "r");
		while (fscanf(archFile, "%s%d%s%s", name, &encendido, tipo, ubicacion) != EOF) {
			auxD = Dispositivo(name, encendido, tipo, ubicacion);
			listAuxD->push_back(auxD);
		}
		fclose(archFile);
		//LeerAtributo(listAuxD);
	}
	void EscribirDispositivos(vector<Dispositivo>* listAuxD) {
		arch.open("Dispositivos.txt", ios::out);
		for (int i = 0; i < listAuxD->size(); i++)	{
			auxD = listAuxD->at(i);
			string encendido;
			if (auxD.getEncendido()) { encendido = "1"; }
			else { encendido = "0"; }
			arch << auxD.getName() + " " +
				encendido + " " + auxD.getTipo() + " " + auxD.getTipo() << endl;
		}
		arch.close();
	}
	void EscribirAtributos(vector<Dispositivo>* listAuxD) {
		for (int i = 0; i < listAuxD->size(); i++) {
			for (int j = 0; j < listAuxD->at(i).getSizeAtributos(); j++) {
				auxA = listAuxD->at(i).getAtributo(j);
				string movimiento;
				string dispositivoId;
				if (auxA.getMovimiento()) { movimiento = "1"; }
				else { movimiento = "0"; }
				dispositivoId = to_string(i);
				arch << movimiento + " " + auxA.getHora() + " " + auxA.getFecha() + " " + dispositivoId << endl;
			}
		}
	}
};
