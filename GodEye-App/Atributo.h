#pragma once
#include "Header.h"
using namespace std;
using namespace System;

class Atributo
{
private:
	bool movimiento;
	string hora;
	string fecha;
public:
	Atributo(int m = 0, string h=" ", string f=" ") :hora(h), fecha(f) {
		if (m == 1) { this->movimiento = true; }
		else { this->movimiento = false; }
	}
	~Atributo() {}
	bool getMovimiento() { return this->movimiento; }
	string getHora() { return this->hora; }
	string getFecha() { return this->fecha; }
	void setMovimiento(int m) {
		if (m == 1) { this->movimiento = true; }
		else { this->movimiento = false; }
	}
	void setHora(string h) { this->hora = h; }
	void setFecha(string f) { this->fecha = f; }
};