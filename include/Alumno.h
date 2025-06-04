#pragma once
#include <string>
#include "Persona.h"
class Alumno : public Persona
{
private:
    int _legajo;
    bool _activo;

public:
    Alumno();
    Alumno(int legajo,
           const std::string &dni,
           const std::string &nombre,
           const std::string &apellido,
           const std::string &telefono,
           const std::string &email,
           const std::string &direccion,
           const Fecha &fechaNacimiento,
           bool activo);

    void setLegajo(int legajo);
    void setActivo(bool activo);

    int getLegajo() const;
    bool getActivo() const;

    std::string toCSV() const;

    bool operator!=(const Alumno& otro) const;
};
