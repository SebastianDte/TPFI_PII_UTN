#include "ProfesorArchivo.h"
#include <iostream>
#include "cstring"



    ProfesorArchivo::ProfesorArchivo(){

        strcpy(_nombreArchivo,"profesor.dat") ;

    }

    ProfesorArchivo::ProfesorArchivo(std::string nombreArchivo){

        strncpy(_nombreArchivo, nombreArchivo.c_str(), sizeof _nombreArchivo);   ///Utilizar la funcion copiarcadenasegura
        _nombreArchivo[sizeof _nombreArchivo  - 1] = '\0';


    }

    bool ProfesorArchivo::alta(Profesor regProfesor){
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

    int ProfesorArchivo::generarID (int cantRegistros){
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


    Profesor ProfesorArchivo::leer(int posicion){

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

    int ProfesorArchivo::buscar(int id){
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

    bool ProfesorArchivo::alta(Profesor regModificado, int posicion){
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




