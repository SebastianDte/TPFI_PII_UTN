#include <cstring>
#include "persona.h"
#include <string>

void Persona::copiarCadenaSegura(char *destino, const std::string &origen, size_t tam)
{
    strncpy(destino, origen.c_str(), tam);
    destino[tam - 1] = '\0';
}

// Constructor por defecto
Persona::Persona()
{
    _dni[0] = '\0';
    _nombre[0] = '\0';
    _apellido[0] = '\0';
    _telefono[0] = '\0';
    _email[0] = '\0';
    _direccion[0] = '\0';
    _fechaNacimiento = Fecha();
}

// Constructor con parámetros
Persona::Persona(const std::string &dni, const std::string &nombre, const std::string &apellido,
                 const std::string &telefono, const std::string &email, const std::string &direccion,
                 const Fecha &fechaNacimiento)
{
    copiarCadenaSegura(_dni, dni, sizeof(_dni));
    copiarCadenaSegura(_nombre, nombre, sizeof(_nombre));
    copiarCadenaSegura(_apellido, apellido, sizeof(_apellido));
    copiarCadenaSegura(_telefono, telefono, sizeof(_telefono));
    copiarCadenaSegura(_email, email, sizeof(_email));
    copiarCadenaSegura(_direccion, direccion, sizeof(_direccion));
    _fechaNacimiento = fechaNacimiento;
}

// Setters
void Persona::setDni(const std::string& dni) {
    copiarCadenaSegura(_dni, dni, sizeof(_dni));
}
void Persona::setNombre(const std::string& nombre) {
    copiarCadenaSegura(_nombre, nombre, sizeof(_nombre));
}
void Persona::setApellido(const std::string& apellido) {
    copiarCadenaSegura(_apellido, apellido, sizeof(_apellido));
}
void Persona::setTelefono(const std::string& telefono) {
    copiarCadenaSegura(_telefono, telefono, sizeof(_telefono));
}
void Persona::setEmail(const std::string& email) {
    copiarCadenaSegura(_email, email, sizeof(_email));
}
void Persona::setDireccion(const std::string& direccion) {
    copiarCadenaSegura(_direccion, direccion, sizeof(_direccion));
}
void Persona::setFechaNacimiento(const Fecha& fecha) {
    _fechaNacimiento = fecha;
}

// Getters
std::string Persona::getDni() const {
    return _dni;
}
std::string Persona::getNombre() const {
    return _nombre;
}
std::string Persona::getApellido() const {
    return _apellido;
}
std::string Persona::getTelefono() const {
    return _telefono;
}
std::string Persona::getEmail() const {
    return _email;
}
std::string Persona::getDireccion() const {
    return _direccion;
}
Fecha Persona::getFechaNacimiento() const {
    return _fechaNacimiento;
}

