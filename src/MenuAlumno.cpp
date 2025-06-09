#include <iostream>
#include "MenuAlumno.h"
#include "AlumnoManager.h"
#include "Utilidades.h"

MenuAlumno::MenuAlumno()
{
    _manager = AlumnoManager();
}

void MenuAlumno:: mostrarMenuAlumno()
{
    Utilidades _utilidades = Utilidades();
    int opcion;

    do
    {
        _utilidades.limpiarPantallaConEncabezado("=== MENU DE ALUMNOS ===");;
        std::cout << "1. Alta de alumno" << std::endl;
        std::cout << "2. Baja de alumno" << std::endl;
        std::cout << "3. Modificar alumno" << std::endl;
        std::cout << "4. Listar alumnos" << std::endl;
        std::cout << "5. Buscar alumno por Legajo" << std::endl;
        std::cout << "0. Volver al men� principal" << std::endl;
        std::cout << "=========================================\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        system("cls");
        switch(opcion)
        {
        case 1:
            _manager.altaAlumno();
            system("pause");
            break;
        case 2:
            _manager.bajaAlumno();
            system("pause");
            break;
        case 3:
           _manager.modificarAlumno();
            system("pause");
            break;
        case 4:
            _manager.listarAlumnos();
            system("pause");
            break;
        case 5:
            _manager.buscarAlumnoLegajo();
            system("pause");
            break;
        case 0:
            std::cout << "Volviendo al menú principal..." << std::endl;
            break;
        default:
            std::cout << "Opción inválida. Intente nuevamente.\n";
        }

    }
    while(opcion != 0);

}
