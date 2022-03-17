#ifndef LECTOR_H
#define LECTOR_H
#include "definiciones.h"
//Libreria del sistema de entrada del compilador

// inicializa sistema de entrada
void initSystem(char* inputFile);

// Devuelve un caracter
char readChar();

// cierra el archivo
void endSystem();

void getWord(tipoelem *lexema);

void devolver();

void avanzar();

#endif