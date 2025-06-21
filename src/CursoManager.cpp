#include <iostream>
#include <limits>
#include "Curso.h"
#include "CursoManager.h"
#include "CursoArchivo.h"
#include "Utilidades.h"
#include "ProfesorArchivo.h"
#include "Profesor.h"
#include "InscripcionArchivo.h"
#include "Inscripcion.h"

CursoManager::CursoManager()
{
    _archivo = CursoArchivo("cursos.dat");
    _utilidades = Utilidades();
}



// Verifica si el número de aula está disponible para un nuevo curso, si es para
// modificar un curso, se debe pasar el id del curso a modificar
// para que no haya conflicto consigo mismo
bool CursoManager::aulaUnica(int& numeroAula, int idCursoExcluido)
{
    CursoArchivo archivoCurso;
    int cant = archivoCurso.cantRegistros();

    for (int i = 0; i < cant; i++)
    {
        Curso curso = archivoCurso.leer(i);
        if (curso.getNumeroAula() == numeroAula)
        {
            if (idCursoExcluido == -1 || curso.getId() != idCursoExcluido)
            {
                return false;
            }
        }
    }

    return true;
}

bool CursoManager::pedirNombreCurso(std::string& nombre)
{
    std::string input;
    while (true)
    {
        std::cout << "Ingrese nombre del curso (m�ximo 49 caracteres): ";
        std::getline(std::cin, input);

        if (_utilidades.esComandoSalir(input))
            return false;

        if (input.empty())
        {
            std::cout << "\nEl nombre no puede estar vac�o. Intente nuevamente.\n\n";
            continue;
        }

        if (input.length() < 3)
        {
            std::cout << "\nEl nombre debe tener al menos 3 caracteres. Intente nuevamente.\n\n";
            continue;
        }

        if (input.length() > 49)
        {
            std::cout << "\nEl nombre solo puede tener m�ximo 49 caracteres. Intente nuevamente.\n\n";
            continue;
        }

        nombre = input;
        return true;
    }
}

bool CursoManager::pedirCantidadMaximaAlumnos(int& cantidad)
{
    std::string input;
    while (true)
    {
        std::cout << "Ingrese la cantidad m�xima de alumnos: ";
        std::getline(std::cin, input);

        if (_utilidades.esComandoSalir(input))
            return false;

        if (!_utilidades.esEnteroValido(input))
        {
            std::cout << "\nDebe ingresar un n�mero entero v�lido. Intente nuevamente.\n\n";
            continue;
        }

        cantidad = std::stoi(input);
        if (cantidad <= 0)
        {
            std::cout << "\nLa cantidad debe ser mayor que cero. Intente nuevamente.\n\n";
            continue;
        }

        if (cantidad > 500)
        {
            std::cout << "\nLa cantidad máxima permitida es 500. Intente nuevamente.\n\n";
            continue;
        }

        return true;
    }
}

bool CursoManager::pedirNumeroAula(int& aula, int idCursoExcluido)
{
    std::string input;
    while (true)
    {
        std::cout << "Ingrese el n�mero de aula: ";
        std::getline(std::cin, input);

        if (_utilidades.esComandoSalir(input))
            return false;

        if (!_utilidades.esEnteroValido(input))
        {
            std::cout << "\nDebe ingresar un n�mero entero v�lido. Intente nuevamente.\n\n";
            continue;
        }

        aula = std::stoi(input);
        if (aula <= 0)
        {
            std::cout << "\nEl número de aula debe ser mayor que cero. Intente nuevamente.\n\n";
            continue;
        }

        if (!aulaUnica(aula, idCursoExcluido))
        {
            std::cout << "\nEl número de aula ya está en uso. Intente nuevamente.\n\n";
            continue;
        }

        return true;
    }
}

