#ifndef DEF_H
#define DEF_H

/**
 * Definiciones de los valores de los componentes lexicos 
 */

#define PACKAGE 300
#define IMPORT 301
#define FUNC 302
#define CHAN 303
#define VAR 304
#define FOR 305
#define RANGE 306
#define GO 307
#define INTEGER 450
#define FLOAT 451
#define IMAGINARY 452
#define STRING 453
#define OPERATOR 454
#define ID 550

#define EOFVALUE -100


// Estructura que contiene los lexemas y componentes lexicos
typedef struct  {
    char *identificador;
    int valor;
}tipoelem;

#endif