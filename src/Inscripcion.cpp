#include "inscripcion.h"


// Constructor por defecto
Inscripcion::Inscripcion(){
	_idInscripcion = 0;
	_legajoAlumno = 0;
	_idCurso = 0;
	_importeAbonado = 0.0f;
	_fechaInscripcion = Fecha();
	_estado = true;
}
//Constructor con parámetros
Inscripcion::Inscripcion(int idInscripcion,int legajoAlumno, int idCurso, const Fecha& fechaInscripcion, float importeAbonado,bool estado) {
	_idInscripcion = idInscripcion;
	_legajoAlumno = legajoAlumno;
	_idCurso = idCurso;
	_fechaInscripcion = fechaInscripcion;
	_importeAbonado = importeAbonado;
	_estado = estado;
}

//Setters
void Inscripcion::setIdInscripcion(int idInscripcion) {
	_idInscripcion = idInscripcion;
}
void Inscripcion::setLegajoAlumno(int legajo) {
	_legajoAlumno = legajo;
}
void Inscripcion::setIdCurso(int idCurso) {
	_idCurso = idCurso;
}
void Inscripcion::setFechaInscripcion(const Fecha& fecha) {
	_fechaInscripcion = fecha;
}
void Inscripcion::setImporteAbonado(float importe) {
	_importeAbonado = importe;
}
void Inscripcion::setEstado(bool estado) {
	_estado = estado;
}
//Getters
int Inscripcion::getIdInscripcion() const {
	return _idInscripcion;
}
int Inscripcion::getLegajoAlumno() const {
	return _legajoAlumno;
}
int Inscripcion::getIdCurso() const {
	return _idCurso;
}
Fecha Inscripcion::getFechaInscripcion() const {
	return _fechaInscripcion;
}
float Inscripcion::getImporteAbonado() const {
	return _importeAbonado;
}
bool Inscripcion::getEstado() const {
	return _estado;
}
