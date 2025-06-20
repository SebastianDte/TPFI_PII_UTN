#include <iostream>
#include <iomanip>
#include "ReportesManager.h"
#include "CursoArchivo.h"
#include "AlumnoArchivo.h"
#include "InscripcionArchivo.h"
#include "ProfesorArchivo.h"
#include "Utilidades.h"

ReportesManager::ReportesManager()
{
    _cursoArchivo = CursoArchivo();
    _alumnoArchivo = AlumnoArchivo();
    _inscripcionArchivo = InscripcionArchivo();
    _profesorArchivo = ProfesorArchivo();
    _utilidades = Utilidades();
}

void ReportesManager::totalInscriptosPorCurso()
{
    std::cout << "Total de inscriptos por curso" << std::endl;

    Inscripcion regInscripcion;
    Curso regCurso;
    std::string input;
    int cantRegCursos, cantRegInscripciones, idCurso, posicion;
    int totalInscriptos = 0;
    int cantInsActivas = 0;
    int indiceIns = 0;

    Inscripcion *vecInscripciones;

    cantRegCursos = _cursoArchivo.cantRegistros();

    if (cantRegCursos == 0)
    {
        std::cout << "No hay cursos registrados en el sistema.\n";
        return;
    }

    cantRegInscripciones = _inscripcionArchivo.cantRegistros();

    if ( cantRegInscripciones == 0 )
    {

        std::cout << "No hay inscripciones registradas en el sistema.\n";
        return;
    }

    while(true)
    {

        system("cls");

        _utilidades.limpiarPantallaConEncabezado("=== REPORTE - TOTAL DE INSCRIPTOS POR CURSO ===");

        std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
        std::cout<<"Ingrese el ID del curso: \n";
        std::getline(std::cin,input);

        if (_utilidades.esComandoSalir(input))
        {
            system("cls");
            std::cout << "\nReporte cancelado.\n\n";
            return;

        }

        if (input.empty())
        {
            system("cls");
            std::cout << "Debe completar este campo. Intente nuevamente.\n\n";
            system("pause");

            continue;

        }


        if ( !_utilidades.esEnteroValido(input) )
        {
            system("cls");
            std::cout << "\nDebe ingresar un número entero. Intente nuevamente.\n\n";
            system("pause");
            continue;
        }

        idCurso = std::stoi(input);

        posicion = _cursoArchivo.buscar(idCurso);

        if ( posicion < 0 )
        {

            system("cls");

            std::cout<<"\nEl ID ingresado no pertenece a un curso registrado.\n\n";
            system("pause");
            continue;

        }

        regCurso = _cursoArchivo.leer(posicion);

        if ( !regCurso.getEstado() )
        {

            system("cls");

            std::cout<<"\nEl ID ingresado no pertenece a un curso activo.\n\n";

            system("pause");
            continue;

        }

        break;

    }

    if ( !_cursoArchivo.tieneInscripcionesActivas( idCurso ) )
    {

        std::cout<<"El curso seleccionado no posee registros de inscripciones.\n";
        return;
    }

    ///Inscripciones

    for ( int i = 0; i < cantRegInscripciones; i ++ )
    {

        _inscripcionArchivo.leer(i, regInscripcion);

        if ( regInscripcion.getEstado() )
        {

            cantInsActivas ++;

        }

    }

    vecInscripciones = new Inscripcion [ cantInsActivas ];

    if ( vecInscripciones == nullptr )
    {

        std::cout<<"No se pudo asignar memoria.\n";
        return;
    }

    for ( int i = 0; i < cantRegInscripciones; i ++ )
    {

        _inscripcionArchivo.leer(i, regInscripcion);

        if ( regInscripcion.getEstado() )
        {

            vecInscripciones[indiceIns] = regInscripcion;

            indiceIns ++;
        }

    }


    for ( int i = 0; i < cantInsActivas; i++ )
    {

        if ( vecInscripciones[i].getIdCurso() == idCurso )
        {

            totalInscriptos ++;

        }

    }

    if (  totalInscriptos == 0 )
    {

        std::cout<<"Curso: "<<regCurso.getNombre()<<".\n";
        std::cout<<"Aun no hay inscriptos en este curso.\n";
        return;
    }

    system("cls");
    std::cout<<"Curso: "<<regCurso.getNombre()<<".\n";
    std::cout<<"Total de alumnos inscriptos: "<<totalInscriptos<<".\n";


    delete [] vecInscripciones;

}

