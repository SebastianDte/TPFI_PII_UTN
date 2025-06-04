#pragma once
#include <cstring>
#include <string>
#include "CursoManager.h"

class InscripcionManager {
private:
	//Aca va luego el atributo NombreArchivo de InscripcionArchivo.
	CursoManager _cursoManager;
	//Aca va el atributo AlumnoManager.

public:
	//CRUD Inscripciones
	void altaInscripcion();
	void bajaInscripcion();
	void modificarInscripcion();
	void listarInscripciones();

};
