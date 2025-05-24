#include <iostream>
#include "MenuCurso.h"
#include "CursoManager.h"

MenuCurso::MenuCurso()
{
    _manager = CursoManager();
}

void MenuCurso:: mostrarMenuCurso()
{

    int opcion;

    do
    {
        system("cls");
        std::cout << "=== SISTEMA COLEGIO ===\n";
        std::cout << "\n=== MENU DE CURSOS ===\n";
        std::cout << "1. Alta de curso" << std::endl;
        std::cout << "2. Baja de curso" << std::endl;
        std::cout << "3. Modificar curso" << std::endl;
        std::cout << "4. Listar cursos" << std::endl;
        std::cout << "5. Buscar curso por ID" << std::endl;
        std::cout << "0. Volver al menú principal" << std::endl;
        std::cout << "======================" << std::endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        system("cls");
        switch(opcion)
        {
        case 1:
            _manager.altaCurso();
            system("pause");
            break;
        case 2:
            _manager.bajaCurso();
            system("pause");
            break;
        case 3:
            _manager.modificarCurso();
            system("pause");
            break;
        case 4:
            _manager.listarCursos();
            system("pause");
            break;
        case 5:
            _manager.buscarCursoID();
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
