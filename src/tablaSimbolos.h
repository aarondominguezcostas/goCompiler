#ifndef TABLA_H
#define TABLA_H

#include "definiciones.h"

/**
 * Funcion que inicializa la tabla de simbolos
 */
void initTable();

/**
 * Funcion que libera la memoria la tabla de simbolos
 */
void destroyTable();

/**
 * Funcion que imprime la tabla de simbolos
 */
void printTable();

/**
 * Funcion que busca un elemento en la tabla de simbolos
 * Si este existe, devuelve un struct con su valor 
 * Si no existe, se inserta en la tabla de simbolos y se devuelve un struct con su valor
 * @param elem elemento a buscar
 */
void findElement(tipoelem *element);
#endif