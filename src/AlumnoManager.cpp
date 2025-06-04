#include <iostream>
#include "Alumno.h"
#include "AlumnoManager.h"
#include "AlumnoArchivo.h"
#include "Utilidades.h"
#include "Fecha.h"

AlumnoManager::AlumnoManager()
{
    _archivo = AlumnoArchivo("alumnos.dat");
    _utilidades = Utilidades();
}


void AlumnoManager::altaAlumno()
{
    Alumno nuevoAlumno;
    std::string inputUsuario;
    int nuevoLegajo = _archivo.cantRegistros() + 1;  // Asigna un legajo secuencial
    nuevoAlumno.setLegajo(nuevoLegajo);

    std::cout << "=== Alta de Alumno ===\n";
    std::cout << "Para cancelar, escribe 'salir' en cualquier momento.\n\n";

    std::cin.clear();
    std::cin.ignore();

    // Ingreso y validación del DNI
    while (true)
    {
        std::cout << "Ingrese DNI (máximo 9 caracteres): ";
        std::getline(std::cin, inputUsuario);
        if (_utilidades.esComandoSalir(inputUsuario))
        {
            std::cout << "Alta de alumno cancelada." << std::endl;
            return;
        }
        if (inputUsuario.empty() || inputUsuario.length() > 20)
        {
            std::cout << "El DNI no puede estar vacío y debe tener como máximo 9 caracteres. Intente nuevamente.\n";
            continue;
        }
        nuevoAlumno.setDni(inputUsuario);
        break;
    }

    // Ingreso y validación del Nombre
    while (true)
    {
        std::cout << "\nIngrese nombre del alumno (máximo 29 caracteres): ";
        std::getline(std::cin, inputUsuario);
        if (_utilidades.esComandoSalir(inputUsuario))
        {
            std::cout << "Alta de alumno cancelada." << std::endl;
            return;
        }
        if (inputUsuario.empty() || inputUsuario.length() > 29)
        {
            std::cout << "El nombre no puede estar vacío y debe tener como máximo 29 caracteres. Intente nuevamente.\n";
            continue;
        }
        nuevoAlumno.setNombre(inputUsuario);
        break;
    }

    // Ingreso y validación del Apellido
    while (true)
    {
        std::cout << "\nIngrese apellido del alumno (máximo 29 caracteres): ";
        std::getline(std::cin, inputUsuario);
        if (_utilidades.esComandoSalir(inputUsuario))
        {
            std::cout << "Alta de alumno cancelada." << std::endl;
            return;
        }
        if (inputUsuario.empty() || inputUsuario.length() > 29)
        {
            std::cout << "El apellido no puede estar vacío y debe tener como máximo 29 caracteres. Intente nuevamente.\n";
            continue;
        }
        nuevoAlumno.setApellido(inputUsuario);
        break;
    }

    // Ingreso y validación del Teléfono
    while (true)
    {
        std::cout << "\nIngrese teléfono (máximo 19 caracteres): ";
        std::getline(std::cin, inputUsuario);
        if (_utilidades.esComandoSalir(inputUsuario))
        {
            std::cout << "Alta de alumno cancelada." << std::endl;
            return;
        }
        if (inputUsuario.empty() || inputUsuario.length() > 19)
        {
            std::cout << "El teléfono no puede estar vacío y debe tener como máximo 19 caracteres. Intente nuevamente.\n";
            continue;
        }
        nuevoAlumno.setTelefono(inputUsuario);
        break;
    }

    // Ingreso y validación del Email
    while (true)
    {
        std::cout << "\nIngrese email (máximo 49 caracteres): ";
        std::getline(std::cin, inputUsuario);
        if (_utilidades.esComandoSalir(inputUsuario))
        {
            std::cout << "Alta de alumno cancelada." << std::endl;
            return;
        }
        if (inputUsuario.empty() || inputUsuario.length() > 49)
        {
            std::cout << "El email no puede estar vacío y debe tener como máximo 49 caracteres. Intente nuevamente.\n";
            continue;
        }
        nuevoAlumno.setEmail(inputUsuario);
        break;
    }

    // Ingreso y validación de la Dirección
    while (true)
    {
        std::cout << "\nIngrese dirección (máximo 49 caracteres): ";
        std::getline(std::cin, inputUsuario);
        if (_utilidades.esComandoSalir(inputUsuario))
        {
            std::cout << "Alta de alumno cancelada." << std::endl;
            return;
        }
        if (inputUsuario.empty() || inputUsuario.length() > 49)
        {
            std::cout << "La dirección no puede estar vacía y debe tener como máximo 49 caracteres. Intente nuevamente.\n";
            continue;
        }
        nuevoAlumno.setDireccion(inputUsuario);
        break;
    }

    // Ingreso de la Fecha de Nacimiento
    // Aquí asumo que la clase Fecha posee un método "setFromString" que reciba el formato "DD/MM/AAAA".
    while (true)
    {
        std::cout << "\nIngrese la fecha de nacimiento (DD/MM/AAAA): ";
        std::getline(std::cin, inputUsuario);
        if (_utilidades.esComandoSalir(inputUsuario))
        {
            std::cout << "Alta de alumno cancelada." << std::endl;
            return;
        }
        Fecha fechaNacimiento;
        /*if (!fechaNacimiento.setFromString(inputUsuario)) {
            std::cout << "Formato de fecha incorrecto. Intente nuevamente." << std::endl;
            continue;
        }*/
        nuevoAlumno.setFechaNacimiento(fechaNacimiento);
        break;
    }

    // El alumno se ingresa como activo por defecto.
    nuevoAlumno.setActivo(true);

    if (_archivo.alta(nuevoAlumno))
    {
        std::cout << "\nAlumno registrado exitosamente con legajo: " << nuevoLegajo << std::endl;
    }
    else
    {
        std::cout << "\nError al guardar el alumno. Intente nuevamente más tarde." << std::endl;
    }
}

