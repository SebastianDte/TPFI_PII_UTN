#include <iostream>
#include "Curso.h"
#include "CursoManager.h"
#include "CursoArchivo.h"
#include "Utilidades.h"
#include "ProfesorArchivo.h"
#include "Profesor.h"

CursoManager::CursoManager()
{
    _archivo = CursoArchivo("cursos.dat");
    _utilidades = Utilidades();
}

bool CursoManager::pedirNombreCurso(std::string& nombre)
{
    std::string input;
    while (true)
    {
        std::cout << "Ingrese nombre del curso (máximo 49 caracteres): ";
        std::getline(std::cin, input);

        if (_utilidades.esComandoSalir(input))
            return false;

        if (input.empty())
        {
            std::cout << "\nEl nombre no puede estar vacío. Intente nuevamente.\n\n";
            continue;
        }

        if (input.length() > 49)
        {
            std::cout << "\nEl nombre solo puede tener máximo 49 caracteres. Intente nuevamente.\n\n";
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
        std::cout << "Ingrese la cantidad máxima de alumnos: ";
        std::getline(std::cin, input);

        if (_utilidades.esComandoSalir(input))
            return false;

        if (!_utilidades.esEnteroValido(input))
        {
            std::cout << "\nDebe ingresar un número entero válido. Intente nuevamente.\n\n";
            continue;
        }

        cantidad = std::stoi(input);
        if (cantidad <= 0)
        {
            std::cout << "\nLa cantidad debe ser mayor que cero. Intente nuevamente.\n\n";
            continue;
        }

        return true;
    }
}

bool CursoManager::pedirNumeroAula(int& aula)
{
    std::string input;
    while (true)
    {
        std::cout << "Ingrese el número de aula: ";
        std::getline(std::cin, input);

        if (_utilidades.esComandoSalir(input))
            return false;

        if (!_utilidades.esEnteroValido(input))
        {
            std::cout << "\nDebe ingresar un número entero válido. Intente nuevamente.\n\n";
            continue;
        }

        aula = std::stoi(input);
        if (aula <= 0)
        {
            std::cout << "\nEl número de aula debe ser mayor que cero. Intente nuevamente.\n\n";
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
            std::cout << "\nDebe ingresar un número entero válido. Intente nuevamente.\n\n";
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
            std::cout << "\nNo se encontró un profesor con ese ID. Intente nuevamente.\n\n";
            continue;
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

    nuevoCurso.setEstado(true);

    std::cout << "Registrando curso...\n\n";

    if (_archivo.alta(nuevoCurso))
    {
        std::cout << "Curso registrado exitosamente con el ID: " << nuevoId << "\n";
    }
    else
    {
        std::cout << "Error al guardar el curso. Intente nuevamente más tarde.\n";
    }
}

void CursoManager::bajaCurso()
{
    /* TODOS:
        2. Pendiente agregar validacion para ver si el curso no tiene alumnos inscriptos, si tiene no se puede dar de baja.
    */

    int total = _archivo.cantRegistros();

    if(total <= 0)
    {
        std::cout << "\nNo hay cursos registrados.\n";
        return;
    }

    std::string inputUsuario;
    int idCurso;

    _utilidades.limpiarPantallaConEncabezado("=== BAJA DE CURSO ===");

    while(true)
    {
        _utilidades.limpiarPantallaConEncabezado("=== BAJA DE CURSO ===");
        std::cout << "\nIngrese el ID del curso a dar de baja (ingrese 'salir' para cancelar): ";
        std::getline(std::cin, inputUsuario);

        if(_utilidades.esComandoSalir(inputUsuario))
        {
            std::cout << "\nBaja de curso cancelada.\n";
            return;
        }

        if(!_utilidades.esEnteroValido(inputUsuario))
        {
            std::cout << "\nDebe ingresar un número entero válido. Por favor, intente nuevamente.\n";
            continue;
        }

        idCurso = std::stoi(inputUsuario);
        if (idCurso <= 0)
        {
            std::cout << "\nEl ID debe ser un número mayor que 0.\n";
            continue;
        }

        int posicion = _archivo.buscar(idCurso);
        if (posicion == -1)
        {
            std::cout << "\nNo se encontró un curso activo con ese ID. Intente nuevamente.\n";
            continue;
        }

        Curso curso = _archivo.leer(posicion);

        if(!curso.getEstado())
        {
            std::cout << "\nEl curso ya está dado de baja.\n";
            return;
        }

        ProfesorArchivo profeArchivo;
        int idProfesor = curso.getIdProfesor();
        int posicionRegProfesor = profeArchivo.buscar(idProfesor);
        Profesor profesorCurso = profeArchivo.leer(posicionRegProfesor);

        _utilidades.limpiarPantallaConEncabezado("=== BAJA DE CURSO ===");
        std::cout << "Curso encontrado:\n";
        std::cout << "ID: " << curso.getId() << "\n";
        std::cout << "Nombre: " << curso.getNombre() << "\n";
        std::cout << "Profesor Asignado:\n";
        std::cout << "ID Profesor: " << curso.getIdProfesor() << "\n";
        std::cout << "Nombre Profesor: " << profesorCurso.getNombre() << " " << profesorCurso.getApellido() << "\n";
        std::cout << "=========================================\n";
        std::cout << "¿Confirma dar de baja este curso? (s/n): ";
        std::getline(std::cin, inputUsuario);

        if (inputUsuario.empty())
        {
            std::cout << "\nNo puede dejar el campo vacío. Por favor ingrese 's' o 'n'.\n";
            continue;
        }

        std::string inputUsuarioMin = _utilidades.aMinusculas(inputUsuario);

        if(inputUsuarioMin == "s")
        {
            curso.setEstado(false);
            if(_archivo.modificar(curso, posicion))
            {
                std::cout << "\nCurso dado de baja correctamente.\n";
            }
            else
            {
                std::cout << "\nError al modificar el archivo.\n";
            }
        }
        else
        {
            std::cout << "\nBaja cancelada.\n";
        }

        break;
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
            std::cout << "Cantidad máxima de alumnos: " << curso.getCantMaximaAlumnos() << std::endl;
            std::cout << "Número de aula: " << curso.getNumeroAula() << std::endl;
            std::cout << "Profesor Asignado:\n";
            std::cout << "ID Profesor: " << curso.getIdProfesor() << "\n";
            std::cout << "Nombre Profesor: " << profesorCurso.getNombre() << " " << profesorCurso.getApellido() << "\n";
            std::cout << "=========================================\n";

            primeraVez = false; // para que no se vuelva a mostrar en la próxima iteración
        }
        else
        {
            _utilidades.limpiarPantallaConEncabezado("=== MODIFICAR CURSO ===");
        }

        std::cout << "\nSeleccione qué desea modificar:\n";
        std::cout << "1. Nombre del curso\n";
        std::cout << "2. Cantidad máxima de alumnos\n";
        std::cout << "3. Número de aula\n";
        std::cout << "4. Profesor asignado\n";
        std::cout << "0. Guardar cambios y salir\n";
        std::cout << "-----------------------------------------\n";
        std::cout << "Ingrese opción: ";
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
            if (pedirNumeroAula(nuevaAula))
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
            std::cout << "Opción inválida. Intente nuevamente.\n";
        }

        if (opcion != 0)
        {
            std::cout << "\nPresione ENTER para continuar...";
            std::cin.get();
        }

    }
    while (opcion != 0);
}



void CursoManager::listarActivos()
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

        if(curso.getEstado())
        {
            registrosEncontrados++;
            ProfesorArchivo profeArchivo;
            int idProfesor = curso.getIdProfesor();
            int posicionRegProfesor = profeArchivo.buscar(idProfesor);
            Profesor profesorCurso = profeArchivo.leer(posicionRegProfesor);


            std::cout << "ID: " << curso.getId() << std::endl;
            std::cout << "Nombre: " << curso.getNombre() << std::endl;
            std::cout << "Cantidad máxima de alumnos: " << curso.getCantMaximaAlumnos() << std::endl;
            std::cout << "Número de aula: " << curso.getNumeroAula() << std::endl;
            std::cout << "Profesor Asignado:\n";
            std::cout << "ID Profesor: " << curso.getIdProfesor() << "\n";
            std::cout << "Nombre Profesor: " << profesorCurso.getNombre() << " " << profesorCurso.getApellido() << "\n";
            std::cout << "---------------------------" << std::endl;
        }
    }

    if (registrosEncontrados == 0)
    {
        std::cout << "No hay cursos activos para mostrar." << std::endl;
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
    _utilidades.limpiarPantallaConEncabezado("=== LISTADO DE CURSOS INACTIVOS ===");
    for(int i = 0; i < total; i++)
    {
        Curso curso = _archivo.leer(i);

        if(!curso.getEstado())
        {
            registrosEncontrados++;
            ProfesorArchivo profeArchivo;
            int idProfesor = curso.getIdProfesor();
            int posicionRegProfesor = profeArchivo.buscar(idProfesor);
            Profesor profesorCurso = profeArchivo.leer(posicionRegProfesor);


            std::cout << "ID: " << curso.getId() << std::endl;
            std::cout << "Nombre: " << curso.getNombre() << std::endl;
            std::cout << "Cantidad máxima de alumnos: " << curso.getCantMaximaAlumnos() << std::endl;
            std::cout << "Número de aula: " << curso.getNumeroAula() << std::endl;
            std::cout << "Profesor Asignado:\n";
            std::cout << "ID Profesor: " << curso.getIdProfesor() << "\n";
            std::cout << "Nombre Profesor: " << profesorCurso.getNombre() << " " << profesorCurso.getApellido() << "\n";
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
    int registrosEncontrados;
    if(total <= 0)
    {
        std::cout << "No hay cursos registrados." << std::endl;
        return;
    }
    _utilidades.limpiarPantallaConEncabezado("=== LISTADO DE CURSOS POR PROFESOR ===");


    std::string inputUsuario;
    int idProfesor;
    std::cin.ignore();
    while (true)
    {
        std::cout << "\nIngrese el ID del profesor asociado al curso a buscar (o escriba 'salir' para cancelar): ";
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

        if(curso.getIdProfesor() == idProfesor)
        {
            registrosEncontrados++;
            ProfesorArchivo profeArchivo;
            int idProfesor = curso.getIdProfesor();
            int posicionRegProfesor = profeArchivo.buscar(idProfesor);
            Profesor profesorCurso = profeArchivo.leer(posicionRegProfesor);


            std::cout << "ID: " << curso.getId() << std::endl;
            std::cout << "Nombre: " << curso.getNombre() << std::endl;
            std::cout << "Cantidad máxima de alumnos: " << curso.getCantMaximaAlumnos() << std::endl;
            std::cout << "Número de aula: " << curso.getNumeroAula() << std::endl;
            std::cout << "Profesor Asignado:\n";
            std::cout << "ID Profesor: " << curso.getIdProfesor() << "\n";
            std::cout << "Nombre Profesor: " << profesorCurso.getNombre() << " " << profesorCurso.getApellido() << "\n";
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

    if(total <= 0)
    {
        std::cout << "No hay cursos registrados." << std::endl;
        return;
    }

    _utilidades.limpiarPantallaConEncabezado("=== LISTADO DE CURSOS SIN CUPO ===");

    for(int i = 0; i < total; i++)
    {
        Curso curso = _archivo.leer(i);

        if(curso.getCantMaximaAlumnos() == 0)
        {
            ProfesorArchivo profeArchivo;
            int idProfesor = curso.getIdProfesor();
            int posicionRegProfesor = profeArchivo.buscar(idProfesor);
            Profesor profesorCurso = profeArchivo.leer(posicionRegProfesor);


            std::cout << "ID: " << curso.getId() << std::endl;
            std::cout << "Nombre: " << curso.getNombre() << std::endl;
            std::cout << "Cantidad máxima de alumnos: " << curso.getCantMaximaAlumnos() << std::endl;
            std::cout << "Número de aula: " << curso.getNumeroAula() << std::endl;
            std::cout << "Profesor Asignado:\n";
            std::cout << "ID Profesor: " << curso.getIdProfesor() << "\n";
            std::cout << "Nombre Profesor: " << profesorCurso.getNombre() << " " << profesorCurso.getApellido() << "\n";
            std::cout << "---------------------------" << std::endl;
        }
    }

    if (registrosEncontrados == 0)
    {
        std::cout << "No hay cursos activos para mostrar." << std::endl;
    }
}


void CursoManager::listarCursos()
{
    int opcion;

    do
    {
        _utilidades.limpiarPantallaConEncabezado("=== SUBMENÚ - LISTADO DE CURSOS ===");
        std::cout << "1. Listar cursos activos\n";
        std::cout << "2. Listar cursos inactivos\n";
        std::cout << "3. Listar cursos sin cupo disponible\n";
        std::cout << "4. Listar cursos por profesor asignado\n";
        std::cout << "0. Volver al menú anterior\n";
        std::cout << "=========================================\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();
        switch(opcion)
        {
        case 1:
            listarActivos();
            system("pause");
            break;
        case 2:
            listarInactivos();
            system("pause");
            break;
        case 3:
            listarSinCupo();
            system("pause");
            break;
        case 4:
            listarPorProfesor();
            system("pause");
            break;
        case 0:
            std::cout << "Volviendo al menú anterior...\n";
            break;
        default:
            std::cout << "Opción no válida. Intente nuevamente.\n";
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

    _utilidades.limpiarPantallaConEncabezado("=== BÚSQUEDA DE CURSOS ===");
    while (true)
    {
        std::cout << "\nIngrese el ID del curso a buscar (o escriba 'salir' para cancelar): ";
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

    if (curso.getEstado())
    {
        ProfesorArchivo profeArchivo;
        int idProfesor = curso.getIdProfesor();
        int posicionRegProfesor = profeArchivo.buscar(idProfesor);
        Profesor profesorCurso = profeArchivo.leer(posicionRegProfesor);

        std::cout << "ID: " << curso.getId() << std::endl;
        std::cout << "Nombre: " << curso.getNombre() << std::endl;
        std::cout << "Cantidad máxima de alumnos: " << curso.getCantMaximaAlumnos() << std::endl;
        std::cout << "Número de aula: " << curso.getNumeroAula() << std::endl;
        std::cout << "Profesor Asignado:\n";
        std::cout << "ID Profesor: " << curso.getIdProfesor() << "\n";
        std::cout << "Nombre Profesor: " << profesorCurso.getNombre() << " " << profesorCurso.getApellido() << "\n";
        std::cout << "---------------------------" << std::endl;
    }
    else
    {
        std::cout << "El curso se encuentra dado de baja.\n";
    }
}
