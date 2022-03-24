#ifndef LEX_H
#define LEX_H
#include "definiciones.h"

/**
 * Funcion que recibe una struct y devuelve el valor del siguiente componente lexico
 *
 *  @param actual struct que contiene el componente lexico
 */
void nextComponent(tipoelem *actual);

#endif