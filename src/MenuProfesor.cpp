#include "iostream"
#include "MenuProfesor.h"



void MenuProfesor::mostrarMenuProfesor(){
    int opcion;



    do{

        system("cls");

        std::cout << "\n==== Menu Profesor ==== \n";
        std::cout << "1) Agregar profesor.\n";
        std::cout << "2) Borrar profesor.\n";
        std::cout << "3) Modificar profersor.\n";
        std::cout << "4) Listar profesores.\n";
        std::cout << "5) Buscar profesor por ID.\n";
        std::cout << "0) Volver al menu principal.\n";
        std::cout << "Ingrese una opcion.\n";
        std::cin >> opcion;

        switch(opcion){

        case 1:
            system("cls");

            _manager.alta();

            system("pause");

            break;

        case 2:

            system("cls");

            //Metodo baja Managger

            system("pause");

            break;

        case 3:

            system("cls");

            _manager.modificar();

            system("pause");

            break;

        case 4:

            system("cls");

            _manager.listar();

            system("pause");

            break;

        case 5:

            system("cls");

            _manager.buscar();

            system("pause");

            break;

        case 0:
            system("cls");

            return;

        default:

            system("cls");

            std::cout<<"La opcion ingresada es incorrecta, intente nuevamente.\n";

            system("pause");

            break;


        }


    }while( opcion !=0 );



    }

