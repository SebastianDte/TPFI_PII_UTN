#include "MenuPrincipal.h"
#include <iostream>

void MenuPrincipal::mostrarMenuPrincipal() {
    int opcion;
    do {
        std::cout << "\n=== MENU PRINCIPAL ===\n";
        std::cout << "1. Menu Alumno\n";
        std::cout << "2. Menu Profesor\n";
        std::cout << "3. Menu Curso\n";
        std::cout << "4. Menu Inscripcion\n";
        std::cout << "5. Menu Reportes\n";
        std::cout << "0. Salir\n";
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;

        switch(opcion) {
            case 1:
                //alumnoMenu.mostrarMenu();
                break;
            case 2:
                //profesorMenu.mostrarMenuProfesor();
                break;
            case 3:
                //cursoMenu.mostrarMenuCurso();
                break;
            case 4:
                //inscripcionMenu.mostrarMenu();
                break;
            case 5:
                //reportesMenu.mostrarMenuReportes();
                break;
            case 0:
                std::cout << "Saliendo del sistema...\n";
                break;
            default:
                std::cout << "Opcion invalida, intente nuevamente.\n";
                break;
        }
    } while(opcion != 0);
}
