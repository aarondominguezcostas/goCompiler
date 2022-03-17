#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tablaSimbolos.h"
#include "analizadorSintactico.h"
#include "sistemaEntrada.h"


int main(){


    //iniciar sistema de entrada
    initSystem("concurrentSum.go");

    //iniciar tabla de simbolos
    initTable();
    printTable();

    analizar();

    printTable();
    destroyTable();
    endSystem();
}