void AlumnoManager::listarAlumnos()
{

    int total = _archivo.cantRegistros();

    if(total <= 0)
    {
        std::cout << "No hay alumnos registrados." << std::endl;
        return;
    }

    std::cout << "=========================================\n";
    std::cout << "         === LISTADO DE ALUMNOS ===       \n";
    std::cout << "=========================================\n";

    for(int i = 0; i < total; i++)
    {
        Alumno alumno = _archivo.leer(i);

        if(alumno.getActivo())
        {
            std::cout << "Legajo: " << alumno.getLegajo() << std::endl;
            std::cout << "DNI: "<< alumno.getDni()<< std::endl;
            std::cout << "Nombre: " << alumno.getNombre()<< std::endl;
            std::cout << "Apellido: "<< alumno.getApellido()<< std::endl;
            std::cout << "Telefono: "<< alumno.getTelefono()<< std::endl;
            std::cout << "Email: "<< alumno.getEmail()<< std::endl;
            std::cout << "Direccion: "<< alumno.getDireccion()<< std::endl;
            //std::cout << "Fecha de nacimiento: "<< alumno.getFechaNacimiento.toString()<< std::endl;





            std::cout << "---------------------------" << std::endl;
        }
    }

}
void AlumnoManager::bajaAlumno() {
    std::string inputUsuario;
    int legajo;
    int posicion;
    Alumno alumno;

    std::cout << "=========================================\n";
    std::cout << "         === BAJA DE ALUMNOS ===       \n";
    std::cout << "=========================================\n";

    while (true) {
        std::cout << "\nIngrese el legajo del alumno a dar de baja (o 'salir' para cancelar): ";
        std::getline(std::cin, inputUsuario);

        if (_utilidades.esComandoSalir(inputUsuario)) {
            std::cout << "\nOperación cancelada." << std::endl;
            return;
        }

        if (!_utilidades.esEnteroValido(inputUsuario)) {
            std::cout << "Debe ingresar un número entero válido. Intente nuevamente." << std::endl;
            continue;
        }

        legajo = std::stoi(inputUsuario);
        if (legajo <= 0) {
            std::cout << "El legajo debe ser mayor que 0." << std::endl;
            continue;
        }

        // Se utiliza filtrarActivos=false para obtener el alumno sin importar su estado.
        posicion = _archivo.buscar(legajo, false);
        if (posicion == -1) {
            std::cout << "No se encontró un alumno con ese legajo. Intente nuevamente." << std::endl;
            continue;
        }

        alumno = _archivo.leer(posicion);

        // Si el alumno ya fue dado de baja, se notifica y se sale.
        if (!alumno.getActivo()) {
            std::cout << "El alumno ya fue dado de baja." << std::endl;
            std::cout << "Legajo: " << alumno.getLegajo() << std::endl;
            std::cout << "Nombre: " << alumno.getNombre() << std::endl;
            std::cout << "Apellido: " << alumno.getApellido() << std::endl;

            return;
        }
        break;
    }

    // Opcional: Se puede mostrar la información del alumno y solicitar confirmación.
    std::cout << "\nAlumno encontrado:" << std::endl;
    std::cout << "Legajo: " << alumno.getLegajo() << std::endl;
    std::cout << "Nombre: " << alumno.getNombre() << std::endl;

    std::cout << "\n¿Confirma dar de baja este alumno? (s/n): ";
    std::getline(std::cin, inputUsuario);
    if (_utilidades.aMinusculas(inputUsuario) != "s") {
        std::cout << "\nBaja de alumno cancelada." << std::endl;
        return;
    }

    // Se procede a desactivar el alumno.
    alumno.setActivo(false);
    if (_archivo.modificar(alumno, posicion)) {
        std::cout << "\nAlumno dado de baja correctamente." << std::endl;
    }
    else {
        std::cout << "\nError al dar de baja el alumno." << std::endl;
    }
}


