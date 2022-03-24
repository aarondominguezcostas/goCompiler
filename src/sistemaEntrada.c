#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definiciones.h"

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
    bufferA[BUFFER_SIZE] = EOF;
    bufferB[BUFFER_SIZE] = EOF;
    inicio = bufferA;
    delantero = bufferA;
    fread(bufferA,sizeof(char),BUFFER_SIZE,archivo);
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

    //se determina el tamaño maximo del lexema
    int max = sizeof(lexema->identificador);
    int count=0;

    //mientras no se llegue a la posicion de delantero
    while(inicio!=delantero){

        //Si es el penúltimo caracter del buffer de lexema, se duplica el tamaño
        //hay que dejar 1 hueco por lo menos para '\0'
        if(count==(max-1)){
            max = max*2;
            lexema->identificador = (char*) realloc(lexema->identificador, max);
            if(lexema->identificador == NULL){
                printf("Error: no se pudo duplicar el tamaño de la palabra");
                exit(1);
                printf("%d\n",max); 
            }
        }

        //se comprueba que no se haya sobrepasado el limite de tamaño de lexemas
        if(count>BUFFER_SIZE){
            printf("tamaño excedido");
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