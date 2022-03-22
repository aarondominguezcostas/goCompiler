
#include <stdio.h>
#include <stdlib.h>
#include "analizadorLexico.h"
#include "definiciones.h"

void analizar(){
    //itera por todos los componentes
    tipoelem e;

    do{
        e =  nextComponent();

        if(e.valor != -100){
            printf("\n<\"%s\", %d>",e.identificador, e.valor);
        }
        free(e.identificador);


    }while(e.valor != -100);

}