#pragma once
#include <string>

class Utilidades
{

public:
    std::string aMinusculas(const std::string& inputUsuario);
    bool esEnteroValido(const std::string& inputUsuario);
    bool esComandoSalir(const std::string& inputUsuario);

    void mostrarEncabezado(const std::string& subtitulo = "");
    void limpiarPantallaConEncabezado(const std::string& subtitulo = "");
};
