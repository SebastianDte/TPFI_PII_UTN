#pragma once
#include <string>
#include "Profesor.h"

class Utilidades
{

public:
    std::string aMinusculas(const std::string& inputUsuario);
    bool esEnteroValido(const std::string& inputUsuario);
    bool esFloatValido(const std::string& inputUsuario);
    bool esComandoSalir(const std::string& inputUsuario);

    bool soloNumeros(const std::string& input);
    bool soloLetras( std::string& input);

    void mostrarEncabezado(const std::string& subtitulo = "");
    void limpiarPantallaConEncabezado(const std::string& subtitulo = "");

    void pausar();
    void pausarYLimpiar();

    Profesor buscarProfesorEnArray(int idProfesor, Profesor* profesores, int cantidad);
};
