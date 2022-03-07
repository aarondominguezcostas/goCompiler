#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tablasimbolos.h"
#include "lector.h"

int main(){

    //inicializar la tabla de simbolos
    init();
    openFile("src/concurrentSum.go");

    char *string = malloc(sizeof(char) * 100);

    //bucle que lee el archivo de entrada hasta el final
    while(!isEnd()){
        readString(string);
        printf("%s\n", string);
    }

    /*testing tabla de simbolos
    insert("hola", 1);
    printTable();
    */

    //se destruye la tabla de simbolos
    destroy();
    closeFile();
}