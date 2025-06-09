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

//M�todo para dar de alta una Inscripci�n.
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
            cout << "Alta de inscripci�n cancelada por el usuario." << endl;
            return;
        }

        if (utilidades.esEnteroValido(entrada)) {
            legajo = stoi(entrada);
        }
        else {
            cout << "Debe ingresar un n�mero entero v�lido." << endl;
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
            cout << "Alta de inscripci�n cancelada por el usuario." << endl;
            return;
        }

        if (utilidades.esEnteroValido(entrada)) {
            idCurso = stoi(entrada);
        }
        else {
            cout << "Debe ingresar un n�mero entero v�lido." << endl;
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
            cout << "Alta de inscripci�n cancelada por el usuario." << endl;
            return;
        }

        if (utilidades.esFloatValido(entrada)) {
            importe = stof(entrada);
            break;
        }
        else {
            cout << "Importe inv�lido. Intente nuevamente." << endl;
        }
    }

    //Fecha automatica del sistema.
    Fecha fecha = Fecha::fechaActual();

	// Generaci�n del ID de inscripci�n automatico.
	int id = archivoInscripciones.obtenerProximoId();

	//Estado Activo por defecto.
    bool estado = true;

	// Creaci�n de la inscripci�n.
    Inscripcion inscripcion(id, legajo, idCurso, fecha, importe, estado);

	// Antes de crear la inscripci�n, se verifica que el alumno no est� ya inscripto en el curso.
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
        cout << "El alumno ya est� inscripto en ese curso." << endl;
        return;
    }


	//Se da de alta la inscripci�n.
    if (archivoInscripciones.alta(inscripcion)) {
        cout << "Inscripci�n realizada con �xito." << endl;
    }
    else {
        cout << "Error al realizar la inscripci�n." << endl;
    }
}

//M�todo para dar de baja una Inscripci�n.
void InscripcionManager::bajaInscripcion() {
    Utilidades utilidades;
    string entrada;
    int idInscripcion;
    InscripcionArchivo archivoInscripciones;

    // Limpiar buffer 
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    utilidades.limpiarPantallaConEncabezado("BAJA DE INSCRIPCION");
    while (true) {
        cout << "Ingrese el ID de la inscripci�n a dar de baja (o escriba 'salir'): ";
        getline(cin, entrada);

        if (utilidades.esComandoSalir(entrada)) {
            cout << "Operaci�n cancelada por el usuario." << endl;
            return;
        }

        if (!utilidades.esEnteroValido(entrada)) {
            cout << "Debe ingresar un n�mero entero v�lido." << endl;
            continue;
        }

        idInscripcion = stoi(entrada);

        int posicion = archivoInscripciones.buscar(idInscripcion);
        if (posicion == -1) {
            cout << "No se encontr� una inscripci�n con ese ID. Intente nuevamente." << endl;
            continue;
        }

        if (archivoInscripciones.baja(idInscripcion)) {
            cout << "Inscripci�n dada de baja con �xito." << endl;
        }
        else {
            cout << "Error al dar de baja la inscripci�n." << endl;
        }

        break;  // Salimos del bucle despu�s de intentar la baja
    }
}

// M�todo para modificar una Inscripci�n.
void InscripcionManager::modificarInscripcion() {
    Utilidades utilidades;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    utilidades.limpiarPantallaConEncabezado("MODIFICAR INSCRIPCION");

    int idInscripcion;
    cout << "Ingrese el ID de la inscripci�n a modificar: ";
    cin >> idInscripcion;
    InscripcionArchivo archivoInscripciones;
    int posicion = archivoInscripciones.buscar(idInscripcion);
    if (posicion == -1) {
        cout << "Inscripci�n no encontrada." << endl;
        return;
    }

    Inscripcion original;
    if (!archivoInscripciones.leer(posicion, original)) {
        cout << "Error al leer la inscripci�n original." << endl;
        return;
    }

    string entrada;
    float nuevoImporte = original.getImporteAbonado();
    int nuevoIdCurso = original.getIdCurso();
    CursoArchivo archivoCursos;

    int opcion;
    cout << "\n�Qu� desea modificar?\n";
    cout << "1. Importe abonado\n";
    cout << "2. ID de curso\n";
    cout << "3. Ambos campos\n";
    cout << "0. Cancelar\n";
    cout << "Seleccione una opci�n: ";
    cin >> opcion;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (opcion == 0) {
        cout << "Operaci�n cancelada por el usuario." << endl;
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
            cout << "Importe inv�lido. Intente nuevamente." << endl;
        }
    }

    if (opcion == 2 || opcion == 3) {
        while (true) {
            cout << "ID de curso actual: " << original.getIdCurso() << endl;
            cout << "Nuevo ID de curso: ";
            getline(cin, entrada);
            if (utilidades.esComandoSalir(entrada)) return;
            if (!utilidades.esEnteroValido(entrada)) {
                cout << "ID de curso inv�lido. Intente nuevamente." << endl;
                continue;
            }
            nuevoIdCurso = stoi(entrada);
            // Validar que el curso exista
            if (archivoCursos.buscar(nuevoIdCurso) == -1) {
                cout << "ID de curso no encontrado. Intente nuevamente." << endl;
                continue;
            }
            // Validar que no exista ya una inscripci�n activa para ese legajo y ese curso
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
                cout << "Ya existe una inscripci�n activa para este alumno en ese curso." << endl;
                continue;
            }
            break;
        }
    }

    // No se modifica ni el legajo ni la fecha de inscripci�n
    Inscripcion inscripcion(idInscripcion, original.getLegajoAlumno(), nuevoIdCurso, original.getFechaInscripcion(), nuevoImporte, original.getEstado());

    if (archivoInscripciones.modificar(inscripcion, posicion)) {
        cout << "Inscripci�n modificada con �xito." << endl;
    }
    else {
        cout << "Error al modificar la inscripci�n." << endl;
    }
}

// M�todo para listar todas las Inscripciones activas.
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
            // Obtener datos del alumno (buscar sin filtrar activos para mostrar aunque est� dado de baja)
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

            cout << "ID Inscripci�n: " << inscripcion.getIdInscripcion() << endl;
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
