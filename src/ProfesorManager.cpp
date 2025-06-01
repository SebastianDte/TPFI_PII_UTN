#include "ProfesorManager.h"
#include <iostream>
#include "Profesor.h"



void ProfesorManager::alta(){
    Profesor regProf;
    ProfesorArchivo archivoProf;

    int dia,mes,anio,id,cantidadRegistros;
    Fecha fechaNacimiento;
    std::string dni,nombre,apellido,telefono,email,direccion;

    std::cout<<"Ingrese el DNI: \n";
    std::cin>>dni;

    std::cout<<"Ingrese el nombre: \n";
    std::cin>>nombre;

    std::cout<<"Ingrese el apellido: \n";
    std::cin>>apellido;

    std::cout<<"Ingrese el telefono: \n";
    std::cin>>telefono;

    std::cout<<"Ingrese el email: \n";
    std::cin>>email;

    std::cout<<"Ingrese la direccion: \n";
    std::cin>>direccion;

   ///Fecha de nacimiento

    std::cout<<"Ingrese dia de nacimiento: \n ";
    std::cin>>dia;
    fechaNacimiento.setDia(dia);

    std::cout<<"Ingrese mes de nacimiento: \n ";
    std::cin>>mes;
    fechaNacimiento.setMes(mes);

    std::cout<<"Ingrese anio de nacimiento: \n ";
    std::cin>>anio;
    fechaNacimiento.setAnio(anio);

    fechaNacimiento = Fecha(dia,mes,anio);

    cantidadRegistros = archivoProf.cantRegistros();

    if ( cantidadRegistros < 0 ){

        id = 1;

        regProf = Profesor (id,dni,nombre,apellido,telefono,email,direccion,fechaNacimiento);

        if ( archivoProf.alta( regProf ) ){

            system("cls");

            std::cout<<"Se guardo el registro correctamente. \n ";
            regProf.mostrar();

            system("pause");

            return;


        }else{

            system("cls");

            std::cout<<"No se pudo guardar el registro correctamente. \n ";

            system("pause");

        }


    }else{

        id = archivoProf.generarID(cantidadRegistros);


        if ( id < 0 ){

            system("cls");

            std::cout<<"No se puede generar un nuevo registro de profesor. \n";

            system("pause");

            return;

        }

        regProf = Profesor (id,dni,nombre,apellido,telefono,email,direccion,fechaNacimiento);


        if ( archivoProf.alta( regProf ) ){

            system("cls");

            std::cout<<"Se guardo el registro correctamente. \n ";
            regProf.mostrar();

        }else{
            system("cls");
            std::cout<<"No se pudo guardar el registro correctamente. \n ";

        }


    }


}

void ProfesorManager::listar(){
    Profesor regProf;
    ProfesorArchivo archivoProf;
    int cantRegistros;

    cantRegistros = archivoProf.cantRegistros();


    for ( int i=0; i<cantRegistros;i++ ){

        regProf = archivoProf.leer(i);

        regProf.mostrar();



    }


}

void ProfesorManager::buscar(){
    Profesor regProf;
    ProfesorArchivo archivoProf;
    int id, posicion;

    std::cout<<"Ingrese el ID del profesor que desea buscar: \n";
    std::cin>> id;

    posicion = archivoProf.buscar(id);

    if ( posicion < 0 ){

        system("cls");

        std::cout<<"El ID del profesor ingresado no existe. \n";

        return;

    }

    regProf = archivoProf.leer(posicion);

    regProf.mostrar();

}

