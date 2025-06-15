#include <iostream>
#include <iomanip>
#include "ReportesManager.h"
#include "CursoArchivo.h"
#include "AlumnoArchivo.h"
#include "InscripcionArchivo.h"
#include "ProfesorArchivo.h"
#include "Utilidades.h"

ReportesManager::ReportesManager()
{
    _cursoArchivo = CursoArchivo();
    _alumnoArchivo = AlumnoArchivo();
    _inscripcionArchivo = InscripcionArchivo();
    _profesorArchivo = ProfesorArchivo();
    _utilidades = Utilidades();
}

void ReportesManager::totalInscriptosPorCurso()
{
    std::cout << "Total de inscriptos por curso" << std::endl;
}

void ReportesManager::alumnosInscriptosEnCurso()
{
    std::cout << "Alumnos inscriptos en un curso" << std::endl;
}

void ReportesManager::importeTotalRecaudadoPorAlumno()
{
    std::cout << "Importe total recaudado por alumno" << std::endl;
}

void ReportesManager::promedioImportePorCurso()
{
    std::cout << "Promedio de importe por curso" << std::endl;
}

void ReportesManager::inscripcionesEntreFechas()
{
    std::cout << "Inscripciones entre fechas" << std::endl;
}

void ReportesManager::cursosConAulaOcupada()
{
    CursoArchivo archivoCursos;
    ProfesorArchivo archivoProfesor;
    Utilidades utilidades;
    int totalCursos = archivoCursos.cantRegistros();

    if (totalCursos <= 0)
    {
        std::cout << "No hay cursos registrados en el sistema." << std::endl;
        return;
    }

    utilidades.limpiarPantallaConEncabezado("=== REPORTE - CURSOS POR AULA ===");

    Curso* cursos = new Curso[totalCursos];
    int* aulas = new int[totalCursos];
    int cantidadAulasUnicas = 0;

    for (int i = 0; i < totalCursos; i++)
    {
        cursos[i] = archivoCursos.leer(i);
    }

    // obtenemos las aulas unicas de los cursos
    for (int i = 0; i < totalCursos; i++)
    {
        bool aulaExiste = false;
        for (int j = 0; j < cantidadAulasUnicas; j++)
        {
            if (aulas[j] == cursos[i].getNumeroAula())
            {
                aulaExiste = true;
                break;
            }
        }
        if (!aulaExiste)
        {
            aulas[cantidadAulasUnicas] = cursos[i].getNumeroAula();
            cantidadAulasUnicas++;
        }
    }

    // las ordenamos para que se puedan ver mas facil
    for (int i = 0; i < cantidadAulasUnicas - 1; i++)
    {
        for (int j = 0; j < cantidadAulasUnicas - i - 1; j++)
        {
            if (aulas[j] > aulas[j + 1])
            {
                int temp = aulas[j];
                aulas[j] = aulas[j + 1];
                aulas[j + 1] = temp;
            }
        }
    }


    for (int i = 0; i < cantidadAulasUnicas; i++)
    {
        int aulaActual = aulas[i];
        int cursosEnAula = 0;

        for (int j = 0; j < totalCursos; j++)
        {
            if (cursos[j].getNumeroAula() == aulaActual)
            {
                cursosEnAula++;
            }
        }

        std::cout << "\n=== AULA " << aulaActual << " ===\n";
        std::cout << "Cantidad de cursos asignados: " << cursosEnAula << "\n";
        std::cout << "---------------------------\n";

        for (int j = 0; j < totalCursos; j++)
        {
            if (cursos[j].getNumeroAula() == aulaActual)
            {
                int posicionProfesor = archivoProfesor.buscar(cursos[j].getIdProfesor());
                Profesor profesor = archivoProfesor.leer(posicionProfesor);

                std::cout << "ID Curso: " << cursos[j].getId() << "\n";
                std::cout << "Nombre: " << cursos[j].getNombre() << "\n";
                std::cout << "Profesor: " << profesor.getNombre() << " " << profesor.getApellido() << "\n";
                std::cout << "Capacidad: " << cursos[j].getCantMaximaAlumnos() << " alumnos\n";
                std::cout << "---------------------------\n";
            }
        }
    }
    delete[] cursos;
    delete[] aulas;
}

void ReportesManager::profesoresConCursosAsignados()
{
    std::cout << "Profesores con cursos asignados" << std::endl;
}


