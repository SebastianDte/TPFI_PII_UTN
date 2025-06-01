#pragma once
#include "ProfesorArchivo.h"

class ProfesorManager{

private:
    ProfesorArchivo _archivo;

public:

    void alta();
    void baja();
    void modificar();
    void listar();
    void buscar();


};
