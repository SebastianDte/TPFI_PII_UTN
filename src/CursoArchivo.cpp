#include <cstring>
#include <iostream>
#include "CursoArchivo.h"
#include "Curso.h"

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

    size_t escribio = fwrite(&regCurso, _tamanioRegistro, 1, pCurso) == 1;
    fclose(pCurso);
    return escribio == 1;
}

int CursoArchivo::buscar(int idCurso) const
{
    FILE* pCurso = fopen(_nombreArchivo, "rb");
    if(pCurso == nullptr) return -1;

    Curso cursoEncontrado;
    int posicion = 0;

    while(fread(&cursoEncontrado, _tamanioRegistro, 1, pCurso) == 1)
    {
        if(cursoEncontrado.getEstado() == true && cursoEncontrado.getId() == idCurso)
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

    if (fseek(pCurso, posicion * _tamanioRegistro, SEEK_SET) != 0)
    {
        fclose(pCurso);
        return false;
    }

    size_t escritos = fwrite(&regCurso, _tamanioRegistro, 1, pCurso);
    fclose(pCurso);

    return escritos == 1;
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
