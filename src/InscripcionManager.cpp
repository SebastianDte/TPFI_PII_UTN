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

    //Ingreso del Legajo Alumno.
    while (true) {
		
        cout << "Legajo Alumno: ";
        getline(cin, entrada);
		if (utilidades.esEnteroValido(entrada)) {
			legajo = stoi(entrada);
		}
		else {
			cout << "Debe ingresar un n�mero entero v�lido." << endl;
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
	int idInscripcion;
	cout << "Ingrese el ID de la inscripci�n a dar de baja: ";
	cin >> idInscripcion;
	InscripcionArchivo archivoInscripciones;
	if (archivoInscripciones.baja(idInscripcion)) {
		cout << "Inscripci�n dada de baja con �xito." << endl;
	}
	else {
		cout << "Error al dar de baja la inscripci�n." << endl;
	}
}

// M�todo para modificar una Inscripci�n.
void InscripcionManager::modificarInscripcion() {
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
        cout << "Inscripci�n modificada con �xito." << endl;
    }
    else {
        cout << "Error al modificar la inscripci�n." << endl;
    }
}

// M�todo para listar todas las Inscripciones activas.
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
			cout << "ID Inscripci�n: " << inscripcion.getIdInscripcion() << endl;
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
