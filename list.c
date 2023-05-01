#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

char** list_add(char** list,const char* element, size_t* size){

    
    char ** aux = calloc(((*size)+1), sizeof(char*));
    if (aux == NULL){
        fprintf(stderr, "Error al agregar el elemento a la lista");
        return (char**) NULL;
    }
    for (size_t i = 0; i < *size; i++)
    {
        aux[i] = strdup(list[i]);   
    }
    if (element == NULL){
        aux[(*size)] = NULL;
        (*size)++;
    }else{
        aux[(*size)] = strdup(element); 
        (*size)++;
    }
    free(list);
    return aux;
}

char** list_remove(char** list, int pos, size_t* size){
    char ** aux = calloc(((*size)-1), sizeof(char*));
    if (aux == NULL){
        fprintf(stderr, "Error al remover el elemento a la lista");
        return list;
    }
    int index = 0;
     for (size_t i = 0; i < *size; i++)
     {
         if (i == pos) continue;
         aux[index++] = strdup(list[i]);   
     }
     if (pos >= 0 && pos < *size){
         (*size)--;
     }
    return aux; 
}
void print_list(char** l, size_t size){
    for (size_t i = 0; i < size; i++)
    {   if (l[i] == NULL) {
            printf("NULL\n");
            continue;
        }
        printf("%s\n", l[i]);
    }
    
}


pid_t stack_push(StackP* stack, pid_t pid, char * p_name){
    char* name = strdup(p_name);
    size_t size = stack->size;
    
    stack->p_name = list_add(stack->p_name,name,&size);
    int *pids = malloc(sizeof(int) * (size));
    if (pids == NULL) return -1;
    for (size_t i = 0; i < size - 1; i++)
    {
        pids[i] = stack->pids[i];
    }
    pids[size-1] = pid;
    stack->pids = malloc(sizeof(int) * size);
    if (stack->pids == NULL) return -1;
    for (size_t i = 0; i < size; i++)
    {
        stack->pids[i] = pids[i];
    }
    stack->size = size;
    free(pids);
    free(name);
    return pid;
    
}
pid_t stack_remove(StackP* stack, pid_t pid){
 
    size_t size = stack->size;

    int pos = -1;
    if (pid == -1) {
        pid = stack->pids[size-1];
        pos = size-1;
    }
    else{
        for (size_t i = 0; i < stack->size; i++)
        {
            if (stack->pids[i] == pid){
                pos = i;
            }
        }
    }
    if (pos == -1){
        return -1;
    }
    char**aux  = list_remove(stack->p_name,pos,&size);
    stack->p_name = realloc(stack->p_name, size*sizeof(char*));
    stack->p_name = aux;
    int *pids = malloc(sizeof(int) * (size));
    if (pids == NULL) return -1;
    for (size_t i = 0; i < size; i++)
    {
        pids[i] = stack->pids[i];
    }
    stack->pids = malloc(sizeof(int) * size);
    if (stack->pids == NULL) return -1;
    for (size_t i = 0; i < size; i++)
    {
        stack->pids[i] = pids[i];
    }
    stack->size = size;
    free(pids);
    return pid;

}
