#include <cstring>
#include <iostream>
#include "CursoArchivo.h"
#include "Curso.h"
#include "Inscripcion.h"
#include "InscripcionArchivo.h"

using namespace std;

CursoArchivo::CursoArchivo(const char *n)
{
    strncpy(_nombreArchivo, n, sizeof(_nombreArchivo));
    _nombreArchivo[sizeof(_nombreArchivo) - 1] = '\0';
    _tamanioRegistro = sizeof(Curso);
}

bool CursoArchivo::alta(const Curso& regCurso)
{
    FILE* pCurso;
    pCurso = fopen(_nombreArchivo, "ab");
    if (pCurso == nullptr) return false;

    bool ok = fwrite(&regCurso, _tamanioRegistro, 1, pCurso) == 1;
    fclose(pCurso);
    return ok;
}

int CursoArchivo::buscar(int idCurso) const
{
    FILE* pCurso = fopen(_nombreArchivo, "rb");
    if(pCurso == nullptr) return -1;

    Curso cursoEncontrado;
    int posicion = 0;

    while(fread(&cursoEncontrado, _tamanioRegistro, 1, pCurso) == 1)
    {
        if(cursoEncontrado.getId() == idCurso)
        {
            fclose(pCurso);
            return posicion;
        }
        posicion++;
    }

    fclose(pCurso);
    return -1;
}

bool CursoArchivo::modificar(const Curso& regCurso, int posicion)
{
    FILE* pCurso = fopen(_nombreArchivo, "rb+");
    if (pCurso == nullptr) return false;

    // validamos que el puntero del archivo pudo moverse a la posicion que queremos
    if (fseek(pCurso, posicion * _tamanioRegistro, SEEK_SET) != 0)
    {
        fclose(pCurso);
        return false;
    }

    size_t escritos = fwrite(&regCurso, _tamanioRegistro, 1, pCurso);
    fclose(pCurso);

    return escritos == 1;
}

bool CursoArchivo::tieneInscripcionesActivas(int idCurso) const {
    InscripcionArchivo archivoInscripcion = InscripcionArchivo();
    int cantidad = archivoInscripcion.cantRegistros();
    Inscripcion insc;

    if (cantidad <= 0) {
        return false;
    }

    for (int i = 0; i < cantidad; i++) {
        if (archivoInscripcion.leer(i, insc)) {
            if (insc.getEstado() && insc.getIdCurso() == idCurso) {
                return true;
            }
        }
    }
    return false;
}

bool CursoArchivo::baja(int idCurso)
{
    int posicion = buscar(idCurso);
    if (posicion == -1) return false;

    InscripcionArchivo archivoInscripcion = InscripcionArchivo();
    int cantRegistrosInscripciones = archivoInscripcion.cantRegistros();
    Inscripcion registroInscripcion;

    for (int i = 0; i < cantRegistrosInscripciones; i++){
        if(archivoInscripcion.leer(i, registroInscripcion)){
            if(registroInscripcion.getEstado() == true && registroInscripcion.getIdCurso() == idCurso){
                return false;
            }
        }
    }

    Curso registro = leer(posicion);
    registro.setEstado(false);
    return modificar(registro, posicion);
}

Curso CursoArchivo::leer(int posicion)
{
    Curso registro;
    registro.setId(0);

    FILE* pCurso = fopen(_nombreArchivo, "rb");
    if (pCurso == nullptr) return registro;

    if(fseek(pCurso, posicion*_tamanioRegistro, SEEK_SET) == 0)
    {
        fread(&registro, _tamanioRegistro, 1, pCurso);
    }

    fclose(pCurso);
    return registro;
}

int CursoArchivo::cantRegistros() const
{
    FILE* pCurso = fopen(_nombreArchivo, "rb");

    if (pCurso == nullptr) return 0;

    if(fseek(pCurso, 0, SEEK_END) != 0)
    {
        fclose(pCurso);
        return 0;
    }

    int cantidadBytes = ftell(pCurso);
    if(cantidadBytes == -1)
    {
        fclose(pCurso);
        return 0;
    }

    fclose(pCurso);
    return cantidadBytes / _tamanioRegistro;
}
