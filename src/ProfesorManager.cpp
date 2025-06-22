#include "ProfesorManager.h"
#include <iostream>
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

    if (_archivo.existeDNI(input)){

        std::cout << "El DNI ingresado pertenece a otro profesor. Intente nuevamente.\n";

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

/// Expresión regular para nombres válidos (letras, espacios, tildes y control sobre las mayusculas)
    std::regex patronNombre(R"(^([A-ZÁÉÍÓÚÑÜ][a-záéíóúñü]+)(\s[A-ZÁÉÍÓÚÑÜ][a-záéíóúñü]+)*$)");


    if (input.empty()) {
        std::cout << "Debe completar este campo. Intente nuevamente.\n\n";
        system("pause");
        return false;
    }


    if (!std::regex_match(input, patronNombre)) {
        std::cout << "El nombre ingresado debe respetar la ubicacion correcta de las mayusculas, contener solo letras y/o espacios. Sin símbolos ni números.\n\n";
        system("pause");
        return false;
    }

    if (input.length() < minimoNombre) {
        std::cout << "Debe ingresar un nombre que contenga al menos " << minimoNombre << " letras.\n\n";
        system("pause");
        return false;
    }

    return true;

}


bool ProfesorManager::apellidoValidacion(const std::string& input){
    const int minimoNombre = 2;

/// Expresión regular para apellidos válidos (letras, espacios, tildes y control de las mayusculas)
    std::regex patronApellido(R"(^([A-ZÁÉÍÓÚÑÜ][a-záéíóúñü]+)(\s[A-ZÁÉÍÓÚÑÜ][a-záéíóúñü]+)*$)");


    if (input.empty()) {
        std::cout << "Debe completar este campo. Intente nuevamente.\n\n";
        system("pause");
        return false;
    }


    if (!std::regex_match(input, patronApellido)) {
        std::cout << "El apellido ingresado debe respetar la ubicacion correcta de las mayusculas, contener solo letras y/o espacios. Sin símbolos ni números.\n\n";
        system("pause");
        return false;
    }

    if (input.length() < minimoNombre) {
        std::cout << "Debe ingresar un nombre que contenga al menos " << minimoNombre << " letras.\n\n";
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



    if ( !_utilidades.soloNumeros(input) ){

       std::cout << "Debe completar este campo con valores numericos. Intente nuevamente.\n\n";

       system("pause");

       return false;

    }



    if ( (input.length() < minimoTEL || input.length() > tamanioTEL ) && _utilidades.soloNumeros(input) ){

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

    // R"(...)" es un "raw string literal", facilita escribir patrones sin escapar las barras \.
    const std::regex patronEmail(R"(([\w\.\-]+)@([\w\-]+)((\.(\w){2,3})+))");


    if (input.empty()){

        std::cout << "Debe completar este campo. Intente nuevamente.\n\n";
        system("pause");
        return false;

    }


    if ( tamanioEmail < minimoEmail || tamanioEmail >maximoEmail ){

        std::cout << "La cantidad de valores ingresados no corresponen a un email. Intente nuevamente.\n\n";

        system("pause");

        return false;

    }

    if (std::regex_match(input, patronEmail)){
        return true;
    }else{

        std::cout << "El formato del email no es válido. Intente nuevamente.\n";
        system("pause");
        return false;
    }


   return true;


}

bool ProfesorManager::direccionValidacion(const std::string& input){
    const int maximoDire = 50;
    const int minimoDire = 3;
    std::regex patronDireccion(R"(^[A-Za-z��������������.\s]+[ ]\d{1,5}$)");/// Patron de una direccion estandard de la bibliteca regex

    int tamanioCadena = input.length();

    if ( tamanioCadena < minimoDire || tamanioCadena >maximoDire ){

        std::cout << "La cantidad de valores ingresados no corresponen a una direccion valida. Intente nuevamente.\n\n";

        system("pause");

        return false;

    }



    if (std::regex_match(input, patronDireccion)) {
        return true;
    } else {
        std::cout << "Direcci�n inv�lida. Use el formato: 'Calle Nombre 123'.\n";

        system("pause");

        return false;
    }

    return true;
}

bool ProfesorManager::fechaValidacion(Fecha& fechaNac){

    std::string input;

    while (true)
    {
        system("cls");

        std::cout << "=========================================\n";
        std::cout << "         === ALTA DE PROFESOR ===       \n";
        std::cout << "=========================================\n";

        std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
        std::cout<<"Ingrese la fecha de nacimiento (DD/MM//AAAA): \n";
        std::getline(std::cin,input);

        if (_utilidades.esComandoSalir(input)){

            std::cout << "\nAlta de profesor cancelada.\n";
            return false;

        }

        if (input.empty()){

            std::cout << "Debe completar este campo. Intente nuevamente.\n\n";
            system("pause");
            continue;

        }

        Fecha fechaTemp; // Usamos un objeto temporal para la validación

        // 1. Validación de formato (DD/MM/AAAA)
        if (!fechaTemp.validarFechaStr(input))
        {
            std::cout << "Formato de fecha incorrecto. Intente nuevamente.\n";
            system("pause");
            continue;
        }

        // 2. Validación de que no sea una fecha futura
        Fecha fechaActual = Fecha::fechaActual();
        if (fechaTemp.esMayorQue(fechaActual))
        {
            std::cout << "La fecha ingresada es posterior a la actual. Intente nuevamente.\n";
            system("pause");
            continue;
        }

        // 3. Validación de edad lógica

        int edad = fechaActual.getAnio() - fechaTemp.getAnio();

        // Ajuste simple por si aún no cumplió años este año
        if (fechaActual.getMes() < fechaTemp.getMes() ||
           (fechaActual.getMes() == fechaTemp.getMes() && fechaActual.getDia() < fechaTemp.getDia())) {
            edad--;
        }

        if (edad < 14 || edad > 90)
        {
            std::cout << "La edad del profesor debe ser entre 14 y 90 años. Intente nuevamente.\n";
            system("pause");
            continue;
        }

        // Si todas las validaciones pasan
        fechaNac = fechaTemp; // Asignamos la fecha validada al parámetro de referencia
        return true;
    }

}




/// ABML

void ProfesorManager::alta(){

int id,cantidadRegistros;
    std::string input;


///DNI
    while(true){

        system("cls");

        std::cout << "=========================================\n";
        std::cout << "         === ALTA DE PROFESOR ===       \n";
        std::cout << "=========================================\n";

        std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
        std::cout<<"Ingrese el numero de DNI (sin puntos):\n";
        std::getline(std::cin,input);

        if (_utilidades.esComandoSalir(input)){

            std::cout << "\nAlta de profesor cancelada.\n";
            return;

        }

        if( !dniValidacion(input)) {

           continue;

        }else{

            _profesor.setDni(input);
            break;
        }

    }


///Nombre
    while(true){


        system("cls");

        std::cout << "=========================================\n";
        std::cout << "         === ALTA DE PROFESOR ===       \n";
        std::cout << "=========================================\n";

        std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
        std::cout<<"Ingrese su nombre: \n";
        std::getline(std::cin,input);


        if (_utilidades.esComandoSalir(input)){

            std::cout << "\nAlta de profesor cancelada.\n";
            return;

        }

        if( !nombreValidacion(input)) {

           continue;

        } else{

            _profesor.setNombre(input);
            break;

        }

    }


///Apellido
    while(true){


        system("cls");

        std::cout << "=========================================\n";
        std::cout << "         === ALTA DE PROFESOR ===       \n";
        std::cout << "=========================================\n";

        std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
        std::cout<<"Ingrese su apellido: \n";
        std::getline(std::cin,input);


        if (_utilidades.esComandoSalir(input)){

            std::cout << "\nAlta de profesor cancelada.\n";
            return;

        }

        if( !nombreValidacion(input)) {

            continue;

        }else{

            _profesor.setApellido(input);
            break;

        }

    }



///Telefono
    while(true){

        system("cls");

        std::cout << "=========================================\n";
        std::cout << "         === ALTA DE PROFESOR ===       \n";
        std::cout << "=========================================\n";

        std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
        std::cout<<"Ingrese su numero telefonico: \n";
        std::getline(std::cin,input);

        if (_utilidades.esComandoSalir(input)){

            std::cout << "\nAlta de profesor cancelada.\n";
            return;

        }

        if( !telefonoValidacion(input) ) {

            continue;

        }else{

            _profesor.setTelefono(input);
            break;

        }

    }


///Email
    while(true){

        system("cls");

        std::cout << "=========================================\n";
        std::cout << "         === ALTA DE PROFESOR ===       \n";
        std::cout << "=========================================\n";

        std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
        std::cout<<"Ingrese su email(usuario@ejemplo.com): \n";
        std::getline(std::cin,input);

        if (_utilidades.esComandoSalir(input)){

            std::cout << "\nAlta de profesor cancelada.\n";
            return;

        }

        if( !emailValidacion(input) ) {

            continue;


        }else{

            _profesor.setEmail(input);
            break;

        }

    }



///Direccion
    while(true){

        system("cls");

        std::cout << "=========================================\n";
        std::cout << "         === ALTA DE PROFESOR ===       \n";
        std::cout << "=========================================\n";

        std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
        std::cout<<"Ingrese su domicilio(calle y numero): \n";
        std::getline(std::cin,input);

        if (_utilidades.esComandoSalir(input)){

            std::cout << "\nAlta de profesor cancelada.\n";
            return;

        }

        if( !direccionValidacion(input) ) {

            continue;

        }else{

            _profesor.setDireccion(input);
            break;

        }

    }


///Fecha de nacimiento

    Fecha fechaNacimiento;

    if( !fechaValidacion(fechaNacimiento) ){
        return;
    }

///Carga de nuevo profesor al sistema
    _profesor.setFechaNacimiento(fechaNacimiento);

    cantidadRegistros = _archivo.cantRegistros();

    if ( cantidadRegistros < 0 ){

        id = 1;

        _profesor.setId(id);

        if ( _archivo.alta( _profesor ) ){

            system("cls");

            std::cout<<"Se guardo el registro correctamente. \n\n ";
            _profesor.mostrar();


            return;


        }else{

            system("cls");

            std::cout<<"No se pudo guardar el registro correctamente. \n\n ";

            return;

        }


    }else{

        id = _archivo.generarID(cantidadRegistros);


        if ( id < 0 ){

            system("cls");

            std::cout<<"No se puede generar un nuevo registro de profesor. \n";


            return;

        }

        _profesor.setId(id);


        if ( _archivo.alta( _profesor ) ){

            system("cls");

            std::cout<<"Se guardo el registro correctamente. \n ";
            _profesor.mostrar();
            return;

        }else{
            system("cls");
            std::cout<<"No se pudo guardar el registro correctamente. \n ";
            std::cin.get();

            return;
        }


    }

}

void ProfesorManager::listar(){

    std::string input;
    int opcion, cantRegistros;
    Utilidades _utilidades;

    cantRegistros = _archivo.cantRegistros();

    if(cantRegistros <= 0){

        std::cout << "No hay profesores registrados.\n";

        return;

    }

    while(true)
    {
        _utilidades.limpiarPantallaConEncabezado("=== SUBMEN� - LISTADO DE PROFESORES ===");
        std::cout << "1. Listar profesores activos\n";
        std::cout << "2. Listar profesores inactivos\n";
        std::cout << "3. Listar por apellido\n";
        std::cout << "0. Volver al men� anterior\n";
        std::cout << "=========================================\n";
        std::cout << "Seleccione una opci�n: ";
        std::getline(std::cin,input);

        if ( !_utilidades.esEnteroValido(input) ){

            std::cout << "\nEl valor ingresado es incorrecto, debe ser un numero entero.Intente nuevamente.\n\n";
            system("pause");
            continue;
        }

        opcion = std::stoi(input);

        switch(opcion)
        {
        case 1:
            system("cls");
            listarActivos();
            system("pause");
            break;
        case 2:
            system("cls");
            listarInactivos();
            system("pause");
            break;
        case 3:
            system("cls");
            listarPorApellido();
            system("pause");
            break;
        case 0:
            return;
        default:
            std::cout << "Opci�n no v�lida. Intente nuevamente.\n";
            system("pause");
            break;
        }
    }
}

void ProfesorManager::listarActivos(){

    int cantRegistrosActivos = 0;
    int cantRegistros;

    std::cout << "=========================================\n";
    std::cout << " === LISTADO DE PROFESORES ACTIVOS ===   \n";
    std::cout << "=========================================\n";

    cantRegistros = _archivo.cantRegistros();

    if(cantRegistros <= 0){

        std::cout << "No hay profesores registrados.\n";

        return;

    }

    for (int i = 0; i <cantRegistros; i++){

        _profesor = _archivo.leer(i);

        if ( _profesor.getEstado() ){

            cantRegistrosActivos ++;
        }

    }

    if ( cantRegistrosActivos == 0 ){

        std::cout << "\nNo hay profesores activos registrados.\n\n";

        return;

    }


    for ( int i=0; i<cantRegistros;i++ ){

        _profesor = _archivo.leer(i);

        if ( _profesor.getEstado() == true ) {

            _profesor.mostrar();

        }

    }

}

void ProfesorManager::listarInactivos(){

    int cantRegistrosInactivos = 0;
    int cantRegistros;

    std::cout << "=========================================\n";
    std::cout << " === LISTADO DE PROFESORES INACTIVOS ===   \n";
    std::cout << "=========================================\n";

    cantRegistros = _archivo.cantRegistros();

    if(cantRegistros <= 0){

        std::cout << "\nNo hay profesores registrados.\n\n";

        return;

    }

    for (int i = 0; i <cantRegistros; i++){

        _profesor = _archivo.leer(i);

        if ( !_profesor.getEstado() ){

            cantRegistrosInactivos ++;
        }

    }

    if ( cantRegistrosInactivos == 0 ){

        std::cout << "\nNo hay profesores inactivos registrados.\n\n";

        return;

    }


    for ( int i=0; i<cantRegistros;i++ ){

        _profesor = _archivo.leer(i);

        if ( !_profesor.getEstado() ) {

            _profesor.mostrar();

        }

    }


}

void ProfesorManager::listarPorApellido(){
    int cantRegistros,cantActivos = 0, indice = 0;
    std::string apellido1;
    std::string apellido2;

    ///Declaro el puntero que va a contener los registros de los profesores
    Profesor *vecProfesores;
    Profesor aux;

    cantRegistros = _archivo.cantRegistros();

    if(cantRegistros <= 0){

        std::cout << "No hay profesores registrados.\n";

        return;
    }


    ///El vector solo almacenara a los profesores activos

    for ( int i = 0; i < cantRegistros; i++ ){

        _profesor = _archivo.leer(i);

        if ( _profesor.getEstado()  ){

            cantActivos ++;

        }

    }




    if ( cantActivos == 0 ){

        std::cout<<"No hay registros de profesores activos.\n";
        return;

    }

    ///Inicializo el puntero

    vecProfesores = new Profesor [cantActivos];

    ///Verifico si se asigno memoria dinamica

    if ( vecProfesores == nullptr ){

        std::cout<<"No se asigno memoria\n";

        return;
    }

    ///Cargo el vector de prof activos,no va a haber desbordamiento gracias a la asignacion de memoria dinamica


    for (int i = 0; i < cantRegistros; i++){

        _profesor = _archivo.leer(i);

        if ( _profesor.getEstado()== true){

            vecProfesores[indice] = _profesor;
            indice ++;
        }

    }



   ///El ordenamiento utiliza la sobrecarga de operadores de la clase string que hace una comparacion usando el codigo ASCII

    for( int i = 0; i < cantActivos - 1; i++ ){

        for ( int j = 0; j < cantActivos -i -1; j++ ){


            apellido1 = _utilidades.aMinusculas(vecProfesores[j].getApellido());
            apellido2 = _utilidades.aMinusculas(vecProfesores[j+1].getApellido());
            if ( apellido1 > apellido2 ){

                aux = vecProfesores[j];
                vecProfesores[j] = vecProfesores[j+1];
                vecProfesores[j+1] = aux;

            }

        }
    }

    for ( int i = 0; i < cantActivos; i++ ){

        std::cout<<"Apellido: "<<vecProfesores[i].getApellido()<<"\n";
        std::cout<<"Nombre: "<<vecProfesores[i].getNombre()<<"\n";
        std::cout<<"DNI: "<<vecProfesores[i].getDni()<<"\n";
        std::cout<<"ID: "<<vecProfesores[i].getId()<<"\n";
        std::cout<<"--------------------\n";

    }


   delete [] vecProfesores;

   return;

}


void ProfesorManager::buscar(){

    int id, posicion, cantRegistros;
    std::string input;

    cantRegistros = _archivo.cantRegistros();

    if(cantRegistros <= 0){

        std::cout << "No hay profesores registrados.\n";

        return;
    }

    while(true){

        system("cls");

        std::cout << "========================================== \n";
        std::cout << "         === B�SQUEDA DE PROFESOR ===      \n";
        std::cout << "==========================================\n";

        std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
        std::cout<<"Ingrese el ID del profesor que desea buscar: \n";
        std::getline(std::cin,input);

        if (_utilidades.esComandoSalir(input)){
            system("cls");
            std::cout << "\nBusqueda de profesor cancelada.\n\n";
            return;

        }

        if (input.empty()){
            system("cls");
            std::cout << "Debe completar este campo. Intente nuevamente.\n\n";
            system("pause");

            continue;

        }


        if ( !_utilidades.esEnteroValido(input) ){
            system("cls");
            std::cout << "\nDebe ingresar un n�mero entero. Intente nuevamente.\n\n";
            system("pause");
            continue;
        }

        id = std::stoi(input);

        posicion = _archivo.buscar(id);

        if ( posicion < 0 ){

            system("cls");

            std::cout<<"\nEl ID ingresado no pertenece a un profesor registrado.\n\n";
            system("pause");
            continue;

        }

        _profesor = _archivo.leer(posicion);

        if ( !_profesor.getEstado() ){

            system("cls");

            std::cout<<"\nEl ID ingresado no pertenece a un profesor activo.\n\n";

            system("pause");
            continue;

        }

       break;

    }

    system("cls");

    _profesor.mostrar();

}

int ProfesorManager::contCursosProfesor(const int& idProfesor){
    Curso cursoProf;
    CursoArchivo archiCurso;
    int contCursos = 0;
    int cantCursos;

    cantCursos = archiCurso.cantRegistros() ;

    if(cantCursos <= 0){

        std::cout << "No hay profesores registrados.\n";

        return -1;
    }


    for ( int i = 0; i< cantCursos; i++ ){

        cursoProf = archiCurso.leer(i);

        if ( cursoProf.getEstado() && cursoProf.getIdProfesor() == idProfesor ){

            contCursos ++;

        }

    }

   return contCursos;

}

void ProfesorManager::bajaCursoProfesor(const int& idProfesor) {
    Curso cursoP;
    CursoArchivo archiCurso;
    int cantRegCursos, opcion, posicion;
    bool inscripActivas = false;
    std::string input;

    cantRegCursos = archiCurso.cantRegistros();

    while (true) {
        system("cls");
        std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
        std::cout << "\nProfesor: " << _profesor.getApellido() << ", " << _profesor.getNombre() << ".\n";
        std::cout << "DNI: " << _profesor.getDni() << ".\n";
        std::cout << "\nEl profesor que desea dar de baja, tiene asignado/s: " << contCursosProfesor(idProfesor) << " curso/s.\n";
        std::cout << "\nElija una opcion:\n";
        std::cout << "1) Dar de baja al profesor y sus cursos asignados.\n";
        std::cout << "2) Dar de baja al profesor y reasignar el/los curso/s a otro profesor.\n";
        std::getline(std::cin, input);

        if (_utilidades.esComandoSalir(input)) {
            std::cout << "\nBaja de profesor cancelada.\n";
            return;
        }

        if (input.empty()) {
            system("cls");
            std::cout << "\nDebe completar este campo. Intente nuevamente.\n\n";
            system("pause");
            continue;
        }

        if (!_utilidades.esEnteroValido(input)) {
            system("cls");
            std::cout << "\nLa opcion ingresada es incorrecta, debe ser un numero entero. Intente nuevamente.\n\n";
            system("pause");
            continue;
        }

        opcion = std::stoi(input);
        posicion = _archivo.buscar(idProfesor);
        _profesor = _archivo.leer(posicion);

        switch (opcion) {
        case 1: {
            system("cls");

            for (int i = 0; i < cantRegCursos; i++) {
                cursoP = archiCurso.leer(i);

                if (cursoP.getEstado() && cursoP.getIdProfesor() == idProfesor) {


                    if ( archiCurso.tieneInscripcionesActivas(cursoP.getId() ) ) {
                        inscripActivas = true;
                        break;
                    }
                    archiCurso.baja(cursoP.getId() );
                }
            }

            if (inscripActivas) {
                std::cout << "\nERROR. El profesor que desea dar de baja tiene cursos a su cargo con inscripciones activas.\n\n";
                std::cin.ignore();
                return;
            }

            _profesor.setEstado(false);
            _archivo.alta(_profesor, posicion);

            std::cout << "\nRegistro de profesor y curso/s eliminados exitosamente.\n";
            std::cin.ignore();
            return;
        }
        case 2:
        {

            system("cls");

            if (_cursoManager.reasignarCursosDeProfesor(idProfesor)) {
                _profesor.setEstado(false);
                _archivo.alta(_profesor, posicion);

                std::cout << "\nRegistro de profesor eliminado exitosamente.\n\n";
                std::cin.ignore();
                return;
            }


            std::cin.ignore();
            return;

        }
        default:
            std::cout << "La opcion ingresada es incorrecta, intente nuevamente.\n";
            system("pause");
            continue;
        }
    }
}

void ProfesorManager::reactivarProfesor(){

    int id, posicion, cantRegistros, cantRegInactivos = 0;
    std::string input;


    cantRegistros = _archivo.cantRegistros();

    if(cantRegistros <= 0){

        std::cout << "No hay profesores registrados.\n";

        return;
    }

    for (int i = 0; i <cantRegistros; i++){

        _profesor = _archivo.leer(i);

        if ( !_profesor.getEstado() ){

            cantRegInactivos ++;
        }

    }

    if ( cantRegInactivos == 0 ){

        std::cout << "\nNo hay profesores inactivos registrados.\n\n";

        return;

    }



    while(true){

        system("cls");

        std::cout << "========================================== \n";
        std::cout << "         === REACTIVACION DE PROFESOR ===      \n";
        std::cout << "==========================================\n";

        std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
        std::cout<<"Ingrese el ID del profesor que desea reactivar: \n";
        std::getline(std::cin,input);

        if (_utilidades.esComandoSalir(input)){
            system("cls");
            std::cout << "\nReactivacion de profesor cancelada.\n\n";
            return;

        }

        if (input.empty()){
            system("cls");
            std::cout << "Debe completar este campo. Intente nuevamente.\n\n";
            system("pause");

            continue;

        }


        if ( !_utilidades.esEnteroValido(input) ){
            system("cls");
            std::cout << "\nDebe ingresar un n�mero entero. Intente nuevamente.\n\n";
            system("pause");
            continue;
        }

        id = std::stoi(input);
        posicion = _archivo.buscar(id);

        if ( posicion < 0 ){

            std::cout << "\nEl ID ingresado no pertenece a un registro de profesor. Intente nuevamente.\n\n";
            system("pause") ;
            continue;
        }

        _profesor = _archivo.leer(posicion);

        if ( _profesor.getEstado() ){

            system("cls");

            std::cout<<"\nEl ID ingresado pertenece a un profesor activo.\n\n";

            system("pause");
            continue;

        }

        _profesor.mostrar();

        _profesor.setEstado(true);

        if( !_archivo.alta(_profesor,posicion) ){

          std::cout<<"\nEl registro del profesor no se ha podido reactivar.\n\n";;

          return;

        }

        std::cout<<"\nEl registro del profesor ha sido reactivado.\n\n";

       break;

    }


}

void ProfesorManager::modificar(){

    Fecha fechaNacimiento;
    int id, posicion, opcion, cantRegistros;
    std::string input;

    cantRegistros = _archivo.cantRegistros();

    if(cantRegistros <= 0){

        std::cout << "No hay profesores registrados.\n";

        return;
    }

    while(true){

        system("cls");

        std::cout << "=========================================\n";
        std::cout << "         === MODIFICAR PROFESOR ===      \n";
        std::cout << "=========================================\n";

        std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
        std::cout<<"Ingrese el ID del profesor que desea modificar: \n";
        std::getline(std::cin,input);


        if (_utilidades.esComandoSalir(input)){
            system("cls");
            std::cout << "\nModificacion de profesor cancelada.\n\n";
            return;

        }

        if (input.empty()){

            system("cls");
            std::cout << "\nDebe completar este campo. Intente nuevamente.\n\n";

            system("pause");
            continue;

        }

        if ( !_utilidades.esEnteroValido(input) ){
            system("cls");
            std::cout << "\nDebe ingresar un n�mero entero. Intente nuevamente.\n\n";
            system("pause");
            continue;
        }

        id = std::stoi(input);

        posicion = _archivo.buscar(id);

        if ( posicion < 0 ){

            system("cls");

            std::cout<<"\nEl ID ingresado no pertenece a un profesor registrado.Intente nuevamente.\n\n";
            system("pause");
            continue;

        }

        _profesor = _archivo.leer(posicion);

        if ( !_profesor.getEstado() ){

            system("cls");

            std::cout<<"\nEl ID ingresado no pertenece a un profesor activo.\n\n";

            system("pause");
            continue;

        }

       break;

    }

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
                std::cout << "         === MODIFICAR PROFESOR ===      \n";
                std::cout << "=========================================\n";

                std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
                std::cout<<"\nIngrese el nuevo DNI: \n\n";
                std::getline(std::cin,input);

                if (_utilidades.esComandoSalir(input)){
                    system("cls");
                    std::cout << "\nModificacion de profesor cancelada.\n\n";
                    return;

                }

                if( !dniValidacion(input)) {;
                    continue;


                }
               break;
            }

            _profesor.setDni(input);

            if ( _archivo.alta(_profesor,posicion) ){

                system("cls");

                std::cout<<"\nEl registro se modifico correctamente. \n";
                _profesor.mostrar();

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

                std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
                std::cout<<"Ingrese el nuevo nombre: \n";
                std::getline(std::cin,input);


                if (_utilidades.esComandoSalir(input)){
                    system("cls");
                    std::cout << "\nModificacion de profesor cancelada.\n\n";
                    return;

                }


                if( !nombreValidacion(input)) {;
                    continue;


                }
               break;
            }

            _profesor.setNombre(input);

            if ( _archivo.alta(_profesor,posicion) ){

                system("cls");

                std::cout<<"\nEl registro se modifico correctamente. \n";
                _profesor.mostrar();

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

                std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
                std::cout<<"Ingrese el nuevo apellido: \n";
                std::getline(std::cin,input);

                if (_utilidades.esComandoSalir(input)){
                    system("cls");
                    std::cout << "\nModificacion de profesor cancelada.\n\n";
                    return;

                }

                if( !apellidoValidacion(input)) {;
                    continue;


                }
               break;
            }

            _profesor.setApellido(input);

            if ( _archivo.alta(_profesor,posicion) ){

                system("cls");

                std::cout<<"\nEl registro se modifico correctamente. \n";
                _profesor.mostrar();

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

                std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
                std::cout<<"Ingrese el nuevo numero de telefono: \n";
                std::getline(std::cin,input);


                if (_utilidades.esComandoSalir(input)){
                    system("cls");
                    std::cout << "\nModificacion de profesor cancelada.\n\n";
                    return;

                }

                if( !telefonoValidacion(input)) {;
                    continue;


                }
               break;
            }

            _profesor.setTelefono(input);

            if ( _archivo.alta(_profesor,posicion) ){

                system("cls");

                std::cout<<"\nEl registro se modifico correctamente. \n";
                _profesor.mostrar();

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

                std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
                std::cout<<"Ingrese el nuevo email: \n";
                std::getline(std::cin,input);


                if (_utilidades.esComandoSalir(input)){
                    system("cls");
                    std::cout << "\nModificacion de profesor cancelada.\n\n";
                    return;

                }


                if( !emailValidacion(input)) {;
                    continue;


                }
               break;
            }

            _profesor.setEmail(input);

            if ( _archivo.alta(_profesor,posicion) ){

                system("cls");

                std::cout<<"\nEl registro se modifico correctamente. \n";
                _profesor.mostrar();

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

                std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
                std::cout<<"Ingrese la nueva direccion: \n";
                std::getline(std::cin,input);


                if (_utilidades.esComandoSalir(input)){
                    system("cls");
                    std::cout << "\nModificacion de profesor cancelada.\n\n";
                    return;

                }

                if( !direccionValidacion(input)) {;
                    continue;


                }
               break;
            }

            _profesor.setDireccion(input);

            if ( _archivo.alta(_profesor,posicion) ){

                system("cls");

                std::cout<<"\nEl registro se modifico correctamente. \n";
                _profesor.mostrar();

                std::cin.get();

            }else{

                system("cls");

                std::cout<<"No se pudo modificar el registro. \n";

                std::cin.get();

                return;

            }

            break;

        case 7:

            std::cin.ignore();

            while(true){


                system("cls");
                std::cout << "=========================================\n";
                std::cout << "         === MODIFICAR PROFESOR ===        \n";
                std::cout << "=========================================\n";

                std::cout << "Para cancelar, escriba 'salir' en cualquier momento.\n\n";
                std::cout<<"Ingrese la fecha de nacimiento (DD/MM//AAAA): \n";
                std::getline(std::cin,input);

                if (_utilidades.esComandoSalir(input)){
                    system("cls");
                    std::cout << "\nModificacion de profesor cancelada.\n\n";
                    return;
                }


                if (input.empty()){

                    std::cout << "Debe completar este campo. Intente nuevamente.\n\n";

                    system("pause");

                    continue;
                }



                if( !fechaNacimiento.validarFechaStr(input) ) {

                    std::cout << "La fecha ingresada no es valida. Intente nuevamente." << std::endl;

                    system("pause");

                    continue;

                }else{

                    _profesor.setFechaNacimiento(fechaNacimiento);
                    std::cout<<"Presione cualquier tecla para continuar... \n";
                    break;

                }

            }

            if ( _archivo.alta(_profesor,posicion) ){

                system("cls");

                std::cout<<"\nEl registro se modifico correctamente. \n";
                _profesor.mostrar();

                std::cin.get();

            }else{

                system("cls");

                std::cout<<"No se pudo modificar el registro. \n";

                std::cin.get();

                return;

            }

            break;

        case 0:

            std::cin.ignore();
            return;
            break;

        default:

            system("cls");

            std::cout<<"La opcion ingresada es incorrecta, intente nuevamente.\n";

            std::cin.get();

            break;


        }


    }while( opcion !=0 );

}


