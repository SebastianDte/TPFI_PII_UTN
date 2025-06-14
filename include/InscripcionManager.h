#pragma once
#include <cstring>
#include <string>
#include "CursoManager.h"
#include "AlumnoManager.h"
#include "Inscripcion.h"

class InscripcionManager {
private:
	//Aca va luego el atributo NombreArchivo de InscripcionArchivo.
	CursoManager _cursoManager;
	AlumnoManager _alumnoManager;
	Utilidades _utilidades;
	

	bool pedirLegajoAlumno(int& legajo);
	bool pedirIdCurso(int& idCurso);
	bool pedirImporte(float& importe);
	bool verificarInscripcionExistente(int legajo, int idCurso);
public:
	//CRUD Inscripciones
	void altaInscripcion();
	void bajaInscripcion();
	void modificarInscripcion();
	void listarInscripcionesActivas();
	void listarInscripcionesInactivas();
	void listarTodasInscripciones();
	void mostrarUnaInscripcion(const Inscripcion& inscripcion);

};
