#include <limits>
#include <iostream>
#include <iomanip>
#include "Utilidades.h"

std::string Utilidades::aMinusculas(const std::string& inputUsuario)
{

    std::string resultado = inputUsuario;
    for(int i = 0; i < (int)resultado.length(); i++)
    {
        if(resultado[i] >= 'A' && resultado[i] <= 'Z')
        {
            resultado[i] = resultado[i] + 32;
        }
    }
    return resultado;
}


bool Utilidades::esEnteroValido(const std::string& inputUsuario)
{
    // funcion para validar que recibamos valores enteros validos
    if(inputUsuario.empty()) return false;

    for (int i = 0; i < (int)inputUsuario.length(); i++)
    {
        // se compara con el codigo ASCII
        if (inputUsuario[i] < '0' || inputUsuario[i] > '9') return false;
    }
    return true;
}


bool Utilidades::esComandoSalir(const std::string& inputUsuario)
{
    return aMinusculas(inputUsuario) == "salir";
}


void Utilidades::mostrarEncabezado(const std::string& subtitulo)
{
    const int anchoTotal = 41;
    std::string linea(anchoTotal, '=');

    std::cout << linea << "\n";
    std::cout << std::setw((anchoTotal + 15) / 2) << "SISTEMA COLEGIO" << "\n";
    if (!subtitulo.empty())
    {
        int espaciosIzquierda = (anchoTotal - (int)subtitulo.length()) / 2;
        std::cout << std::setw(espaciosIzquierda + (int)subtitulo.length()) << subtitulo << "\n";
    }
    std::cout << linea << "\n";
}

void Utilidades::limpiarPantallaConEncabezado(const std::string& subtitulo)
{
    system("cls");
    mostrarEncabezado(subtitulo);
}


