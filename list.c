#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

char** list_add(char** list,const char* element, size_t* size){
    char ** aux = realloc(list, ((*size)+1) * sizeof(char*));
    if (aux == NULL){
        fprintf(stderr, "Error al agregar el elemento a la lista");
        exit(EXIT_FAILURE);
    }
    aux[(*size)++] = strdup(element); 
    return aux;
}

void print_list(char** l, size_t size){
    for (size_t i = 0; i < size; i++)
    {
        printf("%s\n", l[i]);
    }
    
}
