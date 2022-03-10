#ifndef LECTOR_H
#define LECTOR_H

//Libreria del sistema de entrada del compilador

// inicializa sistema de entrada
void initSystem(char* inputFile);

// Devuelve un caracter
char readChar();

// cierra el archivo
void endSystem();

#endif