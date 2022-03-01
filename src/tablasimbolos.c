// En este fichero se define la tabla de simbolos a utilizar por el analizador lexico.

#include "abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

abb tabla;

void init(){
    //inicializamos la tabla de simbolos
    crear(&tabla);
}

void destroy(){
    //destruimos la tabla de simbolos
    destruir(&tabla);
}

void insert(char* id, int valor){
    //insertamos un elemento en la tabla de simbolos
    tipoelem elemento;
    strcpy(elemento.identificador, id);
    elemento.valor = valor;

    insertar(&tabla, elemento);
}

void printTable(){
    //imprimimos la tabla de simbolos
    printf("\nTabla de simbolos:\n");
    tipoelem x;
    leer(tabla, &x);
    printf("%s: %d\n", x.identificador, x.valor);
}