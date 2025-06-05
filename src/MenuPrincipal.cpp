#include "MenuPrincipal.h"
#include "MenuProfesor.h"
#include "MenuCurso.h"
#include "MenuInscripcion.h"
#include "Utilidades.h"
#include <iostream>


void MenuPrincipal::mostrarMenuPrincipal() {
    Utilidades _utilidades = Utilidades();
    int opcion;
    do
    {
        _utilidades.limpiarPantallaConEncabezado("MENU PRINCIPAL");
        std::cout << "1. Menu Alumno\n";
        std::cout << "2. Menu Profesor\n";
        std::cout << "3. Menu Curso\n";
        std::cout << "4. Menu Inscripcion\n";
        std::cout << "5. Menu Reportes\n";
        std::cout << "0. Salir\n";
        std::cout << "===========================\n";
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;

        system("cls");

        switch(opcion) {
            case 1:
                 alumnoMenu.mostrarMenuAlumno();
                break;
            case 2:
                _profesorMenu.mostrarMenuProfesor();
                break;
            case 3:
                _cursoMenu.mostrarMenuCurso();

                break;
            case 4:
                //_inscripcionMenu.mostrarMenu();
                break;
            case 5:
                // reportesMenu.mostrarMenuReportes();
                break;
            case 0:
                std::cout << "Saliendo del sistema...\n";
                break;
            default:
                std::cout << "Opcion invalida, intente nuevamente.\n";
                break;
        }

        std::cout << std::endl;
        system("pause");
    }
    while(opcion != 0);
}
