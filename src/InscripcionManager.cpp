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

    //Ingreso del Legajo Alumno.
    while (true) {
		
        cout << "Legajo Alumno: ";
        getline(cin, entrada);
		if (utilidades.esEnteroValido(entrada)) {
			legajo = stoi(entrada);
		}
		else {
			cout << "Debe ingresar un número entero válido." << endl;
			continue;
		}
        if (archivoAlumnos.buscar(legajo,true) != -1) break;
        cout << "Legajo no encontrado. Intente nuevamente." << endl;
    }

	//Ingreso del ID del Curso.
    int idCurso;
    while (true) {
        cout << "ID Curso: ";
	    getline(cin, entrada);
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
	int idInscripcion;
	cout << "Ingrese el ID de la inscripción a dar de baja: ";
	cin >> idInscripcion;
	InscripcionArchivo archivoInscripciones;
	if (archivoInscripciones.baja(idInscripcion)) {
		cout << "Inscripción dada de baja con éxito." << endl;
	}
	else {
		cout << "Error al dar de baja la inscripción." << endl;
	}
}

// Método para modificar una Inscripción.
void InscripcionManager::modificarInscripcion() {
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

    int legajo, idCurso;
    float importe;
    int dia, mes, anio;
    cout << "Nuevo Legajo Alumno: ";
    cin >> legajo;
    cout << "Nuevo ID Curso: ";
    cin >> idCurso;
    cout << "Nueva Fecha (dd mm aaaa): ";
    cin >> dia >> mes >> anio;
    cout << "Nuevo Importe abonado: ";
    cin >> importe;

    Fecha fecha(dia, mes, anio);
    Inscripcion inscripcion(idInscripcion, legajo, idCurso, fecha, importe, original.getEstado());

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
	int cantidad = archivoInscripciones.cantRegistros();
	if (cantidad == 0) {
		cout << "No hay inscripciones registradas." << endl;
		return;
	}
	Inscripcion inscripcion;
	for (int i = 0; i < cantidad; i++) {
		if (archivoInscripciones.leer(i, inscripcion) && inscripcion.getEstado()) {
			cout << "ID Inscripción: " << inscripcion.getIdInscripcion() << endl;
			cout << "Legajo Alumno: " << inscripcion.getLegajoAlumno() << endl;
			cout << "ID Curso: " << inscripcion.getIdCurso() << endl;
			cout << "Fecha: " << inscripcion.getFechaInscripcion().toString() << endl;

            cout << std::fixed << std::setprecision(3);
            cout << "Importe Abonado: $" << inscripcion.getImporteAbonado() << endl;

			cout << "Estado: " << (inscripcion.getEstado() ? "Activo" : "Inactivo") << endl;
			cout << "------------------------" << endl;
		}
	}
}
