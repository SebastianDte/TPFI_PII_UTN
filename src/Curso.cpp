#include <cstring>
#include "Curso.h"
#include <string>

using namespace std;

Curso::Curso()
{
    _id = 0;
    _nombre[0] = '\0';
    _cantMaximaAlumnos = 0;
    _idProfesor = 0;
    _estado = true;
}

Curso::Curso(int id, string nombre, int cantMaximaAlumnos, int idProfesor, bool estado)
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

void Curso::setNombre(string nombre)
{
    strncpy(_nombre, nombre.c_str(), sizeof(_nombre) - 1);
    _nombre[sizeof(_nombre) - 1] = '\0';
}

void Curso::setCantMaximaAlumnos(int cantMaximaAlumnos)
{
    _cantMaximaAlumnos = cantMaximaAlumnos;
}

void Curso::setIdProfesor(int idProfesor)
{
    _idProfesor = idProfesor;
}

void Curso::setEstado(bool estado)
{
    _estado = estado;
}

int Curso::getId()
{
    return _id;
}

string Curso::getNombre()
{
    return string(_nombre);
}

int Curso::getCantMaximaAlumnos()
{
    return _cantMaximaAlumnos;
}

int Curso::getIdProfesor()
{
    return _idProfesor;
}

bool Curso::getEstado()
{
    return _estado;
}

string Curso::toCSV()
{
    return to_string(_id) + "," +
           string(_nombre) + "," +
           to_string(_cantMaximaAlumnos) + "," +
           to_string(_idProfesor) + "," +
           (_estado ? "ACTIVO" : "INACTIVO");
}