void ReportesManager::alumnosInscriptosEnCurso()
{
    Utilidades utilidades;
    CursoArchivo archivoCursos;
    std::string inputUsuario;
    int idCursoSeleccionado;
    int posCurso;

    while (true)
    {
        utilidades.limpiarPantallaConEncabezado("=== REPORTE - ALUMNOS POR CURSO ===");
        std::cout << "Ingrese el ID del curso para ver los inscriptos (o 'salir' para cancelar): ";
        std::getline(std::cin, inputUsuario);

        if (utilidades.esComandoSalir(inputUsuario))
        {
            std::cout << "Reporte cancelado.\n";
            return;
        }

        if (!utilidades.esEnteroValido(inputUsuario))
        {
            std::cout << "Debe ingresar un número entero válido. Intente nuevamente.\n";
            utilidades.pausar();
            continue;
        }

        idCursoSeleccionado = std::stoi(inputUsuario);
        posCurso = archivoCursos.buscar(idCursoSeleccionado);

        if (posCurso == -1)
        {
            std::cout << "No se encontró un curso con el ID " << idCursoSeleccionado << ". Intente nuevamente.\n";
            utilidades.pausar();
            continue;
        }

        break;
    }

    InscripcionArchivo archivoInscripciones;
    AlumnoArchivo archivoAlumnos;

    int totalInscripciones = archivoInscripciones.cantRegistros();
    int totalAlumnos = archivoAlumnos.cantRegistros();

    if (totalInscripciones == 0)
    {
        std::cout << "No hay ninguna inscripción registrada en el sistema.\n";
        return;
    }

    Inscripcion* inscripciones = new Inscripcion[totalInscripciones];

    if (inscripciones == nullptr)
    {
        std::cout << "Error: No se pudo asignar memoria para las inscripciones.\n";
        return;
    }

    Alumno* alumnos = new Alumno[totalAlumnos];

    if (alumnos == nullptr)
    {
        std::cout << "Error: No se pudo asignar memoria para los alumnos.\n";
        return;
    }

    for(int i = 0; i < totalInscripciones; i++)
    {
        archivoInscripciones.leer(i, inscripciones[i]);
    }
    for(int i = 0; i < totalAlumnos; i++)
    {
        alumnos[i] = archivoAlumnos.leer(i);
    }

    Curso cursoSeleccionado = archivoCursos.leer(posCurso);
    std::cout << "\n--- Alumnos Inscriptos en: " << cursoSeleccionado.getNombre() << " ---\n";

    int alumnosEncontrados = 0;

    for (int i = 0; i < totalInscripciones; i++)
    {
        if (inscripciones[i].getIdCurso() == idCursoSeleccionado && inscripciones[i].getEstado() == true)
        {
            int legajoBuscado = inscripciones[i].getLegajoAlumno();
            for (int j = 0; j < totalAlumnos; j++)
            {
                if (alumnos[j].getLegajo() == legajoBuscado)
                {
                    std::cout << "----------------------------------\n";
                    std::cout << "Legajo: " << alumnos[j].getLegajo() << std::endl;
                    std::cout << "DNI: " << alumnos[j].getDni() << std::endl;
                    std::cout << "Nombre: " << alumnos[j].getNombre() << std::endl;
                    std::cout << "Apellido: " << alumnos[j].getApellido() << std::endl;

                    alumnosEncontrados++;
                    break;
                }
            }
        }
    }

    if (alumnosEncontrados == 0)
    {
        std::cout << "\nNo se encontraron alumnos inscriptos en este curso.\n";
    }
    std::cout << "----------------------------------\n";

    delete[] inscripciones;
    delete[] alumnos;
}