bool CursoManager::pedirIdProfesor(int& idProfesor)
{
    std::string input;
    ProfesorArchivo archivoProfesor;

    while (true)
    {
        std::cout << "Ingrese el ID del profesor asignado: ";
        std::getline(std::cin, input);

        if (_utilidades.esComandoSalir(input))
            return false;

        if (!_utilidades.esEnteroValido(input))
        {
            std::cout << "\nDebe ingresar un n�mero entero v�lido. Intente nuevamente.\n\n";
            continue;
        }

        idProfesor = std::stoi(input);
        if (idProfesor <= 0)
        {
            std::cout << "\nEl ID debe ser mayor que 0. Intente nuevamente.\n\n";
            continue;
        }

        int pos = archivoProfesor.buscar(idProfesor);
        if (pos < 0)
        {
            std::cout << "\nNo se encontr� un profesor con ese ID. Intente nuevamente.\n\n";
            continue;
        }
        else
        {
            Profesor profesor = archivoProfesor.leer(pos);
            if (!profesor.getEstado())
            {
                std::cout << "\nEl profesor se encuentra inactivo. Intente nuevamente.\n\n";
                continue;
            }
        }

        return true;
    }
}

void CursoManager::altaCurso()
{

    Curso nuevoCurso;
    std::string inputUsuario; // uso un input general para poder detectar la palabra clave "salir" si el usuario la ingresa
    int cantMaximaAlumnos = 0;
    int idProfesor = 0;
    int numeroAula = 0;

    int ultimoId = _archivo.cantRegistros(); //buscamos el ultimo id del archivo
    int nuevoId = ultimoId + 1;
    nuevoCurso.setId(nuevoId);

    _utilidades.limpiarPantallaConEncabezado("=== ALTA DE CURSO ===");

    std::cout << "Para cancelar, escribe 'salir' en cualquier momento.\n\n";

    if (!pedirNombreCurso(inputUsuario))
    {
        std::cout << "\nAlta de curso cancelada.\n";
        return;
    }
    nuevoCurso.setNombre(inputUsuario);

    if (!pedirCantidadMaximaAlumnos(cantMaximaAlumnos))
    {
        std::cout << "\nAlta de curso cancelada.\n";
        return;
    }
    nuevoCurso.setCantMaximaAlumnos(cantMaximaAlumnos);

    if (!pedirNumeroAula(numeroAula))
    {
        std::cout << "\nAlta de curso cancelada.\n";
        return;
    }
    nuevoCurso.setNumeroAula(numeroAula);

    if (!pedirIdProfesor(idProfesor))
    {
        std::cout << "\nAlta de curso cancelada.\n";
        return;
    }
    nuevoCurso.setIdProfesor(idProfesor);

    std::cout << "Registrando curso...\n\n";

    if (_archivo.alta(nuevoCurso))
    {
        std::cout << "Curso registrado exitosamente con el ID: " << nuevoId << "\n";
    }
    else
    {
        std::cout << "Error al guardar el curso. Intente nuevamente m�s tarde.\n";
    }
}

