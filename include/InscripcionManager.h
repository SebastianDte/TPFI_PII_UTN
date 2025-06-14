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
	void listarTodasInscripciones();

	//Listas
	void listarInscripcionesActivas();
	void listarInscripcionesInactivas();
	void mostrarUnaInscripcion(const Inscripcion& inscripcion);

	//Metodo auxiliares.
	bool existeAlumnoActivo(int legajo);
	bool existeCursoActivo(int idCurso);

	void bajaInscripcionesPorCurso(int idCurso);
	void bajaInscripcionesPorAlumno(int legajo);
};
