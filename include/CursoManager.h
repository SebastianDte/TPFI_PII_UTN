#pragma once
#include "CursoArchivo.h"
#include "Utilidades.h"
#include "Profesor.h"

class CursoManager
{
private:
    CursoArchivo _archivo;
    Utilidades _utilidades;
    Profesor buscarProfesorEnArray(int idProfesor, Profesor* profesores, int cantidad);

public:
    CursoManager();

    void altaCurso();
    void modificarCurso();
    void bajaCurso();

    void listarCursos();
    void listar();
    void listarInactivos();
    void listarSinCupo();
    void listarPorProfesor();

    void buscarCursoID();
    void reactivarCurso();

    bool pedirNombreCurso(std::string& nombre);
    bool pedirCantidadMaximaAlumnos(int& cantidad);
    bool pedirNumeroAula(int& aula, int idCursoExcluido = -1);
    bool pedirIdProfesor(int& idProfesor);
    bool aulaUnica(int& numeroAula, int idCursoExcluido = -1);
    bool reasignarCursosDeProfesor(int idProfesorActual);
};
