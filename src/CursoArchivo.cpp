#include <cstring>
#include "CursoArchivo.h"
#include "Curso.h"

using namespace std;

CursoArchivo::CursoArchivo(const char *n)
{
    strcpy(_nombreArchivo, n);
    _tamanioRegistro = sizeof(Curso);
}

bool CursoArchivo::alta(Curso regCurso)
{
    FILE* pCurso;
    pCurso = fopen(_nombreArchivo, "ab");
    if (pCurso == nullptr)
    {
        return false;
    }

    int escribio = fwrite(&regCurso, _tamanioRegistro, 1, pCurso);
    fclose(pCurso);
    return escribio;
}

int CursoArchivo::buscar(int idCurso)
{
    FILE* pCurso;
    Curso cursoEncontrado;
}

bool CursoArchivo::modificar(Curso regCurso, int posicion)
{

}

Curso CursoArchivo::leer(int posicion)
{

}

int CursoArchivo::cantRegistros()
{

}