void CursoManager::modificarCurso()
{
    int total = _archivo.cantRegistros();
    Curso curso;
    int posicion = -1;

    if (total <= 0)
    {
        std::cout << "\nNo hay cursos registrados.\n";
        return;
    }

    std::string inputUsuario;
    int idCurso;

    _utilidades.limpiarPantallaConEncabezado("=== MODIFICAR CURSO ===");
    while (true)
    {
        std::cout << "\nIngrese el ID del curso a modificar (o escriba 'salir' para cancelar): ";
        std::getline(std::cin, inputUsuario);

        if (_utilidades.esComandoSalir(inputUsuario))
        {
            std::cout << "\nOperaci�n cancelada.\n";
            return;
        }

        if (!_utilidades.esEnteroValido(inputUsuario))
        {
            std::cout << "Debe ingresar un n�mero entero v�lido. Intente nuevamente.\n";
            continue;
        }

        idCurso = std::stoi(inputUsuario);
        if (idCurso <= 0)
        {
            std::cout << "El ID debe ser mayor que 0.\n";
            continue;
        }

        posicion = _archivo.buscar(idCurso);
        if (posicion == -1)
        {
            std::cout << "No se encontr� un curso activo con ese ID. Intente nuevamente.\n";
            continue;
        }

        curso = _archivo.leer(posicion);
        break;
    }

    Curso cursoOriginal = curso; // esto es para mantener el estado original y poder comparar si hubo modificaciones

    bool primeraVez = true;
    int opcion;
    do
    {
        if (primeraVez)
        {
            _utilidades.limpiarPantallaConEncabezado("=== MODIFICAR CURSO ===");
            ProfesorArchivo profeArchivo;
            int idProfesor = curso.getIdProfesor();
            int posicionRegProfesor = profeArchivo.buscar(idProfesor);
            Profesor profesorCurso = profeArchivo.leer(posicionRegProfesor);

            std::cout << "           CURSO SELECCIONADO           \n";
            std::cout << "-----------------------------------------\n";
            std::cout << "ID: " << curso.getId() << "\n";
            std::cout << "Nombre: " << curso.getNombre() << std::endl;
            std::cout << "Cantidad m�xima de alumnos: " << curso.getCantMaximaAlumnos() << std::endl;
            std::cout << "Número de aula: " << curso.getNumeroAula() << std::endl;
            std::cout << "Profesor Asignado:\n";
            std::cout << "ID Profesor: " << curso.getIdProfesor() << "\n";
            std::cout << "Nombre Profesor: " << profesorCurso.getNombre() << " " << profesorCurso.getApellido() << "\n";
            std::cout << "=========================================\n";

            primeraVez = false; // para que no se vuelva a mostrar en la pr�xima iteraci�n
        }
        else
        {
            _utilidades.limpiarPantallaConEncabezado("=== MODIFICAR CURSO ===");
        }

        std::cout << "\nSeleccione qu� desea modificar:\n";
        std::cout << "1. Nombre del curso\n";
        std::cout << "2. Cantidad m�xima de alumnos\n";
        std::cout << "3. Número de aula\n";
        std::cout << "4. Profesor asignado\n";
        std::cout << "0. Guardar cambios y salir\n";
        std::cout << "-----------------------------------------\n";
        std::cout << "Ingrese opci�n: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion)
        {
        case 1:
        {
            std::string nuevoNombre;
            if (pedirNombreCurso(nuevoNombre))
            {
                curso.setNombre(nuevoNombre);
                std::cout << "Nombre actualizado.\n";
            }
            break;
        }
        case 2:
        {
            int nuevaCantidad;
            if (pedirCantidadMaximaAlumnos(nuevaCantidad))
            {
                curso.setCantMaximaAlumnos(nuevaCantidad);
                std::cout << "Cantidad actualizada.\n";
            }
            break;
        }
        case 3:
        {
            int nuevaAula;
            if (pedirNumeroAula(nuevaAula, curso.getId()))
            {
                curso.setNumeroAula(nuevaAula);
                std::cout << "Aula actualizada.\n";
            }
            break;
        }
        case 4:
        {
            int nuevoProfesorId;
            if (pedirIdProfesor(nuevoProfesorId))
            {
                curso.setIdProfesor(nuevoProfesorId);
                std::cout << "Profesor actualizado.\n";
            }
            break;
        }
        case 0:
            if (curso != cursoOriginal)
            {
                if (_archivo.modificar(curso, posicion))
                {
                    std::cout << "\nCurso modificado correctamente.\n";
                }
                else
                {
                    std::cout << "\nError al guardar los cambios.\n";
                }
            }
            else
            {
                std::cout << "\nNo se realizaron cambios en el curso.\n";
            }
            break;
        default:
            std::cout << "Opci�n inv�lida. Intente nuevamente.\n";
        }

        if (opcion != 0)
        {
            std::cout << "\nPresione ENTER para continuar...";
            std::cin.get();
        }

    }
    while (opcion != 0);
}

void CursoManager::listar()
{
    int total = _archivo.cantRegistros();
    int registrosEncontrados = 0;
    if(total <= 0)
    {
        std::cout << "No hay cursos registrados." << std::endl;
        return;
    }
    system("cls");
    std::cout << "=========================================\n";
    std::cout << "         === LISTADO DE CURSOS ===       \n";
    std::cout << "=========================================\n";

    for(int i = 0; i < total; i++)
    {
        Curso curso = _archivo.leer(i);
        if (curso.getEstado())
        {

            registrosEncontrados++;
            ProfesorArchivo profeArchivo;
            int idProfesor = curso.getIdProfesor();
            int posicionRegProfesor = profeArchivo.buscar(idProfesor);
            Profesor profesorCurso = profeArchivo.leer(posicionRegProfesor);


            std::cout << "ID: " << curso.getId() << std::endl;
            std::cout << "Nombre: " << curso.getNombre() << std::endl;
            std::cout << "Cantidad m�xima de alumnos: " << curso.getCantMaximaAlumnos() << std::endl;
            std::cout << "N�mero de aula: " << curso.getNumeroAula() << std::endl;
            std::cout << "Profesor Asignado:\n";
            std::cout << "ID Profesor: " << curso.getIdProfesor() << "\n";
            std::cout << "Nombre Profesor: " << profesorCurso.getNombre() << " " << profesorCurso.getApellido() << "\n";
            std::cout << "Estado: " << (curso.getEstado() ? "ACTIVO" : "INACTIVO") << "\n";
            std::cout << "---------------------------" << std::endl;
        }
    }

    if (registrosEncontrados == 0)
    {
        std::cout << "No hay cursos activos para mostrar." << std::endl;
    }

}

