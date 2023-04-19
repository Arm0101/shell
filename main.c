#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>


#include "list.h"
#include "parser.h"


int main(){  
    char * line = NULL;
    size_t len;
    ssize_t nread;

    // char * ca = "hola mundo como estan";
    // char* l = strdup(ca);
    // char* t1 = strtok(l," ");
    // puts(t1);
    // puts(l);
    // return 0;
    while (1)
    {
        printf("my-prompt$ ");
        nread = getline(&line,&len,stdin);
        if (nread == 1 && !strcmp(line, "\n")) continue;
        if (nread == -1) return -1;
        
                                                                                                                                                                                                                                                                                                                                                                                                                        
        char * l = strchr(line,'\n');
        *l = '\0';

        parse_command(line);
        
        

    }
}