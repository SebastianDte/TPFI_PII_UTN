#pragma once

#include "MenuAlumno.h"
#include "MenuReportes.h"
#include "MenuProfesor.h"
#include "MenuCurso.h"
#include "MenuInscripcion.h"

class MenuPrincipal {
public:
    void mostrarMenuPrincipal();

private:
    MenuAlumno _alumnoMenu;
    MenuProfesor _profesorMenu;
    MenuCurso _cursoMenu;
	MenuInscripcion _inscripcionMenu;
    MenuReportes _reportesMenu;
};
