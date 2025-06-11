#pragma once

#include "string"
#include "Persona.h"


class Profesor : public Persona {

private:

    int _id;
    bool _estado;

public:

    Profesor ();

    Profesor ( const int &id, const bool &estado,const std::string& dni,
            const std::string& nombre,const std::string& apellido,
            const std::string& telefono,const std::string& email,
            const std::string& direccion,const Fecha& fechaNacimiento);

    ///Setters
    void setId ( const int &id );
    void setEstado (const bool &estado);

    ///Getters
    int getId ();
    bool getEstado ();

    void mostrar();




};
