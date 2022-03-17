#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definiciones.h"

#define A 0
#define B 1
#define BUFFER_SIZE 32

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
    bufferA[BUFFER_SIZE] = EOF;
    bufferB[BUFFER_SIZE] = EOF;
    inicio = bufferA;
    delantero = bufferA;
    fread(bufferA,sizeof(char),BUFFER_SIZE,archivo);
}

// TODO > comprobar que se lee caracter a caracter
// cambiar a leer de los dos buffers
char readChar(){
    if( *delantero == EOF ){
        //cargar nuevo bloque A
        if (delantero == bufferA+BUFFER_SIZE){
            
            if(inicio >= &bufferB[0] && inicio <= &bufferB[BUFFER_SIZE]){
                //no se puede cargar un nuevo bloque
                printf("No se puede cargar un nuevo bloque");
                return EOF;
            }
            
            _loadBlock(B);
        }else if (delantero == bufferB+BUFFER_SIZE){

            //comprobar que el puntero de inicio no esta en el bloque que se va a cargar
            if(inicio >= &bufferA[0] && inicio <= &bufferA[BUFFER_SIZE]){
                //no se puede cargar un nuevo bloque
                printf("No se puede cargar un nuevo bloque");
                return EOF;
            }

            _loadBlock(A);
        }else{
            return EOF;
        }
    }

    char res = *delantero;
    delantero++;
    return res;

}

// se finaliza el sistema
void endSystem(){
    inicio=NULL;
    delantero=NULL;
    fclose(archivo);
}

//cargar nuevo bloque de caracteres
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
    lexema->identificador = (char*)malloc(sizeof(char)*8);

    int max = sizeof(lexema->identificador);
    int count=0;
    while(inicio!=delantero){

        //hay que duplicar el tamaño de la palabra
        if(count==max){
            void *try = realloc(lexema->identificador,max*2);
            if(try==NULL){
                printf("Error: no se pudo duplicar el tamaño de la palabra");
                exit(1);
            }
            max = max*2;
        }

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