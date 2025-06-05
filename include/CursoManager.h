#pragma once
#include "CursoArchivo.h"
#include "Utilidades.h"

class CursoManager
{
private:
    CursoArchivo _archivo;
    Utilidades _utilidades;

public:
    CursoManager();

    void altaCurso();
    void bajaCurso();
    void modificarCurso();

    void listarCursos();
    void listarActivos();
    void listarInactivos();
    void listarSinCupo();
    void listarPorProfesor();

    void buscarCursoID();

    bool pedirNombreCurso(std::string& nombre);
    bool pedirCantidadMaximaAlumnos(int& cantidad);
    bool pedirNumeroAula(int& aula);
    bool pedirIdProfesor(int& idProfesor);
};
