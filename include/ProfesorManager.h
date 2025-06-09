#pragma once
#include "Profesor.h"
#include "ProfesorArchivo.h"
#include "Utilidades.h"

class ProfesorManager{

private:
    ProfesorArchivo _archivo;
    Utilidades _utilidades;
    Profesor _profesor;

public:

    bool dniValidacion(const std::string& input);
    bool nombreValidacion(const std::string& input);
    bool apellidoValidacion(const std::string& input);
    bool telefonoValidacion(const std::string& input);
    bool emailValidacion(const std::string& input);
    bool direccionValidacion(const std::string& input);


    void alta();
    void modificar();
    void listar();
    void buscar();

};
