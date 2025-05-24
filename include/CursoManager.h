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
    void buscarCursoID();
};
