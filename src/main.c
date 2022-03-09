#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tablasimbolos.h"
#include "lector.h"

int main(){

    //el archivo se tiene que abrir aqui
    FILE *archivo = fopen("concurrentSum.go","r");
    if(archivo == NULL){
        //lanzar error
        return 1;
    }else{
        //inicializar la tabla de simbolos
        initTable();
        //inicializar sistema de entrada
        initSystem(archivo);

        printTable();

        char res;
        do{
            printf("%c",res);
            res = readChar();
        }while(res!= EOF);
        //se destruye la tabla de simbolos
        destroyTable();
    
        //se cierra el fichero
        endSystem();
        fclose(archivo);
    }
}