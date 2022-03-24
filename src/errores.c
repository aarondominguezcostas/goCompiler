
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void showError(int errorCode){
    switch(errorCode){
        case 1:
            printf("\nError: No se pudo abrir el archivo\n");
            exit(EXIT_FAILURE);
            break;
        case 2:
            printf("\nError: El tamaño del lexema es superior al limite\n");
            break;
        case 3:
            printf("\nError: No se puede cargar el bloque\n");
            break;
        case 4:
            printf("\nError: Ya ha aparecido una base\n");
            break;
        case 5:
            printf("\nError: \"_\" solo puede separar digitos sucesivos\n");
            break;
        case 6:
            printf("\nError: la mantissa necesita digitos\n");
            break;
        case 7:
            printf("\nError: no se puede usar E como exponente en hexadecimal\n");
            break;
        default:
            printf("\nError: No se pudo identificar el error\n");
            break;
    }
}