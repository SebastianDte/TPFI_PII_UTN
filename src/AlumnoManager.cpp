#include <iostream>
#include "Alumno.h"
#include "AlumnoManager.h"
#include "AlumnoArchivo.h"
#include "Utilidades.h"
#include "Fecha.h"
#include <regex> /// LIBRERIA PARA VALIDACIONES
AlumnoManager::AlumnoManager()
{
    _archivo = AlumnoArchivo("alumnos.dat");
    _utilidades = Utilidades();
}

///VALIDACIONES
bool AlumnoManager::pedirDNI(std::string& dni)
{
    std::string input;
    while (true)
    {
        std::cout << "\nIngrese DNI (7 u 8 d�gitos, sin puntos): ";
        std::getline(std::cin, input);

        if (_utilidades.esComandoSalir(input))
        {
            return false;
        }

        if (input.empty() || !_utilidades.soloNumeros(input) || (input.length() < 7 || input.length() > 8))
        {
            std::cout << "Formato de DNI inv�lido. Deben ser 7 u 8 d�gitos num�ricos. Intente nuevamente.\n";
            continue;
        }


        if (_archivo.existeDNI(input))
        {
            std::cout << "Error: El DNI ingresado ya pertenece a otro alumno. Intente nuevamente.\n";
            continue;
        }

        dni = input;
        return true;
    }
}

bool AlumnoManager::pedirNombre(std::string& nombre)
{
    std::string input;
    while (true)
    {
        std::cout << "\nIngrese nombre del alumno (m�nimo 2, m�ximo 29 caracteres): ";
        std::getline(std::cin, input);

        if (_utilidades.esComandoSalir(input))
        {
            return false;
        }

        if (input.empty())
        {
            std::cout << "El nombre no puede estar vac�o. Intente nuevamente.\n";
            continue;
        }


        if (input.length() > 29 || input.length() < 2)
        {
            std::cout << "El nombre debe tener entre 2 y 29 caracteres. Intente nuevamente.\n";
            continue;
        }


        std::string temp_input = _utilidades.aMinusculas(input);
        if (!_utilidades.soloLetras(temp_input))
        {
            std::cout << "El nombre solo debe contener letras y espacios internos. Intente nuevamente.\n";
            continue;
        }

        nombre = input;
        return true;
    }
}

bool AlumnoManager::pedirApellido(std::string& apellido)
{
    std::string input;
    while (true)
    {
        std::cout << "\nIngrese apellido del alumno (m�nimo 2, m�ximo 29 caracteres): ";
        std::getline(std::cin, input);

        if (_utilidades.esComandoSalir(input))
        {
            return false;
        }

        if (input.empty())
        {
            std::cout << "El apellido no puede estar vac�o. Intente nuevamente.\n";
            continue;
        }

        if (input.length() > 29 || input.length() < 2)
        {
            std::cout << "El apellido debe tener entre 2 y 29 caracteres. Intente nuevamente.\n";
            continue;
        }

        std::string temp_input = _utilidades.aMinusculas(input);
        if (!_utilidades.soloLetras(temp_input))
        {
            std::cout << "El apellido solo debe contener letras y espacios internos. Intente nuevamente.\n";
            continue;
        }

        apellido = input;
        return true;
    }
}
bool AlumnoManager::pedirEmail(std::string& email)
{
    std::string input;
    while (true)
    {
        std::cout << "\nIngrese email (m�ximo 49 caracteres): ";
        std::getline(std::cin, input);

        if (_utilidades.esComandoSalir(input))
        {
            return false;
        }


        const int maximoEmail = 49;
        const int minimoEmail = 5;
        int tamanioEmail = input.length();
        int contArroba = 0;
        int contPuntos = 0;

        if (input.empty())
        {
            std::cout << "El email no puede estar vac�o. Intente nuevamente.\n";
            continue; // Vuelve a pedir el dato
        }

        if (tamanioEmail < minimoEmail || tamanioEmail > maximoEmail)
        {
            std::cout << "La longitud del email no es v�lida. Intente nuevamente.\n";
            continue;
        }

        for (int i = 0; i < tamanioEmail; i++)
        {
            if (input[i] == '@')
            {
                contArroba++;
            }
            if (input[i] == '.')
            {
                contPuntos++;
            }
        }

        if (contArroba != 1 || contPuntos == 0)
        {
            std::cout << "El formato del email no es v�lido (debe tener un '@' y al menos un '.'). Intente nuevamente.\n";
            continue;
        }

        // Si todas las validaciones pasan, asignamos el valor y salimos.
        email = input;
        return true; // �xito
    }
}




