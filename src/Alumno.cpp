#include <cstring>
#include <string>
#include "Alumno.h"
#include "Persona.h"
/// asdasdasdasdsadasasdasdasd
// Constructor por defecto: se invoca automáticamente el constructor por defecto de Persona.
Alumno::Alumno()
    : Persona(), _legajo(0), _activo(true)
{
}

// Constructor parametrizado: se invoca el constructor de Persona para inicializar
// los atributos comunes y luego se inicializan los miembros propios de Alumno.
Alumno::Alumno(int legajo,
               const std::string &dni,
               const std::string &nombre,
               const std::string &apellido,
               const std::string &telefono,
               const std::string &email,
               const std::string &direccion,
               const Fecha &fechaNacimiento,
               bool activo)
    : Persona(dni, nombre, apellido, telefono, email, direccion, fechaNacimiento),
      _legajo(legajo), _activo(activo)
{
}

void Alumno::setLegajo(int legajo)
{
    _legajo = legajo;
}

void Alumno::setActivo(bool activo)
{
    _activo = activo;
}

int Alumno::getLegajo() const
{
    return _legajo;
}

bool Alumno::getActivo() const
{
    return _activo;
}

std::string Alumno::toCSV() const
{

    std::string csv =
        getDni() + "," +
        getNombre() + "," +
        getApellido() + "," +
        getTelefono() + "," +
        getEmail() + "," +
        getDireccion() + "," +
        getFechaNacimiento().toString() + ",";


    csv += std::to_string(_legajo) + "," + (_activo ? "true" : "false");
    return csv;
}

bool Alumno::operator!=(const Alumno &otro) const {
    // Puedes comparar todos los campos que definen a un alumno.
    // A continuación, se compara usando el legajo, y además otros datos.
    return (_legajo != otro._legajo) ||
           (getDni() != otro.getDni()) ||
           (getNombre() != otro.getNombre()) ||
           (getApellido() != otro.getApellido()) ||
           (getTelefono() != otro.getTelefono()) ||
           (getEmail() != otro.getEmail()) ||
           (getDireccion() != otro.getDireccion()) ||
           (getActivo() != otro.getActivo()) ;
}
