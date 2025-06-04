#pragma once
#include <cstring>
#include <string>
#include"Fecha.h"

class Inscripcion{
private:
	int _idInscripcion;
	int _legajoAlumno;
	int _idCurso;
	Fecha _fechaInscripcion;
	float _importeAbonado;
	bool _estado;
public:
	// Constructor por defecto
	Inscripcion();

	// Constructor con parámetros
	Inscripcion(int idInscripcion,int legajoAlumno, int idCurso, const Fecha& fechaInscripcion, float importeAbonado,bool estado);
	// Getters
	int getIdInscripcion() const;
	int getLegajoAlumno() const;
	int getIdCurso() const;
	Fecha getFechaInscripcion() const;
	float getImporteAbonado() const ;
	bool getEstado()const;
	// Setters
	void setIdInscripcion(int idInscripcion);
	void setLegajoAlumno(int legajo);
	void setIdCurso(int idCurso);
	void setFechaInscripcion(const Fecha& fecha);
	void setImporteAbonado(float importe);
	void setEstado(bool estado);
};
