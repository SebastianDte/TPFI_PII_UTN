#include <iostream>
#include "Profesor.h"





Profesor::Profesor()
: Persona(){

    _id =0;

}


Profesor::Profesor(int id,const std::string& dni,const std::string& nombre,const std::string& apellido,const std::string& telefono,const std::string& email,const std::string& direccion,const Fecha& fechaNacimiento)
: Persona( dni, nombre, apellido, telefono, email, direccion, fechaNacimiento ){

    setId(id);

}

void Profesor::setId ( int id ){
    _id = id;
}

int Profesor::getId(){
    return _id;
}



void Profesor::mostrar(){

    std::cout<<"--------------\n";
    std::cout<<"ID: "<<_id<<"\n";
    std::cout<<"DNI: "<<getDni()<<"\n";
    std::cout<<"NOMBRE: "<<getNombre()<<"\n";
    std::cout<<"APELLIDO: "<<getApellido()<<"\n";
    std::cout<<"TELEFONO: "<<getTelefono()<<"\n";
    std::cout<<"EMAIL: "<<getEmail()<<"\n";
    std::cout<<"DIRECCION: "<<getDireccion()<<".\n";
    std::cout<<"FECHA NAC: "<<getFechaNacimiento().getDia()<<"/"<<getFechaNacimiento().getMes()<<"/"<<getFechaNacimiento().getAnio()<<"\n";
}



