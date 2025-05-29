#include <iostream>
#include "MenuCurso.h"
#include "CursoManager.h"
#include "Utilidades.h"

MenuCurso::MenuCurso()
{
    _manager = CursoManager();
}

void MenuCurso::mostrarMenuCurso()
{
    Utilidades utilidades;
    std::string inputUsuario;
    int opcion = -1;

    do
    {
        std::cin.clear();
        std::cin.ignore();
        system("cls");
        std::cout << "=========================================\n";
        std::cout << "             SISTEMA COLEGIO             \n";
        std::cout << "         === MENU DE CURSOS ===          \n";
        std::cout << "=========================================\n";
        std::cout << "1. Alta de curso\n";
        std::cout << "2. Baja de curso\n";
        std::cout << "3. Modificar curso\n";
        std::cout << "4. Listar cursos\n";
        std::cout << "5. Buscar curso por ID\n";
        std::cout << "0. Volver al menú principal\n";
        std::cout << "=========================================\n";
        std::cout << "Seleccione una opción: ";

        std::getline(std::cin, inputUsuario);

        if (!utilidades.esEnteroValido(inputUsuario))
        {
            std::cout << "Entrada inválida. Debe ingresar un número entero.\n";
            system("pause");
            continue;
        }

        opcion = std::stoi(inputUsuario);

        switch(opcion)
        {
            case 1:
                system("cls");
                _manager.altaCurso();
                system("pause");
                break;
            case 2:
                system("cls");
                _manager.bajaCurso();
                system("pause");
                break;
            case 3:
                system("cls");
                _manager.modificarCurso();
                system("pause");
                break;
            case 4:
                system("cls");
                _manager.listarCursos();
                system("pause");
                break;
            case 5:
                system("cls");
                _manager.buscarCursoID();
                system("pause");
                break;
            case 0:
                std::cout << "Volviendo al menú principal..." << std::endl;
                break;
            default:
                std::cout << "Opción inválida. Intente nuevamente.\n";
                system("pause");
                break;
        }

    } while(opcion != 0);
}

