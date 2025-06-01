#pragma once
#include "string"
#include "Profesor.h"

class ProfesorArchivo{

private:

    char  _nombreArchivo[30];
    //int _tamanioRegistro;

public:

    ProfesorArchivo();

    ProfesorArchivo(std::string nombreArchivo);

    bool alta(Profesor regProfesor);

    int cantRegistros();

    int buscar(int id);

    Profesor leer(int posicion);

    int generarID (int cantRegistros);

    bool alta(Profesor regModificado, int posicion);


};
