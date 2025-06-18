#include <cstring>
#include "AlumnoArchivo.h"
#include "Alumno.h"
#include "Persona.h"
using namespace std;
AlumnoArchivo::AlumnoArchivo(const char *n)
{
    strncpy(_nombreArchivo, n, sizeof(_nombreArchivo));
    _nombreArchivo[sizeof(_nombreArchivo) - 1] = '\0';
    _tamanioRegistro = sizeof(Alumno);
}

bool AlumnoArchivo::alta(const Alumno& regAlumno)
{
    FILE* pAlumno;
    pAlumno = fopen(_nombreArchivo, "ab");
    if (pAlumno == nullptr) return false;

    bool escribio = fwrite(&regAlumno, _tamanioRegistro, 1, pAlumno) == 1;
    fclose(pAlumno);
    return escribio;
}

int AlumnoArchivo::buscar(int legajo, bool filtrarActivos = true) const
{
    FILE* pArchivo = fopen(_nombreArchivo, "rb");
    if (pArchivo == nullptr)
        return -1;

    Alumno regAlumno;
    int posicion = 0;
    while (fread(&regAlumno, _tamanioRegistro, 1, pArchivo) == 1)
    {
        if (regAlumno.getLegajo() == legajo)
        {
            if (!filtrarActivos || regAlumno.getActivo())
            {
                fclose(pArchivo);
                return posicion;
            }
        }
        posicion++;
    }
    fclose(pArchivo);
    return -1;
}

bool AlumnoArchivo::modificar(const Alumno& regAlumno, int posicion)
{
    FILE* pArchivo = fopen(_nombreArchivo, "rb+");
    if (pArchivo == nullptr) return false;


    if (fseek(pArchivo, posicion * _tamanioRegistro, SEEK_SET) != 0)
    {
        fclose(pArchivo);
        return false;
    }

    // Sobrescribe el registro en la posición indicada
    bool resultado = (fwrite(&regAlumno, _tamanioRegistro, 1, pArchivo) == 1);

    fclose(pArchivo);
    return resultado;
}

Alumno AlumnoArchivo::leer(int posicion) const
{
    Alumno registro;
    registro.setLegajo(0);

    FILE* pAlumno = fopen(_nombreArchivo, "rb");
    if (pAlumno == nullptr) return registro;

    if(fseek(pAlumno, posicion * _tamanioRegistro, SEEK_SET) == 0)
    {
        fread(&registro, _tamanioRegistro, 1, pAlumno);
    }

    fclose(pAlumno);
    return registro;

}

int AlumnoArchivo::cantRegistros() const
{
    FILE* pAlumno = fopen(_nombreArchivo, "rb");

    if (pAlumno == nullptr) return 0;

    if(fseek(pAlumno, 0, SEEK_END) != 0)
    {
        fclose(pAlumno);
        return 0;
    }

    int cantidadBytes = ftell(pAlumno);
    if(cantidadBytes == -1)
    {
        fclose(pAlumno);
        return 0;
    }

    fclose(pAlumno);
    return cantidadBytes / _tamanioRegistro;
}

bool AlumnoArchivo::existeDNI(const std::string& dni) const
{
    int total = cantRegistros();
    for (int i = 0; i < total; i++)
    {
        Alumno alumno = leer(i);
        if (alumno.getDni() == dni)
        {
            return true; // Lo encontró, ya existe
        }
    }
    return false; // No lo encontró, está disponible
}