void ProfesorManager::baja(){
    int idBaja, posicion, opcion,cantRegistros, cantRegistrosActivos = 0;
    std::string input;

    cantRegistros = _archivo.cantRegistros();

    if(cantRegistros <= 0){

        std::cout << "No hay profesores registrados.\n";

        return;

    }

    for (int i = 0; i <cantRegistros; i++){

        _profesor = _archivo.leer(i);

        if ( _profesor.getEstado() ){

            cantRegistrosActivos ++;
        }

    }

    if ( cantRegistrosActivos == 0 ){

        std::cout << "\nNo hay profesores activos registrados.\n\n";

        return;

    }

    while(true) {

        system("cls");

        std::cout << "=========================================\n";
        std::cout << "         === BAJA DE PROFESOR ===        \n";
        std::cout << "=========================================\n";

        std::cout <<"Para volveer al menu anterior ingrese 'salir', en cualquier momento.\n";
        std::cout<<"\nIngrese el ID del profesor al que desea dar de baja: \n";
        std::getline(std::cin,input);

        if ( _utilidades.esComandoSalir(input) ){
            system("cls");
            std::cout << "\nBaja de profesor cancelada.\n\n";
            return;

        }

        if (input.empty()){

            system("cls");
            std::cout << "\nDebe completar este campo. Intente nuevamente.\n\n";

            system("pause");
            continue;

        }

        if ( !_utilidades.esEnteroValido(input) ){
            system("cls");
            std::cout << "\nEl ID ingresado es incorrecto, debe ser un numero entero.Intente nuevamente.\n\n";
            system("pause");
            continue;
        }

        idBaja = std::stoi(input);/// Convierto la cadena en un valor entero.

        posicion = _archivo.buscar(idBaja);

        if ( posicion < 0 ) {

            std::cout<<"\nEl ID ingresado no pertenece a un profesor registrado. Intente nuevamente.\n\n";
            system("pause");
            continue;

        }

        ///Filtrar la busqueda solo en profesores activos

        _profesor = _archivo.leer(posicion);

        if ( !_profesor.getEstado() ){

            system("cls");
            std::cout<<"\nEl ID ingresado no corresponde a un profesor activo.Intente nuevamente.\n\n";
            system("pause");
            continue;
        }

       break;
    }

    ///Buscar si el profesor tiene asignados cursos antes de darle de baja.

    if ( contCursosProfesor(idBaja) > 0 ){

       bajaCursoProfesor(idBaja); ///Baja de cursos desde profesormanager

       return;
    }


    while(true){

        system("cls");

        std::cout << "=========================================\n";
        std::cout << "         === BAJA DE PROFESOR ===        \n";
        std::cout << "=========================================\n";

        std::cout<<"\nProfesor: " << _profesor.getApellido()<<", "<<_profesor.getNombre()<<".\n";
        std::cout<<"DNI: " << _profesor.getDni()<<".\n";

        std::cout <<"\nPara volveer al menu anterior ingrese 'salir', en cualquier momento.\n";
        std::cout << "Ingrese una opcion.\n\n";
        std::cout<<"1)Para confirmar.\n";
        std::cout<<"2)Para cancelar.\n";
        std::getline(std::cin,input);


        if ( _utilidades.esComandoSalir(input) ){
            system("cls");
            std::cout << "\nBaja de profesor cancelada.\n\n";
            return;

        }

        if ( !_utilidades.esEnteroValido(input) ){

            std::cout << "\nEl valor ingresado es incorrecto.Intente nuevamente.\n\n";
            system("pause");
            continue;
        }

        opcion = std::stoi(input);

        switch(opcion){

        case 1:

            system("cls");
            _profesor.setEstado(false);
            _archivo.alta(_profesor,posicion);

            std::cout<<"\nRegistro de profesor eliminado exitosamente.\n\n";

            return;
            break;

        case 2:

            system("cls");
            std::cout << "\nBaja de profesor cancelada.\n\n";

            return;
            break;

        default:

            std::cout<<"La opcion ingresada es incorrecta, intente nuevamente.\n";

            system("pause");

            break;
        }

    }


}

