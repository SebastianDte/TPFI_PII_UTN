#include "ProfesorManager.h"
#include <iostream>
#include "Profesor.h"
#include "string"
#include <regex>

///Validaciones
bool ProfesorManager::dniValidacion(const std::string& input){
    const int minimoDNI =7;
    const int tamanioDNI = 8;


    if (input.empty()){
        std::cout << "Debe completar este campo. Intente nuevamente.\n\n";

        system("pause");

        return false;

    }



    if ( _utilidades.soloNumeros(input) == false ){

       std::cout << "Debe completar este campo con valores numericos. Intente nuevamente.\n\n";

       system("pause");

       return false;

    }



    if ( (input.length() < minimoDNI || input.length() > tamanioDNI ) && _utilidades.soloNumeros(input)== true ){

        std::cout << "La cantidad de valores ingresados no corresponen a un DNI. Intente nuevamente.\n\n";

        system("pause");

        return false;

    }

    return true;
}


bool ProfesorManager::nombreValidacion(const std::string& input){
    const int minimoNombre = 2;
    std::string nombreMin = _utilidades.aMinusculas(input);///Lo paso a minuscula para validar con soloLotras()


    if ( nombreMin.empty() ){


        std::cout << "Debe completar este campo. Intente nuevamente.\n\n";

        system("pause");

        return false;


    }

    if ( _utilidades.soloLetras(nombreMin) == false){

        std::cout << "Debe completar este campo sin simbolos, numeros ni espacios inecesarios. Intente nuevamente.\n\n";

        system("pause");

        return false;

    }

    if ( (nombreMin.length() < minimoNombre) && (_utilidades.soloLetras(nombreMin) == true) ){

        std::cout << "Debe ingresar un nombre que contenga al menos 2 letras. Intente nuevamente.\n\n";

        system("pause");

        return false;

    }

    return true;

}


bool ProfesorManager::apellidoValidacion(const std::string& input){
    const int minimoApellido = 2;
    std::string apellidoMin = _utilidades.aMinusculas(input);///Lo paso a minuscula para validar con soloLotras()


    if ( apellidoMin.empty() ){


        std::cout << "Debe completar este campo. Intente nuevamente.\n\n";

        system("pause");

        return false;


    }

    if ( _utilidades.soloLetras(apellidoMin) == false){

        std::cout << "Debe completar este campo sin simbolos, numeros ni espacios inecesarios. Intente nuevamente.\n\n";

        system("pause");

        return false;

    }

    if ( (apellidoMin.length() < minimoApellido) && (_utilidades.soloLetras(apellidoMin)== true) ){

        std::cout << "Debe ingresar un nombre que contenga al menos 2 letras. Intente nuevamente.\n\n";

        system("pause");

        return false;

    }

    return true;


}

bool ProfesorManager::telefonoValidacion(const std::string& input){

    const int tamanioTEL = 20;
    const int minimoTEL = 8;


    if (input.empty()){
        std::cout << "Debe completar este campo. Intente nuevamente.\n\n";

        system("pause");

        return false;

    }



    if ( _utilidades.soloNumeros(input) == false ){

       std::cout << "Debe completar este campo con valores numericos. Intente nuevamente.\n\n";

       system("pause");

       return false;

    }



    if ( (input.length() < minimoTEL || input.length() > tamanioTEL ) && _utilidades.soloNumeros(input)== true ){

        std::cout << "La cantidad de valores ingresados no corresponen a un numero telefonico. Intente nuevamente.\n\n";

        system("pause");

        return false;

    }

    return true;


}


bool ProfesorManager::emailValidacion(const std::string& input ) {
    const int maximoEmail = 50;
    const int minimoEmail = 5;
    int tamanioEmail = input.length();
    int contArroba = 0;  ///Contenga al menos un punto y solamente 1 arroba
    int contPuntos = 0;

    if ( tamanioEmail < minimoEmail || tamanioEmail >maximoEmail ){

        std::cout << "La cantidad de valores ingresados no corresponen a un email. Intente nuevamente.\n\n";

        system("pause");

        return false;

    }

    for (int i=0; i < tamanioEmail; i++ ){

        if ( input [i] == '@' ){

           contArroba ++;

        }

        if ( input [i] == '.' ){

            contPuntos ++;

        }

    }

    if ( contArroba != 1 || contPuntos == 0 ){

        std::cout << "Los valores ingresados no corresponen al formato de un email. Intente nuevamente.\n\n";

        system("pause");

        return false;

    }

   return true;

}

