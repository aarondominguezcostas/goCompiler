#include <stdio.h>
#include <stdlib.h>
#include <string.h>


FILE *file;

void openFile(char *fileName){
    file = fopen(fileName, "r");
    if(file == NULL){
        printf("Error: No se pudo abrir el archivo.\n");
        exit(1);
    }
}

// TODO > arreglar problema con parentesis y otros separadores
void readString(char *string){
    fscanf(file, "%s", string);
}

void closeFile(){
    fclose(file);
}

int isEnd(){
    return feof(file);
}