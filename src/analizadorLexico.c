#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "definiciones.h"
#include "tablaSimbolos.h"
#include "sistemaEntrada.h"
#include "errores.h"

//definicion de todos los automatas del analizador lexico
void _numbers(tipoelem *actual, int first0);
void _identifier(tipoelem *actual);
void _stringLiteral(tipoelem *actual, char limiter);
int _comment();
void _operators(tipoelem *actual, char inicial);
int _floats(tipoelem *actual, int hex, int exponent, int startsFp, int mantissa);

//funcion que devuelve el siguiente componente lexico
void nextComponent(tipoelem *actual){
    char siguiente = 0;
    int done = 0;
    int avanzaNext = 0;

    //este bucle se lleva a cabo mientras no se reconozca un componente lexico
    while(!done){

        //se obtiene el caracter del SE
        siguiente = readChar();

        //si el anterior caracter era un separador, avanzamos el inicio
        if(avanzaNext == 1){
            avanzar();
            avanzaNext = 0;
        }

        //todos los automatas van aqui
        //automata de numeros
        if(isdigit(siguiente)){ 

            if (siguiente == '0'){
                _numbers(actual, 1);
            }
            else{
                _numbers(actual, 0);
            }
            done = 1;

        //automata para numeros en punto flotante
        }else if(siguiente == '.'){

            //el punto tambien puede ser un operador, por lo que se hace que 
            // _floats devuelva 1 si no se reconoce un numero
            if(_floats(actual,0,0,1,0)){
                _operators(actual,siguiente);
            }        
            done = 1;


        //automata de identificadores
        }else if(isalpha(siguiente) || siguiente == '_'){

            _identifier(actual);
            done = 1;

        //automata para strings
        }else if(siguiente == '\'' || siguiente == '"'){
            _stringLiteral(actual, siguiente);
            done = 1;
        
        //automata para comentarios
        }else if(siguiente == '/'){

            //el simbolo '/' puede empezar un comentario o ser un operador, por lo que 
            // _comment devuelve 1 si determina que no es un comentario
            if(_comment()){
                _operators(actual, siguiente);
                done = 1;
            };
        
        //automata para operadores
        }else if(siguiente == '+' || siguiente == '-' || siguiente == '*' || siguiente == '%' || siguiente == '=' || siguiente == '<' || siguiente == '>' || siguiente == '!' || siguiente == '&' || siguiente == '|' || siguiente == '^' || siguiente == '~' || siguiente == '?' || siguiente == ':' || siguiente == '(' || siguiente == ')' || siguiente == '[' || siguiente == ']' || siguiente == '{' || siguiente == '}' || siguiente == ',' || siguiente == ';'){

            _operators(actual, siguiente);
            done = 1;

        //si el siguiente es un espacio o un terminador, se salta y se debe mover el inicio 
        //esto se hace en el turno siguiente para evitar problemas en la carga de bloques
        }else if(siguiente == ' ' || siguiente == '\n' || siguiente == '\t' || siguiente == '\r'){
            avanzaNext = 1;
        
        //si se obtiene EOF, se devuelve un valor arbitrario
        }else if(siguiente == EOF){
            actual->valor = EOFVALUE;
            done = 1;
        }
    }
}

//automata de numeros
//first0 es un flag que indica si el primer digito es 0, para reconocer numeros con base
void _numbers(tipoelem *actual, int first0){

    char siguiente = 0;
    char base = 0;
    int done = 0;
    char under = 0; //determina si el numero anterior era'_'
    int hex = 0; //determina si el numero es hexadecimal

    int mantissa = 0; //flag necesaria para los numeros hexadecimales con exponente
    while(!done){
        siguiente = readChar();

        //si es hexadecimal podemos aceptar [a-fA-F]+
        if(hex && ((siguiente >= 65 && siguiente <= 70) || (siguiente >= 97 && siguiente <= 102))){
            under = 0;
            mantissa = 1;

        //se comprueba si el caracter es una de las bases
        }else if( (siguiente == 'b' || siguiente == 'B' || siguiente == 'o' || siguiente == 'O' || siguiente == 'x' || siguiente == 'X') && first0 ){

            //si ya ha aparecido una base, no se puede volver a aparecer
            if(base){
                showError(4);
                done = 1;
            }else if(under){
                showError(5);
                done = 1;
            }

            //es necesario guardar si es hexadecimal a parte para pasarselo al automata de floats
            if(siguiente == 'x' || siguiente == 'X'){
                hex = 1;
            }

        }else if( siguiente == '_' ){
            
            //no pueden aparecer 2 consecutivas
            if(under){
                showError(5);
                done = 1;
            }else{
                under = 1;
            }

        //si es digito se acepta, ademas se guarda que ya ha aparecido la mantissa
        }else if( isdigit(siguiente) ){
            under = 0;
            mantissa = 1;
        }else if(siguiente == '.'){
            //se comprueba que el anterior no sea un '_'
            if(under){
                showError(5);
                done = 1;
            }else{
                _floats(actual,hex,0,0,mantissa);
                done = 1;
            }
        //si aparece una E en un numero, se detecta exponente y se pasa al automata de floats
        }else if(!hex && (siguiente=='E' || siguiente=='e')){
            _floats(actual, 0, 1,0, mantissa);
            done = 1;

        //si se detecta la i, se establece el numero imaginario
        }else if(siguiente=='i'){
            done = 1;
            getWord(actual);
            actual->valor = IMAGINARY;

        //si no se reconoce el catacter en el automata, se devuelve
        }else{
            done = 1;
            //devolver al SE
            devolver();
            
            //construir tipoelem
            getWord(actual);
            actual->valor = INTEGER;
        }

        //si no se ha reconocido una base, se establece la base 10, y cualquier otra dara error
        base = 1;
    }
}