bool ProfesorManager::direccionValidacion(const std::string& input){
    const int maximoDire = 50;
    const int minimoDire = 3;
    std::regex patronDireccion(R"(^[A-Za-zÁÉÍÓÚáéíóúÑñüÜ.\s]+[ ]\d{1,5}$)");/// Patron de una direccion estandard de la bibliteca regex

    int tamanioCadena = input.length();

    if ( tamanioCadena < minimoDire || tamanioCadena >maximoDire ){

        std::cout << "La cantidad de valores ingresados no corresponen a una direccion valida. Intente nuevamente.\n\n";

        system("pause");

        return false;

    }



    if (std::regex_match(input, patronDireccion)) {
        return true;
    } else {
        std::cout << "Dirección inválida. Use el formato: 'Calle Nombre 123'.\n";

        system("pause");

        return false;
    }

    return true;
}


/// ABML

void ProfesorManager::alta(){

    int id,dia,mes,anio,cantidadRegistros;
    Fecha fechaNacimiento;
    std::string input;

    std::cin.ignore();

    while(true){

        system("cls");

        std::cout << "=========================================\n";
        std::cout << "         === ALTA DE PROFESOR ===       \n";
        std::cout << "=========================================\n";

        std::cout<<"Ingrese DNI: \n";
        std::getline(std::cin,input);

        if (_utilidades.esComandoSalir(input)){

            return;

        }

        if( dniValidacion(input)) {

            _profesor.setDni(input);
            std::cout<<"Presione cualquier tecla para continuar... \n";
            break;


        }

    }

    std::cin.ignore();

    while(true){


        system("cls");

        std::cout << "=========================================\n";
        std::cout << "         === ALTA DE PROFESOR ===       \n";
        std::cout << "=========================================\n";

        std::cout<<"Ingrese su nombre: \n";
        std::getline(std::cin,input);


        if (_utilidades.esComandoSalir(input)){

            return;

        }

        if( nombreValidacion(input)) {

            _profesor.setNombre(input);
            std::cout<<"Presione cualquier tecla para continuar... \n";
            break;

        }

    }


    std::cin.ignore();

    while(true){


        system("cls");

        std::cout << "=========================================\n";
        std::cout << "         === ALTA DE PROFESOR ===       \n";
        std::cout << "=========================================\n";

        std::cout<<"Ingrese su apellido: \n";
        std::getline(std::cin,input);


        if (_utilidades.esComandoSalir(input)){

            return;

        }

        if( nombreValidacion(input)) {

            _profesor.setApellido(input);
            std::cout<<"Presione cualquier tecla para continuar... \n";
            break;

        }

    }


    std::cin.ignore();


    while(true){

        system("cls");

        std::cout << "=========================================\n";
        std::cout << "         === ALTA DE PROFESOR ===       \n";
        std::cout << "=========================================\n";

        std::cout<<"Ingrese su numero telefonico: \n";
        std::getline(std::cin,input);

        if (_utilidades.esComandoSalir(input)){

            return;

        }

        if( telefonoValidacion(input) ) {

            _profesor.setTelefono(input);
            std::cout<<"Presione cualquier tecla para continuar... \n";
            break;


        }

    }

    std::cin.ignore();


    while(true){

        system("cls");

        std::cout << "=========================================\n";
        std::cout << "         === ALTA DE PROFESOR ===       \n";
        std::cout << "=========================================\n";

        std::cout<<"Ingrese su email: \n";
        std::getline(std::cin,input);

        if (_utilidades.esComandoSalir(input)){

            return;

        }

        if( emailValidacion(input) ) {

            _profesor.setEmail(input);
            std::cout<<"Presione cualquier tecla para continuar... \n";
            break;


        }

    }

    std::cin.ignore();


    while(true){

        system("cls");

        std::cout << "=========================================\n";
        std::cout << "         === ALTA DE PROFESOR ===       \n";
        std::cout << "=========================================\n";

        std::cout<<"Ingrese su domicilio(calle y numero): \n";
        std::getline(std::cin,input);

        if (_utilidades.esComandoSalir(input)){

            return;

        }

        if( direccionValidacion(input) ) {

            _profesor.setDireccion(input);
            std::cout<<"Presione cualquier tecla para continuar... \n";
            break;


        }

    }

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



    cantidadRegistros = _archivo.cantRegistros();

    if ( cantidadRegistros < 0 ){

        id = 1;

        _profesor.setId(id);

        if ( _archivo.alta( _profesor ) ){

            system("cls");

            std::cout<<"Se guardo el registro correctamente. \n ";
            _profesor.mostrar();

            std::cin.get();

            return;


        }else{

            system("cls");

            std::cout<<"No se pudo guardar el registro correctamente. \n ";

            std::cin.get();

            return;

        }


    }else{

        id = _archivo.generarID(cantidadRegistros);


        if ( id < 0 ){

            system("cls");

            std::cout<<"No se puede generar un nuevo registro de profesor. \n";

            std::cin.get();

            return;

        }

        _profesor.setId(id);


        if ( _archivo.alta( _profesor ) ){

            system("cls");

            std::cout<<"Se guardo el registro correctamente. \n ";
            _profesor.mostrar();

        }else{
            system("cls");
            std::cout<<"No se pudo guardar el registro correctamente. \n ";
            std::cin.get();

            return;
        }


    }


}


