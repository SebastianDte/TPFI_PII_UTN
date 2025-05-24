#include "Utilidades.h"

std::string Utilidades::aMinusculas(const std::string& inputUsuario)
{

    std::string resultado = inputUsuario;
    for(int i = 0; i < resultado.length(); i++)
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

    for (int i = 0; i < inputUsuario.length(); i++)
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
