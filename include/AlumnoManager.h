#pragma once
#include "AlumnoArchivo.h"
#include "Utilidades.h"
#include "Alumno.h"

class AlumnoManager{

private:
    AlumnoArchivo _archivo;
    Utilidades _utilidades;
    void mostrarAlumno(const Alumno& alumno);

    ///VALIDACIONES
    bool pedirDNI(std::string& dni);
    bool pedirNombre(std::string& nombre);
    bool pedirApellido(std::string& apellido);
    bool pedirTelefono(std::string& telefono);
    bool pedirEmail(std::string& email);
    bool pedirDireccion(std::string& direccion);
    bool pedirFechaNacimiento(Fecha& fecha);

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
