#include <iostream>
#include "MenuProfesor.h"
#include "Utilidades.h"



void MenuProfesor::mostrarMenuProfesor(){
    std::string input;
    int opcion;
    Utilidades _utilidades;

    std::cin.ignore();

    while(true)
    {

        _utilidades.limpiarPantallaConEncabezado("=== MENU PROFESOR ===");
        std::cout << "1. Agregar profesor.\n";
        std::cout << "2. Baja de profesor.\n";
        std::cout << "3. Modificar profersor.\n";
        std::cout << "4. Listar profesores.\n";
        std::cout << "5. Buscar profesor por ID.\n";
        std::cout << "6. Reactivar profesor.\n";
        std::cout << "0. Volver al menu principal.\n";
        std::cout << "=========================================\n";
        std::cout << "Ingrese una opcion.\n";
        std::getline(std::cin,input);

        if ( !_utilidades.esEnteroValido(input) ){

            std::cout << "\nEl valor ingresado es incorrecto, debe ser un numero entero.Intente nuevamente.\n\n";
            system("pause");
            continue;
        }

        opcion = std::stoi(input);

        switch(opcion){

        case 1:

            _manager.alta();

            system("pause");

            break;

        case 2:

            _manager.baja();

            system("pause");

            break;

        case 3:

            _manager.modificar();

            system("pause");

            break;

        case 4:

            _manager.listar();

            system("pause");

            break;

        case 5:


            _manager.buscar();

            system("pause");

            break;

        case 6:


            _manager.reactivarProfesor();

            system("pause");

            break;

        case 0:

            return;

        default:

            std::cout<<"La opcion ingresada es incorrecta, intente nuevamente.\n";

            system("pause");

            break;


        }


    }

}

