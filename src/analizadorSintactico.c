
#include <stdio.h>
#include <stdlib.h>
#include "analizadorLexico.h"
#include "definiciones.h"

void analizar(){
    //itera por todos los componentes
    tipoelem e;
    e.identificador = NULL;

    do{
        
        nextComponent(&e);

        if(e.valor != -100){
            printf("\n<\"%s\", %d>",e.identificador, e.valor);
        }

    }while(e.valor != -100);

    if(e.identificador != NULL){
        free(e.identificador);
        e.identificador = NULL;
    }

}