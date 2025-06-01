#pragma once
#include <string>

class Fecha
{
private:
    int _dia;
    int _mes;
    int _anio;

    bool esFechaValida(int dia, int mes, int anio);
    int diasEnMes(int mes, int anio);
    void agregarDia();
    void restarDia();

public:
    Fecha();
    Fecha(int dia, int mes, int anio);

    int getDia();
    void setDia(int dia);
    int getMes();
    void setMes(int mes);
    int getAnio();
    void setAnio(int anio);

    bool esMayorQue(Fecha otraFecha);
    bool esIgualA(Fecha otraFecha);
    std::string toString();

};
