
#pragma once
#include "Curso.h"

class CursoArchivo
{
    private:
        char _nombreArchivo[30];
        int _tamanioRegistro;

    public:
        CursoArchivo(const char *n="Propietarios.dat");

        bool alta(Curso regCurso);
        int buscar(int idCurso);
        bool modificar(Curso regCurso, int posicion);
        Curso leer(int posicion);

        int cantRegistros();
};