void ProfesorManager::listar(){

    int cantRegistros;

    cantRegistros = _archivo.cantRegistros();

    if(cantRegistros < 0){

        std::cout << "No hay profesores registrados.\n";

        return;

    }

    std::cout << "=========================================\n";
    std::cout << "         === LISTADO DE PROFESORES ===   \n";
    std::cout << "=========================================\n";

    for ( int i=0; i<cantRegistros;i++ ){

        _profesor = _archivo.leer(i);

        _profesor.mostrar();



    }


}

void ProfesorManager::buscar(){

    int id, posicion;

    std::cout << "========================================== \n";
    std::cout << "         === BÚSQUEDA DE PROFESOR ===      \n";
    std::cout << "==========================================\n";

    std::cout<<"Ingrese el ID del profesor que desea buscar: \n";
    std::cin>> id;

    posicion = _archivo.buscar(id);

    if ( posicion < 0 ){

        system("cls");

        std::cout<<"El ID del profesor ingresado no existe. \n";

        return;

    }

    _profesor = _archivo.leer(posicion);

    _profesor.mostrar();

}

void ProfesorManager::modificar(){

    Fecha fechaNac;
    int id, posicion, opcion,diaN,mesN,anioN;
    std::string input;

    std::cout << "=========================================\n";
    std::cout << "         === MODIFICAR PROFESOR ===        \n";
    std::cout << "=========================================\n";

    std::cout<<"\nIngrese el ID del profesor que desea modificar: \n";
    std::cin>> id;

    posicion = _archivo.buscar(id);


    if ( posicion < 0 ){

        system("cls");

        std::cout<<"El ID ingresado no pertenece a un profesor registrado.\n";

        return;

    }



    _profesor = _archivo.leer(posicion);

    system("cls");

    std::cout<<"\nEl profesor que desea modificar es: \n";

    _profesor.mostrar();

    system("pause");

    do{

        system("cls");

        std::cout << "=========================================\n";
        std::cout << "         === MODIFICAR PROFESOR ===        \n";
        std::cout << "=========================================\n";

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
            std::cin.ignore();

            while(true){

                system("cls");

                std::cout << "=========================================\n";
                std::cout << "         === MODIFICAR PROFESOR ===        \n";
                std::cout << "=========================================\n";

                std::cout<<"Ingrese el nuevo DNI: \n";
                std::getline(std::cin,input);

                if (_utilidades.esComandoSalir(input)){

                    return;

                }

                if( dniValidacion(input)) {

                    _profesor.setDni(input);
                    std::cout<<"Presione cualquier tecla para continuar... \n";
                    break;


                }

            }

            if ( _archivo.alta(_profesor,posicion) ){

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
           std::cin.ignore();

            while(true){


                system("cls");
                std::cout << "=========================================\n";
                std::cout << "         === MODIFICAR PROFESOR ===        \n";
                std::cout << "=========================================\n";

                std::cout<<"Ingrese el nuevo nombre: \n";
                std::getline(std::cin,input);


                if (_utilidades.esComandoSalir(input)){

                    return;

                }

                if( nombreValidacion(input)) {

                    _profesor.setNombre(input);
                    std::cout<<"Presione cualquier tecla para continuar... \n";
                    break;

                }

            }

            if ( _archivo.alta(_profesor,posicion) ){

                system("cls");

                std::cout<<"El registro se modifico correctamente. \n";

                std::cin.get();

            }else{

                system("cls");

                std::cout<<"No se pudo modificar el registro. \n";

                std::cin.get();

                return;

            }

            break;

        case 3:

            std::cin.ignore();

            while(true){

                system("cls");

                std::cout << "=========================================\n";
                std::cout << "         === MODIFICAR PROFESOR ===        \n";
                std::cout << "=========================================\n";

                std::cout<<"Ingrese el nuevo apellido: \n";
                std::getline(std::cin,input);

                if (_utilidades.esComandoSalir(input)){

                    return;

                }

                if( apellidoValidacion(input)) {

                    _profesor.setApellido(input);
                    std::cout<<"Presione cualquier tecla para continuar... \n";
                    break;


                }

            }

            if ( _archivo.alta(_profesor,posicion) ){

                system("cls");

                std::cout<<"El registro se modifico correctamente. \n";

                std::cin.get();

            }else{

                system("cls");

                std::cout<<"No se pudo modificar el registro. \n";

                std::cin.get();

                return;

            }

            break;

        case 4:

            std::cin.ignore();

            while(true){


                system("cls");
                std::cout << "=========================================\n";
                std::cout << "         === MODIFICAR PROFESOR ===        \n";
                std::cout << "=========================================\n";

                std::cout<<"Ingrese el nuevo numero de telefono: \n";
                std::getline(std::cin,input);


                if (_utilidades.esComandoSalir(input)){

                    return;

                }

                if( telefonoValidacion(input)) {

                    _profesor.setTelefono(input);
                    std::cout<<"Presione cualquier tecla para continuar... \n";
                    break;

                }

            }

            if ( _archivo.alta(_profesor,posicion) ){

                system("cls");

                std::cout<<"El registro se modifico correctamente. \n";

                std::cin.get();

            }else{

                system("cls");

                std::cout<<"No se pudo modificar el registro. \n";

                std::cin.get();

                return;

            }

            break;

        case 5:

            std::cin.ignore();

            while(true){


                system("cls");
                std::cout << "=========================================\n";
                std::cout << "         === MODIFICAR PROFESOR ===        \n";
                std::cout << "=========================================\n";

                std::cout<<"Ingrese el nuevo email: \n";
                std::getline(std::cin,input);


                if (_utilidades.esComandoSalir(input)){

                    return;

                }

                if( emailValidacion(input)) {

                    _profesor.setEmail(input);
                    std::cout<<"Presione cualquier tecla para continuar... \n";
                    break;

                }

            }

            if ( _archivo.alta(_profesor,posicion) ){

                system("cls");

                std::cout<<"El registro se modifico correctamente. \n";

                std::cin.get();

            }else{

                system("cls");

                std::cout<<"No se pudo modificar el registro. \n";

                std::cin.get();

                return;

            }

            break;


        case 6:

            std::cin.ignore();

            while(true){


                system("cls");
                std::cout << "=========================================\n";
                std::cout << "         === MODIFICAR PROFESOR ===        \n";
                std::cout << "=========================================\n";

                std::cout<<"Ingrese la nueva direccion: \n";
                std::getline(std::cin,input);


                if (_utilidades.esComandoSalir(input)){

                    return;

                }

                if( direccionValidacion(input)) {

                    _profesor.setDireccion(input);
                    std::cout<<"Presione cualquier tecla para continuar... \n";
                    break;

                }

            }

            if ( _archivo.alta(_profesor,posicion) ){

                system("cls");

                std::cout<<"El registro se modifico correctamente. \n";

                std::cin.get();

            }else{

                system("cls");

                std::cout<<"No se pudo modificar el registro. \n";

                std::cin.get();

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

            _profesor.setFechaNacimiento( fechaNac);

            if ( _archivo.alta(_profesor,posicion) ){

                system("cls");

                std::cout<<"El registro se modifico correctamente. \n";

                std::cin.get();

            }else{

                system("cls");

                std::cout<<"No se pudo modificar el registro. \n";

                std::cin.get();

                return;

            }

            break;

        case 0:

            return;

        default:

            system("cls");

            std::cout<<"La opcion ingresada es incorrecta, intente nuevamente.\n";

            std::cin.get();

            break;


        }


    }while( opcion !=0 );

}



