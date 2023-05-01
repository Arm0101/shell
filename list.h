#include <sys/types.h>

#ifndef _LIST_H
#define _LIST_H
    typedef struct
    {
        pid_t* pids;
        char** p_name; 
        size_t size;   
    }StackP;

    char** list_add(char**, const char*,size_t *);
    char** list_remove(char**, int, size_t*);
    void print_list(char**, size_t);
    pid_t stack_push(StackP*, pid_t, char*);
    pid_t stack_remove(StackP*,pid_t);
#endif