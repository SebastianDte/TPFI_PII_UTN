#pragma once
#include <string>
#include "Fecha.h"

class Persona
{
private:
    char _dni[10];
    char _nombre[30];
    char _apellido[30];
    char _telefono[20];
    char _email[50];
    char _direccion[50];
    Fecha _fechaNacimiento;

    void copiarCadenaSegura(char* destino, const std::string& origen, size_t tam);
public:
    // Constructor por defecto
    Persona();

    // Constructor con parámetros
    Persona(const std::string& dni, const std::string& nombre, const std::string& apellido,
            const std::string& telefono, const std::string& email, const std::string& direccion,
            const Fecha& fechaNacimiento);

    // Setters
    void setDni(const std::string& dni);
    void setNombre(const std::string& nombre);
    void setApellido(const std::string& apellido);
    void setTelefono(const std::string& telefono);
    void setEmail(const std::string& email);
    void setDireccion(const std::string& direccion);
    void setFechaNacimiento(const Fecha& fecha);

    // Getters
    std::string getDni() const;
    std::string getNombre() const;
    std::string getApellido() const;
    std::string getTelefono() const;
    std::string getEmail() const;
    std::string getDireccion() const;
    Fecha getFechaNacimiento() const;
};
