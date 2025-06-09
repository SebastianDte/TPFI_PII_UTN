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

//int InscripcionArchivo::obtenerProximoId(){
//    int cantidad = cantRegistros();
//    if (cantidad == 0) return 1; // Primer ID
//    Inscripcion ultima;
//    if (leer(cantidad - 1, ultima)) {
//        return ultima.getIdInscripcion() + 1;
//    }
//    return 1; // Si no se pudo leer, por seguridad
//}


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
        std::getline(cin, entrada);
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
	    std:getline(cin, entrada);
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
        cin >> importe;
        if (!cin.fail() && importe >= 0) break;
        cout << "Importe inválido. Intente nuevamente." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }

    int dia, mes, anio;
    while (true) {
        cout << "Fecha (dd mm aaaa): ";
        cin >> dia >> mes >> anio;
        Fecha fechaTemp;
        if (fechaTemp.esFechaValida(dia, mes, anio)) break;
        cout << "Fecha inválida. Intente nuevamente." << endl;
    }
    Fecha fecha(dia, mes, anio);

    int id = archivoInscripciones.cantRegistros() + 1;
    bool estado = true;

    Inscripcion inscripcion(id, legajo, idCurso, fecha, importe, estado);

    if (archivoInscripciones.alta(inscripcion)) {
        cout << "Inscripción realizada con éxito." << endl;
    }
    else {
        cout << "Error al realizar la inscripción." << endl;
    }
}

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
			cout << "Importe Abonado: " << inscripcion.getImporteAbonado() << endl;
			cout << "Estado: " << (inscripcion.getEstado() ? "Activo" : "Inactivo") << endl;
			cout << "------------------------" << endl;
		}
	}
}
