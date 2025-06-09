#include <iostream>
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

void ReportesManager::importeTotalRecaudadoPorCurso()
{
    std::cout << "Importe total recaudado por curso" << std::endl;
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