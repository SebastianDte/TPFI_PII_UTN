#include <iostream>
#include "Curso.h"
#include "CursoManager.h"
#include "CursoArchivo.h"
#include "Utilidades.h"

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

    // TODO: preguntar si el id debe setearse automaticamente.!!
    int ultimoId = _archivo.cantRegistros(); //buscamos el ultimo id del archivo
    int nuevoId = ultimoId + 1;
    nuevoCurso.setId(nuevoId);

    std::cout << "=== Alta de Curso ===\n";
    std::cout << "Para cancelar, escribe 'salir' en cualquier momento.\n\n";

    std::cin.clear();
    std::cin.ignore();

    while(true)
    {
        std::cout << "Ingrese nombre del curso (máximo 49 caracteres): ";
        std::getline(std::cin, inputUsuario);

        if(_utilidades.esComandoSalir(inputUsuario))
        {
            std::cout << "Alta de curso cancelada." << std::endl;
            return;
        }

        if(inputUsuario.empty())
        {
            std::cout << "El nombre no puede estar vacío. Por favor, intente nuevamente.\n" << std::endl;
            continue;
        }

        if(inputUsuario.length() > 49)
        {
            std::cout << "El nombre solo puede tener máximo 49 caracteres. Por favor, intente nuevamente." << std::endl;
            continue;
        }

        nuevoCurso.setNombre(inputUsuario);
        break;
    }

    while (true)
    {
        std::cout << "\nIngrese la cantidad máxima de alumnos para el curso: ";
        std::getline(std::cin, inputUsuario);

        if(_utilidades.esComandoSalir(inputUsuario))
        {
            std::cout << "Alta de curso cancelada." << std::endl;
            return;
        }

        if(!_utilidades.esEnteroValido(inputUsuario))
        {
            std::cout << "Debe ingresar un número entero válido. Por favor, intente nuevamente." << std::endl;
            continue;
        }

        cantMaximaAlumnos= std::stoi(inputUsuario);

        if (cantMaximaAlumnos <= 0)
        {
            std::cout << "La cantidad debe ser mayor que cero. Por favor, intente nuevamente." << std::endl;
            continue;
        }

        nuevoCurso.setCantMaximaAlumnos(cantMaximaAlumnos);
        break;
    }


    while(true)
    {
        std::cout << "\nIngrese el número de aula: ";
        std::getline(std::cin, inputUsuario);

        if(_utilidades.esComandoSalir(inputUsuario))
        {
            std::cout << "Alta de curso cancelada." << std::endl;
            return;
        }

        if(!_utilidades.esEnteroValido(inputUsuario))
        {
            std::cout << "Debe ingresar un número entero válido. Por favor, intente nuevamente." << std::endl;
            continue;
        }

        numeroAula= std::stoi(inputUsuario);

        if (numeroAula <= 0)
        {
            std::cout << "El número de aula no es válido. Debe ser mayor que 0. Por favor, intente nuevamente." << std::endl;
            continue;
        }

        nuevoCurso.setNumeroAula(numeroAula);
        break;
    }


    while(true)
    {
        std::cout << "\nIngrese el ID del profesor asignado: ";
        std::getline(std::cin, inputUsuario);

        if(_utilidades.esComandoSalir(inputUsuario))
        {
            std::cout << "Alta de curso cancelada." << std::endl;
            return;
        }

        if(!_utilidades.esEnteroValido(inputUsuario))
        {
            std::cout << "Debe ingresar un número entero válido. Por favor, intente nuevamente." << std::endl;
            continue;
        }

        idProfesor = std::stoi(inputUsuario);

        if (idProfesor <= 0)
        {
            std::cout << "El ID del profesor no es válido. Debe ser mayor que 0. Por favor, intente nuevamente." << std::endl;
            continue;
        }

        nuevoCurso.setIdProfesor(idProfesor);
        break;
    }

    nuevoCurso.setEstado(true);

    if(_archivo.alta(nuevoCurso))
    {
        std::cout << "Curso registrado exitosamente con el ID: " << nuevoId << std::endl;
    }
    else
    {
        std::cout << "Error al guardar el curso. Intente nuevamente más tarde." << std::endl;
    }

}

void CursoManager::bajaCurso()
{

    std::string inputUsuario;
    int idCurso;

    std::cout << "=== Baja de Curso ===\n";

    std::cin.clear();
    std::cin.ignore();

    while(true)
    {

        std::cout << "Ingrese el ID del curso a dar de baja (ingrese 'salir' para cancelar): ";
        std::getline(std::cin, inputUsuario);

        if(_utilidades.esComandoSalir(inputUsuario))
        {
            std::cout << "Baja de curso cancelada." << std::endl;
            return;
        }

        if(!_utilidades.esEnteroValido(inputUsuario))
        {
            std::cout << "Debe ingresar un número entero válido. Por favor, intente nuevamente." << std::endl;
            continue;
        }


        idCurso = std::stoi(inputUsuario);
        if (idCurso <= 0)
        {
            std::cout << "El ID debe ser un número mayor que 0" << std::endl;
            continue;
        }

        int posicion = _archivo.buscar(idCurso);
        if (posicion == -1)
        {
            std::cout << "No se encontró un curso activo con ese ID. Intente nuevamente" << std::endl;
            continue;
        }

        Curso curso = _archivo.leer(posicion);

        if(!curso.getEstado())
        {
            std::cout << "El curso ya está dado de baja." << std::endl;
            return;
        }

        // TODO: tenemos que confirmar que sea el curso a dar de baja antes de proceder a hacer alguna accion
        //como tenemos el profesor, seria bueno unir ambos archivos para tener los datos completos para validar que sea el que se quiere dar de baja
        // Pendiente implementar aca esa union, por ahora muestro el nombre
        std::cout << "Curso encontrado: " << curso.getNombre() << std::endl;
        std::cout << "¿Confirma dar de baja este curso? (s/n): ";
        std::getline(std::cin, inputUsuario);

        if (inputUsuario.empty())
        {
            std::cout << "\nNo puede dejar el campo vacío. Por favor ingrese 's' o 'n'.\n\n";
            continue;
        }

        std::string inputUsuarioMin = _utilidades.aMinusculas(inputUsuario);

        if(inputUsuarioMin == "s")
        {
            curso.setEstado(false);
            if(_archivo.modificar(curso, posicion))
            {
                std::cout << "Curso dado de baja correctamente." << std::endl;
            }
            else
            {
                std::cout << "Error al modificar el archivo." << std::endl;
            }
        }
        else
        {
            std::cout << "Baja cancelada." << std::endl;
        }

        break;
    }


}

void CursoManager::modificarCurso() {}

void CursoManager::listarCursos()
{

    int total = _archivo.cantRegistros();

    if(total <= 0)
    {
        std::cout << "No hay cursos registrados." << std::endl;
        return;
    }

    std::cout << "=== Listado de Cursos ===" << std::endl;

    for(int i = 0; i < total; i++)
    {
        Curso curso = _archivo.leer(i);

        if(curso.getEstado())
        {
            std::cout << "ID: " << curso.getId() << std::endl;
            std::cout << "Nombre: " << curso.getNombre() << std::endl;
            std::cout << "Cantidad máxima de alumnos: " << curso.getCantMaximaAlumnos() << std::endl;
            std::cout << "---------------------------" << std::endl;
        }
    }

}

void CursoManager::buscarCursoID() {}
