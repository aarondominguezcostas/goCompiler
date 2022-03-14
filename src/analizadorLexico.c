#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tablaSimbolos.h"
#include "sistemaEntrada.h"
#include "definiciones.h"

void _numbers(tipoelem *actual);

tipoelem nextComponent(){
    char siguiente = 0;
    int done = 0;
    tipoelem actual;

    while(!done){

        siguiente = readChar();

        printf("%c", siguiente);

        //todos los automatas van aqui
        //automata de numeros
        if(isdigit(siguiente)){ 
            printf("Se ha encontrado un numero: ");
            _numbers(&actual);
        }

        done = 1;

        //acabar de analizar componente lexico
        if(siguiente=='e'){

            //devolver al SE

            //construir tipoelem
            getWord(actual.identificador);
            actual.valor = -1;

            findElement(&actual);
            printf("\n%s , %d",actual.identificador, actual.valor);
        }
    }

    return actual;
}

void _numbers(tipoelem *actual){

    char siguiente = 0;
    char base = 0;
    int done = 0;
    char under = 0;

    while(!done){
        siguiente = readChar();
        printf("%c", siguiente);

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
            
            //construir tipoelem
            getWord(actual->identificador);
            actual->valor = 300;
        }

    }

}
