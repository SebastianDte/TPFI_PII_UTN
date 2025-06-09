#include <iostream>
#include "MenuReportes.h"
#include "ReportesManager.h"
#include "Utilidades.h"

MenuReportes::MenuReportes()
{
    _manager = ReportesManager();
}

void MenuReportes::mostrarMenu()
{
    Utilidades _utilidades;
    std::string inputUsuario;
    int opcion = -1;

    do
    {
        std::cin.clear();
        std::cin.ignore();
        _utilidades.limpiarPantallaConEncabezado("=== MENU DE REPORTES ===");
        std::cout << "1. Total de inscriptos por curso\n";
        std::cout << "2. Alumnos inscriptos en un curso\n";
        std::cout << "3. Importe total recaudado por curso\n";
        std::cout << "4. Importe total recaudado por alumno\n";
        std::cout << "5. Promedio de importe por curso\n";
        std::cout << "6. Inscripciones entre fechas\n";
        std::cout << "7. Cursos con aula ocupada\n";
        std::cout << "8. Profesores con cursos asignados\n";
        std::cout << "0. Volver al menú principal\n";
        std::cout << "=========================================\n";
        std::cout << "Seleccione una opción: ";

        std::getline(std::cin, inputUsuario);

        if (!_utilidades.esEnteroValido(inputUsuario))
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
            _manager.totalInscriptosPorCurso();
            system("pause");
            break;
        case 2:
            system("cls");
            _manager.alumnosInscriptosEnCurso();
            system("pause");
            break;
        case 3:
            system("cls");
            _manager.importeTotalRecaudadoPorCurso();
            system("pause");
            break;
        case 4:
            system("cls");
            _manager.importeTotalRecaudadoPorAlumno();
            system("pause");
            break;
        case 5:
            system("cls");
            _manager.promedioImportePorCurso();
            system("pause");
            break;
        case 6:
            system("cls");
            _manager.inscripcionesEntreFechas();
            system("pause");
            break;
        case 7:
            system("cls");
            _manager.cursosConAulaOcupada();
            system("pause");
            break;
        case 8:
            system("cls");
            _manager.profesoresConCursosAsignados();
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
