#ifndef TABLA_H
#define TABLA_H

#include "definiciones.h"

//funcion para crear la tabla de simbolos
void initTable();

//funcion para eliminar la tabla de simbolos
void destroyTable();

//funcion para insertar un elemento en la tabla de simbolos
void insertElement(char* id, int valor);

//funcion para imprimir la tabla de simbolos
void printTable();


void findElement(tipoelem *element);
#endif