void ReportesManager::importeTotalRecaudadoPorAlumno()
{
    Utilidades utilidades;
    utilidades.limpiarPantallaConEncabezado("=== REPORTE - IMPORTE TOTAL POR ALUMNO ===");
    AlumnoArchivo archivoAlumnos;
    InscripcionArchivo archivoInscripciones;

    int totalAlumnos = archivoAlumnos.cantRegistros();
    int totalInscripciones = archivoInscripciones.cantRegistros();

    if (totalAlumnos == 0)
    {
        std::cout << "No hay alumnos registrados en el sistema.\n";
        return;
    }
    Alumno* alumnos = new Alumno[totalAlumnos];
    if (alumnos == nullptr)
    {
        std::cout << "Error: No se pudo asignar memoria para los alumnos.\n";
        return;
    }

    Inscripcion* inscripciones = new Inscripcion[totalInscripciones];
    if (inscripciones == nullptr)
    {
        std::cout << "Error: No se pudo asignar memoria para las inscripciones.\n";
        delete[] alumnos;
        return;
    }

    float* totalRecaudado = new float[totalAlumnos];
    if (totalRecaudado == nullptr)
    {
        std::cout << "Error: No se pudo asignar memoria para los cálculos.\n";
        delete[] alumnos;
        delete[] inscripciones;
        return;
    }

    for(int i = 0; i < totalAlumnos; i++)
    {
        alumnos[i] = archivoAlumnos.leer(i);
    }
    for(int i = 0; i < totalInscripciones; i++)
    {
        archivoInscripciones.leer(i, inscripciones[i]);
    }

    for (int i = 0; i < totalAlumnos; i++)
    {
        totalRecaudado[i] = 0.0f;
    }

    for (int i = 0; i < totalInscripciones; i++)
    {
        if (inscripciones[i].getEstado() == true)
        {
            int legajoDelInscripto = inscripciones[i].getLegajoAlumno();
            for (int j = 0; j < totalAlumnos; j++)
            {
                if (alumnos[j].getLegajo() == legajoDelInscripto)
                {
                    totalRecaudado[j] += inscripciones[i].getImporteAbonado();
                    break;
                }
            }
        }
    }

    int alumnosMostrados = 0;
    for (int i = 0; i < totalAlumnos; i++)
    {
        if (alumnos[i].getActivo() && totalRecaudado[i] > 0)
        {
            std::cout << "----------------------------------\n";
            std::cout << "Legajo: " << alumnos[i].getLegajo() << std::endl;
            std::cout << "DNI: " << alumnos[i].getDni() << std::endl;
            std::cout << "Nombre completo: " << alumnos[i].getNombre() << " " << alumnos[i].getApellido() << std::endl;
            std::cout << "Total Abonado: $" << totalRecaudado[i] << std::endl;
            alumnosMostrados++;
        }
    }

    if (alumnosMostrados == 0)
    {
        std::cout << "No se encontraron datos de recaudación para mostrar.\n";
    }
    std::cout << "----------------------------------\n";

    delete[] alumnos;
    delete[] inscripciones;
    delete[] totalRecaudado;
}

void ReportesManager::promedioImportePorCurso()
{
    std::cout << "Promedio de importe por curso" << std::endl;
}

void ReportesManager::inscripcionesEntreFechas()
{
    std::cout << "Inscripciones entre fechas" << std::endl;
}

