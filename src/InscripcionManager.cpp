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
using namespace std;

//Método para dar de alta una Inscripción.
void InscripcionManager::altaInscripcion() {
    InscripcionArchivo archivoInscripciones;
    AlumnoArchivo archivoAlumnos; 
    CursoArchivo archivoCursos;
    string entrada;
    int legajo;
    Utilidades utilidades;

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
    utilidades.limpiarPantallaConEncabezado("ALTA DE INSCRIPCION");

    //Ingreso del Legajo Alumno.
    while (true) {
        cout << "Legajo Alumno: ";
        getline(cin, entrada);

        if (utilidades.esComandoSalir(entrada)) {
            cout << "Alta de inscripción cancelada por el usuario." << endl;
            return;
        }

        if (utilidades.esEnteroValido(entrada)) {
            legajo = stoi(entrada);
        }
        else {
            cout << "Debe ingresar un número entero válido." << endl;
            continue;
        }
        if (archivoAlumnos.buscar(legajo, true) != -1) break;
        cout << "Legajo no encontrado. Intente nuevamente." << endl;
    }

    //Ingreso del ID del Curso.
    int idCurso;
    while (true) {
        cout << "ID Curso: ";
        getline(cin, entrada);

        if (utilidades.esComandoSalir(entrada)) {
            cout << "Alta de inscripción cancelada por el usuario." << endl;
            return;
        }

        if (utilidades.esEnteroValido(entrada)) {
            idCurso = stoi(entrada);
        }
        else {
            cout << "Debe ingresar un número entero válido." << endl;
            continue;
        }
        if (archivoCursos.buscar(idCurso) != -1) break;
        cout << "ID de curso no encontrado. Intente nuevamente." << endl;
    }

    //Ingreso del Importe Abonado.
    float importe;
    while (true) {
        cout << "Importe abonado: ";
        getline(cin, entrada);

        if (utilidades.esComandoSalir(entrada)) {
            cout << "Alta de inscripción cancelada por el usuario." << endl;
            return;
        }

        if (utilidades.esFloatValido(entrada)) {
            importe = stof(entrada);
            break;
        }
        else {
            cout << "Importe inválido. Intente nuevamente." << endl;
        }
    }

    //Fecha automatica del sistema.
    Fecha fecha = Fecha::fechaActual();

	// Generación del ID de inscripción automatico.
	int id = archivoInscripciones.obtenerProximoId();

	//Estado Activo por defecto.
    bool estado = true;

	// Creación de la inscripción.
    Inscripcion inscripcion(id, legajo, idCurso, fecha, importe, estado);

	// Antes de crear la inscripción, se verifica que el alumno no esté ya inscripto en el curso.
    bool yaInscripto = false;
    Inscripcion inscTemp;
    int cantidad = archivoInscripciones.cantRegistros();
    for (int i = 0; i < cantidad; i++) {
        if (archivoInscripciones.leer(i, inscTemp) &&
            inscTemp.getLegajoAlumno() == legajo &&
            inscTemp.getIdCurso() == idCurso &&
            inscTemp.getEstado()) // Solo inscripciones activas
        {
            yaInscripto = true;
            break;
        }
    }

    if (yaInscripto) {
        cout << "El alumno ya está inscripto en ese curso." << endl;
        return;
    }


	//Se da de alta la inscripción.
    if (archivoInscripciones.alta(inscripcion)) {
        cout << "Inscripción realizada con éxito." << endl;
    }
    else {
        cout << "Error al realizar la inscripción." << endl;
    }
}

//Método para dar de baja una Inscripción.
void InscripcionManager::bajaInscripcion() {
    Utilidades utilidades;
    string entrada;
    int idInscripcion;
    InscripcionArchivo archivoInscripciones;

    // Limpiar buffer 
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    utilidades.limpiarPantallaConEncabezado("BAJA DE INSCRIPCION");
    while (true) {
        cout << "Ingrese el ID de la inscripción a dar de baja (o escriba 'salir'): ";
        getline(cin, entrada);

        if (utilidades.esComandoSalir(entrada)) {
            cout << "Operación cancelada por el usuario." << endl;
            return;
        }

        if (!utilidades.esEnteroValido(entrada)) {
            cout << "Debe ingresar un número entero válido." << endl;
            continue;
        }

        idInscripcion = stoi(entrada);

        int posicion = archivoInscripciones.buscar(idInscripcion);
        if (posicion == -1) {
            cout << "No se encontró una inscripción con ese ID. Intente nuevamente." << endl;
            continue;
        }

        if (archivoInscripciones.baja(idInscripcion)) {
            cout << "Inscripción dada de baja con éxito." << endl;
        }
        else {
            cout << "Error al dar de baja la inscripción." << endl;
        }

        break;  // Salimos del bucle después de intentar la baja
    }
}