void CursoManager::listarPorProfesor()
{
    int total = _archivo.cantRegistros();
    //Agregu� la inicializaci�n de registrosEncontrados, por un warning.
    int registrosEncontrados = 0;
    if(total <= 0)
    {
        std::cout << "No hay cursos registrados." << std::endl;
        return;
    }
    _utilidades.limpiarPantallaConEncabezado("=== LISTADO DE CURSOS POR PROFESOR ===");


    std::string inputUsuario;
    int idProfesor;
    while (true)
    {
        std::cout << "\nIngrese el ID del profesor asociado al curso a buscar (o escriba 'salir' para cancelar): ";
        std::getline(std::cin, inputUsuario);

        if (_utilidades.esComandoSalir(inputUsuario))
        {
            std::cout << "\nOperaci�n cancelada.\n";
            return;
        }

        if (!_utilidades.esEnteroValido(inputUsuario))
        {
            std::cout << "Debe ingresar un n�mero entero v�lido. Intente nuevamente.\n";
            continue;
        }

        idProfesor = std::stoi(inputUsuario);
        if (idProfesor <= 0)
        {
            std::cout << "El ID debe ser mayor que 0.\n";
            continue;
        }
        break;
    }

    for(int i = 0; i < total; i++)
    {
        Curso curso = _archivo.leer(i);

        if(curso.getIdProfesor() == idProfesor && curso.getEstado() )
        {
            registrosEncontrados++;
            ProfesorArchivo profeArchivo;
            int idProfesor = curso.getIdProfesor();
            int posicionRegProfesor = profeArchivo.buscar(idProfesor);
            Profesor profesorCurso = profeArchivo.leer(posicionRegProfesor);

            std::cout << "---------------------------" << std::endl;
            std::cout << "ID: " << curso.getId() << std::endl;
            std::cout << "Nombre: " << curso.getNombre() << std::endl;
            std::cout << "Cantidad m�xima de alumnos: " << curso.getCantMaximaAlumnos() << std::endl;
            std::cout << "N�mero de aula: " << curso.getNumeroAula() << std::endl;
            std::cout << "Profesor Asignado:\n";
            std::cout << "ID Profesor: " << curso.getIdProfesor() << "\n";
            std::cout << "Nombre Profesor: " << profesorCurso.getNombre() << " " << profesorCurso.getApellido() << "\n";
            std::cout << "Estado: " << (curso.getEstado() ? "ACTIVO" : "INACTIVO") << "\n";
            std::cout << "---------------------------" << std::endl;
        }
    }

    if (registrosEncontrados == 0)
    {
        std::cout << "No hay cursos activos para mostrar." << std::endl;
    }

}

