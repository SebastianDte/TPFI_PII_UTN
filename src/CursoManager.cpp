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
#include "InscripcionManager.h"

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
    std::string opcionUsuario;
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
        std::getline(std::cin, opcionUsuario);

        if (!_utilidades.esEnteroValido(opcionUsuario))
        {
            std::cout << "Debe ingresar un número entero válido.\n";
            continue;
        }

        opcion = std::stoi(opcionUsuario);

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
                InscripcionArchivo archivoInscripciones;
                int inscriptosActuales = archivoInscripciones.contarInscriptosActivosPorCurso(curso.getId());
                if (nuevaCantidad < inscriptosActuales)
                {
                    std::cout << "\nError: El nuevo cupo (" << nuevaCantidad << ") no puede ser menor que la cantidad de alumnos ya inscriptos (" << inscriptosActuales << ").\n";
                }
                else
                {
                    curso.setCantMaximaAlumnos(nuevaCantidad);
                    std::cout << "Cantidad actualizada.\n";
                }
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

    // para hacer mas eficiente la carga al listar uso la memoria dinamica, de esta manera evito tener que estar consultando al disco cada vez
    ProfesorArchivo archivoProfesor;
    int totalProfesores = archivoProfesor.cantRegistros();
    Profesor* profesores = new Profesor[totalProfesores];
    if (profesores == nullptr)
    {
        std::cout << "\nError: Ocurrió un error de memoria al cargar profesores.\n";
        return;
    }

    for (int i = 0; i < totalProfesores; i++)
    {
        profesores[i] = archivoProfesor.leer(i);
    }

    _utilidades.limpiarPantallaConEncabezado("=== LISTADO DE CURSOS ===");
    for(int i = 0; i < total; i++)
    {
        Curso curso = _archivo.leer(i);
        if (curso.getEstado())
        {

            registrosEncontrados++;

            Profesor profesorCurso = _utilidades.buscarProfesorEnArray(curso.getIdProfesor(), profesores, totalProfesores);

            std::cout << "ID: " << curso.getId() << std::endl;
            std::cout << "Nombre: " << curso.getNombre() << std::endl;
            std::cout << "Cantidad m�xima de alumnos: " << curso.getCantMaximaAlumnos() << std::endl;
            std::cout << "N�mero de aula: " << curso.getNumeroAula() << std::endl;
            std::cout << "Profesor Asignado:\n";
            std::cout << "ID Profesor: " << curso.getIdProfesor() << "\n";
            if (profesorCurso.getId() != -1)
            {
                std::cout << "Nombre Profesor: " << profesorCurso.getNombre() << " " << profesorCurso.getApellido() << "\n";
            }
            else
            {
                std::cout << "Nombre Profesor: (Profesor no encontrado)\n";
            }
            std::cout << "Estado: " << (curso.getEstado() ? "ACTIVO" : "INACTIVO") << "\n";
            std::cout << "---------------------------" << std::endl;
        }
    }

    delete[] profesores;

    if (registrosEncontrados == 0)
    {
        std::cout << "No hay cursos activos para mostrar." << std::endl;
    }
}

