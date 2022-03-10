#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tablaSimbolos.h"
#include "sistemaEntrada.h"

void nextComponent(){
    char siguiente = 0;
    int done = 0;


    while(!done){
        siguiente = readChar();

        //todos los automatas van aqui
        if(isdigit(siguiente)){
            printf("\n numero: ");
        }

        printf("%c",siguiente);
        if(siguiente==EOF){
            done = 1;
        }
    }
    
    
}