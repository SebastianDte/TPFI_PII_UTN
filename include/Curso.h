#pragma once
#include <string>

class Curso
{
private:
    int _id;
    char _nombre[50];
    int _cantMaximaAlumnos;
    int _numeroAula;
    int _idProfesor;
    bool _estado;

public:
    Curso();
    Curso(int id, const std::string& nombre, int cantMaximaAlumnos, int idProfesor, bool estado);

    void setId(int id);
    void setNombre(const std::string& nombre);
    void setCantMaximaAlumnos(int cantMaximaAlumnos);
    void setNumeroAula(int numeroAula);
    void setIdProfesor(int idProfesor);
    void setEstado(bool estado);

    int getId() const;
    std::string getNombre() const;
    int getCantMaximaAlumnos() const;
    int getNumeroAula() const;
    int getIdProfesor() const;
    bool getEstado() const;

    std::string toCSV() const;

    bool operator!=(const Curso& otro) const;
};
