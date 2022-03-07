#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//definir tama;o de bloques


//TODO - Imlementar doble buffer 
// leer bloque  a bloque
void initSystem(){
    
}

// TODO > comprobar que se lee caracter a caracter
// cambiar a leer de los dos buffers
void readChar(char siguiente){
    fscanf(file, "%c", siguiente);
}

// se finaliza el sistema
void endSystem(){
    fclose(file);
}

//cargar nuevo bloque de caracteres

//gestionar errores
