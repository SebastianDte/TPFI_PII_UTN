#pragma once

#include <string>

class Curso
{
private:
    int _id;
    char _nombre[50];
    int _cantMaximaAlumnos;
    int _idProfesor;
    bool _estado;

public:
    Curso();
    Curso(int id, std::string nombre, int cantMaximaAlumnos, int idProfesor, bool estado);

    void setId(int id);
    void setNombre(std::string nombre);
    void setCantMaximaAlumnos(int cantMaximaAlumnos);
    void setIdProfesor(int idProfesor);
    void setEstado(bool estado);

    int getId();
    std::string getNombre();
    int getCantMaximaAlumnos();
    int getIdProfesor();
    bool getEstado();

    std::string toCSV();
};
