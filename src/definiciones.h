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
#define FLOAT32 308

#define L 30

#define INTEGER 310
#define ID 310


//exponer menos codigo aqui
typedef struct{
    char *identificador;
    int valor;
} tipoelem;

#endif