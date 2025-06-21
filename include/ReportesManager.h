#pragma once
#include "CursoArchivo.h"
#include "AlumnoArchivo.h"
#include "InscripcionArchivo.h"
#include "ProfesorArchivo.h"
#include "Utilidades.h"

class ReportesManager
{
    private:
        CursoArchivo _cursoArchivo;
        AlumnoArchivo _alumnoArchivo;
        InscripcionArchivo _inscripcionArchivo;
        ProfesorArchivo _profesorArchivo;
        Utilidades _utilidades;

    public:
        ReportesManager();
        void totalInscriptosPorCurso();
        void alumnosInscriptosEnCurso();
        void importeTotalRecaudadoPorCurso();
        void importeTotalRecaudadoPorAlumno();
        void promedioImportePorCurso();
        void inscripcionesEntreFechas();
        void cursosConAulaOcupada();
        void profesoresConCursosAsignados();
        bool pedirAnioValido(int& anio);
        bool pedirFecha(Fecha& fecha, const std::string& mensaje);
};
