#pragma once
#include <vector>
#include "Atributo.h"
using namespace std;
using namespace System;
class Dispositivo
{
private:
	string name;
	bool encendido;
	string tipo;
	string ubicacion;
	vector<Atributo> listAtributos;
public:
	Dispositivo(string n, int e, string t, string u) :name(n), tipo(t), ubicacion(u) {
		listAtributos = vector<Atributo>();
		if (e == 1) { this->encendido == true; }
		else { this->encendido == false; }
	}
	Dispositivo() {}
	~Dispositivo() {}

	string getName() { return this->name; }
	bool getEncendido() { return this->encendido; }
	string getTipo() { return this->tipo; }
	string getUbicacion() { return this->ubicacion; }


	void setName(string n) { this->name = n; }
	void serEncendido(int e) {
		if (e == 1) { this->encendido == true; }
		else { this->encendido == false; }
	}
	void setTipo(string t) { this->tipo = t; }
	void setUbicacion(string u) { this->ubicacion = u; }

	//Para los Atributos
	void addAtributo(int m, string h, string f) {
		Atributo a = Atributo(m, h, f);
		this->listAtributos.push_back(a);
	}
	Atributo getAtributo(int id) {
		return this->listAtributos.at(id);
	}
	vector<Atributo> getAllAtributos() {
		return this->listAtributos;
	}
	void editAtributo(int m, string h, string f, int id) {
		Atributo a = Atributo(m, h, f);
		this->listAtributos.at(id) = a;
	}
};
