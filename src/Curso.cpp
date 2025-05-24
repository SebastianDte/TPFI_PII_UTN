#include <cstring>
#include "Curso.h"
#include <string>

Curso::Curso()
{
    _id = 0;
    _nombre[0] = '\0';
    _cantMaximaAlumnos = 0;
    _idProfesor = 0;
    _estado = true;
}

Curso::Curso(int id, const std::string& nombre, int cantMaximaAlumnos, int idProfesor, bool estado)
{
    _id = id;
    strncpy(_nombre, nombre.c_str(), sizeof(_nombre) - 1);
    _nombre[sizeof(_nombre) - 1] = '\0'; //agregar valor nulo al final
    _cantMaximaAlumnos = cantMaximaAlumnos;
    _idProfesor = idProfesor;
    _estado = estado;
}

void Curso::setId(int id)
{
    _id = id;
}

void Curso::setNombre(const std::string& nombre)
{
    strncpy(_nombre, nombre.c_str(), sizeof(_nombre) - 1);
    _nombre[sizeof(_nombre) - 1] = '\0';
}

void Curso::setCantMaximaAlumnos(int cantMaximaAlumnos)
{
    _cantMaximaAlumnos = cantMaximaAlumnos;
}

void Curso::setNumeroAula(int numeroAula)
{
    _numeroAula = numeroAula;
}

void Curso::setIdProfesor(int idProfesor)
{
    _idProfesor = idProfesor;
}

void Curso::setEstado(bool estado)
{
    _estado = estado;
}

int Curso::getId() const
{
    return _id;
}

std::string Curso::getNombre() const
{
    return std::string(_nombre);
}

int Curso::getCantMaximaAlumnos() const
{
    return _cantMaximaAlumnos;
}

int Curso::getNumeroAula() const
{
    return _numeroAula;
}

int Curso::getIdProfesor() const
{
    return _idProfesor;
}

bool Curso::getEstado() const
{
    return _estado;
}

std::string Curso::toCSV() const
{
    return std::to_string(_id) + "," +
           std::string(_nombre) + "," +
           std::to_string(_cantMaximaAlumnos) + "," +
           std::to_string(_idProfesor) + "," +
           (_estado ? "ACTIVO" : "INACTIVO");
}
