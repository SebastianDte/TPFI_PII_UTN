#pragma once
#include <cstring>
#include <string>
#include "CursoManager.h"
#include "AlumnoManager.h"
#include "Inscripcion.h"
#include "InscripcionArchivo.h"

class InscripcionManager {
private:
	InscripcionArchivo _archivoInscripciones;
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
	void mostrarInscripcionPorId(int idInscripcion);
	//Metodo auxiliares.
	bool existeAlumnoActivo(int legajo);
	bool existeCursoActivo(int idCurso);

	bool controlCupo(int idCurso);

	void bajaInscripcionesPorCurso(int idCurso);
	void bajaInscripcionesPorAlumno(int legajo);
};
