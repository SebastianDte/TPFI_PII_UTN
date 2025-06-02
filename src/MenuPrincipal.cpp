#include "MenuPrincipal.h"
#include "MenuProfesor.h"
#include "MenuCurso.h"
#include <iostream>

void MenuPrincipal::mostrarMenuPrincipal() {
    MenuProfesor menuProfesor;

    // Si usás MenuCurso como atributo (_cursoMenu), asegurate de declararlo en la clase.


    int opcion;
    do {
        system("cls");
        std::cout << "=== SISTEMA COLEGIO ===\n";
        std::cout << "\n=== MENU PRINCIPAL ===\n";
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
                // alumnoMenu.mostrarMenu();
                break;
            case 2:
                _profesorMenu.mostrarMenuProfesor();
                break;
            case 3:

                // Acá lo nuevo que sumó la otra rama:
                // MenuCurso cursoMenu;
                // cursoMenu.mostrarMenuCurso();
                // _cursoMenu.mostrarMenuCurso();
                break;
            case 4:
                // inscripcionMenu.mostrarMenu();  // pendiente
                break;
            case 5:
                // reportesMenu.mostrarMenuReportes();  // pendiente

                _cursoMenu.mostrarMenuCurso();  // ojo que _cursoMenu debe ser un atributo

                _cursoMenu.mostrarMenuCurso();


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
    } while(opcion != 0);
}
