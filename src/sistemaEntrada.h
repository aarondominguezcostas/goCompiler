#ifndef LECTOR_H
#define LECTOR_H
#include "definiciones.h"

//Libreria del sistema de entrada del compilador

/**
 *  Funcion encargada de inicializar el sistema de entrada
 *  @param inputFile nombre del fichero a analizar
 */
void initSystem(char* inputFile);

/**
 *  Funcion encargada de leer un caracter del buffer del archivo
 *  @return caracter leido
 */
char readChar();

/**
 *  Funcion encargada de liberar la memoria en el sistema de entrada
 */
void endSystem();

/**
 * Esta funcion se encarga de leer el buffer y guardar el lexema reconocido en el identificador de la estructura
 * @param lexema estructura en la que se va a guardar el lexema
 */
void getWord(tipoelem *lexema);

/**
 * Funcion que permite devolver un caracter al sistema de entrada
 */
void devolver();

/**
 * Funcion que permite al sistema de entrada saltar un caracter
 */
void avanzar();

/**
 * Funcion utilizada para saltar todo el contenido de un comentario
 */
void readComment();

#endif