void ReportesManager::cursosConAulaOcupada()
{
    CursoArchivo archivoCursos;
    ProfesorArchivo archivoProfesor;
    Utilidades utilidades;
    int totalCursos = archivoCursos.cantRegistros();

    if (totalCursos <= 0)
    {
        std::cout << "No hay cursos registrados en el sistema." << std::endl;
        return;
    }

    utilidades.limpiarPantallaConEncabezado("=== REPORTE - CURSOS POR AULA ===");

    Curso* cursos = new Curso[totalCursos];
    int* aulas = new int[totalCursos];
    int cantidadAulasUnicas = 0;

    for (int i = 0; i < totalCursos; i++)
    {
        cursos[i] = archivoCursos.leer(i);
    }

    // obtenemos las aulas unicas de los cursos
    for (int i = 0; i < totalCursos; i++)
    {
        bool aulaExiste = false;
        for (int j = 0; j < cantidadAulasUnicas; j++)
        {
            if (aulas[j] == cursos[i].getNumeroAula())
            {
                aulaExiste = true;
                break;
            }
        }
        if (!aulaExiste)
        {
            aulas[cantidadAulasUnicas] = cursos[i].getNumeroAula();
            cantidadAulasUnicas++;
        }
    }

    // las ordenamos para que se puedan ver mas facil
    for (int i = 0; i < cantidadAulasUnicas - 1; i++)
    {
        for (int j = 0; j < cantidadAulasUnicas - i - 1; j++)
        {
            if (aulas[j] > aulas[j + 1])
            {
                int temp = aulas[j];
                aulas[j] = aulas[j + 1];
                aulas[j + 1] = temp;
            }
        }
    }


    for (int i = 0; i < cantidadAulasUnicas; i++)
    {
        int aulaActual = aulas[i];
        int cursosEnAula = 0;

        for (int j = 0; j < totalCursos; j++)
        {
            if (cursos[j].getNumeroAula() == aulaActual)
            {
                cursosEnAula++;
            }
        }

        std::cout << "\n=== AULA " << aulaActual << " ===\n";
        std::cout << "Cantidad de cursos asignados: " << cursosEnAula << "\n";
        std::cout << "---------------------------\n";

        for (int j = 0; j < totalCursos; j++)
        {
            if (cursos[j].getNumeroAula() == aulaActual)
            {
                int posicionProfesor = archivoProfesor.buscar(cursos[j].getIdProfesor());
                Profesor profesor = archivoProfesor.leer(posicionProfesor);

                std::cout << "ID Curso: " << cursos[j].getId() << "\n";
                std::cout << "Nombre: " << cursos[j].getNombre() << "\n";
                std::cout << "Profesor: " << profesor.getNombre() << " " << profesor.getApellido() << "\n";
                std::cout << "Capacidad: " << cursos[j].getCantMaximaAlumnos() << " alumnos\n";
                std::cout << "---------------------------\n";
            }
        }
    }
    delete[] cursos;
    delete[] aulas;
}