void CursoManager::listarSinCupo()
{
    int total = _archivo.cantRegistros();
    int registrosEncontrados = 0;

    if (total <= 0)
    {
        std::cout << "No hay cursos registrados." << std::endl;
        return;
    }

    InscripcionArchivo archivoInscripciones;
    _utilidades.limpiarPantallaConEncabezado("=== LISTADO DE CURSOS SIN CUPO ===");

    for (int i = 0; i < total; i++)
    {
        Curso curso = _archivo.leer(i);
        if (!curso.getEstado()) continue;

        int cantidadInscriptos = 0;
        int totalInscripciones = archivoInscripciones.cantRegistros();

        for (int j = 0; j < totalInscripciones; j++)
        {
            Inscripcion inscripcion;
            if (archivoInscripciones.leer(j, inscripcion) &&
                    inscripcion.getEstado() &&
                    inscripcion.getIdCurso() == curso.getId())
            {
                cantidadInscriptos++;
            }
        }

        if (cantidadInscriptos >= curso.getCantMaximaAlumnos())
        {
            registrosEncontrados++;
            ProfesorArchivo profeArchivo;
            int idProfesor = curso.getIdProfesor();
            int posicionRegProfesor = profeArchivo.buscar(idProfesor);
            Profesor profesorCurso = profeArchivo.leer(posicionRegProfesor);

            std::cout << "---------------------------" << std::endl;
            std::cout << "ID: " << curso.getId() << std::endl;
            std::cout << "Nombre: " << curso.getNombre() << std::endl;
            std::cout << "Cantidad máxima de alumnos: " << curso.getCantMaximaAlumnos() << std::endl;
            std::cout << "Cantidad de inscriptos: " << cantidadInscriptos << std::endl;
            std::cout << "Número de aula: " << curso.getNumeroAula() << std::endl;
            std::cout << "Profesor Asignado:\n";
            std::cout << "ID Profesor: " << curso.getIdProfesor() << "\n";
            std::cout << "Nombre Profesor: " << profesorCurso.getNombre() << " " << profesorCurso.getApellido() << "\n";
            std::cout << "---------------------------" << std::endl;
        }
    }

    if (registrosEncontrados == 0)
    {
        std::cout << "No hay cursos sin cupo disponible para mostrar." << std::endl;
    }
}


void CursoManager::listarInactivos()
{
    int total = _archivo.cantRegistros();
    int registrosEncontrados = 0;
    if(total <= 0)
    {
        std::cout << "No hay cursos registrados." << std::endl;
        return;
    }
    system("cls");
    std::cout << "=========================================\n";
    std::cout << "   === LISTADO DE CURSOS INACTIVOS ===   \n";
    std::cout << "=========================================\n";

    for(int i = 0; i < total; i++)
    {
        Curso curso = _archivo.leer(i);
        if (!curso.getEstado())
        {

            registrosEncontrados++;
            ProfesorArchivo profeArchivo;
            int idProfesor = curso.getIdProfesor();
            int posicionRegProfesor = profeArchivo.buscar(idProfesor);
            Profesor profesorCurso = profeArchivo.leer(posicionRegProfesor);


            std::cout << "ID: " << curso.getId() << std::endl;
            std::cout << "Nombre: " << curso.getNombre() << std::endl;
            std::cout << "Cantidad m�xima de alumnos: " << curso.getCantMaximaAlumnos() << std::endl;
            std::cout << "N�mero de aula: " << curso.getNumeroAula() << std::endl;
            std::cout << "Profesor Asignado:\n";
            std::cout << "ID Profesor: " << curso.getIdProfesor() << "\n";
            std::cout << "Nombre Profesor: " << profesorCurso.getNombre() << " " << profesorCurso.getApellido() << "\n";
            std::cout << "Estado: " << (curso.getEstado() ? "ACTIVO" : "INACTIVO") << "\n";
            std::cout << "---------------------------" << std::endl;
        }
    }

    if (registrosEncontrados == 0)
    {
        std::cout << "No hay cursos inactivos para mostrar." << std::endl;
    }

}

void CursoManager::listarCursos()
{
    std::string input;
    int opcion = -1;

    do
    {
        _utilidades.limpiarPantallaConEncabezado("=== SUBMEN� - LISTADO DE CURSOS ===");
        std::cout << "1. Listar cursos\n";
        std::cout << "2. Listar cursos sin cupo disponible\n";
        std::cout << "3. Listar cursos por profesor asignado\n";
        std::cout << "4. Listar cursos inactivos\n";
        std::cout << "0. Volver al men� anterior\n";
        std::cout << "=========================================\n";
        std::cout << "Seleccione una opci�n: ";
        std::getline(std::cin, input);

        if (!_utilidades.esEnteroValido(input))
        {
            std::cout << "Debe ingresar un número válido. Intente nuevamente.\n";
            system("pause");
            continue;
        }

        opcion = std::stoi(input);
        switch(opcion)
        {
        case 1:
            listar();
            system("pause");
            break;
        case 2:
            listarSinCupo();
            system("pause");
            break;
        case 3:
            listarPorProfesor();
            system("pause");
            break;
        case 4:
            listarInactivos();
            system("pause");
            break;
        case 0:
            std::cout << "Volviendo al men� anterior...\n";
            break;
        default:
            std::cout << "Opci�n no v�lida. Intente nuevamente.\n";
            system("pause");
            break;
        }
    }
    while(opcion != 0);
}

