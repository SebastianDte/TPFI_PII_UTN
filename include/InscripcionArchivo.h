#pragma once
#include <string>
#include "Inscripcion.h"

class InscripcionArchivo{
private:
	char _nombreArchivo[30];
	int _tamanioRegistro;
public:
	InscripcionArchivo(const std::string& n = "Inscripciones.dat");

	//ABML
	bool alta(const Inscripcion& regInscripcion);
	bool baja(int idInscripcion);
	bool modificar(const Inscripcion& regInscripcion, int posicion);
	int buscar(int idInscripcion) const;
	bool leer(int posicion, Inscripcion& insc) const;
	int cantRegistros() const;
};