void ReportesManager::profesoresConCursosAsignados()
{
    int cantRegCursos, cantRegProfesores, idProfesor, posicion;;
    int cantCursosActivos = 0;
    int indiceCursos = 0;
    std::string input;
    Curso _regCurso;
    Profesor _regProfesor;
    Curso *vecCursos;

///Cuento la cantidad de registros en el archivo cursos.dat y prefesores.dat

    cantRegCursos = _cursoArchivo.cantRegistros();
    cantRegProfesores = _profesorArchivo.cantRegistros();

/// Cursos
    if( cantRegCursos == 0 )
    {

        std::cout<<"No hay registros de cursos.\n";
        return;
    }

    if ( cantRegProfesores <= 0 ){

        std::cout<<"No hay registros de profesores activos.\n";
        return;
    }

///Filtro los activos

    for ( int i = 0; i< cantRegCursos; i++ )
    {

        _regCurso = _cursoArchivo.leer(i);

        if ( _regCurso.getEstado() == true )
        {

            cantCursosActivos ++;

        }

    }

    if( cantCursosActivos == 0 )
    {

        std::cout<<"No hay registros de cursos activos.\n";
        return;
    }

///Solicito memoria dinamica para el vector de Cursos activos

    vecCursos = new Curso [cantCursosActivos];

    if ( vecCursos == nullptr )
    {

        std::cout<<"No se pudo asignar memoria.\n";

        return;
    }

    ///Cargo el vector

    for (int i = 0; i < cantRegCursos; i++ )
    {

        _regCurso = _cursoArchivo.leer(i);

        if ( _regCurso.getEstado() == true )
        {

            vecCursos[indiceCursos] = _regCurso;

            indiceCursos ++;

        }

    }

    if ( cantRegProfesores <= 0 )
    {

        std::cout<<"No hay registros de profesores activos.\n";
        return;
    }


    ///Validacion del ingreso del ID profesor

    while(true)
    {

        system("cls");

        std::cout << "==================================================\n";
        std::cout << "     REPORTE DE PROFESORES CON CURSOS ASIGNADOS   \n";
        std::cout << "==================================================\n\n";
        std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
        std::cout<<"Ingrese el ID del profesor: \n";
        std::getline(std::cin,input);


        if (_utilidades.esComandoSalir(input)){
            system("cls");
            std::cout << "\nReporte cancelado.\n\n";
            return;

        }

        if (input.empty()){
            system("cls");
            std::cout << "Debe completar este campo. Intente nuevamente.\n\n";
            system("pause");
            return;
        }

        if ( !_utilidades.esEnteroValido(input) ){
            system("cls");
            std::cout << "\nDebe ingresar un número entero. Intente nuevamente.\n\n";
            system("pause");
            continue;
        }

        idProfesor = std::stoi(input);

        posicion = _profesorArchivo.buscar(idProfesor);

        if ( posicion < 0 )
        {

            system("cls");

            std::cout<<"\nEl ID ingresado no pertenece a un profesor registrado.\n\n";
            system("pause");
            continue;

        }

        _regProfesor = _profesorArchivo.leer(posicion);

        if ( !_regProfesor.getEstado() )
        {

            system("cls");

            std::cout<<"\nEl ID ingresado no pertenece a un profesor activo.\n\n";

            system("pause");
            continue;

        }

        break;

    }

    system("cls");

    std::cout << "==================================================\n";
    std::cout << "     REPORTE DE PROFESORES CON CURSOS ASIGNADOS   \n";
    std::cout << "==================================================\n\n";


    std::cout<<"\nProfesor: " << _regProfesor.getApellido()<<", "<<_regProfesor.getNombre()<<".\n";
    std::cout<<"DNI: "<<_regProfesor.getDni()<<".\n";
    std::cout<<"ID: "<<_regProfesor.getId()<<".\n";

    bool tieneCursos = false;

    for ( int c = 0; c < cantCursosActivos ; c++ )
    {

        if ( vecCursos[c].getIdProfesor() == _regProfesor.getId() )
        {

            std::cout<<"\n-Curso: " << vecCursos[c].getNombre()<<".\n";
            std::cout<<"-ID curso: " << vecCursos[c].getId()<<".\n";
            std::cout<<"-Aula: " << vecCursos[c].getNumeroAula()<<".\n";

            tieneCursos = true;
        }


    }

    if ( !tieneCursos)
    {

        std::cout<<"\nNo posee cursos asignados.\n\n";

    }


    delete [] vecCursos;


}


bool ReportesManager::pedirAnioValido(int& anio)
{
    std::string input;
    int anioActual = Fecha::fechaActual().getAnio();

    while (true)
    {
        std::cout << "Ingrese el año para filtrar inscripciones (0 = año actual, 'salir' para cancelar): ";
        std::getline(std::cin, input);

        if (_utilidades.esComandoSalir(input))
            return false;

        if (!_utilidades.esEnteroValido(input))
        {
            std::cout << "Entrada inválida. Intente nuevamente.\n\n";
            continue;
        }

        anio = std::stoi(input);

        if (anio == 0)
        {
            anio = anioActual;
            return true;
        }

        if (anio < 0)
        {
            std::cout << "El año no puede ser negativo. Intente nuevamente.\n\n";
            continue;
        }

        if (anio > anioActual)
        {
            std::cout << "El año no puede ser mayor al actual (" << anioActual << "). Intente nuevamente.\n\n";
            continue;
        }

        return true;
    }
}


