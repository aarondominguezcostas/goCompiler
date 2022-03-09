#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define A 0
#define B 1
#define BUFFER_SIZE 32

FILE *archivo;

char bufferA[BUFFER_SIZE+1];
char bufferB[BUFFER_SIZE+1];
char *inicio;
char *delantero;

// inicializa el sistema de entrada
// DUDA / Cargar 2 bloques o solo 1
void initSystem(FILE *input){
    archivo = input;
    bufferA[BUFFER_SIZE] = EOF;
    bufferB[BUFFER_SIZE] = EOF;
    inicio = bufferA;
    delantero = bufferA;
    fread(bufferA,1,BUFFER_SIZE,archivo);
}

// TODO > comprobar que se lee caracter a caracter
// cambiar a leer de los dos buffers
char readChar(){
    if( *delantero == EOF ){

        //cargar nuevo bloque A
        printf("Cargando nuevo bloque\n");
        if (delantero == bufferA[BUFFER_SIZE]){
            fread(bufferB,1,BUFFER_SIZE,archivo);
            delantero = bufferB;
        }else if (delantero == bufferB[BUFFER_SIZE]){
            fread(bufferA,1,BUFFER_SIZE,archivo);
            delantero = bufferA;
        }else{
            return EOF;
        }
    }

}

// se finaliza el sistema
void endSystem(){
    inicio=NULL;
    delantero=NULL;
}

//cargar nuevo bloque de caracteres

//gestionar errores