void ProfesorManager::modificar(){
    Profesor regProf;
    ProfesorArchivo archivoProf;
    Fecha fechaNac;
    int id, posicion, opcion,diaN,mesN,anioN;
    std::string dni,nombre,apellido,telefono,email,direccion;

    std::cout<<"Ingrese el ID del profesor que desea modificar: \n";
    std::cin>> id;

    posicion = archivoProf.buscar(id);


    if ( posicion < 0 ){

        system("cls");

        std::cout<<"El ID ingresado no pertenece a un profesor registrado.\n";

        return;

    }

    if ( posicion < 0 ){

        system("pause");

        return;

    }


    regProf = archivoProf.leer(posicion);

    system("cls");

    regProf.mostrar();

    system("pause");

    do{

        system("cls");

        std::cout<<"Ingrese el atributo que desea modificar: \n";
        std::cout << "1) DNI.\n";
        std::cout << "2) Nombre.\n";
        std::cout << "3) Apellido.\n";
        std::cout << "4) Telefono.\n";
        std::cout << "5) Email.\n";
        std::cout << "6) Direccion.\n";
        std::cout << "7) Fecha de Nacimiento.\n";
        std::cout << "0) Salir al menu profesor.\n";
        std::cout << "Ingrese una opcion.\n";
        std::cin >> opcion;

        switch(opcion){

        case 1:
            system("cls");

            std::cout << "Ingrese el nuevo DNI.\n";
            std::cin>> dni;
            regProf.setDni(dni);

            if ( archivoProf.alta(regProf,posicion) ){

                system("cls");

                std::cout<<"El registro se modifico correctamente. \n";

                system("pause");

            }else{

                system("cls");

                std::cout<<"No se pudo modificar el registro. \n";

                system("pause");

                return;

            }

            break;

        case 2:

            system("cls");

            std::cout << "Ingrese el nuevo nombre.\n";
            std::cin>> nombre;
            regProf.setNombre(nombre);

            if ( archivoProf.alta(regProf,posicion) ){

                system("cls");

                std::cout<<"El registro se modifico correctamente. \n";

                system("pause");

            }else{

                system("cls");

                std::cout<<"No se pudo modificar el registro. \n";

                system("pause");

                return;

            }

            break;

        case 3:

            system("cls");

            std::cout << "Ingrese el nuevo apellido.\n";
            std::cin>> apellido;
            regProf.setApellido(apellido);

            if ( archivoProf.alta(regProf,posicion) ){

                system("cls");

                std::cout<<"El registro se modifico correctamente. \n";

                system("pause");

            }else{

                system("cls");

                std::cout<<"No se pudo modificar el registro. \n";

                system("pause");

                return;

            }

            break;

        case 4:

            system("cls");

            std::cout << "Ingrese el nuevo numero de telefono.\n";
            std::cin>> telefono;
            regProf.setTelefono(telefono);


            if ( archivoProf.alta(regProf,posicion) ){

                system("cls");

                std::cout<<"El registro se modifico correctamente. \n";

                system("pause");

            }else{

                system("cls");

                std::cout<<"No se pudo modificar el registro. \n";

                system("pause");

                return;

            }

            break;

        case 5:

            system("cls");

            std::cout << "Ingrese el nuevo email.\n";
            std::cin>> email;
            regProf.setNombre(email);


            if ( archivoProf.alta(regProf,posicion) ){

                system("cls");

                std::cout<<"El registro se modifico correctamente. \n";

                system("pause");

            }else{

                system("cls");

                std::cout<<"No se pudo modificar el registro. \n";

                system("pause");

                return;

            }

            break;


        case 6:

            system("cls");

            std::cout << "Ingrese la nueva direccion.\n";
            std::cin>> direccion;
            regProf.setDireccion(direccion);


            if ( archivoProf.alta(regProf,posicion) ){

                system("cls");

                std::cout<<"El registro se modifico correctamente. \n";

                system("pause");

            }else{

                system("cls");

                std::cout<<"No se pudo modificar el registro. \n";

                system("pause");

                return;

            }

            break;

        case 7:

            system("cls");

            std::cout << "Ingrese dia de nacimiento.\n";
            std::cin>> diaN;
            std::cout << "Ingrese mes de nacimiento.\n";
            std::cin>> mesN;
            std::cout << "Ingrese año de nacimiento.\n";
            std::cin>> anioN;

            fechaNac = Fecha(diaN,mesN,anioN);

            regProf.setFechaNacimiento( fechaNac);

            if ( archivoProf.alta(regProf,posicion) ){

                system("cls");

                std::cout<<"El registro se modifico correctamente. \n";

                system("pause");

            }else{

                system("cls");

                std::cout<<"No se pudo modificar el registro. \n";

                system("pause");

                return;

            }

            break;


        case 0:

            return;

        default:

            system("cls");

            std::cout<<"La opcion ingresada es incorrecta, intente nuevamente.\n";

            system("pause");

            break;


        }


    }while( opcion !=0 );




}

   // void baja();
