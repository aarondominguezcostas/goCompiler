#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "definiciones.h"
#include "tablaSimbolos.h"
#include "sistemaEntrada.h"

void _numbers(tipoelem *actual);
void _identifier(tipoelem *actual);
void _stringLiteral(tipoelem *actual, char limiter);
int _comment();
void _operators(tipoelem *actual, char inicial);

tipoelem nextComponent(){
    char siguiente = 0;
    int done = 0;
    int avanzaNext = 0;

    //creo el elemento para devolverlo
    tipoelem actual;

    while(!done){

        siguiente = readChar();

        //si el anterior caracter era un separador, avanzamos el inicio
        if(avanzaNext == 1){
            avanzar();
            avanzaNext = 0;
        }

        //todos los automatas van aqui
        //automata de numeros
        if(isdigit(siguiente)){ 
            //printf("\nSe ha encontrado un numero");
           // printf("%c", siguiente);

            _numbers(&actual);
            done = 1;

        //automata de identificadores
        }else if(isalpha(siguiente) || siguiente == '_'){
            //printf("\nSe ha encontrado un identificador: %c \n", siguiente);
    
            _identifier(&actual);
            done = 1;

        //automata para strings
        }else if(siguiente == '\'' || siguiente == '"'){
            _stringLiteral(&actual, siguiente);
            done = 1;
        
        //automata para comentarios
        }else if(siguiente == '/'){
            if(_comment()){
                _operators(&actual, siguiente);
                done = 1;
            };

        //automata para operadores
        }else if(siguiente == '+' || siguiente == '-' || siguiente == '*' || siguiente == '%' || siguiente == '=' || siguiente == '<' || siguiente == '>' || siguiente == '!' || siguiente == '&' || siguiente == '|' || siguiente == '^' || siguiente == '~' || siguiente == '?' || siguiente == ':' || siguiente == '.' || siguiente == '(' || siguiente == ')' || siguiente == '[' || siguiente == ']' || siguiente == '{' || siguiente == '}' || siguiente == ',' || siguiente == ';'){
            //printf("\nSe ha encontrado un operador: %c \n", siguiente);
            //avanzaNext = 1;
            _operators(&actual, siguiente);
            done = 1;

        }else if(siguiente == ' ' || siguiente == '\n' || siguiente == '\t' || siguiente == '\r'){
            avanzaNext = 1;
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
    int hex = 0;
    //int fp = 0;

    while(!done){
        siguiente = readChar();


        if(hex == 1 && ((siguiente >= 65 && siguiente <= 70) || (siguiente >= 97 && siguiente <= 102))){
            under = 0;
        }else if( siguiente == 'b' || siguiente == 'B' || siguiente == 'o' || siguiente == 'O' || siguiente == 'x' || siguiente == 'X' ){

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
            if(siguiente == 'x' || siguiente == 'X'){
                hex = 1;
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

// automata que reconoce strings
void _stringLiteral(tipoelem *actual, char limiter){
    int skip = 0;
    int done = 0;
    char siguiente = 0;

    while(!done){
        siguiente = readChar();

        if( siguiente == '\\' ){
            skip = 1;
        }else if( !skip && siguiente == limiter ){
            done = 1;
            //construir tipoelem
            getWord(actual);
            actual->valor = STRING;


        }else if( siguiente == '\n' ){
            printf("\nError: se ha encontrado un salto de linea en un string literal");
            done = 1;
        }else{
            skip = 0;
        }
    }
}

//automata de comentarios
int _comment(){
    char siguiente = 0;

    siguiente = readChar();

    if( siguiente == '*' ){
        int done = 0;
        while(!done){
            while(siguiente != '*'){
                siguiente = readChar();
            
                //es necesario ir avanzando el puntero de inicio
                avanzar();
            }
            siguiente = readChar();
            if( siguiente == '/' ){
                readComment();
                done = 1;
            }
        }

    }else if( siguiente == '/' ){
        while(siguiente != '\n'){
            siguiente = readChar();
        }
        devolver();
        readComment();
    }else{
        devolver();
        return 1;
    }
    return 0;
}

//automata para reconocer operadores
void _operators(tipoelem *actual, char inicial){
    int done = 0;
    char siguiente = 0;

    siguiente = readChar();

    if( siguiente == '<' || siguiente == '>' || siguiente == '^' || siguiente == '=' || siguiente == '&' || siguiente == '|' || siguiente == '-' || siguiente == '+' || siguiente == '.'){
        while(!done){
            siguiente = readChar();
            if( siguiente == '<' || siguiente == '>' || siguiente == '^' || siguiente == '=' || siguiente == '&' || siguiente == '|' || siguiente == '-' || siguiente == '+' || siguiente == '.'){
                //no hacer nada
            }else{
                devolver();

                getWord(actual);

                actual->valor = OPERATOR;
                done = 1;
            }
        }
    }else{
        done = 1;
        //devolver al SE
        devolver();
        
        //construir tipoelem
        getWord(actual);

        actual->valor = inicial;
    }
}