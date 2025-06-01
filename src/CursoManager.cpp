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


    system("cls");
    std::cout << "=========================================\n";
    std::cout << "         === ALTA DE CURSO ===           \n";
    std::cout << "=========================================\n";
    std::cout << "Para cancelar, escribe 'salir' en cualquier momento.\n\n";


    while(true)
    {
        std::cout << "Ingrese nombre del curso (máximo 49 caracteres): ";
        std::getline(std::cin, inputUsuario);

        if(_utilidades.esComandoSalir(inputUsuario))
        {
            std::cout << "\nAlta de curso cancelada.\n";
            return;
        }

        if(inputUsuario.empty())
        {
            std::cout << "\nEl nombre no puede estar vacío. Por favor, intente nuevamente.\n\n";
            continue;
        }

        if(inputUsuario.length() > 49)
        {
            std::cout << "\nEl nombre solo puede tener máximo 49 caracteres. Por favor, intente nuevamente.\n\n";
            continue;
        }

        nuevoCurso.setNombre(inputUsuario);
        break;
    }




    while (true)
    {
        std::cout << "Ingrese la cantidad máxima de alumnos para el curso: ";
        std::getline(std::cin, inputUsuario);

        if(_utilidades.esComandoSalir(inputUsuario))
        {
            std::cout << "\nAlta de curso cancelada.\n";
            return;
        }

        if(!_utilidades.esEnteroValido(inputUsuario))
        {
            std::cout << "\nDebe ingresar un número entero válido. Por favor, intente nuevamente.\n\n";
            continue;
        }

        cantMaximaAlumnos= std::stoi(inputUsuario);

        if (cantMaximaAlumnos <= 0)
        {
            std::cout << "\nLa cantidad debe ser mayor que cero. Por favor, intente nuevamente.\n\n";
            continue;
        }

        nuevoCurso.setCantMaximaAlumnos(cantMaximaAlumnos);
        break;
    }




    while(true)
    {
        std::cout << "Ingrese el número de aula: ";
        std::getline(std::cin, inputUsuario);

        if(_utilidades.esComandoSalir(inputUsuario))
        {
            std::cout << "\nAlta de curso cancelada.\n";
            return;
        }

        if(!_utilidades.esEnteroValido(inputUsuario))
        {
            std::cout << "\nDebe ingresar un número entero válido. Por favor, intente nuevamente.\n\n";
            continue;
        }

        numeroAula= std::stoi(inputUsuario);

        if (numeroAula <= 0)
        {
            std::cout << "\nEl número de aula no es válido. Debe ser mayor que 0. Por favor, intente nuevamente.\n\n";
            continue;
        }

        nuevoCurso.setNumeroAula(numeroAula);
        break;
    }




    while(true)
    {
        std::cout << "Ingrese el ID del profesor asignado: ";
        std::getline(std::cin, inputUsuario);

        if(_utilidades.esComandoSalir(inputUsuario))
        {
            std::cout << "\nAlta de curso cancelada.\n";
            return;
        }

        if(!_utilidades.esEnteroValido(inputUsuario))
        {
            std::cout << "\nDebe ingresar un número entero válido. Por favor, intente nuevamente.\n\n";
            continue;
        }

        idProfesor = std::stoi(inputUsuario);

        if (idProfesor <= 0)
        {
            std::cout << "\nEl ID del profesor no es válido. Debe ser mayor que 0. Por favor, intente nuevamente.\n\n";
            continue;
        }

        // buscar si el profesor existe
        ProfesorArchivo profeArchivo;
        int posicionRegProfesor = profeArchivo.buscar(idProfesor);

        if (posicionRegProfesor < 0)
        {
            std::cout << "\nNo existe un profesor registrado con el ID indicado. Por favor, intente nuevamente.\n\n";
            continue;
        }

        nuevoCurso.setIdProfesor(idProfesor);
        break;
    }

    nuevoCurso.setEstado(true);


    std::cout << "Registrando curso...\n\n";

    if(_archivo.alta(nuevoCurso))
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

    system("cls");
    std::cout << "=========================================\n";
    std::cout << "         === BAJA DE CURSO ===           \n";
    std::cout << "=========================================\n";


    while(true)
    {
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

        system("cls");
        std::cout << "=========================================\n";
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

    std::cout << "=========================================\n";
    std::cout << "         === MODIFICAR CURSO ===         \n";
    std::cout << "=========================================\n";


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


    system("cls");

    std::cout << "=========================================\n";
    std::cout << "    MODIFICAR CURSO SELECCIONADO\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "ID: " << curso.getId() << "\n";
    std::cout << "Nombre: " << curso.getNombre() << "\n";
    std::cout << "=========================================\n";

    int opcion;
    do
    {
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

        system("cls");

        switch (opcion)
        {
        case 1:
        {
            std::string nuevoNombre;
            std::cout << "Nuevo nombre del curso: ";
            std::getline(std::cin, nuevoNombre);
            curso.setNombre(nuevoNombre);
            std::cout << "Nombre actualizado.\n";
            break;
        }
        case 2:
        {
            int nuevaCantidad;
            std::cout << "Nueva cantidad máxima de alumnos: ";
            std::cin >> nuevaCantidad;
            std::cin.ignore();
            curso.setCantMaximaAlumnos(nuevaCantidad);
            std::cout << "Cantidad actualizada.\n";
            break;
        }
        case 3:
        {
            int nuevaAula;
            std::cout << "Nuevo número de aula: ";
            std::cin >> nuevaAula;
            std::cin.ignore();
            curso.setNumeroAula(nuevaAula);
            std::cout << "Aula actualizada.\n";
            break;
        }
        case 4:
        {
            int nuevoProfesorId;
            std::cout << "Nuevo ID de profesor: ";
            std::cin >> nuevoProfesorId;
            std::cin.ignore();
            curso.setIdProfesor(nuevoProfesorId);
            std::cout << "Profesor actualizado.\n";
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
            system("cls");
        }

    }
    while (opcion != 0);
}


void CursoManager::listarCursos()
{
    int total = _archivo.cantRegistros();

    if(total <= 0)
    {
        std::cout << "No hay cursos registrados." << std::endl;
        return;
    }

    std::cout << "=========================================\n";
    std::cout << "         === LISTADO DE CURSOS ===       \n";
    std::cout << "=========================================\n";

    for(int i = 0; i < total; i++)
    {
        Curso curso = _archivo.leer(i);

        if(curso.getEstado())
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

    std::cout << "=========================================\n";
    std::cout << "         === BÚSQUEDA DE CURSOS ===      \n";
    std::cout << "=========================================\n";

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
