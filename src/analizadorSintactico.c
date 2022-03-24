
#include <stdio.h>
#include <stdlib.h>
#include "analizadorLexico.h"
#include "definiciones.h"

void analizar(){
    //Primero se crea el componente que se va a reutilizar para recibir los componentes lexicos
    tipoelem e;
    e.identificador = NULL;

    //se itera hasta que se recibe EOF, cuyo valor se establece en -100
    do{
        nextComponent(&e);

        if(e.valor != -100){
            printf("\n<\"%s\", %d>",e.identificador, e.valor);
        }
    }while(e.valor != -100);

    //se libera la memoria del identificador
    if(e.identificador != NULL){
        free(e.identificador);
        e.identificador = NULL;
    }

}