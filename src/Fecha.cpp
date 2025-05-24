#include <iostream>
#include "Fecha.h"
using namespace std;

bool esAnioBisiesto(int anio)
{
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}


Fecha::Fecha()
{
    _dia = 1;
    _mes = 1;
    _anio = 2023;
}

Fecha::Fecha(int dia, int mes, int anio)
{
    if(esFechaValida(dia, mes, anio))
    {
        _dia = dia;
        _mes = mes;
        _anio = anio;
    }
    else
    {
        // si la fecha no es valida agregamos el valor por defecto
        _dia = 1;
        _mes = 1;
        _anio = 2023;
    }
}

bool Fecha::esFechaValida(int dia, int mes, int anio)
{
    if (mes < 1 || mes > 12 || dia < 1 || anio < 1900 || anio > 2100)
    {
        return false;
    }
    if (dia > diasEnMes(mes, anio))
    {
        return false;
    }
    return true;
}

int Fecha::getDia()
{
    return _dia;
}

void Fecha::setDia(int dia)
{
    if (dia < 0 || dia > 31)
    {
        cout << "Dia invalido." << endl;
        _dia = 1;
        return;
    }
    _dia = dia;
}

int Fecha::getMes()
{
    return _mes;
}

void Fecha::setMes(int mes)
{
    if (mes < 0 || mes > 12)
    {
        cout << "Mes invalido." << endl;
        _mes = 1;
        return;
    }
    _mes = mes;
}

int Fecha::getAnio()
{
    return _anio;
}

void Fecha::setAnio(int anio)
{
    if (anio < 1900 || anio > 2100)
    {
        _anio = 2023;
        return;
    }
    _anio = anio;
}

int Fecha::diasEnMes(int mes, int anio)
{
    switch(mes)
    {
    case 2:
        return (esAnioBisiesto(anio)) ? 29 : 28;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    default:
        return 31;
    }
}

void Fecha::agregarDia()
{
    int diasDelMes = diasEnMes(_mes, _anio);
    // validar si es febrero y cuantos dias tiene el mes
    if (_mes == 2)
    {
        if(_dia == diasDelMes)  //fin de mes
        {
            // dia cambia a 1, mes se le suma 1, anio queda igual.
            _dia = 1;
            _mes += 1;
        }
        else     // no es fin de mes
        {
            _dia += 1;
        }
    }
    else if (_mes == 12)     // es diciembre
    {
        if (_dia == diasDelMes)  // fin de anio
        {
            _dia = 1;
            _mes = 1;
            _anio += 1;
        }
        else
        {
            _dia += 1;
        }
    }
    else if (_mes == 1 || _mes == 3 || _mes == 5 || _mes == 7 || _mes == 8 || _mes == 10)    // meses con 31 dias
    {
        if(_dia == 31)
        {
            _dia = 1;
            _mes +=1;
        }
        else
        {
            _dia += 1;
        }
    }
    else
    {
        // meses con 30 dias
        if(_dia == 30)
        {
            _dia = 1;
            _mes +=1;
        }
        else
        {
            _dia += 1;
        }
    }

}

void Fecha::restarDia()
{
    cout << "Restar dia" << endl;
    // estamos a 1 de enero
    if(_dia == 1 && _mes == 1)
    {
        _anio--;
        _mes = 12;
        _dia = diasEnMes(_mes, _anio);
    }
    else if (_dia == 1) // el dia es 1, pero el mes es distinto de enero
    {
        _mes--;
        _dia = diasEnMes(_mes, _anio);
    }
    else // cualquier otro dia del mes
    {
        _dia--;
    }
}


bool Fecha::esMayorQue(Fecha otraFecha)
{
    if (_anio > otraFecha.getAnio()) return true;
    if (_anio == otraFecha.getAnio())
    {
        if (_mes > otraFecha.getMes()) return true;
        if (_mes == otraFecha.getMes())
        {
            if (_dia > otraFecha.getDia()) return true;
        }
    }
    return false;
}


bool Fecha::esIgualA(Fecha otraFecha)
{
    return _dia == otraFecha.getDia() && _mes == otraFecha.getMes() && _anio == otraFecha.getAnio();
}

std::string Fecha::toString()
{
    return std::to_string(_dia)  + "/" + std::to_string(_mes) + "/" + std::to_string(_anio);
}
