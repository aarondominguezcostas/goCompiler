
#include <stdio.h>
#include <stdlib.h>
#include "analizadorLexico.h"
#include "definiciones.h"

void analizar(){

    tipoelem e;
    do{
        e = nextComponent();

        if(e.valor != -1){
            printf("\n%s: %d",e.identificador, e.valor);
        }
    }while(e.valor != -100);

}