#include <iomanip>
#include "InscripcionManager.h"
#include "InscripcionArchivo.h"
#include "Inscripcion.h"
#include "CursoManager.h"
#include <iostream>
#include "Fecha.h"
#include "AlumnoArchivo.h"
#include "AlumnoManager.h"
#include "Utilidades.h"

#include <limits>
using namespace std;


//Método para dar de alta una Inscripción.
void InscripcionManager::altaInscripcion() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    int legajo = 0, idCurso = 0;
    float importe = 0.0f;
    _utilidades.limpiarPantallaConEncabezado("ALTA DE INSCRIPCION");
    std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
    
    // Paso 1: Legajo del alumno
        if (!pedirLegajoAlumno(legajo)) {
            std::cout << "\nAlta de inscripción cancelada.\n";
            return;
        }

    // Paso 2: ID del curso + Control de cupo
    while (true) {
        _utilidades.limpiarPantallaConEncabezado("ALTA DE INSCRIPCION");
        std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
        std::cout << "Legajo Alumno: " << legajo << "\n";

        if (!pedirIdCurso(idCurso)) {
            std::cout << "\nAlta de inscripción cancelada.\n";
            return;
        }

        if (verificarInscripcionExistente(legajo, idCurso)) {
            std::cout << "\nEl alumno ya está inscripto en ese curso.\n";
            _utilidades.pausar();
            continue;
        }

		if (controlCupo(idCurso)) break; 
		else {
			std::cout << "\nNo se pudo inscribir al curso por falta de cupo.\n";
			_utilidades.pausarYLimpiar();
			return;
		} 
    }

    // Paso 3: Importe abonado
    while (true) {
        _utilidades.limpiarPantallaConEncabezado("ALTA DE INSCRIPCION");
        std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
        std::cout << "Legajo Alumno: " << legajo << "\n";
        std::cout << "ID Curso: " << idCurso << "\n";

        if (!pedirImporte(importe)) {
            std::cout << "\nAlta de inscripción cancelada.\n";
            return;
        }

        break;
    }

    // Paso final: Guardar la inscripción
    Fecha fecha = Fecha::fechaActual(); //Fecha actual del sistema.
    InscripcionArchivo archivoInscripciones;
	int id = archivoInscripciones.obtenerProximoId(); //ID único para la inscripción.
	bool estado = true; // Inscripción activa por defecto.

    Inscripcion nueva(id, legajo, idCurso, fecha, importe, estado);

    if (archivoInscripciones.alta(nueva)) {
        _utilidades.limpiarPantallaConEncabezado("ALTA DE INSCRIPCION");
        std::cout << "\nInscripción realizada con éxito.\n";
        mostrarUnaInscripcion(nueva);
        return;
    }
    else {
        std::cout << "\nError al guardar la inscripción.\n";
        _utilidades.pausarYLimpiar();
        return;
    }   
}

//Método para dar de baja una Inscripción.
void InscripcionManager::bajaInscripcion() {
    InscripcionArchivo archivoInscripciones;
    string entrada;
    int idInscripcion;

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        _utilidades.limpiarPantallaConEncabezado("BAJA DE INSCRIPCION");
        std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
        std::cout << "Ingrese el ID de la inscripción a dar de baja: ";
        std::getline(std::cin, entrada);

        if (_utilidades.esComandoSalir(entrada)) {
            std::cout << "\nOperación cancelada por el usuario.\n";
            _utilidades.pausarYLimpiar();
            return;
        }

        if (!_utilidades.esEnteroValido(entrada)) {
            std::cout << "\nDebe ingresar un número entero válido.\n";
            _utilidades.pausarYLimpiar();
            continue;
        }

        idInscripcion = std::stoi(entrada);
        int posicion = archivoInscripciones.buscar(idInscripcion);

        if (posicion == -1) {
            std::cout << "\nNo se encontró una inscripción con ese ID. Intente nuevamente.\n";
            _utilidades.pausarYLimpiar();
            continue;
        }

        Inscripcion insc;
        archivoInscripciones.leer(posicion, insc);
        _utilidades.limpiarPantallaConEncabezado("DATOS DE LA INSCRIPCION");
        mostrarUnaInscripcion(insc);


        while (true) {
            std::cout << "\n¿Desea dar de baja esta inscripción? (s/n): ";
            std::getline(std::cin, entrada);
            std::string respuesta = _utilidades.aMinusculas(entrada);

            respuesta = _utilidades.aMinusculas(respuesta);

            if (respuesta == "s") {
                break;
            }
            else if (respuesta == "n") {
                std::cout << "\nBaja cancelada por el usuario.\n";
                _utilidades.pausarYLimpiar();
                return;
            }
            else {
                std::cout << "Entrada inválida. Por favor ingrese 's' para Sí o 'n' para No.\n";
            }
        }

        if (archivoInscripciones.baja(idInscripcion)) {
            std::cout << "\nInscripción dada de baja con éxito.\n";
        }
        else {
            std::cout << "\nError al dar de baja la inscripción.\n";
        }

        _utilidades.pausarYLimpiar();
        return;
    }
}

