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


//M�todo para dar de alta una Inscripci�n.
void InscripcionManager::altaInscripcion() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int legajo = 0, idCurso = 0;
    float importe = 0.0f;
    bool cancelar = false;

    // Paso 1: Legajo del alumno
    while (true) {
        _utilidades.limpiarPantallaConEncabezado("ALTA DE INSCRIPCION");
        std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";

        if (!pedirLegajoAlumno(legajo)) {
            std::cout << "\nAlta de inscripci�n cancelada.\n";
            return;
        }

        break;
    }

    // Paso 2: ID del curso
    while (true) {
        _utilidades.limpiarPantallaConEncabezado("ALTA DE INSCRIPCION");
        std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
        std::cout << "Legajo Alumno: " << legajo << "\n";

        if (!pedirIdCurso(idCurso)) {
            std::cout << "\nAlta de inscripci�n cancelada.\n";
            return;
        }

        if (verificarInscripcionExistente(legajo, idCurso)) {
            std::cout << "\nEl alumno ya est� inscripto en ese curso.\n";
            _utilidades.pausar();
            continue;
        }

        break;
    }

    // Paso 3: Importe abonado
    while (true) {
        _utilidades.limpiarPantallaConEncabezado("ALTA DE INSCRIPCION");
        std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
        std::cout << "Legajo Alumno: " << legajo << "\n";
        std::cout << "ID Curso: " << idCurso << "\n";

        if (!pedirImporte(importe)) {
            std::cout << "\nAlta de inscripci�n cancelada.\n";
            return;
        }

        break;
    }

    // Paso final: Guardar la inscripci�n
    Fecha fecha = Fecha::fechaActual();
    InscripcionArchivo archivoInscripciones;
    int id = archivoInscripciones.obtenerProximoId();
    bool estado = true;

    Inscripcion nueva(id, legajo, idCurso, fecha, importe, estado);

    if (archivoInscripciones.alta(nueva)) {
        _utilidades.limpiarPantallaConEncabezado("ALTA DE INSCRIPCION");
        std::cout << "\nInscripci�n realizada con �xito.\n";
        mostrarUnaInscripcion(nueva);
    }
    else {
        std::cout << "\nError al guardar la inscripci�n.\n";
    }

    _utilidades.pausarYLimpiar();
}

//M�todo para dar de baja una Inscripci�n.
void InscripcionManager::bajaInscripcion() {
    InscripcionArchivo archivoInscripciones;
    string entrada;
    int idInscripcion;

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        _utilidades.limpiarPantallaConEncabezado("BAJA DE INSCRIPCION");
        std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
        std::cout << "Ingrese el ID de la inscripci�n a dar de baja: ";
        std::getline(std::cin, entrada);

        if (_utilidades.esComandoSalir(entrada)) {
            std::cout << "\nOperaci�n cancelada por el usuario.\n";
            _utilidades.pausarYLimpiar();
            return;
        }

        if (!_utilidades.esEnteroValido(entrada)) {
            std::cout << "\nDebe ingresar un n�mero entero v�lido.\n";
            _utilidades.pausarYLimpiar();
            continue;
        }

        idInscripcion = std::stoi(entrada);
        int posicion = archivoInscripciones.buscar(idInscripcion);

        if (posicion == -1) {
            std::cout << "\nNo se encontr� una inscripci�n con ese ID. Intente nuevamente.\n";
            _utilidades.pausarYLimpiar();
            continue;
        }

        Inscripcion insc;
        archivoInscripciones.leer(posicion, insc);
        _utilidades.limpiarPantallaConEncabezado("DATOS DE LA INSCRIPCION");
        mostrarUnaInscripcion(insc);


        while (true) {
            std::cout << "\n�Desea dar de baja esta inscripci�n? (s/n): ";
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
                std::cout << "Entrada inv�lida. Por favor ingrese 's' para S� o 'n' para No.\n";
            }
        }

        if (archivoInscripciones.baja(idInscripcion)) {
            std::cout << "\nInscripci�n dada de baja con �xito.\n";
        }
        else {
            std::cout << "\nError al dar de baja la inscripci�n.\n";
        }

        _utilidades.pausarYLimpiar();
        return;
    }
}

