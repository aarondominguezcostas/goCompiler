#ifndef DEF_H
#define DEF_H

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

typedef struct  {
    char *identificador;
    int valor;
}tipoelem;

#endif