void CursoManager::listarPorProfesor()
{
    int total = _archivo.cantRegistros();
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

    ProfesorArchivo archivoProfesor;
    int posProfesor = archivoProfesor.buscar(idProfesor);
    if(posProfesor == -1)
    {
        std::cout << "No se encontró un profesor con el ID " << idProfesor << ".\n";
        return;
    }
    Profesor profesorBuscado = archivoProfesor.leer(posProfesor);

    for(int i = 0; i < total; i++)
    {
        Curso curso = _archivo.leer(i);

        if(curso.getIdProfesor() == idProfesor && curso.getEstado() )
        {
            registrosEncontrados++;

            std::cout << "---------------------------" << std::endl;
            std::cout << "ID: " << curso.getId() << std::endl;
            std::cout << "Nombre: " << curso.getNombre() << std::endl;
            std::cout << "Cantidad m�xima de alumnos: " << curso.getCantMaximaAlumnos() << std::endl;
            std::cout << "N�mero de aula: " << curso.getNumeroAula() << std::endl;
            std::cout << "Profesor Asignado:\n";
            std::cout << "ID Profesor: " << curso.getIdProfesor() << "\n";
            std::cout << "Nombre Profesor: " << profesorBuscado.getNombre() << " " << profesorBuscado.getApellido() << "\n";
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

    ProfesorArchivo archivoProfesor;
    int totalProfesores = archivoProfesor.cantRegistros();
    Profesor* profesores = new Profesor[totalProfesores];
    if (profesores == nullptr)
    {
        std::cout << "\nError: Ocurrió un error de memoria al cargar profesores.\n";
        return;
    }

    for (int i = 0; i < totalProfesores; i++)
    {
        profesores[i] = archivoProfesor.leer(i);
    }

    InscripcionArchivo archivoInscripciones;
    int totalInscripciones = archivoInscripciones.cantRegistros();
    Inscripcion* inscripciones = new Inscripcion[totalInscripciones];

    if (inscripciones == nullptr)
    {
        std::cout << "\nError: Ocurrió un error de memoria al cargar inscripciones.\n";
        delete[] profesores; //por si falla en este punto, devolvemos la memoria de profes
        return;
    }

    for (int i = 0; i < totalInscripciones; i++)
    {
        if(!archivoInscripciones.leer(i, inscripciones[i]))
        {
            std::cout << "\nError: No se pudo leer el registro de inscripción en la posición " << i << ".\n";
            delete[] profesores;
            delete[] inscripciones;
            return;
        }
    }

    _utilidades.limpiarPantallaConEncabezado("=== LISTADO DE CURSOS SIN CUPO ===");

    for (int i = 0; i < total; i++)
    {
        Curso curso = _archivo.leer(i);
        if (!curso.getEstado()) continue;

        int cantidadInscriptos = 0;

        for (int j = 0; j < totalInscripciones; j++)
        {
            if (inscripciones[j].getEstado() && inscripciones[j].getIdCurso() == curso.getId())
            {
                cantidadInscriptos++;
            }
        }

        if (cantidadInscriptos >= curso.getCantMaximaAlumnos())
        {
            registrosEncontrados++;
            Profesor profesorCurso = _utilidades.buscarProfesorEnArray(curso.getIdProfesor(), profesores, totalProfesores);

            std::cout << "---------------------------" << std::endl;
            std::cout << "ID: " << curso.getId() << std::endl;
            std::cout << "Nombre: " << curso.getNombre() << std::endl;
            std::cout << "Cantidad máxima de alumnos: " << curso.getCantMaximaAlumnos() << std::endl;
            std::cout << "Cantidad de inscriptos: " << cantidadInscriptos << std::endl;
            std::cout << "Número de aula: " << curso.getNumeroAula() << std::endl;
            std::cout << "Profesor Asignado:\n";
            std::cout << "ID Profesor: " << curso.getIdProfesor() << "\n";
            if (profesorCurso.getId() != -1)
            {
                std::cout << "Nombre Profesor: " << profesorCurso.getNombre() << " " << profesorCurso.getApellido() << "\n";
            }
            else
            {
                std::cout << "Nombre Profesor: (Profesor no encontrado)\n";
            }
            std::cout << "---------------------------" << std::endl;
        }
    }

    delete[] profesores;
    delete[] inscripciones;
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

    ProfesorArchivo archivoProfesor;
    int totalProfesores = archivoProfesor.cantRegistros();
    Profesor* profesores = new Profesor[totalProfesores];
    if (profesores == nullptr)
    {
        std::cout << "\nError: Ocurrió un error de memoria al cargar profesores.\n";
        return;
    }

    for (int i = 0; i < totalProfesores; i++)
    {
        profesores[i] = archivoProfesor.leer(i);
    }

    _utilidades.limpiarPantallaConEncabezado("=== LISTADO DE CURSOS INACTIVOS ===");

    for(int i = 0; i < total; i++)
    {
        Curso curso = _archivo.leer(i);
        if (!curso.getEstado())
        {

            registrosEncontrados++;
            Profesor profesorCurso = _utilidades.buscarProfesorEnArray(curso.getIdProfesor(), profesores, totalProfesores);

            std::cout << "ID: " << curso.getId() << std::endl;
            std::cout << "Nombre: " << curso.getNombre() << std::endl;
            std::cout << "Cantidad m�xima de alumnos: " << curso.getCantMaximaAlumnos() << std::endl;
            std::cout << "Número de aula: " << curso.getNumeroAula() << std::endl;
            std::cout << "Profesor Asignado:\n";
            std::cout << "ID Profesor: " << curso.getIdProfesor() << "\n";
            if (profesorCurso.getId() != -1)
            {
                std::cout << "Nombre Profesor: " << profesorCurso.getNombre() << " " << profesorCurso.getApellido() << "\n";
            }
            else
            {
                std::cout << "Nombre Profesor: (Profesor no encontrado)\n";
            }
            std::cout << "Estado: " << (curso.getEstado() ? "ACTIVO" : "INACTIVO") << "\n";
            std::cout << "---------------------------" << std::endl;
        }
    }

    delete[] profesores;
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
        std::cout << "\n\nADVERTENCIA: El curso tiene inscripciones activas.\n";
        std::cout << "Para dar de baja el curso, es necesario dar de baja todas las inscripciones asociadas.\n";
        std::string confirmacion;

        while (true)
        {
            std::cout << "¿Desea continuar y dar de baja las inscripciones? (s/n): ";
            std::getline(std::cin, confirmacion);
            confirmacion = _utilidades.aMinusculas(confirmacion);

            if (confirmacion == "s" || confirmacion == "n")
            {
                break;
            }
            std::cout << "Opción no válida. Por favor, ingrese 's' para sí o 'n' para no.\n";
        }

        if (confirmacion == "s")
        {
            InscripcionManager inscripcionManager;
            inscripcionManager.bajaInscripcionesPorCurso(idCurso);
            std::cout << "\nInscripciones dadas de baja.\n";
        }
        else
        {
            std::cout << "\nOperación cancelada. El curso y sus inscripciones no han sido modificados.\n";
            return;
        }
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
    CursoArchivo cursoArchivo;
    int totalCursos = cursoArchivo.cantRegistros();
    if (totalCursos <= 0)
    {
        std::cout << "No hay cursos registrados." << std::endl;
        return true; // como no hay cursos, entonces por defecto decimos que la reasignacion es exitosa
    }

    Curso* todosLosCursos = new Curso[totalCursos];

    if (todosLosCursos == nullptr)
    {
        std::cout << "\nError: Ocurrió un error de memoria al cargar cursos.\n";
        return false;
    }
    for (int i = 0; i < totalCursos; i++)
    {
        todosLosCursos[i] = cursoArchivo.leer(i);
    }

    ProfesorArchivo profeArchivo;
    int totalProfesores = profeArchivo.cantRegistros();
    Profesor* todosLosProfesores = new Profesor[totalProfesores];
    if (todosLosProfesores == nullptr)
    {
        std::cout << "\nError: Ocurrió un error de memoria al cargar profesores.\n";
        delete[] todosLosCursos;
        return false;
    }

    for (int i = 0; i < totalProfesores; i++)
    {
        todosLosProfesores[i] = profeArchivo.leer(i);
    }

    int cursosAReasignarCont = 0;
    for (int i = 0; i < totalCursos; i++)
    {
        if (todosLosCursos[i].getIdProfesor() == idProfesorActual)
        {
            cursosAReasignarCont++;
        }
    }

    if (cursosAReasignarCont == 0)
    {
        // devuelvo la memoria, no hay cursos para reasignar.
        delete[] todosLosCursos;
        delete[] todosLosProfesores;
        return true;
    }

    Curso* cursosAReasignar = new Curso[cursosAReasignarCont];

    if (cursosAReasignar == nullptr)
    {
        std::cout << "Error: Ocurrió un error de memoria al filtrar los cursos a reasignar.\n";
        delete[] todosLosCursos;
        delete[] todosLosProfesores;
        return false;
    }

    int indice = 0;
    for (int i = 0; i < totalCursos; i++)
    {
        if (todosLosCursos[i].getIdProfesor() == idProfesorActual)
        {
            cursosAReasignar[indice++] = todosLosCursos[i];
        }
    }


    int contCursosReasignados = 0;
    bool operacionCancelada = false;


    for (int i = 0; i < cursosAReasignarCont; i++)
    {
        // como hay que modificar el objeto, debemos pasar las referencoias al array dinamico
        Curso& curso = cursosAReasignar[i];
        _utilidades.limpiarPantallaConEncabezado("===REASIGNACIÓN DE CURSOS===");

        std::cout << "Reasignando curso '" << curso.getNombre() << "' (ID: " << curso.getId() << ")\n";
        std::cout << "Profesor actual ID: " << idProfesorActual << "\n\n";

        std::cout << "Profesores disponibles para reasignar:" << std::endl;
        for (int j = 0; j < totalProfesores; j++)
        {
            if (todosLosProfesores[j].getEstado() && todosLosProfesores[j].getId() != idProfesorActual)
            {
                std::cout << "  ID: " << todosLosProfesores[j].getId() << " - " << todosLosProfesores[j].getNombre() << " " << todosLosProfesores[j].getApellido() << std::endl;
            }
        }

        int nuevoIdProfe = 0;
        bool valido = false;
        std::string inputId;

        do
        {
            std::cout << "\nIngrese ID del nuevo profesor para este curso ('salir' para cancelar TODO): ";
            std::getline(std::cin, inputId);

            if (_utilidades.esComandoSalir(inputId))
            {
                operacionCancelada = true;
                break;
            }

            if (!_utilidades.esEnteroValido(inputId))
            {
                std::cout << "Entrada inválida. Debe ingresar un número entero.\n";
                continue;
            }

            nuevoIdProfe = std::stoi(inputId);

            if (nuevoIdProfe <= 0)
            {
                std::cout << "El ID debe ser un número positivo.\n";
            }
            else if (nuevoIdProfe == idProfesorActual)
            {
                std::cout << "No puede reasignar el curso al mismo profesor.\n";
            }
            else
            {
                Profesor profe = _utilidades.buscarProfesorEnArray(nuevoIdProfe, todosLosProfesores, totalProfesores);
                if (profe.getId() == -1 || !profe.getEstado())
                {
                    std::cout << "El ID no corresponde a un profesor válido y activo. Intente nuevamente.\n";
                }
                else
                {
                    curso.setIdProfesor(nuevoIdProfe);
                    std::cout << "El curso será reasignado a: " << profe.getNombre() << " " << profe.getApellido() << std::endl;
                    contCursosReasignados++;
                    valido = true;
                }
            }
        }
        while (!valido);

        if (operacionCancelada) break;
        std::cout << "-------------------------" << std::endl;
        system("pause");
    }

    bool exitoFinal = false;

    if (operacionCancelada)
    {
        std::cout << "\nOperación de reasignación cancelada por el usuario.\n";
    }
    else if  (contCursosReasignados != cursosAReasignarCont)
    {
        std::cout << "\nNo todos los cursos fueron reasignados. Para eliminar al profesor, debe reasignar todos sus cursos.\n";
    }
    else
    {
        std::cout << "\nGuardando todos los cambios en el archivo...\n";
        bool todosGuardados = true;

        for (int i = 0; i < cursosAReasignarCont; i++)
        {
            int posOriginal = cursoArchivo.buscar(cursosAReasignar[i].getId());
            if (posOriginal == -1 || !cursoArchivo.modificar(cursosAReasignar[i], posOriginal))
            {
                std::cout << "Error al guardar cambios para el curso ID: " << cursosAReasignar[i].getId() << std::endl;
                todosGuardados = false;
            }
        }

        if (todosGuardados)
        {
            std::cout << "Todos los cursos fueron reasignados y guardados exitosamente.\n";
            exitoFinal = true;
        }
        else
        {
            std::cout << "\nFallo en el guardado. La baja del profesor se cancela para mantener la integridad de los datos.\n";
        }
    }

    delete[] todosLosCursos;
    delete[] todosLosProfesores;
    delete[] cursosAReasignar;

    return exitoFinal;
}
