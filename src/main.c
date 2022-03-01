#include <stdio.h>
#include <stdlib.h>

#include "tablasimbolos.h"

int main(){

    //inicializar la tabla de simbolos
    init();

    //testing tabla de simbolos
    insert("hola", 1);
    printTable();

    //se destruye la tabla de simbolos
    destroy();
}