bool AlumnoManager::pedirDireccion(std::string& direccion)
{

    std::regex patronDireccion(R"(^[A-Za-z��������������.\s]+ \d{1,5}$)");
    std::string input;

    while (true)
    {
        std::cout << "\nIngrese direcci�n: ";
        std::getline(std::cin, input);

        if (_utilidades.esComandoSalir(input))
        {
            return false; // El usuario cancel�
        }

        // La validaci�n:
        if (std::regex_match(input, patronDireccion))
        {
            direccion = input;
            return true;
        }
        else
        {
            std::cout << "Formato inv�lido. Use 'NOMBRE CALLE' seguido de 'NUMERO' (m�ximo 5 d�gitos). Intente nuevamente.\n";

        }
    }
}
void AlumnoManager::mostrarAlumno(const Alumno& alumno)
{
    std::cout << "Legajo: " << alumno.getLegajo() << std::endl;
    std::cout << "DNI: "<< alumno.getDni()<< std::endl;
    std::cout << "Nombre: " << alumno.getNombre()<< std::endl;
    std::cout << "Apellido: "<< alumno.getApellido()<< std::endl;
    std::cout << "Telefono: "<< alumno.getTelefono()<< std::endl;
    std::cout << "Email: "<< alumno.getEmail()<< std::endl;
    std::cout << "Direccion: "<< alumno.getDireccion()<< std::endl;
    std::cout << "Fecha de nacimiento: "<< alumno.getFechaNacimiento().toString() << std::endl;
    std::cout << "---------------------------" << std::endl;
}


void AlumnoManager::altaAlumno()
{
    Alumno nuevoAlumno;
    std::string inputUsuario;
    int nuevoLegajo = _archivo.cantRegistros() + 1;  // Asigna un legajo secuencial
    nuevoAlumno.setLegajo(nuevoLegajo);

    _utilidades.limpiarPantallaConEncabezado("=== ALTA DE ALUMNO ===");
    std::cout << "Para cancelar, escribe 'salir' en cualquier momento.\n\n";

    std::cin.clear();
    std::cin.ignore();

    // Ingreso y validaci�n del DNI
    if (!pedirDNI(inputUsuario))
    {
        std::cout << "Alta de alumno cancelada." << std::endl;
        return;
    }
    nuevoAlumno.setDni(inputUsuario);

    // Ingreso y validaci�n del nombre
    if (!pedirNombre(inputUsuario))
    {
        std::cout << "Alta de alumno cancelada." << std::endl;
        return;
    }
    nuevoAlumno.setNombre(inputUsuario);


    // Ingreso y validaci�n del Apellido
    if (!pedirApellido(inputUsuario))
    {
        std::cout << "Alta de alumno cancelada." << std::endl;
        return;
    }
    nuevoAlumno.setApellido(inputUsuario);

    // Ingreso y validaci�n del Tel�fono
    while (true)
    {
        std::cout << "\nIngrese tel�fono (m�ximo 19 caracteres): ";
        std::getline(std::cin, inputUsuario);
        if (_utilidades.esComandoSalir(inputUsuario))
        {
            std::cout << "Alta de alumno cancelada." << std::endl;
            return;
        }
        if (inputUsuario.empty() || inputUsuario.length() > 19)
        {
            std::cout << "El tel�fono no puede estar vac�o y debe tener como m�ximo 19 caracteres. Intente nuevamente.\n";
            continue;
        }
        nuevoAlumno.setTelefono(inputUsuario);
        break;
    }

    // Ingreso y validaci�n del Email
    if (!pedirEmail(inputUsuario))
    {
        std::cout << "Alta cancelada.\n";
        return;
    }
    nuevoAlumno.setEmail(inputUsuario); // Asigna el email validado

    // Ingreso y validaci�n de la Direcci�n
    if(!pedirDireccion(inputUsuario))
    {
        std::cout << "Alta cancelada." << std::endl;
        return;
    }
    nuevoAlumno.setDireccion(inputUsuario);



    // Fecha nacimiento
    while (true)
    {
        std::cout << "\nIngrese la fecha de nacimiento (DD/MM/AAAA): ";
        std::getline(std::cin, inputUsuario);
        if (_utilidades.esComandoSalir(inputUsuario))
        {
            std::cout << "Alta de alumno cancelada." << std::endl;
            return;
        }
        Fecha fechaNacimiento = Fecha();
        if (!fechaNacimiento.validarFechaStr(inputUsuario))
        {
            std::cout << "Formato de fecha incorrecto. Intente nuevamente." << std::endl;
            continue;
        }
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
        std::cout << "\nError al guardar el alumno. Intente nuevamente m�s tarde." << std::endl;
    }
}