void CursoManager::buscarCursoID()
{
    int total = _archivo.cantRegistros();
    Curso curso;
    int posicion = -1;

    if (total <= 0)
    {
        std::cout << "\nNo hay cursos registrados.\n";
        return;
    }


    std::string inputUsuario;
    int idCurso;

    _utilidades.limpiarPantallaConEncabezado("=== B�SQUEDA DE CURSOS ===");
    while (true)
    {
        std::cout << "\nIngrese el ID del curso a buscar (o escriba 'salir' para cancelar): ";
        std::getline(std::cin, inputUsuario);

        if (_utilidades.esComandoSalir(inputUsuario))
        {
            std::cout << "\nOperaci�n cancelada.\n";
            return;
        }

        if (!_utilidades.esEnteroValido(inputUsuario))
        {
            std::cout << "Debe ingresar un n�mero entero v�lido. Intente nuevamente.\n";
            continue;
        }

        idCurso = std::stoi(inputUsuario);
        if (idCurso <= 0)
        {
            std::cout << "El ID debe ser mayor que 0.\n";
            continue;
        }

        posicion = _archivo.buscar(idCurso);
        if (posicion == -1)
        {
            std::cout << "No se encontr� un curso activo con ese ID. Intente nuevamente.\n";
            continue;
        }

        curso = _archivo.leer(posicion);
        break;
    }

    ProfesorArchivo profeArchivo;
    int idProfesor = curso.getIdProfesor();
    int posicionRegProfesor = profeArchivo.buscar(idProfesor);
    Profesor profesorCurso = profeArchivo.leer(posicionRegProfesor);

    std::cout << "---------------------------" << std::endl;
    std::cout << "ID: " << curso.getId() << std::endl;
    std::cout << "Nombre: " << curso.getNombre() << std::endl;
    std::cout << "Cantidad m�xima de alumnos: " << curso.getCantMaximaAlumnos() << std::endl;
    std::cout << "N�mero de aula: " << curso.getNumeroAula() << std::endl;
    std::cout << "Profesor Asignado:\n";
    std::cout << "ID Profesor: " << curso.getIdProfesor() << "\n";
    std::cout << "Nombre Profesor: " << profesorCurso.getNombre() << " " << profesorCurso.getApellido() << "\n";
    std::cout << "---------------------------" << std::endl;

}

void CursoManager::bajaCurso()
{
    int total = _archivo.cantRegistros();
    Curso curso;
    int posicion = -1;

    if (total <= 0)
    {
        std::cout << "\nNo hay cursos registrados.\n";
        return;
    }


    std::string inputUsuario;
    int idCurso;

    _utilidades.limpiarPantallaConEncabezado("=== BAJA DE CURSO ===");
    while (true)
    {
        std::cout << "\nIngrese el ID del curso a dar de baja (o escriba 'salir' para cancelar): ";
        std::getline(std::cin, inputUsuario);

        if (_utilidades.esComandoSalir(inputUsuario))
        {
            std::cout << "\nOperación cancelada.\n";
            return;
        }

        if (!_utilidades.esEnteroValido(inputUsuario))
        {
            std::cout << "Debe ingresar un número entero válido. Intente nuevamente.\n";
            continue;
        }

        idCurso = std::stoi(inputUsuario);
        if (idCurso <= 0)
        {
            std::cout << "El ID debe ser mayor que 0.\n";
            continue;
        }

        posicion = _archivo.buscar(idCurso);
        if (posicion == -1)
        {
            std::cout << "No se encontró un curso activo con ese ID. Intente nuevamente.\n";
            continue;
        }

        curso = _archivo.leer(posicion);
        break;
    }

    ProfesorArchivo profeArchivo;
    int idProfesor = curso.getIdProfesor();
    int posicionRegProfesor = profeArchivo.buscar(idProfesor);
    Profesor profesorCurso = profeArchivo.leer(posicionRegProfesor);

    std::cout << "---- Información Curso ----\n" ;
    std::cout << "---------------------------" << std::endl;
    std::cout << "ID: " << curso.getId() << std::endl;
    std::cout << "Nombre: " << curso.getNombre() << std::endl;
    std::cout << "Cantidad m�xima de alumnos: " << curso.getCantMaximaAlumnos() << std::endl;
    std::cout << "N�mero de aula: " << curso.getNumeroAula() << std::endl;
    std::cout << "Profesor Asignado:\n";
    std::cout << "ID Profesor: " << curso.getIdProfesor() << "\n";
    std::cout << "Nombre Profesor: " << profesorCurso.getNombre() << " " << profesorCurso.getApellido() << "\n";
    std::cout << "---------------------------" << std::endl;


    if (_archivo.tieneInscripcionesActivas(idCurso))
    {
        std::cout << "\n\nERROR: No se puede dar de baja el curso porque tiene inscripciones activas.\n";
        return;
    }

    if (_archivo.baja(idCurso))
    {
        std::cout << "Curso dado de baja exitosamente.\n";
    }
    else
    {
        std::cout << "No se encontró un curso con ese ID.\n";
    }

}


