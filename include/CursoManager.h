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
    void modificarCurso();

    void listarCursos();
    void listar();
    void listarSinCupo();
    void listarPorProfesor();

    void buscarCursoID();

    bool pedirNombreCurso(std::string& nombre);
    bool pedirCantidadMaximaAlumnos(int& cantidad);
    bool pedirNumeroAula(int& aula, int idCursoExcluido = -1);
    bool pedirIdProfesor(int& idProfesor);
    bool aulaUnica(int& numeroAula, int idCursoExcluido = -1);
};
