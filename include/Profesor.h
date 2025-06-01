#pragma once

#include "string"
#include "Persona.h"


class Profesor : public Persona {

private:

    int _id;

public:

    Profesor ();

    Profesor ( int id,const std::string& dni,const std::string& nombre,const std::string& apellido,
              const std::string& telefono,const std::string& email,const std::string& direccion,const Fecha& fechaNacimiento);

    void setId ( int id );

    int getId ();

    //void cargar(int id);

    void mostrar();




};
