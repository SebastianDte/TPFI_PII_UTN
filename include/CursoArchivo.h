#pragma once
#include "Curso.h"

class CursoArchivo
{
    private:
        char _nombreArchivo[30];
        int _tamanioRegistro;

    public:
        CursoArchivo(const char *n="cursos.dat");

        bool alta(const Curso& regCurso);
        bool baja(int idCurso);
        int buscar(int idCurso) const;
        bool modificar(const Curso& regCurso, int posicion);
        Curso leer(int posicion);

        int cantRegistros() const;
        bool tieneInscripcionesActivas(int idCurso) const;
};
