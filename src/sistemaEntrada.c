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

void _loadBlock(int block);

// inicializa el sistema de entrada
// DUDA / Cargar 2 bloques o solo 1
void initSystem(char* inputFile){
    archivo = fopen(inputFile, "r");
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
        if (delantero == bufferA+BUFFER_SIZE){
            

            
            _loadBlock(B);
        }else if (delantero == bufferB+BUFFER_SIZE){

            //comprobar que el puntero de inicio no esta en el bloque que se va a cargar
            //if(inicio >= &bufferA[0] && inicio <= &bufferA[BUFFER_SIZE]){
            //    //no se puede cargar un nuevo bloque
            //    printf("No se puede cargar un nuevo bloque");
            //    return EOF;
            //}

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
        count = fread(bufferA,1,BUFFER_SIZE,archivo);
        delantero = bufferA;

        if (count < BUFFER_SIZE){
            bufferA[count] = EOF;
        }
    }else if(block==B){
        count = fread(bufferB,1,BUFFER_SIZE,archivo);
        delantero = bufferB;

        if (count < BUFFER_SIZE){
            bufferB[count] = EOF;
        }
    }

}

//TODO : devolver todo entre el puntero de inicio y delantero, y mover los punteros
void getWord(){

}

//devolver caracter