//Método para Modificar una Inscripción.
void InscripcionManager::modificarInscripcion() {
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    _utilidades.limpiarPantallaConEncabezado("MODIFICAR INSCRIPCION");

    InscripcionArchivo archivoInscripciones;
    int idInscripcion, posicion;
    string entrada;

    // --- Pedir ID inscripción existente ---
    while (true) {
        cout << "Ingrese salir en cualquier momento para cancelar la operación.\n";
        cout << "Ingrese el ID de la inscripción a modificar: ";
        getline(cin, entrada);

        if (_utilidades.esComandoSalir(entrada)) {
            cout << "\nOperación cancelada por el usuario.\n";
            return;
        }

        if (!_utilidades.esEnteroValido(entrada)) {
            cout << "\nDebe ingresar un número entero válido.\n\n";
            continue;
        }

        idInscripcion = stoi(entrada);
        posicion = archivoInscripciones.buscar(idInscripcion);
        if (posicion == -1) {
            cout << "\nInscripción no encontrada. Intente nuevamente.\n\n";
            continue;
        }

        break;
    }

    // --- Leer inscripción original ---
    Inscripcion original;
    if (!archivoInscripciones.leer(posicion, original)) {
        cout << "\nError al leer la inscripción.\n";
        return;
    }

    // --- Menú de modificación ---
    float nuevoImporte = original.getImporteAbonado();
    int nuevoIdCurso = original.getIdCurso();
    int opcion = mostrarMenuModificacion(original);

    if (opcion == 0) {
        cout << "\nOperación cancelada por el usuario.\n";
        return;
    }

    // --- Modificar importe ---
    if (opcion == 1 || opcion == 3) {
        _utilidades.limpiarPantallaConEncabezado("MODIFICAR IMPORTE");
        cout << "Importe actual: $" << original.getImporteAbonado() << endl;
        if (!pedirImporte(nuevoImporte)) {
            cout << "\nOperación cancelada por el usuario.\n";
            return;
        }
    }

    // --- Modificar curso ---
    if (opcion == 2 || opcion == 3) {
        _utilidades.limpiarPantallaConEncabezado("MODIFICAR CURSO");
        cout << "ID Curso actual: " << original.getIdCurso() << endl;

        while (true) {
            if (!pedirIdCurso(nuevoIdCurso)) {
                cout << "\nOperación cancelada por el usuario.\n";
                return;
            }

            if (nuevoIdCurso == original.getIdCurso()) {
                cout << "\nYa está inscripto en ese curso. Intente con otro.\n\n";
                continue;
            }

            break;
        }
    }

    // --- Crear inscripción modificada ---
    Inscripcion modificado(idInscripcion,
        original.getLegajoAlumno(),
        nuevoIdCurso,
        original.getFechaInscripcion(),
        nuevoImporte,
        original.getEstado());

    if (archivoInscripciones.modificar(modificado, posicion)) {
        _utilidades.limpiarPantallaConEncabezado("MODIFICAR INSCRIPCION");
        cout << "Inscripción modificada con éxito.\n";
        mostrarUnaInscripcion(modificado);
    }
    else {
        cout << "Error al modificar la inscripción.\n";
    }

    _utilidades.pausarYLimpiar();
}