void AlumnoManager::bajaAlumno()
{
    std::string inputUsuario;
    int legajo;
    int posicion;
    Alumno alumno;

    _utilidades.limpiarPantallaConEncabezado("=== BAJA DE ALUMNOS ===");

    while (true)
    {
        std::cout << "\nIngrese el legajo del alumno a dar de baja (o 'salir' para cancelar): ";
        std::getline(std::cin, inputUsuario);

        if (_utilidades.esComandoSalir(inputUsuario))
        {
            std::cout << "\nOperaci�n cancelada." << std::endl;
            return;
        }

        if (!_utilidades.esEnteroValido(inputUsuario))
        {
            std::cout << "Debe ingresar un n�mero entero v�lido. Intente nuevamente." << std::endl;
            continue;
        }

        legajo = std::stoi(inputUsuario);
        if (legajo <= 0)
        {
            std::cout << "El legajo debe ser mayor que 0." << std::endl;
            continue;
        }

        // Se utiliza filtrarActivos=false para obtener el alumno sin importar su estado.
        posicion = _archivo.buscar(legajo, false);
        if (posicion == -1)
        {
            std::cout << "No se encontr� un alumno con ese legajo. Intente nuevamente." << std::endl;
            continue;
        }

        alumno = _archivo.leer(posicion);

        // Si el alumno ya fue dado de baja, se notifica y se sale.
        if (!alumno.getActivo())
        {
            std::cout << "El alumno ya fue dado de baja." << std::endl;
            std::cout << "Legajo: " << alumno.getLegajo() << std::endl;
            std::cout << "Nombre: " << alumno.getNombre() << std::endl;
            std::cout << "Apellido: " << alumno.getApellido() << std::endl;

            return;
        }
        break;
    }


    std::cout << "\nAlumno encontrado:" << std::endl;
    std::cout << "Legajo: " << alumno.getLegajo() << std::endl;
    std::cout << "Nombre: " << alumno.getNombre() << std::endl;

    std::cout << "\n�Confirma dar de baja este alumno? (s/n): ";
    std::getline(std::cin, inputUsuario);
    if (_utilidades.aMinusculas(inputUsuario) != "s")
    {
        std::cout << "\nBaja de alumno cancelada." << std::endl;
        return;
    }

    // Se procede a desactivar el alumno.
    alumno.setActivo(false);
    if (_archivo.modificar(alumno, posicion))
    {
        std::cout << "\nAlumno dado de baja correctamente." << std::endl;
    }
    else
    {
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

    _utilidades.limpiarPantallaConEncabezado("=== BUSQUEDA DE ALUMNOS ===");

    while (true)
    {
        std::cout << "\nIngrese el legajo del alumno a buscar (o escriba 'salir' para cancelar): ";
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

        Legajo = std::stoi(inputUsuario);
        if (Legajo <= 0)
        {
            std::cout << "El LEGAJO debe ser mayor que 0.\n";
            continue;
        }

        posicion = _archivo.buscar(Legajo, false);
        if (posicion == -1)
        {
            std::cout << "No se encontr� un alumno activo con ese LEGAJO. Intente nuevamente.\n";
            continue;
        }

        alumno = _archivo.leer(posicion);
        break;
    }
    if (alumno.getActivo())
    {
        std::cout << "\nAlumno encontrado:" << std::endl;
        mostrarAlumno(alumno);
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
            std::cout << "\nOperaci�n cancelada.\n";
            return;
        }

        if (!_utilidades.esEnteroValido(inputUsuario))
        {
            std::cout << "Debe ingresar un n�mero entero v�lido. Intente nuevamente.\n";
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
            std::cout << "No se encontr� un alumno con ese legajo. Intente nuevamente.\n";
            continue;
        }

        alumno = _archivo.leer(posicion);


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
        std::cout << "\nSeleccione qu� desea modificar:\n";
        std::cout << "1. DNI del alumno\n";
        std::cout << "2. Nombre del alumno\n";
        std::cout << "3. Apellido del alumno\n";
        std::cout << "4. N�mero de telefono\n";
        std::cout << "5. Direccion\n";
        std::cout << "0. Guardar cambios y salir\n";
        std::cout << "-----------------------------------------\n";
        std::cout << "Ingrese opci�n: ";
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
            std::cout << "Nuevo n�mero de telefono del alumno: ";
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
            std::cout << "Opci�n inv�lida. Intente nuevamente.\n";
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

void AlumnoManager::listarAlumnos()
{
    int opcion;

    do
    {
        _utilidades.limpiarPantallaConEncabezado("=== SUBMEN� - LISTADO DE ALUMNOS ===");
        std::cout << "1. Listar alumnos activos\n";
        std::cout << "2. Listar alumnos inactivos\n";
        std::cout << "3. Listar alumnos por apellido\n";
        std::cout << "0. Volver al men� anterior\n";
        std::cout << "=========================================\n";
        std::cout << "Seleccione una opci�n: ";
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
            listarPorApellido();
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


void AlumnoManager::listarActivos()
{

    int total = _archivo.cantRegistros();

    if(total <= 0)
    {
        std::cout << "No hay alumnos registrados." << std::endl;
        return;
    }
    _utilidades.limpiarPantallaConEncabezado("=== LISTADO DE ALUMNOS ACTIVOS ===");
    for(int i = 0; i < total; i++)
    {
        Alumno alumno = _archivo.leer(i);

        if(alumno.getActivo())
        {
            mostrarAlumno(alumno);


        }
    }

}


void AlumnoManager::listarInactivos()
{
    int total = _archivo.cantRegistros();
    int registrosEncontrados = 0;

    if(total <= 0)
    {
        std::cout << "No hay alumnos registrados." << std::endl;
        return;
    }
    _utilidades.limpiarPantallaConEncabezado("=== LISTADO DE ALUMNOS INACTIVOS ===");
    for(int i = 0; i < total; i++)
    {
        Alumno alumno = _archivo.leer(i);

        if(!alumno.getActivo())
        {
            registrosEncontrados++;
            mostrarAlumno(alumno);
        }
    }
    if (registrosEncontrados == 0)
    {
        std::cout << "No hay alumnos inactivos para mostrar." << std::endl;
    }
}
void AlumnoManager::listarPorApellido()
{
    _utilidades.limpiarPantallaConEncabezado("=== LISTADO DE ALUMNOS POR APELLIDO ===");
    int total = _archivo.cantRegistros();

    if (total <= 0)
    {
        std::cout << "No hay alumnos registrados." << std::endl;
        return;
    }
    Alumno* alumnos = new Alumno[total];
    if (alumnos == nullptr)
    {
        std::cout << "Error al asignar memoria." << std::endl;
        return;
    }
    for (int i = 0; i < total; i++)
    {
        alumnos[i] = _archivo.leer(i);
    }

    for (int i = 0; i < total - 1; i++)
    {
        for (int j = 0; j < total - i - 1; j++)
        {
            // Comparamos los apellidos de los alumnos adyacentes
            if (alumnos[j].getApellido() > alumnos[j + 1].getApellido())
            {
                // Si est�n en el orden incorrecto, los intercambiamos (swap)
                Alumno temp = alumnos[j];
                alumnos[j] = alumnos[j + 1];
                alumnos[j + 1] = temp;
            }
        }
    }


    std::cout << "\nAlumnos activos ordenados por apellido:\n";
    std::cout << "-------------------------------------\n";
    int registrosEncontrados = 0;
    for (int i = 0; i < total; i++)
    {
        if (alumnos[i].getActivo())
        {
            mostrarAlumno(alumnos[i]);
            registrosEncontrados++;
        }
    }

    if (registrosEncontrados == 0)
    {
        std::cout << "No hay alumnos activos para mostrar." << std::endl;
    }


    delete[] alumnos;
}

