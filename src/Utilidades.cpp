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

bool Utilidades::esFloatValido(const std::string& inputUsuario)
{
    if (inputUsuario.empty()) return false;

    bool puntoEncontrado = false;
    int digitos = 0;

    for (size_t i = 0; i < inputUsuario.length(); i++) {
        char c = inputUsuario[i];
        if (c >= '0' && c <= '9') {
            digitos++;
            continue;
        }
        if (c == '.') {
            if (puntoEncontrado) return false;
            puntoEncontrado = true;
            continue;
        }
        return false;
    }
    return digitos > 0;
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


bool Utilidades::soloNumeros(const std::string& input){

    int tamanio = input.length();

    for ( int i = 0; i<tamanio; i++ ){

       if ( input[i] < '0' || input[i] > '9' ){

            return false;

       }

    }

   return true;
}

bool Utilidades::soloLetras(std::string& input){

    int tamanio = input.length();


    for ( int i = 0; i<tamanio; i++ ){

        ///codigos ASCII para letras minusculas del 97 al 122, espacio=32

        ///Nombres compuestos


        if (input[i] < 'a' || input[i] > 'z'){


            if ( input[i] == ' ' ){

                if( input.front() == ' ' || input.back() == ' ' ) {

                    return false;

                }else{

                    continue;

                }

            }

            return false;

        }




    }

    return true;

}

void Utilidades::pausar() {
    std::cout << "\nPresione ENTER para continuar...";
    std::cin.get();
}

void Utilidades::pausarYLimpiar() {
    pausar();
    system("cls");
}