// Métodos para listar.
// Parámetro: -1 = todas, 1 = solo activas, 0 = solo inactivas
void InscripcionManager::mostrarListadoInscripciones(int filtroEstado) {
    string titulo = "Listado de inscripciones";
    if (filtroEstado == 1) titulo += " activas";
    else if (filtroEstado == 0) titulo += " inactivas";

    _utilidades.limpiarPantallaConEncabezado(titulo);

    InscripcionArchivo archivoInscripciones;
    AlumnoArchivo archivoAlumnos;
    CursoArchivo archivoCursos;
    int cantidad = archivoInscripciones.cantRegistros();
    if (cantidad == 0) {
        cout << "No hay inscripciones registradas." << endl;
        return;
    }

    Inscripcion insc;
    for (int i = 0; i < cantidad; i++) {
        if (!archivoInscripciones.leer(i, insc)) continue;

        // Filtrado por estado
        if (filtroEstado != -1 && insc.getEstado() != (filtroEstado == 1)) continue;

        // Mostrar la información.
        int posAlumno = archivoAlumnos.buscar(insc.getLegajoAlumno(), false);
        int posCurso = archivoCursos.buscar(insc.getIdCurso());
        Alumno alumno;
        Curso curso;
        bool alumnoOk = (posAlumno != -1 && (alumno = archivoAlumnos.leer(posAlumno), true));
        bool cursoOk = (posCurso != -1 && (curso = archivoCursos.leer(posCurso), true));

        cout << "ID Inscripción: " << insc.getIdInscripcion() << endl;
        cout << "Alumno: " << (alumnoOk ? alumno.getNombre() + " " + alumno.getApellido() : "(No encontrado)") << endl;
        cout << "Curso: " << (cursoOk ? curso.getNombre() : "(No encontrado)") << endl;
        cout << "Fecha: " << insc.getFechaInscripcion().toString() << endl;
        cout << fixed << setprecision(3);
        cout << "Importe Abonado: $" << insc.getImporteAbonado() << endl;
        cout << "Estado: " << (insc.getEstado() ? "Activo" : "Inactivo") << endl;
        cout << "------------------------" << endl;
    }
}

void InscripcionManager::mostrarUnaInscripcion(const Inscripcion& inscripcion) {
    cout << "ID Inscripción: " << inscripcion.getIdInscripcion() << endl;
    cout << "Legajo Alumno: " << inscripcion.getLegajoAlumno() << endl;
    cout << "ID Curso: " << inscripcion.getIdCurso() << endl;
    cout << "Fecha Inscripción: " << inscripcion.getFechaInscripcion().toString() << endl;
    cout << std::fixed << std::setprecision(3);
    cout << "Importe Abonado: $" << inscripcion.getImporteAbonado() << endl;
    cout << "Estado: " << (inscripcion.getEstado() ? "Activo" : "Inactivo") << endl;
    cout << "------------------------" << endl;
}

void InscripcionManager::mostrarInscripcionPorId() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string entrada;
    int idInscripcion;
    _utilidades.limpiarPantallaConEncabezado("Busqueda por ID de Inscripción");
    while (true) {
        std::cout << "ID de inscripción: ";
        std::getline(std::cin, entrada);

        if (_utilidades.esComandoSalir(entrada)) return;

        if (!_utilidades.esEnteroValido(entrada)) {
            std::cout << "\nDebe ingresar un número entero válido.\n\n";
            continue;
        }

        idInscripcion = std::stoi(entrada);
        break;
    }

    mostrarInscripcionPorId(idInscripcion);
}

bool InscripcionManager::mostrarInscripcionPorId(int idInscripcion) {
    InscripcionArchivo archivoInscripciones;
    int pos = archivoInscripciones.buscar(idInscripcion);

    if (pos == -1) {
        std::cout << "\nNo se encontró una inscripción con ese ID.\n";
        return false;
    }

    Inscripcion insc;
    if (archivoInscripciones.leer(pos, insc)) {
        mostrarUnaInscripcion(insc);
        return true;
    }
    else {
        std::cout << "\nError al leer la inscripción.\n";
        return false;
    }
}


//Metodos auxiliares para validaciones.
bool InscripcionManager::pedirLegajoAlumno(int& legajo) {
    AlumnoArchivo archivoAlumnos;
    std::string entrada;

    while (true) {
        std::cout << "Legajo Alumno: ";
        std::getline(std::cin, entrada);

        if (_utilidades.esComandoSalir(entrada)) return false;

        if (!_utilidades.esEnteroValido(entrada)) {
            std::cout << "\nDebe ingresar un número entero válido.\n\n";
            continue;
        }

        legajo = std::stoi(entrada);
        if (existeAlumnoActivo(legajo)) return true;
        std::cout << "\nLegajo no encontrado. Intente nuevamente.\n\n";
    }
}

bool InscripcionManager::pedirIdCurso(int& idCurso) {
    CursoArchivo archivoCursos;
    std::string entrada;

    while (true) {
        std::cout << "ID Curso: ";
        std::getline(std::cin, entrada);

        if (_utilidades.esComandoSalir(entrada)) return false;

        if (!_utilidades.esEnteroValido(entrada)) {
            std::cout << "\nDebe ingresar un número entero válido.\n\n";
            continue;
        }

        idCurso = std::stoi(entrada);
		if (existeCursoActivo(idCurso)) return true;

        std::cout << "\nID de curso no encontrado. Intente nuevamente.\n\n";
    }
}