//automata de numeros en punto flotante
// hex -> indica si es un numero hexadecimal 
// exponente -> indica si ya ha aparecido el exponente
// startsFp -> indica si empieza por un '.'
// mantissa -> indica si han aparecido numeros en la mantissa

int _floats(tipoelem *actual, int hex, int exponent, int startsFp, int mantissa) {
    char siguiente = 0;
    int done = 0;
    char under = 0;
    int point = 1;
    int checkExponent = 0;

    while(!done){
        siguiente = readChar();

        //se comprueba que sea un numero
        if( isdigit(siguiente)){
            under = 0;
            exponent = 0;
            mantissa = 1;

        //tambien se aceptan [a-fA-F]+ si el numero es hexadecimal
        }else if(hex && ((siguiente >= 65 && siguiente <= 70) || (siguiente >= 97 && siguiente <= 102))){
            under = 0;
            exponent = 0;
            mantissa = 1;
            if(siguiente=='e' || siguiente=='E'){
                checkExponent = 1;
            }
        //se sigue aceptando _ si no es consecutivo
        }else if(siguiente == '_'){
            if(under || point){
                showError(5);
                done = 1;
            }else{
                under = 1;
                point = 0;
            }
        //exponentes en numeros decimales
        }else if(!hex && (siguiente == 'e' || siguiente == 'E')){
            if(under){
                showError(5);
                done = 1;
            }else{
                exponent = 1;
            }
        //exponentes en numeros hexadecimales
        }else if(hex && (siguiente == 'p' || siguiente == 'P')){
            if(under){
                showError(5);
                done = 1;
            }else if(!mantissa){
                showError(6);
                done = 1;
            }else{
                exponent = 1;
            }
        //si aparecen + o - se deben comprobar los exponentes
        }else if(siguiente == '+' || siguiente == '-'){
            if(checkExponent){
                showError(7);
                done = 1;
            }else if(!exponent){
                //si no hay un exponente, es una operacion, hay que devolver
                done = 1;
                devolver();
                getWord(actual);
                actual->valor = FLOAT;
            }

        //si aparece una i es imaginario
        }else if(siguiente == 'i'){
            done = 1;
            getWord(actual);
            actual->valor = IMAGINARY;

        //si no se reconoce el caracter se devuelve al SE y se genera el componente lexico
        }else{
            if(!startsFp){
                done = 1;
                //devolver al SE
                devolver();
                
                //construir tipoelem
                getWord(actual);
                actual->valor = FLOAT;

            //si empezaba en punto flotante y es el primer caracter, no se devuelve nada ya que es un operador
            }else{
                devolver();
                done = 1;
                return 1;
            }

        }
        startsFp = 0;
    }
    //por defecto se devuelve 0
    return 0;

}
//automata de identificadores
void _identifier(tipoelem *actual){
    char siguiente = 0;
    int done = 0;

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

        //si aparece backslash, el siguiente caracter no se tiene en cuenta
        if( siguiente == '\\' && !skip){
            skip = 1;
        }else if( !skip && siguiente == limiter ){
            done = 1;
            //construir tipoelem
            getWord(actual);
            actual->valor = STRING;
        }else{
            skip = 0;
        }
    }
}

//automata de comentarios
int _comment(){
    char siguiente = 0;

    siguiente = readChar();

    //si es de multiples lineas
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

    //si es comentario de una linea se para en \n
    }else if( siguiente == '/' ){
        while(siguiente != '\n'){
            siguiente = readChar();
            
            //es necesario ir avanzando el puntero de inicio
            avanzar();
        }
        devolver();
        readComment();

    //si no es ningun tipo de comentario, el '/' era un operador
    }else{
        devolver();
        return 1;
    }
    return 0;
}

//automata para reconocer operadores
void _operators(tipoelem *actual, char inicial){
    char siguiente = 0;
    int multiple = 0;

    siguiente = readChar();

    //se hacen todas las comparaciones posibles para generar los operadores definidos en GO 
    // Ver > https://go.dev/ref/spec#Operators_and_punctuation

    //si se detecta que el operador tiene mas de un caracter, se establece la flag multiple a 1
    //de esta forma se devuelve el valor OPERADOR, si no, se devuelve el valor ascii del operador
    
    if(inicial == '<' || inicial == '>'){
        if(siguiente==inicial){
            siguiente = readChar();
            if(siguiente != '='){
                devolver();
            } 
            multiple = 1;
        }else if(siguiente == '='){
            multiple = 1;
        }else if(inicial == '<' && siguiente == '-'){
            multiple = 1;
        }else{
            devolver();
        }
    }else if(inicial == '+' || inicial == '-'){
        if(siguiente == inicial || siguiente == '='){
            multiple = 1;
        }else{
            devolver();
        }
    }else if(inicial == '&'){
        if(siguiente == '^'){
            siguiente = readChar();
            if(siguiente != '='){
                devolver();
            } 
            multiple = 1;
        }else if(siguiente == '=' || siguiente == '&'){
            multiple = 1;
        }else{
            devolver();
        }
    }else if((inicial == '*' || inicial == '/' || inicial == '%' || inicial == '^' || inicial == '!' || inicial == ':') && siguiente == '='){
        multiple = 1;
    }else if(inicial == '|' && (siguiente == inicial || siguiente == '=')){
        multiple = 1;
    }else if(inicial =='.' && siguiente == '.'){
        siguiente = readChar();
        if(siguiente == '.'){
            multiple = 1;
        }else{
            devolver();
        }
    }else{
        devolver();
    }
    getWord(actual);

    if(multiple){
        actual->valor = OPERATOR;
    }else{
        actual->valor = inicial;
    }
}