void AlumnoManager::buscarAlumnoLegajo()
{
    int total = _archivo.cantRegistros();
    Alumno alumno;
    int posicion = -1;

    if (total <= 0)
    {
        std::cout << "\nNo hay alumnos registrados.\n";
        return;
    }


    std::string inputUsuario;
    int Legajo;

    std::cout << "========================================== \n";
    std::cout << "         === BÚSQUEDA DE ALUMNOS ===      \n";
    std::cout << "==========================================\n";

    while (true)
    {
        std::cout << "\nIngrese el legajo del alumno a buscar (o escriba 'salir' para cancelar): ";
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

        Legajo = std::stoi(inputUsuario);
        if (Legajo <= 0)
        {
            std::cout << "El LEGAJO debe ser mayor que 0.\n";
            continue;
        }

        posicion = _archivo.buscar(Legajo, false);
        if (posicion == -1)
        {
            std::cout << "No se encontró un alumno activo con ese LEGAJO. Intente nuevamente.\n";
            continue;
        }

        alumno = _archivo.leer(posicion);
        break;
    }
    if (alumno.getActivo())
    {
        std::cout << "\nAlumno encontrado:" << std::endl;
        std::cout << "Legajo: " << alumno.getLegajo() << std::endl;
        std::cout << "Nombre: " << alumno.getNombre() << std::endl;
        std::cout << "Apellido: " << alumno.getApellido() << std::endl;
    }
    else
    {
        std::cout << "El alumno se encuentra dado de baja.\n";
    }





}

void AlumnoManager::modificarAlumno()
{
    int total = _archivo.cantRegistros();
    Alumno alumno ;
    int posicion = -1;

    if (total <= 0)
    {
        std::cout << "\nNo hay alumnos registrados.\n";
        return;
    }


    std::string inputUsuario;
    int legajo;

    std::cout << "=========================================\n";
    std::cout << "         === MODIFICAR ALUMNO ===        \n";
    std::cout << "=========================================\n";

while (true)
{
    std::cout << "\nIngrese el LEGAJO del alumno a modificar (o escriba 'salir' para cancelar): ";
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

    legajo = std::stoi(inputUsuario);
    if (legajo <= 0)
    {
        std::cout << "El LEGAJO debe ser mayor que 0.\n";
        continue;
    }

    // Se utiliza filtrarActivos = false para obtener el alumno independientemente de su estado.
    posicion = _archivo.buscar(legajo, false);
    if (posicion == -1)
    {
        std::cout << "No se encontró un alumno con ese legajo. Intente nuevamente.\n";
        continue;
    }

    alumno = _archivo.leer(posicion);

    // Si el alumno está inactivo, notificar y salir.
    if (!alumno.getActivo())
    {
        std::cout << "El alumno se encuentra dado de baja.\n";
        return;
    }
    break;
}
    Alumno alumnoOriginal = alumno; // esto es para mantener el estado original y poder comparar si hubo modificaciones


    system("cls");

    std::cout << "=========================================\n";
    std::cout << "    MODIFICAR AlUMNO SELECCIONADO\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "ID: " << alumno.getLegajo() << "\n";
    std::cout << "Nombre: " << alumno.getNombre() << "\n";
    std::cout << "=========================================\n";

    int opcion;
    do
    {
        std::cout << "\nSeleccione qué desea modificar:\n";
        std::cout << "1. DNI del alumno\n";
        std::cout << "2. Nombre del alumno\n";
        std::cout << "3. Apellido del alumno\n";
        std::cout << "4. Número de telefono\n";
        std::cout << "5. Direccion\n";
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
            std::string nuevoDni;
            std::cout << "Nuevo DNI del alumno: ";
            std::getline(std::cin, nuevoDni);
            alumno.setDni(nuevoDni);
            std::cout << "DNI actualizado.\n";
            break;
        }
        case 2:
        {
            std::string nuevoNombre;
            std::cout << "Nuevo nombre del alumno: ";
            std::getline(std::cin, nuevoNombre);
            alumno.setNombre(nuevoNombre);
            std::cout << "Nombre actualizado.\n";
            break;
        }
        case 3:
        {
            std::string nuevoApellido;
            std::cout << "Nuevo apellido del alumno: ";
            std::cin >> nuevoApellido;
            std::cin.ignore();
            alumno.setApellido(nuevoApellido);
            std::cout << "Apellido actualizado.\n";
            break;
        }
        case 4:
        {
            std::string nuevoTelefono;
            std::cout << "Nuevo número de telefono del alumno: ";
            std::cin >> nuevoTelefono;
            std::cin.ignore();
            alumno.setTelefono(nuevoTelefono);
            std::cout << "Telefono actualizado.\n";
            break;
        }
        case 5:
        {
            std::string nuevaDireccion;
            std::cout << "Nueva direccion del alumno: ";
            std::getline(std::cin, nuevaDireccion);
            alumno.setDireccion(nuevaDireccion);
            std::cout << "Direccion actualizada.\n";
            break;
        }
        case 0:
            if (alumno != alumnoOriginal)
            {
                if (_archivo.modificar(alumno, posicion))
                {
                    std::cout << "\nalumno modificado correctamente.\n";
                }
                else
                {
                    std::cout << "\nError al guardar los cambios.\n";
                }
            }
            else
            {
                std::cout << "\nNo se realizaron cambios en los alumnos.\n";
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
