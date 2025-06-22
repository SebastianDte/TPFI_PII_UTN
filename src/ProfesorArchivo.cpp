#include "ProfesorArchivo.h"
#include <iostream>
#include "cstring"



ProfesorArchivo::ProfesorArchivo(){

    strcpy(_nombreArchivo,"profesor.dat") ;

}



bool ProfesorArchivo::alta(const Profesor& regProfesor){
    bool result;

    FILE *pProf;

    pProf = fopen(_nombreArchivo,"ab");

    if ( pProf == nullptr ){

        return false;
    }

    result = fwrite(&regProfesor,sizeof(Profesor),1,pProf);

    fclose(pProf);

    return result;


}

int ProfesorArchivo::cantRegistros(){

    int cantByteTotal,tamRegistro, cantidadRegistros;

    FILE *pProf;

    pProf = fopen(_nombreArchivo,"rb");

    if( pProf==nullptr ){

       return -1;

    }

    tamRegistro = sizeof(Profesor);

    fseek( pProf,0,SEEK_END);

    cantByteTotal = ftell(pProf);

    cantidadRegistros = cantByteTotal / tamRegistro;

    fclose(pProf);

    return cantidadRegistros;
}

int ProfesorArchivo::generarID (const int& cantRegistros){
    Profesor regProf;
    int ultID = cantRegistros -1 ;

    FILE *pProf;

    pProf = fopen(_nombreArchivo,"rb");

    if ( pProf == nullptr ){

        return -1;

    }

    fseek(pProf,sizeof(Profesor)*ultID,SEEK_SET);

    fread(&regProf,sizeof(Profesor),1,pProf);

    ultID = regProf.getId();

    ultID++;

    fclose(pProf);

    return ultID;
}


Profesor ProfesorArchivo::leer(const int& posicion){

    Profesor registro;

    FILE *pProf;

    pProf = fopen(_nombreArchivo,"rb");

    if ( pProf == nullptr ){

        std::cout<<"No se pudo abrir el archivo\n";

        exit(-1);
    }

    fseek(pProf,sizeof(Profesor)*posicion,SEEK_SET);

    fread(&registro,sizeof(Profesor),1,pProf);

    fclose(pProf);

    return registro;

}

int ProfesorArchivo::buscar(const int& id){
    Profesor profReg;
    int contPos = 0;

    FILE *pProf;

    pProf = fopen( _nombreArchivo,"rb");

    if ( pProf == nullptr ){

        std::cout<<"No se pudo abrir el archivo \n";

        return -1;

    }

    while( fread ( &profReg,sizeof(Profesor),1,pProf ) == 1){

        if ( profReg.getId() == id ){

            fclose(pProf);

            return contPos;

        }else{

            contPos++;

        }


    }

    fclose(pProf);

    return -1;

}

bool ProfesorArchivo::alta(const Profesor& regModificado, const int& posicion){
    bool result;

    FILE *pProf;

    pProf = fopen(_nombreArchivo,"rb+");

    if( pProf == nullptr ){

        std::cout<<"No se pudo modificar el registro.\n";

        return false;

    }

    fseek( pProf,sizeof(Profesor)*posicion,SEEK_SET);

    result = fwrite(&regModificado,sizeof(Profesor),1,pProf);

    fclose(pProf);

    return result;


}

bool ProfesorArchivo::existeDNI(const std::string& dni){
    int total = cantRegistros();
    Profesor _profesor;

    for (int i = 0; i < total; i++){

        _profesor = leer(i);

        if (_profesor.getDni() == dni)
        {
            return true; /// YA existe un registro con este DNI
        }
    }
    return false;
}


