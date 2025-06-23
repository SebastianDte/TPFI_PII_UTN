#pragma once
#include "string"
#include "Profesor.h"

class ProfesorArchivo{

private:

    char  _nombreArchivo[30];

public:

    ProfesorArchivo();

    bool alta(const Profesor& regProfesor);

    int cantRegistros();

    int buscar(const int& id);

    Profesor leer(const int& posicion);

    int generarID (const int& cantRegistros);

    bool alta(const Profesor& regModificado,const int& posicion);

    bool existeDNI(const std::string& dni);
};
