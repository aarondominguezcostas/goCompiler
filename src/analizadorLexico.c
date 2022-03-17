#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "definiciones.h"
#include "tablaSimbolos.h"
#include "sistemaEntrada.h"

void _numbers(tipoelem *actual);
void _identifier(tipoelem *actual);


tipoelem nextComponent(){
    char siguiente = 0;
    int done = 0;

    //creo el elemento para devolverlo
    tipoelem actual;

    while(!done){

        siguiente = readChar();


        //todos los automatas van aqui
        //automata de numeros
        if(isdigit(siguiente)){ 
            printf("\nSe ha encontrado un numero");
            printf("%c", siguiente);

            _numbers(&actual);
            done = 1;

        //automata de identificadores
        }else if(isalpha(siguiente) || siguiente == '_'){
            printf("\nSe ha encontrado un identificador: %c \n", siguiente);
    
            _identifier(&actual);
            done = 1;

        //todos los caracteres como ' ' y '\n' 
        }else if(siguiente == ' ' || siguiente == '\n' || siguiente == '\t' || siguiente == '\r' || siguiente == '"'){
            actual.valor = -1;
            avanzar();
            done = 1;
        }else if(siguiente == EOF){
            actual.valor = -100;
            done = 1;
        }

        
    }

    return actual;
}

//automata de numeros
void _numbers(tipoelem *actual){

    char siguiente = 0;
    char base = 0;
    int done = 0;
    char under = 0;
    //int fp = 0;

    while(!done){
        siguiente = readChar();

        if( siguiente == 'b' || siguiente == 'B' || siguiente == 'o' || siguiente == 'O' || siguiente == 'x' || siguiente == 'X' ){

            //si ya ha aparecido una base, no se puede volver a aparecer
            if(base==1){
                printf("\nError: ya ha aparecido una base");
                done = 1;
            }else if(under==1){
                printf("\nError: _ solo puede separar digitos sucesivos");
                done = 1;
            }else{
                base = 1;
            }

        }else if( siguiente == '_' ){
            
            //no pueden aparecer 2 consecutivas
            if(under==1){
                printf("\nError: ya ha aparecido un _");
                done = 1;
            }else{
                under = 1;
            }

        }else if( isdigit(siguiente) ){
            under = 0;
        }else{
            done = 1;
            //devolver al SE
            devolver();
            
            //construir tipoelem
            getWord(actual);
            actual->valor = INTEGER;
        }
    }
}

//automata de identificadores
void _identifier(tipoelem *actual){
    char siguiente = 0;
    int done = 0;

    actual->valor=-1;

    while(!done){
        siguiente = readChar();

        if( isalpha(siguiente) || siguiente == '_' || isdigit(siguiente) ){
            //no hacer nada
            printf("siguiendo id: %c\n",siguiente);
        }else{
            done = 1;
            //devolver al SE
            devolver();
            
            //construir tipoelem
            getWord(actual);


            //buscar en la tabla de simbolos
            findElement(actual);
        }
    }
}