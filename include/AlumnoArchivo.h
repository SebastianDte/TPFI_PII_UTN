#pragma once
#include "Alumno.h"

class AlumnoArchivo
{
private:
    char _nombreArchivo[30];
    int _tamanioRegistro;

public:
    AlumnoArchivo(const char *n = "alumnos.dat");

    bool alta(const Alumno& regAlumno);
    int buscar(int legajo,bool filtrarActivos) const;
    bool modificar(const Alumno& regAlumno, int posicion);
    Alumno leer(int posicion) const;

    bool existeDNI(const std::string& dni) const;
    bool tieneInscripcionesActivas(int legajo) const;

    int cantRegistros() const;
};