// M�todo para modificar una Inscripci�n.
void InscripcionManager::modificarInscripcion() {
    Utilidades utilidades;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    utilidades.limpiarPantallaConEncabezado("MODIFICAR INSCRIPCION");
    InscripcionArchivo archivoInscripciones;
    int idInscripcion, posicion;
    string entrada;

    // 1. Solicitar ID
    while (true) {
        utilidades.limpiarPantallaConEncabezado("MODIFICAR INSCRIPCION");
        cout << "Ingrese el ID de la inscripci�n a modificar: ";
        getline(cin, entrada);

        if (!utilidades.esEnteroValido(entrada)) {
            cout << "Debe ingresar un n�mero entero v�lido." << endl;
            utilidades.pausarYLimpiar();
            continue;
        }

        idInscripcion = stoi(entrada);
        posicion = archivoInscripciones.buscar(idInscripcion);
        if (posicion == -1) {
            cout << "Inscripci�n no encontrada. Intente nuevamente." << endl;
            utilidades.pausarYLimpiar();
            continue;
        }

        break;
    }

    // 2. Leer la inscripci�n original
    Inscripcion original;
    if (!archivoInscripciones.leer(posicion, original)) {
        cout << "Error al leer la inscripci�n." << endl;
        return;
    }


    // 3. Men� de opciones
    float nuevoImporte = original.getImporteAbonado();
    int nuevoIdCurso = original.getIdCurso();
    CursoArchivo archivoCursos;
    int opcion;

    while (true) {
        utilidades.limpiarPantallaConEncabezado("MODIFICAR INSCRIPCION");
        cout << "Datos de la inscripci�n a modificar:" << endl;
        mostrarUnaInscripcion(original);
        cout << "\n�Qu� desea modificar?\n";
        cout << "1. Importe abonado\n";
        cout << "2. ID de curso\n";
        cout << "3. Ambos campos\n";
        cout << "0. Cancelar\n";
        cout << "Seleccione una opci�n: ";
        getline(cin, entrada);

        if (utilidades.esEnteroValido(entrada)) {
            opcion = stoi(entrada);
            if (opcion >= 0 && opcion <= 3) break;
        }

        cout << "Opci�n inv�lida. Intente nuevamente." << endl;
        utilidades.pausarYLimpiar();
    }

    if (opcion == 0) {
        cout << "Operaci�n cancelada por el usuario." << endl;
        return;
    }

    // 4. Modificar campos seg�n opci�n
    if (opcion == 1 || opcion == 3) {
        while (true) {
            utilidades.limpiarPantallaConEncabezado("MODIFICAR INSCRIPCION");
            cout << "Importe actual: $" << original.getImporteAbonado() << endl;
            cout << "Nuevo importe: ";
            getline(cin, entrada);
            if (utilidades.esComandoSalir(entrada)) return;
            if (utilidades.esFloatValido(entrada)) {
                nuevoImporte = stof(entrada);
                break;
            }
            cout << "Importe inv�lido. Intente nuevamente." << endl;
            utilidades.pausarYLimpiar();
        }
    }

    if (opcion == 2 || opcion == 3) {
        while (true) {
            utilidades.limpiarPantallaConEncabezado("MODIFICAR INSCRIPCION");
            cout << "ID de curso actual: " << original.getIdCurso() << endl;
            cout << "Nuevo ID de curso: ";
            getline(cin, entrada);
            if (utilidades.esComandoSalir(entrada)) return;
            if (!utilidades.esEnteroValido(entrada)) {
                cout << "ID de curso inv�lido. Intente nuevamente." << endl;
                utilidades.pausarYLimpiar();
                continue;
            }

            nuevoIdCurso = stoi(entrada);

            // Verificar que el curso exista
            if (archivoCursos.buscar(nuevoIdCurso) == -1) {
                cout << "ID de curso no encontrado. Intente nuevamente." << endl;
                utilidades.pausarYLimpiar();
                continue;
            }
            //Verificar que no est� intentando inscribirse al mismo curso actual.
            if (nuevoIdCurso == original.getIdCurso()) {
                cout << "Ya est� inscripto en ese curso." << endl;
                utilidades.pausarYLimpiar();
                continue;
            }
            break;
        }
    }

    // 5. Crear la inscripci�n modificada
    Inscripcion modificado(idInscripcion, original.getLegajoAlumno(), nuevoIdCurso,
        original.getFechaInscripcion(), nuevoImporte, original.getEstado());

    if (archivoInscripciones.modificar(modificado, posicion)) {
        utilidades.limpiarPantallaConEncabezado("MODIFICAR INSCRIPCION");
        cout << "Inscripci�n modificada con �xito." << endl;
        mostrarUnaInscripcion(modificado);
        utilidades.pausarYLimpiar();
    }
    else {
        cout << "Error al modificar la inscripci�n." << endl;
    }
    return;
}

// M�todos para listar.
void InscripcionManager::listarInscripcionesActivas() {
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

void InscripcionManager::listarInscripcionesInactivas() {
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
        if (archivoInscripciones.leer(i, inscripcion) && !inscripcion.getEstado()) {
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

void InscripcionManager::listarTodasInscripciones() {
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
        if (archivoInscripciones.leer(i, inscripcion)){
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

void InscripcionManager::mostrarUnaInscripcion(const Inscripcion& inscripcion) {
    cout << "ID Inscripci�n: " << inscripcion.getIdInscripcion() << endl;
    cout << "Legajo Alumno: " << inscripcion.getLegajoAlumno() << endl;
    cout << "ID Curso: " << inscripcion.getIdCurso() << endl;
    cout << "Fecha Inscripci�n: " << inscripcion.getFechaInscripcion().toString() << endl;
    cout << std::fixed << std::setprecision(3);
    cout << "Importe Abonado: $" << inscripcion.getImporteAbonado() << endl;
    cout << "Estado: " << (inscripcion.getEstado() ? "Activo" : "Inactivo") << endl;
    cout << "------------------------" << endl;

}

//Metodos auxiliares
bool InscripcionManager::pedirLegajoAlumno(int& legajo) {
    AlumnoArchivo archivoAlumnos;
    std::string entrada;

    while (true) {
        std::cout << "Legajo Alumno: ";
        std::getline(std::cin, entrada);

        if (_utilidades.esComandoSalir(entrada)) return false;

        if (!_utilidades.esEnteroValido(entrada)) {
            std::cout << "\nDebe ingresar un n�mero entero v�lido.\n\n";
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
            std::cout << "\nDebe ingresar un n�mero entero v�lido.\n\n";
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

        std::cout << "\nImporte inv�lido. Intente nuevamente.\n\n";
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
