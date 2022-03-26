#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definiciones.h"
#include "errores.h"

#define A 0
#define B 1
#define BUFFER_SIZE 64

FILE *archivo;

char bufferA[BUFFER_SIZE+1];
char bufferB[BUFFER_SIZE+1];
char *inicio;
char *delantero;

void _loadBlock(int block);

// inicializa el sistema de entrada
// DUDA / Cargar 2 bloques o solo 1
void initSystem(char* inputFile){
    archivo = fopen(inputFile, "r");

    if(archivo == NULL){
        showError(1);
    }

    //se inicializan los buffers
    bufferA[BUFFER_SIZE] = EOF;
    bufferB[BUFFER_SIZE] = EOF;
    inicio = bufferA;
    delantero = bufferA;
    //se carga el primer bloque
    _loadBlock(A);
}

// cambiar a leer de los dos buffers
char readChar(){
    //se comprueba que no está al final del buffer
    if( *delantero == EOF ){
        //cargar nuevo bloque A
        if (delantero == bufferA+BUFFER_SIZE){
            
            //comprobar que el puntero de inicio no esta en el bloque que se va a cargar
            if(inicio >= &bufferB[0] && inicio <= &bufferB[BUFFER_SIZE]){
                //no se puede cargar un nuevo bloque
                showError(3);
                return EOF;
            }
            
            _loadBlock(B);
        }else if (delantero == bufferB+BUFFER_SIZE){

            //comprobar que el puntero de inicio no esta en el bloque que se va a cargar
            if(inicio >= &bufferA[0] && inicio <= &bufferA[BUFFER_SIZE]){
                //no se puede cargar un nuevo bloque
                showError(3);
                return EOF;
            }

            _loadBlock(A);
        }else{
            delantero++;
            return EOF;
        }
    }

    //se devuelve el caracter correspondiente
    char res = *delantero;
    delantero++;
    return res;

}

//liberar memoria del sistema de entrada y cerrar el archivo
void endSystem(){
    inicio=NULL;
    delantero=NULL;
    fclose(archivo);
}

//funcion privada que carga un nuevo bloque en el buffer correspondiente
void _loadBlock(int block){
    int count = 0;
    if(block==A){
        count = fread(bufferA,sizeof(char),BUFFER_SIZE,archivo);
        delantero = bufferA;

        if (count < BUFFER_SIZE){
            bufferA[count] = EOF;
        }
    }else if(block==B){
        count = fread(bufferB,sizeof(char),BUFFER_SIZE,archivo);
        delantero = bufferB;

        if (count < BUFFER_SIZE){
            bufferB[count] = EOF;
        }
    }
}

//esta funcion se encarga de devolver el lexema
void getWord(tipoelem *lexema){

    //se calculan las posiciones de inicio y delantero dentro de los buffers para saber el tamaño del lexema
    int posI;
    if(inicio >= &bufferB[0] && inicio <= &bufferB[BUFFER_SIZE] ){
        posI = inicio - &bufferB[0] + BUFFER_SIZE;
    }else{
        posI = inicio - &bufferA[0];
    }

    int posD;
    if(delantero >= &bufferB[0] && delantero <= &bufferB[BUFFER_SIZE] ){
        posD = delantero - &bufferB[0] + BUFFER_SIZE;
    }else{
        posD = delantero - &bufferA[0];
    }

    int size;
    if(posI > posD){
        size = (posD+2*BUFFER_SIZE)-posI;
    }else{
        size = posD-posI;
    }

    // se tiene que añadir ["\0"]
    size += 1;

    //se reserva memoria para el lexema
    lexema->identificador = (char*)malloc(sizeof(char)*size);

    int count=0;

    //mientras no se llegue a la posicion de delantero
    while(inicio!=delantero){

        //se comprueba que no se haya sobrepasado el limite de tamaño de lexemas
        if(count>BUFFER_SIZE){
            showError(2);
            inicio = delantero;
        }else{
            //se recorren los buffers
            lexema->identificador[count] = *inicio;
            inicio++;
            count++;

            //si se llega al final del buffer se cambia al inicio del otro
            if(inicio == bufferA+BUFFER_SIZE){
                inicio = bufferB;
            }else if(inicio == bufferB+BUFFER_SIZE){
                inicio = bufferA;
            }
        }
    }

    //se termina el lexema con '\0'
    lexema->identificador[count] = '\0';
}

//devolver caracter
void devolver(){
    delantero--;
}

//avanzar inicio
void avanzar(){
    inicio++;

    //comprobar que no se quedo EOF
    if(inicio == bufferA+BUFFER_SIZE){
        inicio = bufferB;
    }else if(inicio == bufferB+BUFFER_SIZE){
        inicio = bufferA;
    }
}

// funcion que se encarga de mover el puntero de inicio, saltandose el comentario
void readComment(){
    //primero se comprueba que delantero no esta en el final del buffer
    if (delantero == bufferA+BUFFER_SIZE){
        _loadBlock(B);
    }else if(delantero == bufferB+BUFFER_SIZE){
        _loadBlock(A);
    }
    //se mueve el puntero de inicio a la posicion del delantero
    inicio = delantero;
}