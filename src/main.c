#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tablaSimbolos.h"
#include "analizadorSintactico.h"
#include "sistemaEntrada.h"


int main(){


    //iniciar sistema de entrada
    initSystem("concurrentSum.go");

    //iniciar tabla de simbolos e imprimirla
    initTable();
    printTable();

    //iniciar analizador sintactico
    analizar();

    //volver a imprimir la tabla de simbolos
    printTable();

    //liberar memoria correspondiente a la tabla de simbolos y al sistema de entrada
    destroyTable();
    endSystem();
}