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

	//Metodo auxiliares para validaciones
	bool pedirLegajoAlumno(int& legajo);
	bool pedirIdCurso(int& idCurso);
	bool pedirImporte(float& importe);
	bool verificarInscripcionExistente(int legajo, int idCurso);
	bool existeAlumnoActivo(int legajo);
	bool existeCursoActivo(int idCurso);
	bool controlCupo(int idCurso);
	int mostrarMenuModificacion(const Inscripcion& original);

	void mostrarUnaInscripcion(const Inscripcion& inscripcion);

public:
	//CRUD Inscripciones
	void altaInscripcion();
	void bajaInscripcion();
	void modificarInscripcion();

	//Listas
	void mostrarListadoInscripciones(int filtroEstado);
	bool mostrarInscripcionPorId(int idInscripcion);
	void mostrarInscripcionPorId();

	//Metodos para bajas en cascada
	void bajaInscripcionesPorCurso(int idCurso);
	void bajaInscripcionesPorAlumno(int legajo);

	int contarInscriptosActivosPorCurso(int idCurso) const;
};
