// En este fichero se define la tabla de simbolos a utilizar por el analizador lexico.

#include "abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definiciones.h"

//variable global que almacena la tabla de simbolos
abb tabla;

//definicion de prototipos
void insertElement(char* id, int valor);
void initTable();
void destroyTable();
void printTable();
void _printTable(abb A);

void initTable(){
    //inicializamos la tabla de simbolos
    crear(&tabla);

    //aqui se deberian cargar todas las palabras reservadas a la tabla de simbolos
    char *palabras[9];
    palabras[0] = "package";
    palabras[1] = "import";
    palabras[2] = "func";
    palabras[3] = "chan";
    palabras[4] = "var";
    palabras[5] = "for";
    palabras[6] = "range";
    palabras[7] = "go";
    palabras[8] = "float32";

    int valores[9];
    valores[0] = PACKAGE;
    valores[1] = IMPORT;
    valores[2] = FUNC;
    valores[3] = CHAN;
    valores[4] = VAR;
    valores[5] = FOR;
    valores[6] = RANGE;
    valores[7] = GO;
    valores[8] = FLOAT32;

    for(int i = 0; i < 9; i++){
        insertElement(palabras[i], valores[i]);
    }

}

//destruye la tabla de simbolos para liberar memoria
void destroyTable(){
    destruir(&tabla);
}

//funcion que permite insertar un elemento en la tabla de simbolos
void insertElement(char* id, int valor){
    tipoelem elemento;
    elemento.identificador = (char*)malloc(sizeof(char)*8);
    strcpy(elemento.identificador, id);
    elemento.valor = valor;

    insertar(&tabla, elemento);
}

void insertTipoelem(tipoelem elemento){
    insertar(&tabla, elemento);
}

//funcion externa que permite imprimir la tabla de simbolos
void printTable(){
    //imprimimos la tabla de simbolos
    printf("\nTabla de simbolos:\n");
    _printTable(tabla);
}

//funcion recursiva privada que recorre en profundidad la tabla de simbolos 
void _printTable(abb A){
    tipoelem E;
    if (!es_vacio(A)) {
        _printTable(izq(A));
        leer(A, &E);
        printf("%-10s : %d\n",E.identificador, E.valor);
        _printTable(der(A));
    }
}

//funcion externa que permite buscar un elemento en la tabla de simbolos
//si el elemento esta en la tabla de simbolos, devuelve un valor, si no, se introduce

void findElement(tipoelem *element){

    //buscamos el elemento en la tabla de simbolos
    //printf("\nBuscando elemento %s en la tabla de simbolos...\n", element->identificador);
    buscar_nodo(tabla, element->identificador, element);
    
    if(element->valor == -1){
        element->valor = ID;
        insertTipoelem(*element);
        //printf("\nElemento %s no encontrado en la tabla de simbolos. Se ha insertado con el valor: %d.\n", element->identificador, element->valor);

    }
}