#pragma once
#include "AlumnoArchivo.h"
#include "Utilidades.h"
#include "Alumno.h"

class AlumnoManager{

private:
    AlumnoArchivo _archivo;
    Utilidades _utilidades;
    void mostrarAlumno(const Alumno& alumno);

public:
    AlumnoManager();

    void altaAlumno();
    void bajaAlumno();
    void modificarAlumno();

    void listarAlumnos();
    void listarActivos();
    void listarInactivos();
    void listarPorApellido();



    void buscarAlumnoLegajo();
};