bool ReportesManager::pedirAnioValido(int& anio)
{
    std::string input;
    int anioActual = Fecha::fechaActual().getAnio();

    while (true)
    {
        std::cout << "Ingrese el año para filtrar inscripciones (0 = año actual, 'salir' para cancelar): ";
        std::getline(std::cin, input);

        if (_utilidades.esComandoSalir(input))
            return false;

        if (!_utilidades.esEnteroValido(input))
        {
            std::cout << "Entrada inválida. Intente nuevamente.\n\n";
            continue;
        }

        anio = std::stoi(input);

        if (anio == 0)
        {
            anio = anioActual;
            return true;
        }

        if (anio < 0)
        {
            std::cout << "El año no puede ser negativo. Intente nuevamente.\n\n";
            continue;
        }

        if (anio > anioActual)
        {
            std::cout << "El año no puede ser mayor al actual (" << anioActual << "). Intente nuevamente.\n\n";
            continue;
        }

        return true;
    }
}


void ReportesManager::importeTotalRecaudadoPorCurso()
{
    _utilidades.limpiarPantallaConEncabezado("=== REPORTE - RECAUDACIÓN POR CURSO ===");

    int anioFiltro;
    if (!pedirAnioValido(anioFiltro))
    {
        std::cout << "\nReporte cancelado por el usuario.\n";
        return;
    }

    int totalCursos = _cursoArchivo.cantRegistros();
    if(totalCursos <= 0)
    {
        std::cout << "No hay cursos cargados.\n";
        return;
    }

    // pedimos memoria
    Curso* cursos = new Curso[totalCursos];
    for (int i = 0; i < totalCursos; i++)
    {
        cursos[i] = _cursoArchivo.leer(i);
    }

    int totalInscripciones = _inscripcionArchivo.cantRegistros();
    if (totalInscripciones <= 0)
    {
        std::cout << "No hay inscripciones cargadas.\n";
        delete[] cursos;
        return;
    }

    Inscripcion* inscripciones = new Inscripcion[totalInscripciones];
    for (int i = 0; i < totalInscripciones; i++)
    {
        _inscripcionArchivo.leer(i, inscripciones[i]);
    }

    // pedimos memoria para almacenar los datos del recaudo y cantidad inscriptos para cada curso
    float* totalRecaudado = new float[totalCursos];
    int* cantidadInscriptos = new int[totalCursos];
    for (int i = 0; i < totalCursos; i++)
    {
        totalRecaudado[i] = 0;
        cantidadInscriptos[i] = 0;
    }

    for (int i = 0; i < totalInscripciones; i++)
    {
        if (!inscripciones[i].getEstado()) continue;
        if (inscripciones[i].getFechaInscripcion().getAnio() != anioFiltro) continue;

        int idCurso = inscripciones[i].getIdCurso();
        for (int j = 0; j < totalCursos; j++)
        {
            if (cursos[j].getId() == idCurso && cursos[j].getEstado())
            {
                totalRecaudado[j] += inscripciones[i].getImporteAbonado();
                cantidadInscriptos[j]++;
                break;
            }
        }
    }

    std::cout << "\nRECAUDACIÓN POR CURSO EN EL AÑO " << anioFiltro << "\n";
    std::cout << "-------------------------------------------------------------------\n";
    std::cout << std::left << std::setw(10) << "ID"
              << std::setw(30) << "NOMBRE CURSO"
              << std::setw(15) << "IMPORTE"
              << "INSCRIPCIONES\n";
    std::cout << "-------------------------------------------------------------------\n";

    bool hayDatos = false;

    for (int i = 0; i < totalCursos; i++)
    {
        if (cursos[i].getEstado() && cantidadInscriptos[i] > 0)
        {
            hayDatos = true;
            // uso de setw para establecer mejor los anchos (recomendado por libro de Joyanes)
            std::cout << std::left << std::setw(10) << cursos[i].getId()
                      << std::setw(30) << cursos[i].getNombre()
                      << "$" << std::setw(14) << totalRecaudado[i]
                      << cantidadInscriptos[i] << "\n";
        }
    }

    if (!hayDatos)
    {
        std::cout << "No hay datos de inscripciones para ese año.\n";
    }

    std::cout << "-------------------------------------------------------------------\n";

    delete[] cursos;
    delete[] inscripciones;
    delete[] totalRecaudado;
    delete[] cantidadInscriptos;
}