bool InscripcionManager::pedirImporte(float& importe) {
    std::string entrada;

    while (true) {
        std::cout << "Importe abonado: ";
        std::getline(std::cin, entrada);

        if (_utilidades.esComandoSalir(entrada)) return false;

        if (_utilidades.esFloatValido(entrada)) {
            importe = std::stof(entrada);
            return true;
        }

        std::cout << "\nImporte inválido. Intente nuevamente.\n\n";
    }
}

bool InscripcionManager::verificarInscripcionExistente(int legajo, int idCurso) {
    InscripcionArchivo archivoInscripciones;
    Inscripcion insc;
    int cantidad = archivoInscripciones.cantRegistros();

    for (int i = 0; i < cantidad; i++) {
        if (archivoInscripciones.leer(i, insc) &&
            insc.getLegajoAlumno() == legajo &&
            insc.getIdCurso() == idCurso &&
            insc.getEstado()) {
            return true;
        }
    }
    return false;
}

bool InscripcionManager::existeAlumnoActivo(int legajo) {
    AlumnoArchivo archivo;
    int pos = archivo.buscar(legajo, true);
    return pos != -1;
}

bool InscripcionManager::existeCursoActivo(int idCurso) {
    CursoArchivo archivo;
    int pos = archivo.buscar(idCurso);
    if (pos == -1) return false;

    Curso curso = archivo.leer(pos);
    return curso.getEstado();
}

bool InscripcionManager::controlCupo(int idCurso) {
    InscripcionArchivo archivoInscripciones;
    int inscriptos = 0;
    int total = archivoInscripciones.cantRegistros();
    Inscripcion inscTemp;
    for (int i = 0; i < total; i++) {
        if (archivoInscripciones.leer(i, inscTemp) &&
            inscTemp.getIdCurso() == idCurso &&
            inscTemp.getEstado()) {
            inscriptos++;
        }
    }

    CursoArchivo archivoCursos;
    int posCurso = archivoCursos.buscar(idCurso);
    Curso curso = archivoCursos.leer(posCurso);
    int capacidadMaxima = curso.getCantMaximaAlumnos();

    if (inscriptos >= capacidadMaxima) return false;

    return true;
}

// Método para mostrar el menú de modificación de inscripción.
int InscripcionManager::mostrarMenuModificacion(const Inscripcion& original) {
    std::string entrada;

    while (true) {
        _utilidades.limpiarPantallaConEncabezado("MODIFICAR INSCRIPCION");
        cout << "Datos actuales de la inscripción:\n";
        mostrarUnaInscripcion(original);
        cout << "\n¿Qué desea modificar?\n";
        cout << "1. Importe abonado\n";
        cout << "2. ID de curso\n";
        cout << "3. Ambos campos\n";
        cout << "0. Cancelar\n";
        cout << "Seleccione una opción: ";

        getline(cin, entrada);

        if (_utilidades.esEnteroValido(entrada)) {
            int opcion = stoi(entrada);
            switch (opcion) {
            case 0: case 1: case 2: case 3:
                return opcion;
            default:
                cout << "\nOpción inválida. Intente nuevamente.\n\n";
            }
        }
        else {
            cout << "\nDebe ingresar un número válido.\n\n";
        }
    }
}

//Metodos que utilizan Curso y  alumno para la baja en cascada.
void InscripcionManager::bajaInscripcionesPorCurso(int idCurso) {
    InscripcionArchivo archivoInscripciones;
    Inscripcion inscripcion;

    for (int i = 0; i < archivoInscripciones.cantRegistros(); i++) {
        if (archivoInscripciones.leer(i, inscripcion) && inscripcion.getEstado() && inscripcion.getIdCurso() == idCurso) {
            archivoInscripciones.baja(inscripcion.getIdInscripcion());
        }
    }
}

void InscripcionManager::bajaInscripcionesPorAlumno(int legajo) {
    InscripcionArchivo archivoInscripciones;
    Inscripcion inscripcion;

    for (int i = 0; i < archivoInscripciones.cantRegistros(); i++) {
        if (archivoInscripciones.leer(i, inscripcion) && inscripcion.getEstado() && inscripcion.getLegajoAlumno() == legajo) {
            archivoInscripciones.baja(inscripcion.getIdInscripcion());
        }
    }
}