void CursoManager::reactivarCurso()
{
    int total = _archivo.cantRegistros();
    if (total <= 0)
    {
        std::cout << "\nNo hay cursos registrados.\n";
        return;
    }

    std::string input;
    int idCurso;
    Curso curso;
    int posicion = -1;

    _utilidades.limpiarPantallaConEncabezado("=== REACTIVAR CURSO ===");

    while (true)
    {
        std::cout << "Ingrese el ID del curso a reactivar (o escriba 'salir' para cancelar): ";
        std::getline(std::cin, input);

        if (_utilidades.esComandoSalir(input))
        {
            std::cout << "\nOperación cancelada.\n";
            return;
        }

        if (!_utilidades.esEnteroValido(input))
        {
            std::cout << "Debe ingresar un número entero válido.\n";
            continue;
        }

        idCurso = std::stoi(input);
        if (idCurso <= 0)
        {
            std::cout << "El ID debe ser mayor que 0.\n";
            continue;
        }

        posicion = _archivo.buscar(idCurso);
        if (posicion == -1)
        {
            std::cout << "No se encontró un curso con ese ID.\n";
            continue;
        }

        curso = _archivo.leer(posicion);

        if (curso.getEstado())
        {
            std::cout << "El curso ya está activo.\n";
            return;
        }

        break;
    }

    // valido el profe
    ProfesorArchivo archivoProfesor;
    Profesor profesor;
    int posProfe = archivoProfesor.buscar(curso.getIdProfesor());
    bool cambiarProfesor = false;

    if (posProfe < 0)
    {
        std::cout << "\nEl profesor asignado originalmente no existe. Debe seleccionar uno nuevo.\n";
        cambiarProfesor = true;
    }
    else
    {
        profesor = archivoProfesor.leer(posProfe);
        if (!profesor.getEstado())
        {
            std::cout << "\nEl profesor asignado originalmente está inactivo. Debe seleccionar uno nuevo.\n";
            cambiarProfesor = true;
        }
        else
        {
            std::cout << "\nProfesor actual: " << profesor.getNombre() << " " << profesor.getApellido() << "\n";
            std::cout << "¿Desea cambiar el profesor asignado? (s/n): ";
            std::getline(std::cin, input);

            if (_utilidades.aMinusculas(input) == "s")
            {
                cambiarProfesor = true;
            }
        }
    }

    if (cambiarProfesor)
    {
        int nuevoIdProfesor;
        if (!pedirIdProfesor(nuevoIdProfesor)) return;
        posProfe = archivoProfesor.buscar(nuevoIdProfesor);
        profesor = archivoProfesor.leer(posProfe);
        curso.setIdProfesor(nuevoIdProfesor);
    }

    // verificar si el aula sigue disponible
    int aula = curso.getNumeroAula();
    if (!aulaUnica(aula, curso.getId()))
    {
        std::cout << "\nAdvertencia: El aula " << aula << " ya está asignada a otro curso activo.\n";
        std::cout << "Debe cambiar el número de aula antes de reactivar el curso.\n";

        int nuevaAula;
        if (!pedirNumeroAula(nuevaAula, curso.getId())) return;
        curso.setNumeroAula(nuevaAula);
    }


    std::cout << "\nCurso listo para ser reactivado:\n";
    std::cout << "ID: " << curso.getId() << "\n";
    std::cout << "Nombre: " << curso.getNombre() << "\n";
    std::cout << "Aula: " << curso.getNumeroAula() << "\n";
    std::cout << "Profesor ID: " << curso.getIdProfesor() << "\n";
    std::cout << "Nombre Profesor: " << profesor.getNombre() << " " << profesor.getApellido() << "\n";
    std::cout << "\n¿Desea confirmar la reactivación? (s/n): ";
    std::getline(std::cin, input);

    if (_utilidades.aMinusculas(input) == "s")
    {
        curso.setEstado(true);
        if (_archivo.modificar(curso, posicion))
        {
            std::cout << "\nCurso reactivado exitosamente.\n";
        }
        else
        {
            std::cout << "\nError al modificar el curso.\n";
        }
    }
    else
    {
        std::cout << "\nReactivación cancelada.\n";
    }
}