// Método para modificar una Inscripción.
void InscripcionManager::modificarInscripcion() {
    Utilidades utilidades;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    utilidades.limpiarPantallaConEncabezado("MODIFICAR INSCRIPCION");

    int idInscripcion;
    cout << "Ingrese el ID de la inscripción a modificar: ";
    cin >> idInscripcion;
    InscripcionArchivo archivoInscripciones;
    int posicion = archivoInscripciones.buscar(idInscripcion);
    if (posicion == -1) {
        cout << "Inscripción no encontrada." << endl;
        return;
    }

    Inscripcion original;
    if (!archivoInscripciones.leer(posicion, original)) {
        cout << "Error al leer la inscripción original." << endl;
        return;
    }

    string entrada;
    float nuevoImporte = original.getImporteAbonado();
    int nuevoIdCurso = original.getIdCurso();
    CursoArchivo archivoCursos;

    int opcion;
    cout << "\n¿Qué desea modificar?\n";
    cout << "1. Importe abonado\n";
    cout << "2. ID de curso\n";
    cout << "3. Ambos campos\n";
    cout << "0. Cancelar\n";
    cout << "Seleccione una opción: ";
    cin >> opcion;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (opcion == 0) {
        cout << "Operación cancelada por el usuario." << endl;
        return;
    }

    if (opcion == 1 || opcion == 3) {
        while (true) {
            cout << "Importe actual: $" << original.getImporteAbonado() << endl;
            cout << "Nuevo importe: ";
            getline(cin, entrada);
            if (utilidades.esComandoSalir(entrada)) return;
            if (utilidades.esFloatValido(entrada)) {
                nuevoImporte = stof(entrada);
                break;
            }
            cout << "Importe inválido. Intente nuevamente." << endl;
        }
    }

    if (opcion == 2 || opcion == 3) {
        while (true) {
            cout << "ID de curso actual: " << original.getIdCurso() << endl;
            cout << "Nuevo ID de curso: ";
            getline(cin, entrada);
            if (utilidades.esComandoSalir(entrada)) return;
            if (!utilidades.esEnteroValido(entrada)) {
                cout << "ID de curso inválido. Intente nuevamente." << endl;
                continue;
            }
            nuevoIdCurso = stoi(entrada);
            // Validar que el curso exista
            if (archivoCursos.buscar(nuevoIdCurso) == -1) {
                cout << "ID de curso no encontrado. Intente nuevamente." << endl;
                continue;
            }
            // Validar que no exista ya una inscripción activa para ese legajo y ese curso
            int cantidad = archivoInscripciones.cantRegistros();
            Inscripcion inscTemp;
            bool yaInscripto = false;
            for (int i = 0; i < cantidad; i++) {
                if (archivoInscripciones.leer(i, inscTemp) &&
                    inscTemp.getLegajoAlumno() == original.getLegajoAlumno() &&
                    inscTemp.getIdCurso() == nuevoIdCurso &&
                    inscTemp.getEstado() &&
                    inscTemp.getIdInscripcion() != idInscripcion) {
                    yaInscripto = true;
                    break;
                }
            }
            if (yaInscripto) {
                cout << "Ya existe una inscripción activa para este alumno en ese curso." << endl;
                continue;
            }
            break;
        }
    }

    // No se modifica ni el legajo ni la fecha de inscripción
    Inscripcion inscripcion(idInscripcion, original.getLegajoAlumno(), nuevoIdCurso, original.getFechaInscripcion(), nuevoImporte, original.getEstado());

    if (archivoInscripciones.modificar(inscripcion, posicion)) {
        cout << "Inscripción modificada con éxito." << endl;
    }
    else {
        cout << "Error al modificar la inscripción." << endl;
    }
}

// Método para listar todas las Inscripciones activas.
void InscripcionManager::listarInscripciones() {
    InscripcionArchivo archivoInscripciones;
    AlumnoArchivo archivoAlumnos;
    CursoArchivo archivoCursos;
    int cantidad = archivoInscripciones.cantRegistros();
    if (cantidad == 0) {
        cout << "No hay inscripciones registradas." << endl;
        return;
    }
    Inscripcion inscripcion;
    for (int i = 0; i < cantidad; i++) {
        if (archivoInscripciones.leer(i, inscripcion) && inscripcion.getEstado()) {
            // Obtener datos del alumno (buscar sin filtrar activos para mostrar aunque esté dado de baja)
            int posAlumno = archivoAlumnos.buscar(inscripcion.getLegajoAlumno(), false);
            Alumno alumno;
            bool alumnoOk = false;
            if (posAlumno != -1) {
                alumno = archivoAlumnos.leer(posAlumno);
                alumnoOk = true;
            }

            // Obtener datos del curso (no se filtra por estado)
            int posCurso = archivoCursos.buscar(inscripcion.getIdCurso());
            Curso curso;
            bool cursoOk = false;
            if (posCurso != -1) {
                curso = archivoCursos.leer(posCurso);
                cursoOk = true;
            }

            cout << "ID Inscripción: " << inscripcion.getIdInscripcion() << endl;
            if (alumnoOk) {
                cout << "Alumno: " << alumno.getNombre() << " " << alumno.getApellido() << endl;
            }
            else {
                cout << "Alumno: (No encontrado)" << endl;
            }
            if (cursoOk) {
                cout << "Curso: " << curso.getNombre() << endl;
            }
            else {
                cout << "Curso: (No encontrado)" << endl;
            }
            cout << "Fecha: " << inscripcion.getFechaInscripcion().toString() << endl;
            cout << std::fixed << std::setprecision(3);
            cout << "Importe Abonado: $" << inscripcion.getImporteAbonado() << endl;
            cout << "Estado: " << (inscripcion.getEstado() ? "Activo" : "Inactivo") << endl;
            cout << "------------------------" << endl;
        }
    }
}