void ReportesManager::importeTotalRecaudadoPorCurso()
{
    _utilidades.limpiarPantallaConEncabezado("=== REPORTE - RECAUDACIÓN POR CURSO ===");

    int anioFiltro;
    if (!pedirAnioValido(anioFiltro))
    {
        std::cout << "\nReporte cancelado por el usuario.\n";
        return;
    }

    int totalCursos = _cursoArchivo.cantRegistros();
    if(totalCursos <= 0)
    {
        std::cout << "No hay cursos cargados.\n";
        return;
    }

    // pedimos memoria
    Curso* cursos = new Curso[totalCursos];
    for (int i = 0; i < totalCursos; i++)
    {
        cursos[i] = _cursoArchivo.leer(i);
    }

    int totalInscripciones = _inscripcionArchivo.cantRegistros();
    if (totalInscripciones <= 0)
    {
        std::cout << "No hay inscripciones cargadas.\n";
        delete[] cursos;
        return;
    }

    Inscripcion* inscripciones = new Inscripcion[totalInscripciones];
    for (int i = 0; i < totalInscripciones; i++)
    {
        _inscripcionArchivo.leer(i, inscripciones[i]);
    }

    // pedimos memoria para almacenar los datos del recaudo y cantidad inscriptos para cada curso
    float* totalRecaudado = new float[totalCursos];
    int* cantidadInscriptos = new int[totalCursos];
    for (int i = 0; i < totalCursos; i++)
    {
        totalRecaudado[i] = 0;
        cantidadInscriptos[i] = 0;
    }

    for (int i = 0; i < totalInscripciones; i++)
    {
        if (!inscripciones[i].getEstado()) continue;
        if (inscripciones[i].getFechaInscripcion().getAnio() != anioFiltro) continue;

        int idCurso = inscripciones[i].getIdCurso();
        for (int j = 0; j < totalCursos; j++)
        {
            if (cursos[j].getId() == idCurso && cursos[j].getEstado())
            {
                totalRecaudado[j] += inscripciones[i].getImporteAbonado();
                cantidadInscriptos[j]++;
                break;
            }
        }
    }

    std::cout << "\nRECAUDACIÓN POR CURSO EN EL AÑO " << anioFiltro << "\n";
    std::cout << "-------------------------------------------------------------------\n";
    std::cout << std::left << std::setw(10) << "ID"
              << std::setw(30) << "NOMBRE CURSO"
              << std::setw(15) << "IMPORTE"
              << "INSCRIPCIONES\n";
    std::cout << "-------------------------------------------------------------------\n";

    bool hayDatos = false;

    for (int i = 0; i < totalCursos; i++)
    {
        if (cursos[i].getEstado() && cantidadInscriptos[i] > 0)
        {
            hayDatos = true;
            // uso de setw para establecer mejor los anchos (recomendado por libro de Joyanes)
            std::cout << std::left << std::setw(10) << cursos[i].getId()
                      << std::setw(30) << cursos[i].getNombre()
                      << "$" << std::setw(14) << totalRecaudado[i]
                      << cantidadInscriptos[i] << "\n";
        }
    }

    if (!hayDatos)
    {
        std::cout << "No hay datos de inscripciones para ese año.\n";
    }

    std::cout << "-------------------------------------------------------------------\n";

    delete[] cursos;
    delete[] inscripciones;
    delete[] totalRecaudado;
    delete[] cantidadInscriptos;
}