bool CursoManager::reasignarCursosDeProfesor(int idProfesorActual)
{
    CursoArchivo _archivo = CursoArchivo();
    int totalCursos = _archivo.cantRegistros();

    if (totalCursos <= 0)
    {
        std::cout << "No hay cursos registrados." << std::endl;
        return false;
    }

    ProfesorArchivo profeArchivo;
    bool huboCambio = false;

    for (int i = 0; i < totalCursos; i++)
    {
        Curso curso = _archivo.leer(i);

        // muestro solo los cursos asignados al profe que queremos reasignar
        if (curso.getIdProfesor() == idProfesorActual)
        {
            std::cout << "Curso ID: " << curso.getId() << " - " << curso.getNombre() << std::endl;
            std::cout << "Profesor actual: " << idProfesorActual << std::endl;

            int totalProfes = profeArchivo.cantRegistros();
            // mostrar los profes disponibles
            std::cout << "Profesores disponibles para reasignar:" << std::endl;
            for (int j = 0; j < totalProfes; j++)
            {
                Profesor profe = profeArchivo.leer(j);
                if (profe.getEstado())
                {
                    std::cout << "ID: " << profe.getId() << " - " << profe.getNombre() << " " << profe.getApellido() << std::endl;
                }
            }

            int nuevoIdProfe = 0;
            bool valido = false;
            do
            {
                std::cout << "Ingrese ID del nuevo profesor para este curso (0 para omitir reasignación): ";
                std::cin >> nuevoIdProfe;

                if (nuevoIdProfe == 0)
                {
                    std::cout << "Se omite reasignar este curso." << std::endl;
                    valido = true;
                }
                else
                {
                    int posProfe = profeArchivo.buscar(nuevoIdProfe);
                    if (posProfe == -1)
                    {
                        std::cout << "Profesor no encontrado. Intente nuevamente." << std::endl;
                    }
                    else
                    {
                        Profesor profeSeleccionado = profeArchivo.leer(posProfe);
                        if (!profeSeleccionado.getEstado())
                        {
                            std::cout << "Profesor está dado de baja. Intente con otro." << std::endl;
                        }
                        else if (nuevoIdProfe == idProfesorActual)
                        {
                            std::cout << "El nuevo profesor no puede ser el mismo que el actual. Intente otro." << std::endl;
                        }
                        else
                        {
                            curso.setIdProfesor(nuevoIdProfe);
                            if (_archivo.modificar(curso, i))
                            {
                                std::cout << "Curso reasignado correctamente." << std::endl;
                                huboCambio = true;
                            }
                            else
                            {
                                std::cout << "Error al modificar el curso." << std::endl;
                            }
                            valido = true;
                        }
                    }
                }
            } while (!valido);

            std::cout << "-------------------------" << std::endl;
        }
    }

    if (!huboCambio)
    {
        std::cout << "No se realizaron cambios en la reasignación de cursos." << std::endl;
        return false;
    }

    return true;
}
